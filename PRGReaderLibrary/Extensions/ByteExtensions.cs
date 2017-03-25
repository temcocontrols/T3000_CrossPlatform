namespace PRGReaderLibrary
{
    using System;

    public static class ByteExtensions
    {
        /// <summary>
        /// Returns Boolean values for bits from 0 to 7
        /// </summary>
        /// <param name="value"></param>
        /// <param name="bit">Can be from 0 to 7</param>
        /// <returns></returns>
        public static bool GetBit(this byte value, uint bit)
        {
            if (bit > 7)
            {
                throw new ArgumentException("The bit can be from 0 to 7", nameof(bit));
            }

            return (value / ((uint)Math.Pow(2, bit))) % 2 == 1;
        }
    }
}
