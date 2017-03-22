namespace PRGReaderLibrary
{
    using System;
    using System.IO;

    public static class PRGReader
    {
        public static PRG Read(string path)
        {
            if (!File.Exists(path))
            {
                throw new ArgumentException($"File not exists: {path}", nameof(path));
            }

            return PRG.FromBytes(File.ReadAllBytes(path));
        }
    }
}
