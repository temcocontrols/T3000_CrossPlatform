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
        /// <param name="parent">parent class for messages</param>
        /// <!--Modified by LRUIZ 2018-06-05-->
        /// <returns></returns>
        public static Prg Read(string path, Object parent)
        {
            if (!File.Exists(path))
            {
                throw new ArgumentException($"File not exists: {path}", nameof(path));
            }

            return new Prg(File.ReadAllBytes(path),parent);
        }
    }
}
