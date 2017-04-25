namespace PRGReaderLibrary.Tests
{
    using System.IO;
    using System.Reflection;

    public static class TestUtilities
    {
        private static string PathToTestFiles =>
            Path.Combine(
                Path.GetDirectoryName(
                    Path.GetDirectoryName(
                        Path.GetDirectoryName(
                            Assembly.GetExecutingAssembly().Location
                        )
                    )
                ), "TestFiles");

        public static string GetFullPathForPrgFile(string filename) =>
            Path.Combine(PathToTestFiles, "Prgs", filename);

        public static string GetFullPathForProgramCodeFile(string filename) =>
            Path.Combine(PathToTestFiles, "ProgramCodes", filename);
    }
}
