namespace PRGReaderLibrary
{
    using System;
    using System.Text;
    using System.Collections;
    using System.Collections.Generic;

    public static class StringExtensions
    {
        public static string PropertiesText<T>(this T obj, bool shortMode = false)
        {
            var type = obj.GetType();
            var properties = type.GetProperties();
            var builder = new StringBuilder();
            builder.AppendLine($"{type.Name} Data:");
            for (var i = 0; i < properties.Length; ++i)
            {
                var property = properties[i];

                builder.Append(shortMode ? "" : $"{property.Name}: ");
                var value = property.GetValue(obj);
                if (value != null)
                {
                    var valueType = value.GetType();
                    if (valueType.IsArray)
                    {
                        builder.Append(shortMode
                            ? $"Array({(value as Array).Length})"
                            : $"{value}. Length: {(value as Array).Length}");
                    }
                    else if (valueType.IsGenericType)
                    {
                        builder.Append(shortMode
                            ? $"Generic({(value as IList).Count})"
                            : $"{value}. Length: {(value as IList).Count}");
                    }
                    else
                    {
                        builder.Append($"{value}");
                    }
                }
                else
                {
                    builder.Append($"null");
                }

                builder.Append(shortMode && i != properties.Length - 1 ? ", " : Environment.NewLine);
            }

            return builder.ToString();
        }

        public static byte[] ToBytes(this string text, int length = 0)
        {
            if (text == null)
            {
                throw new ArgumentNullException(nameof(text));
            }

            length = length == 0 ? text.Length : length;
            var bytes = new byte[length];
            for (var i = 0; i < Math.Min(text.Length, length); ++i)
            {
                bytes[i] = i < text.Length ?
                    (byte)text[i] : (byte)0; //'\0'
            }

            return bytes;
        }

        public static string ClearBinarySymvols(this string text) =>
            text.TrimEnd('\0');

        public static string AddBinarySymvols(this string text, int length)
        {
            for (var i = text.Length; i < length; ++i)
            {
                text += '\0';
            }

            return text;
        }

        public static IList<string> ToLines(this string text, 
            StringSplitOptions options = StringSplitOptions.None) =>
            text.Split(new[] { "\r\n", "\r", "\n" }, options);
    }
}
