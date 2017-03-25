namespace PRGReaderLibrary.Tests
{
    using System;
    using NUnit.Framework;

    public static class BytesAssert
    {
        public static void AreEqual(byte[] bytes1, byte[] bytes2)
        {
            Assert.AreEqual(bytes1.Length, bytes2.Length, "Bytes arrays lenghts not equals");

            var isEquals = true;
            for (var i = 0; i < bytes1.Length; ++i)
            {
                if (bytes1[i] != bytes2[i])
                {
                    isEquals = false;
                    Console.WriteLine($"Byte: {i}. Expected: {bytes1[i]}. Actual: {bytes2[i]}");
                }
            }

            Assert.IsTrue(isEquals, "Bytes arrays not equals");
        }
    }
}
