namespace PRGReaderLibrary
{
    using System;

    public static class IntegerExtensions
    {
        public static byte[] ToBytes(this int integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this uint integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this short integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this ushort integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this long integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this ulong integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this float integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this double integer) => BitConverter.GetBytes(integer);
        public static byte[] ToBytes(this bool integer) => BitConverter.GetBytes(integer);

        public static byte[] ToBytes(this byte[] bytes, int offset = 0, int length = 0)
        {
            if (offset == 0 && length == 0)
            {
                return bytes;
            }

            length = length == 0 ? 
                bytes.Length - offset : 
                Math.Min(bytes.Length - offset, length);
            var newBytes = new byte[length];
            Array.ConstrainedCopy(bytes, offset, newBytes, 0, length);

            return newBytes;
        }
    }
}
