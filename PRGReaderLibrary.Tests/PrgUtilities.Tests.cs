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

        [Test]
        public void PRGUtilities_IsDos()
        {
            IsDos("asy1.prg", true);
            IsDos("panel1.prg", true);
            IsDos("testvariables.prg", true);
            IsDos("panel11.prg", true);
            IsDos("panel2.prg", true);
            IsDos("temco.prg", true);

            IsDos("balsam2.prg", false);
            IsDos("90185.prg", false);
            IsDos("BTUMeter.prg", false);
            IsDos("SelfTestRev3.prg", false);
        }

        [Test]
        public void PRGUtilities_IsCurrentVersion()
        {
            IsCurrentVersion("BTUMeter.prg", true);

            //I don't know this versions
            //IsCurrentVersion("SelfTestRev3.prg", true);
            //IsCurrentVersion("balsam2.prg", true);
            //IsCurrentVersion("90185.prg", true);

            IsCurrentVersion("asy1.prg", false);
            IsCurrentVersion("panel1.prg", false);
            IsCurrentVersion("testvariables.prg", false);
            IsCurrentVersion("panel11.prg", false);
            IsCurrentVersion("panel2.prg", false);
            IsCurrentVersion("temco.prg", false);
        }
    }
}
