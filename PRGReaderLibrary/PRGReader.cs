namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Text;

    public static class PRGReader
    {
        public static PRG Read(string path)
        {
            if (!File.Exists(path))
            {
                throw new ArgumentException($"File not exists: {path}", nameof(path));
            }

            using (var stream = File.OpenRead(path))
            {
                using (var reader = new BinaryReader(stream, Encoding.ASCII))
                {
                    var prg = new PRG();
                    prg.RawData = File.ReadAllBytes(path);
                    prg.DateTime = reader.ReadBytes(26).ConvertToString();
                    prg.Signature = reader.ReadBytes(4).ConvertToString();
                    if (!prg.Signature.Equals(Constants.Signature, StringComparison.Ordinal))
                    {
                        throw new Exception($"File corrupted. {prg.PropertiesText()}");
                    }

                    prg.PanelNumber = reader.ReadUInt16();
                    prg.NetworkNumber = reader.ReadUInt16();
                    prg.Version = reader.ReadUInt16();
                    prg.MiniVersion = reader.ReadUInt16();
                    prg.Reserved = reader.ReadBytes(32);

                    if (prg.Version < 210 || prg.Version == 0x2020)
                    {
                        throw new Exception($"File not loaded. File version less than 2.10. {prg.PropertiesText()}");
                    }

                    var l = MaxConstants.MAX_TBL_BANK;

                    prg.Length = stream.Length;
                    prg.Coef = ((prg.Length * 1000L) / 20000L) * 1000L +
                        (((prg.Length * 1000L) % 20000L) * 1000L) / 20000L;
                    //float coef = (float)length/20.;

                    var ltot = 0L;
                    var maxPrg = 0;
                    var maxGrp = 0;
                    
                    for (var i = BlocksEnum.OUT; i <= BlocksEnum.UNIT; ++i)
                    {
                        if (i == BlocksEnum.DMON)
                        {
                            continue;
                        }

                        if (i == BlocksEnum.AMON)
                        {
                            if (prg.Version < 230 && prg.MiniVersion >= 230)
                            {
                                throw new Exception($"Versions conflict! {prg.PropertiesText()}");
                            }
                            if (prg.Version >= 230 && prg.MiniVersion > 0)
                                continue;
                        }

                        if (i == BlocksEnum.ALARMM)
                        {
                            if (prg.Version < 216)
                            {
                                var size = reader.ReadUInt16();
                                var count = reader.ReadUInt16();
                                for (var j = 0; j < count; ++j)
                                {
                                    var data = reader.ReadBytes(size);
                                    prg.Infos.Add(data);
                                }
                                continue;
                            }
                        }
                        else
                        {
                            var count = reader.ReadUInt16();
                            var size = reader.ReadUInt16();
                            if (i == BlocksEnum.PRG)
                            {
                                maxPrg = count;
                            }
                            if (i == BlocksEnum.GRP)
                            {
                                maxGrp = count;
                            }
                            //if (count == info[i].str_size)
                            {
                                // fread(info[i].address, nitem, l, h);
                            }
                            for (var j = 0; j < count; ++j)
                            {
                                var bytes = reader.ReadBytes(size);
                                switch (i)
                                {
                                    case BlocksEnum.VAR:
                                        prg.Vars.Add(StrVariablePoint.FromBytes(bytes));
                                        break;

                                    default:
                                        prg.Infos.Add(bytes);
                                        break;
                                }
                            }
                            //Console.WriteLine(string.Join(Environment.NewLine,
                            //    prg.Alarms.Select(c=>new string(c)).Where(c => !string.IsNullOrWhiteSpace(c))));
                            ltot += size * count + 2;
                        }
                    }
                    
                    //var l = Math.Min(maxPrg, tbl_bank[PRG]);
                    for (var i = 0; i < maxPrg; ++i)
                    {
                        var size = reader.ReadUInt16();
                        var data = reader.ReadBytes(size);
                        ltot += size + 2;

                        //var prgData = PRGData.FromBytes(data);
                        //if (!prgData.IsEmpty)
                        {
                            //prg.PrgDatas.Add(prgData);
                        }
                    }

                    foreach (var data in prg.PrgDatas)
                    {
                        Console.WriteLine(data.PropertiesText());
                    }

                    {
                        var size = reader.ReadUInt16();
                        //prg.WrTimes = reader.ReadBytes(size);
                        for (var j = 0; j < size; j += SizeConstants.WR_ONE_DAY_SIZE * MaxConstants.MAX_WR)
                        {
                            var list = new List<WrOneDay>();
                            for (var k = 0; k < SizeConstants.WR_ONE_DAY_SIZE; ++k)
                            {
                                var data = reader.ReadBytes(MaxConstants.MAX_WR);
                                list.Add(WrOneDay.FromBytes(data));
                            }

                            prg.WrTimes.Add(list);
                        }
                    }

                    {
                        var size = reader.ReadUInt16();
                        for (var j = 0; j < size; j += SizeConstants.AR_DATES_SIZE)
                        {
                            var data = reader.ReadBytes(SizeConstants.AR_DATES_SIZE);
                            prg.ArDates.Add(data);
                        }
                    }

                    {
                        var size = reader.ReadUInt16();
                    }

                    for (var i = 0; i < maxGrp; ++i)
                    {
                        var size = reader.ReadUInt16();
                        var data = reader.ReadBytes(size);
                        ltot += size + 2;

                        prg.GrpDatas.Add(data);
                    }

                    {
                        var size = reader.ReadUInt16();

                        for (var j = 0; j < MaxConstants.MAX_ICON_NAME_TABLE; ++j)
                        {
                            var bytes = reader.ReadBytes(SizeConstants.ICON_NAME_TABLE_SIZE);
                            prg.IconNameTable.Add(bytes);
                        }
                    }

                    return prg;
                }
            }
        }
    }
}
