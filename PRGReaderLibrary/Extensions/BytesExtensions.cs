namespace PRGReaderLibrary
{
    using System;
    using System.Text;

    public static class BytesExtensions
    {
        public static string ConvertToString(this byte[] bytes, int offset = 0, int length = 0) =>
            Encoding.ASCII.GetString(bytes, offset, 
                length == 0 ? bytes.Length : length).Trim('\0');

        public static bool ConvertToBoolean(this byte[] bytes, int offset = 0) =>
            BitConverter.ToBoolean(bytes, offset);
    }
}
