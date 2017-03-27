namespace PRGReaderLibrary
{
    using System;
    using System.Text;

    public static class BytesExtensions
    {
        public static string GetString(this byte[] bytes, int offset = 0, int length = 0) =>
            Encoding.ASCII.GetString(bytes, offset, length == 0 ? bytes.Length : length);

        public static bool ToBoolean(this byte[] bytes, int offset = 0) =>
            BitConverter.ToBoolean(bytes, offset);

        public static ushort ToUInt16(this byte[] bytes, int offset = 0) =>
            BitConverter.ToUInt16(bytes, offset);

        public static uint ToUInt32(this byte[] bytes, int offset = 0) =>
            BitConverter.ToUInt32(bytes, offset);

        public static ulong ToUInt64(this byte[] bytes, int offset = 0) =>
            BitConverter.ToUInt32(bytes, offset);

        public static short ToInt16(this byte[] bytes, int offset = 0) =>
            BitConverter.ToInt16(bytes, offset);

        public static int ToInt32(this byte[] bytes, int offset = 0) =>
            BitConverter.ToInt32(bytes, offset);

        public static long ToInt64(this byte[] bytes, int offset = 0) =>
            BitConverter.ToInt32(bytes, offset);

        public static double ToDouble(this byte[] bytes, int offset = 0) =>
            BitConverter.ToDouble(bytes, offset);

        public static float ToFloat(this byte[] bytes, int offset = 0) =>
            BitConverter.ToSingle(bytes, offset);

        //Marasmus
        public static byte ToByte(this byte[] bytes, int offset = 0) => bytes[offset];

        public static byte[] ToBytes(this byte[] bytes, int offset = 0, int length = 0)
        {
            if (offset < 0 || offset >= bytes.Length)
            {
                throw new ArgumentOutOfRangeException(nameof(offset), 
                    $@"Offset can be from 0 to bytes.Length - 1.
Offset: {offset}, bytes.Length: {bytes.Length}");
            }
            if (length < 0 || length > bytes.Length - offset)
            {
                throw new ArgumentOutOfRangeException(nameof(length), 
                    $@"Length can be from 0 to (bytes.Length - offset)({bytes.Length - offset}).
Offset: {offset}, Length: {length}, bytes.Length: {bytes.Length}");
            }

            if (offset == 0 && length == 0)
            {
                return bytes;
            }

            length = length == 0 ? bytes.Length : length;

            //Constrains with offset
            length = Math.Min(length, bytes.Length - offset);

            var newBytes = new byte[length];
            Array.ConstrainedCopy(bytes, offset, newBytes, 0, length);

            return newBytes;
        }

        public static bool GetBit(this byte[] bytes, uint bit, int offset = 0) =>
            bytes[offset].GetBit(bit);
    }
}
