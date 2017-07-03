namespace PRGReaderLibrary
{
    using System;
    using System.IO;

    public static class PrgWriter
    {
        public static void Write(Prg prg, string path)
        {
            if (prg == null)
            {
                throw new ArgumentNullException(nameof(prg));
            }
            if (path == null)
            {
                throw new ArgumentNullException(nameof(path));
            }

            File.WriteAllBytes(path, prg.ToBytes());
        }
    }
}
