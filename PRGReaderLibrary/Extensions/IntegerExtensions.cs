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
    }
}
