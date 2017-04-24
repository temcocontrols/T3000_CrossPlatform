namespace PRGReaderLibrary
{
    using System;

    public static class DebugUtilities
    {
        private static bool isText(char value) =>
            char.IsLetterOrDigit(value) ||
            char.IsWhiteSpace(value) ||
            char.IsPunctuation(value);

        private static bool isText(byte value) => isText((char)value);

        private static bool IsTextByte(byte[] bytes, int index)
        {
            var isLetter = isText(bytes[index]);
            var prevIsLetter = index > 0 
                ? isText(bytes[index - 1]) 
                : true;
            var nextIsLetter = index < bytes.Length - 1 
                ? isText(bytes[index + 1]) 
                : true;

            return isLetter && (nextIsLetter || prevIsLetter);
        }

        /// <summary>
        /// Debug binary objects. Example:
        /// Console.WriteLine(DebugUtilities.CompareBytes(bytes, ToBytes()));
        /// in constructor after switch
        /// </summary>
        /// <param name="bytes1"></param>
        /// <param name="bytes2"></param>
        /// <returns></returns>
        public static string CompareBytes(byte[] bytes1, byte[] bytes2, int offset = 0,
             int length = 0,
             bool onlyDif = true, 
             bool toText = true,
             bool textAsLine = false)
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

                var isTextByte1 = toText && IsTextByte(bytes1, i);
                var isTextByte2 = toText && IsTextByte(bytes2, i);

                if (textAsLine)
                {
                    var j = i;
                    for (; isTextByte1 && isTextByte2 && j < length; ++j)
                    {
                        isTextByte1 = toText && IsTextByte(bytes1, j);
                        isTextByte2 = toText && IsTextByte(bytes2, j);
                    }
                    j -= 2;
                    if (j > i)
                    {
                        text += $"{i} - {j}:\t" +
                                $"{bytes1.GetString(i, j - i)}\t" +
                                $"{bytes2.GetString(i, j - i)}\t" +
                                $"{(isEquals && !onlyDif ? "" : "<---")}" +
                                $"{Environment.NewLine}";
                        i = j;
                        continue;
                    }
                }

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
