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
        public static string CompareBytes(byte[] bytes1, byte[] bytes2, int offset = 0, bool onlyDif = true)
        {
            var text = string.Empty;
            for (var i = offset; i < Math.Min(bytes1.Length, bytes2.Length); ++i)
            {
                if (onlyDif && bytes1[i] == bytes2[i])
                {
                    continue;
                }

                text += $"{i}:\t{bytes1[i]}\t{bytes2[i]}{Environment.NewLine}";
            }

            return text;
        }
    }
}
