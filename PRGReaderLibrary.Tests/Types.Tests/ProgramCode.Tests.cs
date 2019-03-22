namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.Collections.Generic;
    using System.IO;

    [TestFixture]
    [Category("PRGReaderLibrary.Types")]
    public class ProgramCode_Tests
    {
        [Test]
        public void GetLinePart_Tests()
        {
            var path = TestUtilities.GetFullPathForPrgFile("BTUMeter.prg");
            var prg = Prg.Load(path);

            var bytes = prg.ProgramCodes[0].Code;
            {
                //20 IF TIME-ON ( INIT ) > 00:00:05 AND METERTOT < 1 THEN STOP INIT
                var offset = 56;

                var ifPart = Line.GetLinePart(bytes, ref offset);
                Assert.AreEqual(20, ifPart.Length);
                var ff = bytes.ToByte(ref offset);
                Assert.AreEqual(0xFF, ff);
                var thenEnd = bytes.ToUInt16(ref offset);
                Assert.AreEqual(83, thenEnd);
                var thenPart = Line.GetLinePart(bytes, ref offset, nextPart: thenEnd);
                Assert.AreEqual(4, thenPart.Length);
            }


        }
    }
}
