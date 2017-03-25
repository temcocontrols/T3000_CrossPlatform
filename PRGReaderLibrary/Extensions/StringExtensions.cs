namespace PRGReaderLibrary
{
    using System;
    using System.Text;
    using System.Collections;

    public static class StringExtensions
    {
        public static string PropertiesText<T>(this T obj)
        {
            var type = obj.GetType();
            var builder = new StringBuilder();
            builder.AppendLine($"{type.Name} Data:");
            foreach (var property in type.GetProperties())
            {
                builder.Append($"{property.Name}: ");
                var value = property.GetValue(obj);
                if (value == null)
                {
                    builder.AppendLine($"null");
                    continue;
                }

                var valueType = value.GetType();
                if (valueType.IsArray)
                {
                    builder.AppendLine($"{value}. Length: {(value as Array).Length}");
                }
                else if (valueType.IsGenericType)
                {
                    builder.AppendLine($"{value}. Length: {(value as IList).Count}");
                }
                else
                {
                    builder.AppendLine($"{value}");
                }
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
            text.Normalize();

        public static string AddBinarySymvols(this string text, int length)
        {
            for (var i = text.Length; i < length; ++i)
            {
                text += '\0';
            }

            return text;
        }
    }
}
