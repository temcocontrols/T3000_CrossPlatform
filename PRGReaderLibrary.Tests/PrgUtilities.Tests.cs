namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.IO;

    [TestFixture]
    public class PRGUtilities_Tests
    {
        public bool IsDos(string name, bool isDos = true)
        {
            var path = TestUtilities.GetFullPathForTestFile(name);
            var bytes = File.ReadAllBytes(path);

            return PrgUtilities.IsDosVersion(bytes);
        }

        [Test]
        public void PRGUtilities_IsDos()
        {
            Assert.IsTrue(IsDos("asy1.prg"));
            Assert.IsTrue(IsDos("panel1.prg"));
            Assert.IsTrue(IsDos("testvariables.prg"));
            Assert.IsTrue(IsDos("panel11.prg"));
            Assert.IsTrue(IsDos("panel2.prg"));
            Assert.IsTrue(IsDos("temco.prg"));

            Assert.IsFalse(IsDos("balsam2.prg"));
            Assert.IsFalse(IsDos("90185.prg"));
            Assert.IsFalse(IsDos("BTUMeter.prg"));
            Assert.IsFalse(IsDos("SelfTestRev3.prg"));
        }
    }
}
