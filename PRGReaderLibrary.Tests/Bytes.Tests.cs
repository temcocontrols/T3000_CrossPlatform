namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;

    [TestFixture]
    public class Bytes_Tests
    {
        [Test]
        public void StringToFromBytes_Simple()
        {
            var expected = "Text";
            var bytes = expected.ToBytes();
            var actual = bytes.GetString();

            Assert.AreEqual(expected, actual);
        }

        [Test]
        public void StringToFromBytes_Cropped()
        {
            var expected = "CroppedDescription";
            var bytes = expected.ToBytes(10);
            var actual = bytes.GetString(0, 10);

            Assert.AreEqual(expected.Substring(0, 10), actual);
        }
    }
}
