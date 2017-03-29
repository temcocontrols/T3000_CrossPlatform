namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;

    public static class ObjectAssert
    {
        public static void AreEqual(object expected, object actual, string message = "")
        {
            Assert.AreEqual(expected.GetType(), actual.GetType(), $@"{message}
Objects types not equals.
Expected type: {expected.GetType()}
Actual type: {actual.GetType()}");

            var type = expected.GetType();
            foreach (var property in type.GetProperties())
            {
                var expectedValue = property.GetValue(expected);
                var actualValue = property.GetValue(actual);

                Assert.AreEqual(expectedValue, actualValue, $@"{message}
{property.Name} not equals.
Expected properties: {expected.PropertiesText()}
Actual properties: {actual.PropertiesText()}");


            }
        }
    }
}
