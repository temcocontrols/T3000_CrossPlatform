namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class PrgData
    {
        public int Length { get; set; }
        public ushort Size1 { get; set; }
        public string Data1 { get; set; }
        public ushort TypesSize { get; set; }
        public IList<PrgType> Types { get; set; } = new List<PrgType>();
        public ushort Time { get; set; }
        public ushort IndexRemoteLocalList { get; set; }
        public bool IsEmpty => Size1 == 0;

        public static PrgData FromBytes(byte[] bytes)
        {
            var prgData = new PrgData();
            if (bytes == null || bytes.Length == 0)
            {
                return prgData;
            }

            var length = bytes.Length;
            prgData.Length = length;

            var index = 0;
            if (index >= length)
            {
                return prgData;
            }

            var size1 = bytes.ToUInt16(index);
            prgData.Size1 = size1;
            index += 2;

            prgData.Data1 = bytes.GetString(index, size1);
            index += size1;

            index += 3; //TODO: what is it? reserved?

            var typesSize = bytes.ToUInt16(index);
            prgData.TypesSize = typesSize;
            index += 2;

            for (var j = 0; j < typesSize;)
            {
                var type = new PrgType();
                type.Size = 1;
                var typeFromData = (Types)(bytes[index + j]);
                switch (typeFromData)
                {
                    case PRGReaderLibrary.Types.FLOAT_TYPE:
                    case PRGReaderLibrary.Types.LONG_TYPE:
                        type.Size = 4;
                        break;
                    case PRGReaderLibrary.Types.INTEGER_TYPE:
                        type.Size = 2;
                        break;
                    default:
                    {
                        switch (typeFromData)
                        {
                            case PRGReaderLibrary.Types.FLOAT_TYPE_ARRAY:
                            case PRGReaderLibrary.Types.LONG_TYPE_ARRAY:
                                type.Size = 4;
                                break;
                            case PRGReaderLibrary.Types.INTEGER_TYPE_ARRAY:
                                type.Size = 2;
                                break;
                        }
                        var l1 = bytes.ToUInt16(index + j + 1);
                        var c1 = bytes.ToUInt16(index + j + 3);
                        type.Size *= c1 * Math.Max(l1, (ushort)1);
                        j += 4;
                    }
                    break;
                }
                ++j;

                type.Data = new byte[type.Size];
                Array.ConstrainedCopy(bytes, index + j, type.Data, 0, type.Size);
                j += type.Size;

                var start = j;
                for (; bytes[index + j] != 0; ++j);
                type.Name = bytes.GetString(index + start, j - start);
                ++j;

                prgData.Types.Add(type);
            }
            index += typesSize;

            prgData.Time = bytes.ToUInt16(index);
            index += 2;

            prgData.IndexRemoteLocalList = bytes.ToUInt16(index);
            index += 2;

            if (index != length)
            {
                //throw new Exception($"Last index not equals length. Error in data: {prgData.PropertiesText()}");
            }
            foreach (var type in prgData.Types)
            {
                Console.WriteLine(type.PropertiesText());
            }

            return prgData;
        }
    }
}