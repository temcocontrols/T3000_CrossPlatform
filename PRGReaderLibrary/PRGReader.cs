namespace PRGReaderLibrary
{
    using System;
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
                    prg.DateTime = new string(reader.ReadChars(26));
                    prg.Signature = new string(reader.ReadChars(4));
                    if (!prg.Signature.Equals(Constants.Signature, StringComparison.Ordinal))
                    {
                        throw new Exception($"File corrupted. {prg.ToString()}");
                    }

                    prg.PanelNumber = reader.ReadUInt16();
                    prg.NetworkNumber = reader.ReadUInt16();
                    prg.Version = reader.ReadUInt16();
                    prg.MiniVersion = reader.ReadUInt16();
                    reader.ReadBytes(32); // reserved bytes

                    if (prg.Version < 210 || prg.Version == 0x2020)
                    {
                        throw new Exception($"File not loaded. File version less than 2.10. {prg.ToString()}");
                    }

                    prg.Lenght = stream.Length;
                    prg.Coef = ((prg.Lenght * 1000L) / 20000L) * 1000L +
                        (((prg.Lenght * 1000L) % 20000L) * 1000L) / 20000L;
                    //float coef = (float)length/20.;

                    var ltot = 0L;
                    var maxPrg = 0;
                    var maxGrp = 0;

                    for (var i = Constants.OUT; i <= Constants.UNIT; ++i)
                    {
                        if (i == Constants.DMON)
                        {
                            continue;
                        }

                        if (i == Constants.AMON)
                        {
                            if (prg.Version < 230 && prg.MiniVersion >= 230)
                            {
                                throw new Exception($"Versions conflict! {prg.ToString()}");
                            }
                            if (prg.Version >= 230 && prg.MiniVersion > 0)
                                continue;
                        }

                        if (i == Constants.ALARMM)
                        {
                            if (prg.Version < 216)
                            {
                                var size = reader.ReadUInt16();
                                var count = reader.ReadUInt16();
                                for (var j = 0; j < count; ++j)
                                {
                                    var data = reader.ReadChars(size);
                                    prg.Infos.Add(data);
                                }
                                continue;
                            }
                        }
                        else
                        {
                            var size = reader.ReadUInt16();
                            var count = reader.ReadUInt16();
                            if (i == Constants.PRG)
                            {
                                maxPrg = size;
                            }
                            if (i == Constants.GRP)
                            {
                                maxGrp = size;
                            }
                            //if (count == info[i].str_size)
                            {
                                // fread(info[i].address, nitem, l, h);
                            }
                            for (var j = 0; j < count; ++j)
                            {
                                var data = reader.ReadChars(size);
                                prg.Infos.Add(data);
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

                        var prgData = PRGData.FromBytes(data);
                        if (!prgData.IsEmpty)
                        {
                            prg.PrgDatas.Add(prgData);
                        }
                    }

                    foreach (var data in prg.PrgDatas)
                    {
                        Console.WriteLine(data.ToString());
                    }

                    {
                        var size = reader.ReadUInt16();
                        prg.WrTimes = reader.ReadBytes(size);
                    }

                    {
                        var size = reader.ReadUInt16();
                        prg.ArDates = reader.ReadBytes(size);
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
                        prg.IconNameTable = reader.ReadBytes(size);
                    }

                    return prg;
                }
            }
        }
    }
}
