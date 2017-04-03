namespace PRGReaderLibrary
{
    using System;

    public static class DebugUtilities
    {
        /// <summary>
        /// Debug binary objects. Example:
        /// Console.WriteLine(DebugUtilities.CompareBytes(bytes, ToBytes()));
        /// in constructor after switch
        /// </summary>
        /// <param name="bytes1"></param>
        /// <param name="bytes2"></param>
        /// <returns></returns>
        public static string CompareBytes(byte[] bytes1, byte[] bytes2)
        {
            var text = string.Empty;
            for (var i = 0; i < Math.Min(bytes1.Length, bytes2.Length); ++i)
            {
                text += $"{i}:\t{bytes1[i]}\t{bytes2[i]}{Environment.NewLine}";
            }

            return text;
        }
    }
}
