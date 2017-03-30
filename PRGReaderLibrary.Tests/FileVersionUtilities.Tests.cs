namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.IO;

    [TestFixture]
    public class FileVersionUtilities_Tests
    {
        public byte[] GetBytesFromName(string name)
        {
            var path = TestUtilities.GetFullPathForTestFile(name);

            return File.ReadAllBytes(path);
        }

        public void IsDos(string name, bool expected) =>
            Assert.AreEqual(expected,
                FileVersionUtilities.IsDosVersion(GetBytesFromName(name)),
                $"{nameof(FileVersionUtilities.IsDosVersion)}: {name}");

        public void IsCurrentVersion(string name, bool expected, int revision = CurrentVersionConstants.FileRevision) =>
            Assert.AreEqual(expected,
                FileVersionUtilities.IsCurrentVersion(GetBytesFromName(name), revision),
                $"{nameof(FileVersionUtilities.IsCurrentVersion)}: {name}. Rev: {revision}");

        public void GetFileVersion(string name, FileVersion expected) =>
            Assert.AreEqual(expected,
                FileVersionUtilities.GetFileVersion(GetBytesFromName(name)),
                $"{nameof(FileVersionUtilities.GetFileVersion)}: {name}");

        [Test]
        public void PRGUtilities_IsDos()
        {
            //Dos
            IsDos("asy1.prg", true);
            IsDos("panel1.prg", true);
            IsDos("testvariables.prg", true);
            IsDos("panel11.prg", true);
            IsDos("panel2.prg", true);
            IsDos("temco.prg", true);

            //Current
            IsDos("BTUMeter.prg", false);

            //Unsupported
            IsDos("SelfTestRev3.prg", false);
            IsDos("ChamberRev5.prg", false);
            IsDos("balsam2.prg", false);
            IsDos("90185.prg", false);
        }

        [Test]
        public void PRGUtilities_IsCurrentVersion()
        {
            //Current
            IsCurrentVersion("BTUMeter.prg", true);

            //Dos
            IsCurrentVersion("asy1.prg", false);
            IsCurrentVersion("panel1.prg", false);
            IsCurrentVersion("testvariables.prg", false);
            IsCurrentVersion("panel11.prg", false);
            IsCurrentVersion("panel2.prg", false);
            IsCurrentVersion("temco.prg", false);

            //Unsupported
            IsCurrentVersion("balsam2.prg", false);
            IsCurrentVersion("90185.prg", false);

            //Past revisions
            //The version number, apparently, was not yet supported
            IsCurrentVersion("SelfTestRev3.prg", false, 3);
            IsCurrentVersion("ChamberRev5.prg", false, 5);
        }

        [Test]
        public void PRGUtilities_GetFileVersion()
        {
            //Current
            GetFileVersion("BTUMeter.prg", FileVersion.Current);

            //Dos
            GetFileVersion("asy1.prg", FileVersion.Dos);
            GetFileVersion("panel1.prg", FileVersion.Dos);
            GetFileVersion("testvariables.prg", FileVersion.Dos);
            GetFileVersion("panel11.prg", FileVersion.Dos);
            GetFileVersion("panel2.prg", FileVersion.Dos);
            GetFileVersion("temco.prg", FileVersion.Dos);

            //Unsupported
            GetFileVersion("SelfTestRev3.prg", FileVersion.Unsupported);
            GetFileVersion("ChamberRev5.prg", FileVersion.Unsupported);
            GetFileVersion("balsam2.prg", FileVersion.Unsupported);
            GetFileVersion("90185.prg", FileVersion.Unsupported);
        }
    }
}
