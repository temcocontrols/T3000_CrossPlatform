namespace PRGReaderLibrary
{
    public enum Sign
    {
        Positive,
        Negative
    }

    public static class SignExtensions
    {
        public static string GetString(this Sign sign)
        {
            return sign == Sign.Positive ? "+" : "-";
        }
    }
}
