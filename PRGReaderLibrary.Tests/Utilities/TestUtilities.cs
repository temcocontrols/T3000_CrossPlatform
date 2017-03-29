namespace PRGReaderLibrary.Tests
{
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
    }
}
