namespace PRGReaderLibrary
{
    using System;

    public class PRGData
    {
        public int TypeSize { get; set; }
        public int Lenght { get; set; }
        public int Size1 { get; set; }
        public string Data1 { get; set; }
        public int Size2 { get; set; }
        public bool IsEmpty => Size1 == 0;

        public static PRGData FromBytes(byte[] data)
        {
            var prgData = new PRGData();
            if (data == null || data.Length == 0)
            {
                return prgData;
            }

            var lenght = data.Length;
            prgData.Lenght = lenght;

            var index = 0;
            if (index >= lenght)
            {
                return prgData;
            }

            var size1 = BitConverter.ToUInt16(data, index);
            prgData.Size1 = size1;
            index += 2;

            //var data1 = BitConverter(data, index);

            index += size1 + 3;

            if (index >= lenght)
            {
                return prgData;
            }
            var size2 = BitConverter.ToUInt16(data, index);
            prgData.Size2 = size2;
            return prgData;
            index += 2;
            for (var j = 0; j < size2;)
            {
                prgData.TypeSize = 1;
                switch (data[index + j])
                {
                    case TypesConstants.FLOAT_TYPE:
                    case TypesConstants.LONG_TYPE:
                        prgData.TypeSize = 4;
                        break;
                    case TypesConstants.INTEGER_TYPE:
                        prgData.TypeSize = 2;
                        break;
                    default:
                    {
                        switch (data[j])
                        {
                            case TypesConstants.FLOAT_TYPE_ARRAY:
                            case TypesConstants.LONG_TYPE_ARRAY:
                                prgData.TypeSize = 4;
                                break;
                            case TypesConstants.INTEGER_TYPE_ARRAY:
                                prgData.TypeSize = 2;
                                break;
                        }
                        var l1 = data[j + 1] * 256 + data[j + 2];
                        var c1 = data[j + 3] * 256 + data[j + 4];
                        //prgData.TypeSize *= c1 * Math.Max(l1, 1);
                        j += 4;
                    }
                        break;
                }

                j++;
                //memset(&q[j], 0, typeSize);
                j += prgData.TypeSize;
                //j += 1 + strlen(&q[j]);
            }

            //size = reader.ReadUInt16();//time
            //reader.ReadBytes(size);
            //size = reader.ReadUInt16();//ind_remote_local_list

            return prgData;
        }

        public override string ToString() => StringUtilities.ObjectToString(this);
    }
}