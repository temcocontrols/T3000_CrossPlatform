namespace T3000
{
    using System;

    public static class EnumUtilities
    {
        /// <summary>
        /// Returns next value of enum
        /// </summary>
        /// <typeparam name="T">Type of enum</typeparam>
        /// <param name="value"></param>
        /// <returns></returns>
        public static T NextValue<T>(T value) where T : struct, IConvertible
        {
            if (!typeof(T).IsEnum)
            {
                throw new ArgumentException("T must be an enumerated type");
            }

            var values = Enum.GetValues(value.GetType());
            var currentIndex = (int)(object)value;

            return currentIndex == values.Length - 1 ? (T)(object)0 : (T)(object)(currentIndex + 1);
        }
    }
}
