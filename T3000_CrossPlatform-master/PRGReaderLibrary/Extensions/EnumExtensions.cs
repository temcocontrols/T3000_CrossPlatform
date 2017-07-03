namespace PRGReaderLibrary
{
    using System;
    using System.Linq;

    public static class EnumExtensions
    {
        public static T GetAttribute<T>(this Enum value) where T : Attribute
        {
            var info = value.GetType().GetMember(value.ToString())
                                            .FirstOrDefault();

            return (T)info?.GetCustomAttributes(typeof(T), false)?.FirstOrDefault();
        }

        /*
        public static string GetName(this Enum value)
        {
            return value.GetAttribute<NameAttribute>()?.Name ?? value.ToString();
        }*/

        public static string GetName<T>(this T value) where T : struct, IConvertible
        {
            if (!typeof(T).IsEnum)
            {
                throw new ArgumentException("T must be an enumerated type");
            }
            
            return ((Enum)(object)value).GetAttribute<NameAttribute>()?.Name ?? value.ToString();
        }
    }
}
