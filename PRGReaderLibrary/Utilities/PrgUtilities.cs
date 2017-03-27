namespace PRGReaderLibrary
{
    using System;

    public static class PrgUtilities
    {
        public static bool IsDosVersion(byte[] bytes) =>
            bytes.GetString(26, 4).Equals(Constants.Signature, StringComparison.Ordinal);

        public static bool IsCurrentVersion(byte[] bytes) =>
            bytes.ToByte(0) == 0x55 &&
            bytes.ToByte(1) == 0xff &&
            true; //bytes.ToByte(2) == 0x06; it is version
    }
}
