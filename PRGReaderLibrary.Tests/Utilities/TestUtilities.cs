namespace PRGReaderLibrary.Tests
{
    using System;
    using System.IO;
    using System.Reflection;

    public static class TestUtilities
    {
        public static string GetFullPathForTestFile(string filename) =>
            Path.Combine(
                Path.GetDirectoryName(
                    Path.GetDirectoryName(
                        Path.GetDirectoryName(
                            Assembly.GetExecutingAssembly().Location
                        )
                    )
                ),
                "TestFiles", filename);

        public static string GetTextPresentationForBytesArrays(byte[] bytes1, byte[] bytes2)
        {
            var text = string.Empty;
            for (var i = 0; i < Math.Min(bytes1.Length, bytes2.Length); ++i)
            {
                text += $"{i}:\t{bytes1[i]}\t{bytes2[i]}{Environment.NewLine}";
            }

            return text;
        }
    }
}
