namespace T3000
{
    using System;
    using System.Linq;

    public static class EnumExtensions
    {
        /// <summary>
        /// Returns next value of enum
        /// </summary>
        /// <typeparam name="T">Type of enum</typeparam>
        /// <param name="value"></param>
        /// <returns></returns>
        public static T NextValue<T>(this T value) where T : struct, IConvertible
        {
            if (!typeof(T).IsEnum)
            {
                throw new ArgumentException("T must be an enumerated type");
            }

            var values = Enum.GetValues(typeof(T)).Cast<T>();
            if ((int)(object)value == (int)(object)values.Last())
            {
                return values.First();
            }

            return values.First(i => (int)(object)i > (int)(object)value);
        }

        /// <summary>
        /// Returns prev value of enum
        /// </summary>
        /// <typeparam name="T">Type of enum</typeparam>
        /// <param name="value"></param>
        /// <returns></returns>
        public static T PrevValue<T>(this T value) where T : struct, IConvertible
        {
            if (!typeof(T).IsEnum)
            {
                throw new ArgumentException("T must be an enumerated type");
            }

            var values = Enum.GetValues(typeof(T)).Cast<T>();
            if ((int)(object)value == (int)(object)values.First())
            {
                return values.Last();
            }

            return values.Last(i => (int)(object)i < (int)(object)value);
        }

    }
}
