namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class PRGData
    {
        public int Length { get; set; }
        public ushort Size1 { get; set; }
        public string Data1 { get; set; }
        public ushort TypesSize { get; set; }
        public IList<PRGType> Types { get; set; } = new List<PRGType>();
        public ushort Time { get; set; }
        public ushort IndexRemoteLocalList { get; set; }
        public bool IsEmpty => Size1 == 0;

        public static PRGData FromBytes(byte[] bytes)
        {
            var prgData = new PRGData();
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
                var type = new PRGType();
                type.Size = 1;
                var typeFromData = (TypesEnum)(bytes[index + j]);
                switch (typeFromData)
                {
                    case TypesEnum.FLOAT_TYPE:
                    case TypesEnum.LONG_TYPE:
                        type.Size = 4;
                        break;
                    case TypesEnum.INTEGER_TYPE:
                        type.Size = 2;
                        break;
                    default:
                    {
                        switch (typeFromData)
                        {
                            case TypesEnum.FLOAT_TYPE_ARRAY:
                            case TypesEnum.LONG_TYPE_ARRAY:
                                type.Size = 4;
                                break;
                            case TypesEnum.INTEGER_TYPE_ARRAY:
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