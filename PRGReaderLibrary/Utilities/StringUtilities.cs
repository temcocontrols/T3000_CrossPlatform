namespace PRGReaderLibrary
{
    using System;
    using System.Text;
    using System.Collections;

    public static class StringUtilities
    {
        public static string ObjectToString<T>(T obj)
        {
            var type = obj.GetType();
            var builder = new StringBuilder();
            builder.AppendLine($"{type.Name} Data:");
            foreach (var property in type.GetProperties())
            {
                builder.Append($"{property.Name}: ");
                var value = property.GetValue(obj);
                var valueType = value.GetType();
                if (valueType.IsArray)
                {
                    builder.AppendLine($"{value}. Lenght: {(value as Array).Length}");
                }
                else if (valueType.IsGenericType)
                {
                    builder.AppendLine($"{value}. Lenght: {(value as IList).Count}");
                }
                else
                {
                    builder.AppendLine($"{value}");
                }
            }

            return builder.ToString();
        }
    }
}
