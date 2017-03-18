namespace PRGReaderLibrary
{
    using System.Text;

    public static class StringUtilities
    {
        public static string ObjectToString<T>(T obj)
        {
            var type = obj.GetType();
            var builder = new StringBuilder();
            builder.AppendLine($"{type.Name} Data:");
            foreach (var property in type.GetProperties())
            {
                builder.AppendLine($"{property.Name}: {property.GetValue(obj)}");
            }

            return builder.ToString();
        }
    }
}
