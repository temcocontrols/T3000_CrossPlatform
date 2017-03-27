namespace PRGReaderLibrary
{
    using System;

    public static class PrgUtilities
    {
        public static bool IsDosVersion(byte[] bytes) =>
            bytes.GetString(26, 4).Equals(Constants.Signature, StringComparison.Ordinal);
    }
}
