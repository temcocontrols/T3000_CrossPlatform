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
        public static byte ToBit(this bool boolean, int bit) =>
            boolean ? (byte)Math.Pow(2, bit) : (byte)0;
        public static byte ToByte(this bool boolean) =>
            boolean ? (byte)1 : (byte)0;

        public static byte ToBits(this bool[] booleans, int startBit = 0)
        {
            byte bits = 0;
            var bit = 0U;
            foreach (var boolean in booleans)
            {
                bits += boolean.ToBit(Convert.ToInt32(startBit + bit));
                ++bit;
            }

            return bits;
        }
    }
}
