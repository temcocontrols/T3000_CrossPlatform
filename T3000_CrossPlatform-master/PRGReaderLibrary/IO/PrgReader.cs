namespace PRGReaderLibrary
{
    using System;
    using System.IO;

    public static class PrgReader
    {
        /// <summary>
        /// Read file from disk
        /// </summary>
        /// <param name="path">Path to .prg file</param>
        /// <returns></returns>
        public static Prg Read(string path)
        {
            if (!File.Exists(path))
            {
                throw new ArgumentException($"File not exists: {path}", nameof(path));
            }

            return new Prg(File.ReadAllBytes(path));
        }
    }
}
