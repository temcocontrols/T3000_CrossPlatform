namespace PRGReaderLibrary
{
    using System;

    public static class FileVersionUtilities
    {
        public const string DosSignature = "!@#$";
        public const string Rev6Signature = "Uÿ"; //0x55 0xff
        public const int CurrentFileRevision = 6;

        public static bool IsDosVersion(byte[] bytes) =>
            bytes.GetString(26, 4).Equals(DosSignature, StringComparison.Ordinal);

        public static bool IsCurrentVersion(byte[] bytes, int revision = CurrentFileRevision) =>
            bytes.ToByte(0) == 0x55 &&
            bytes.ToByte(1) == 0xff &&
            bytes.ToByte(2) == revision; //version

        public static FileVersion GetFileVersion(byte[] bytes)
        {
            if (IsCurrentVersion(bytes, CurrentFileRevision))
                return FileVersion.Current;

            if (IsDosVersion(bytes))
                return FileVersion.Dos;

            return FileVersion.Unsupported;
        }
    }
}
