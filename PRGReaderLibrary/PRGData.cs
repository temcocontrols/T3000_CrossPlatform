namespace PRGReaderLibrary
{
    using System;
    using System.Text;
    using System.Collections.Generic;

    public class PRGData
    {
        public int Lenght { get; set; }
        public ushort Size1 { get; set; }
        public string Data1 { get; set; }
        public ushort TypesSize { get; set; }
        public IList<PRGType> Types { get; set; } = new List<PRGType>();
        public ushort Time { get; set; }
        public ushort IndexRemoteLocalList { get; set; }
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

            prgData.Data1 = Encoding.Unicode.GetString(data, index, size1);
            index += size1;

            index += 3; //TODO: what is it? reserved?

            var typesSize = BitConverter.ToUInt16(data, index);
            prgData.TypesSize = typesSize;
            index += 2;

            for (var j = 0; j < typesSize;)
            {
                var type = new PRGType();
                type.Size = 1;
                switch (data[index + j])
                {
                    case TypesConstants.FLOAT_TYPE:
                    case TypesConstants.LONG_TYPE:
                        type.Size = 4;
                        break;
                    case TypesConstants.INTEGER_TYPE:
                        type.Size = 2;
                        break;
                    default:
                    {
                        switch (data[index + j])
                        {
                            case TypesConstants.FLOAT_TYPE_ARRAY:
                            case TypesConstants.LONG_TYPE_ARRAY:
                                type.Size = 4;
                                break;
                            case TypesConstants.INTEGER_TYPE_ARRAY:
                                type.Size = 2;
                                break;
                        }
                        var l1 = BitConverter.ToUInt16(data, index + j + 1);
                        var c1 = BitConverter.ToUInt16(data, index + j + 3);
                        type.Size *= c1 * Math.Max(l1, (ushort)1);
                        j += 4;
                    }
                    break;
                }
                ++j;

                type.Data = new byte[type.Size];
                Array.ConstrainedCopy(data, index + j, type.Data, 0, type.Size);
                j += type.Size;

                var start = j;
                for (; data[index + j] != 0; ++j);
                type.Name = Encoding.ASCII.GetString(data, index + start, j - start);
                ++j;

                prgData.Types.Add(type);
            }
            index += typesSize;

            prgData.Time = BitConverter.ToUInt16(data, index);
            index += 2;

            prgData.IndexRemoteLocalList = BitConverter.ToUInt16(data, index);
            index += 2;

            if (index != lenght)
            {
                throw new Exception($"Last index not equals length. Error in data: {prgData.ToString()}");
            }
            foreach (var type in prgData.Types)
            {
                Console.WriteLine(type.ToString());
            }

            return prgData;
        }

        public override string ToString() => StringUtilities.ObjectToString(this);
    }
}