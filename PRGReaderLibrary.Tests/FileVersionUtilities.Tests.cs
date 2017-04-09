namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.IO;

    [TestFixture]
    [Category("PRGReaderLibrary.Utilities")]
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

        public void IsRev6Version(string name, bool expected, int revision = FileVersionUtilities.CurrentFileRevision) =>
            Assert.AreEqual(expected,
                FileVersionUtilities.IsRev6Version(GetBytesFromName(name), revision),
                $"{nameof(FileVersionUtilities.IsRev6Version)}: {name}. Rev: {revision}");

        public void GetFileVersion(string name, FileVersion expected) =>
            Assert.AreEqual(expected,
                FileVersionUtilities.GetFileVersion(GetBytesFromName(name)),
                $"{nameof(FileVersionUtilities.GetFileVersion)}: {name}");

        [Test]
        public void Utilities_IsDos()
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
            IsDos("CustomAnalogRev6.prg", false);
            IsDos("TemcoPanelRev6.prg", false);
            IsDos("T3DemoRev6.prg", false);

            //Unsupported
            IsDos("SelfTestRev3.prg", false);
            IsDos("ChamberRev5.prg", false);
            IsDos("balsam2.prg", false);
            IsDos("90185.prg", false);
        }

        [Test]
        public void Utilities_IsRev6Version()
        {
            //Rev6
            IsRev6Version("BTUMeter.prg", true);
            IsRev6Version("CustomAnalogRev6.prg", true);
            IsRev6Version("TemcoPanelRev6.prg", true);
            IsRev6Version("T3DemoRev6.prg", true);

            //Dos
            IsRev6Version("asy1.prg", false);
            IsRev6Version("panel1.prg", false);
            IsRev6Version("testvariables.prg", false);
            IsRev6Version("panel11.prg", false);
            IsRev6Version("panel2.prg", false);
            IsRev6Version("temco.prg", false);

            //Unsupported
            IsRev6Version("balsam2.prg", false);
            IsRev6Version("90185.prg", false);

            //Past revisions
            //The version number, apparently, was not yet supported
            IsRev6Version("SelfTestRev3.prg", false, 3);
            IsRev6Version("ChamberRev5.prg", false, 5);
        }

        [Test]
        public void Utilities_GetFileVersion()
        {
            //Rev6
            GetFileVersion("BTUMeter.prg", FileVersion.Rev6);
            GetFileVersion("CustomAnalogRev6.prg", FileVersion.Rev6);
            GetFileVersion("TemcoPanelRev6.prg", FileVersion.Rev6);
            GetFileVersion("T3DemoRev6.prg", FileVersion.Rev6);

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
