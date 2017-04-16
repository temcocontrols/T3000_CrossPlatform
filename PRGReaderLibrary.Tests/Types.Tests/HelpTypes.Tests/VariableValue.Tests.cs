namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;

    [TestFixture]
    [Category("PRGReaderLibrary.Types.HelpTypes")]
    public class VariableValue_Tests
    {
        public void InvertedBaseTest(VariableValue value)
        {
            var inverted = value.GetInverted();
            Assert.AreNotEqual(value, inverted,
                $@"Inverted value is equal value
Value: {value.PropertiesText(true)}
Inverted: {inverted.PropertiesText(true)}");

            Assert.AreNotEqual(value.ToObject(), inverted.ToObject(),
                $@"Inverted value.ToObject() is equal value.ToObject()
Value: {value.PropertiesText(true)}
Inverted: {inverted.PropertiesText(true)}");

            Assert.AreNotEqual(value.ToString(), inverted.ToString(), 
                $@"Inverted value.ToString() is equal value.ToString()
Value: {value.PropertiesText(true)}
Inverted: {inverted.PropertiesText(true)}");

            inverted = inverted.GetInverted();
            Assert.AreEqual(value, inverted, 
                $@"Double inverted value is not equal value
Value: {value.PropertiesText(true)}
Double inverted: {inverted.PropertiesText(true)}");

            Assert.AreEqual(value.ToObject(), inverted.ToObject(),
                $@"Double inverted value.ToObject() is not equal value.ToObject()
Value: {value.PropertiesText(true)}
Double inverted: {inverted.PropertiesText(true)}");

            Assert.AreEqual(value.ToString(), inverted.ToString(),
                $@"Double inverted value.ToString() is not equal value.ToString()
Value: {value.PropertiesText(true)}
Double inverted: {inverted.PropertiesText(true)}");
        }

        [Test]
        public void VariableValue_GetInverted()
        {
            //Simple
            InvertedBaseTest(new VariableValue("Off", Unit.OffOn));
            InvertedBaseTest(new VariableValue("Off", Unit.OffOn, null, 1000));
            InvertedBaseTest(new VariableValue(false, Unit.OffOn));
            InvertedBaseTest(new VariableValue(false, Unit.OffOn, null, 1000));
            InvertedBaseTest(new VariableValue("On", Unit.OffOn));
            InvertedBaseTest(new VariableValue("On", Unit.OffOn, null, 1000));
            InvertedBaseTest(new VariableValue(true, Unit.OffOn));
            InvertedBaseTest(new VariableValue(true, Unit.OffOn, null, 1000));

            InvertedBaseTest(new VariableValue(0, Unit.OffOn, null));

            InvertedBaseTest(new VariableValue("Off", Unit.OffOn, null, 0));
            InvertedBaseTest(new VariableValue("On", Unit.OffOn, null, 0));
        }
    }
}
