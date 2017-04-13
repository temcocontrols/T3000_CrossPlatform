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
    }
}
