namespace PRGReaderLibrary.Tests
{
    using System;
    using System.IO;
    using System.Text;
    using System.Security.Cryptography;

    public static class FileUtilities
    {
        public static string GetFileHash(string path)
        {
            using (var md5 = MD5.Create())
            {
                using (var stream = File.OpenRead(path))
                {
                    return Encoding.Default.GetString(md5.ComputeHash(stream));
                }
            }
        }

        public static bool FilesIsEquals(string path1, string path2)
        {
            return string.Equals(GetFileHash(path1), GetFileHash(path2), StringComparison.Ordinal);
        }
    }
}
