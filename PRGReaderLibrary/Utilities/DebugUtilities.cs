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
        public static string CompareBytes(byte[] bytes1, byte[] bytes2, int offset = 0, bool onlyDif = true, int length = 0, bool toText = true)
        {
            var text = string.Empty;
            var maxLength = Math.Min(bytes1.Length, bytes2.Length);
            length = length == 0 ? maxLength : Math.Min(maxLength, offset + length);
            for (var i = offset; i < length; ++i)
            {
                var isEquals = bytes1[i] == bytes2[i];
                if (onlyDif && isEquals)
                {
                    continue;
                }

                var isTextByte1 = toText && char.IsLetter((char) bytes1[i]);
                var isTextByte2 = toText && char.IsLetter((char) bytes2[i]);
                text += $"{i}:\t" +
                        $"{(isTextByte1 ? (char)bytes1[i] : (object)bytes1[i])}\t" +
                        $"{(isTextByte2 ? (char)bytes2[i] : (object)bytes2[i])}\t" +
                        $"{(isEquals && !onlyDif ? "" : "<---")}" +
                        $"{Environment.NewLine}";
            }

            return text;
        }
    }
}
