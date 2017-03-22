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
            var bytes = new byte[length > 0 ? length : text.Length];
            for (var i = 0; i < Math.Min(text.Length, bytes.Length); ++i)
            {
                bytes[i] = (byte)text[i];
            }

            return bytes;
        }
    }
}
