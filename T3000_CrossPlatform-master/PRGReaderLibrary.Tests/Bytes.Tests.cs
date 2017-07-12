namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;

    [TestFixture]
    [Category("PRGReaderLibrary.Utilities")]
    public class Bytes_Tests
    {
        [Test]
        public void StringToFromBytes()
        {
            var expected = "Simple";
            var bytes = expected.ToBytes();
            var actual = bytes.GetString();

            Assert.AreEqual(expected, actual);

            expected = "CroppedDescription";
            bytes = expected.ToBytes(10);
            actual = bytes.GetString(0, 10);

            Assert.AreEqual(expected.Substring(0, 10), actual);
        }
    }
}
