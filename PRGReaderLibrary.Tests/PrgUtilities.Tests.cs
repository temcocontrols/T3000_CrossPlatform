namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.IO;

    [TestFixture]
    public class PRGUtilities_Tests
    {
        public byte[] GetBytesFromName(string name)
        {
            var path = TestUtilities.GetFullPathForTestFile(name);

            return File.ReadAllBytes(path);
        }

        public void IsDos(string name, bool expected) =>
            Assert.AreEqual(expected,
                PrgUtilities.IsDosVersion(GetBytesFromName(name)),
                $"{nameof(PrgUtilities.IsDosVersion)}: {name}");

        public void IsCurrentVersion(string name, bool expected) =>
            Assert.AreEqual(expected, 
                PrgUtilities.IsCurrentVersion(GetBytesFromName(name)),
                $"{nameof(PrgUtilities.IsCurrentVersion)}: {name}");

        public void GetFileVersion(string name, FileVersionEnum expected) =>
            Assert.AreEqual(expected,
                PrgUtilities.GetFileVersion(GetBytesFromName(name)),
                $"{nameof(PrgUtilities.GetFileVersion)}: {name}");

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
            IsCurrentVersion("SelfTestRev3.prg", false);
            IsCurrentVersion("ChamberRev5.prg", false);
            IsCurrentVersion("balsam2.prg", false);
            IsCurrentVersion("90185.prg", false);
        }

        [Test]
        public void PRGUtilities_GetFileVersion()
        {
            //Current
            GetFileVersion("BTUMeter.prg", FileVersionEnum.Current);

            //Dos
            GetFileVersion("asy1.prg", FileVersionEnum.Dos);
            GetFileVersion("panel1.prg", FileVersionEnum.Dos);
            GetFileVersion("testvariables.prg", FileVersionEnum.Dos);
            GetFileVersion("panel11.prg", FileVersionEnum.Dos);
            GetFileVersion("panel2.prg", FileVersionEnum.Dos);
            GetFileVersion("temco.prg", FileVersionEnum.Dos);

            //Unsupported
            GetFileVersion("SelfTestRev3.prg", FileVersionEnum.Unsupported);
            GetFileVersion("ChamberRev5.prg", FileVersionEnum.Unsupported);
            GetFileVersion("balsam2.prg", FileVersionEnum.Unsupported);
            GetFileVersion("90185.prg", FileVersionEnum.Unsupported);
        }
    }
}
