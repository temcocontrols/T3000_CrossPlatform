namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.Collections.Generic;

    [TestFixture]
    public class StrVariablePoint_Tests
    {
        public void StrVariableAreEqual(StrVariablePoint expected, StrVariablePoint actual)
        {
            Assert.AreEqual(expected.Description, actual.Description, nameof(actual.Description));
            Assert.AreEqual(expected.Label, actual.Label, nameof(actual.Label));
            Assert.AreEqual(expected.Value, actual.Value, nameof(actual.Value));
            Assert.AreEqual(expected.ValueString, actual.ValueString, nameof(actual.ValueString));
            Assert.AreEqual(expected.AutoManual, actual.AutoManual, nameof(actual.AutoManual));
            Assert.AreEqual(expected.DigitalAnalog, actual.DigitalAnalog, nameof(actual.DigitalAnalog));
            Assert.AreEqual(expected.Control, actual.Control, nameof(actual.Control));
            Assert.AreEqual(expected.Units, actual.Units, nameof(actual.Units));
        }

        [Test]
        public void StrVariablePointFromToBytes_Simple()
        {
            var list = new List<byte>();
            list.AddRange("Description".ToBytes(21));
            list.AddRange("Label".ToBytes(9));
            list.AddRange(((uint)5000).ToBytes());
            list.Add(4 + 2 + 1);
            list.Add(1);

            var expected = list.ToArray();
            var point = new StrVariablePoint(expected);
            var actual = expected.ToBytes();

            BytesAssert.AreEqual(expected, actual);

            var point2 = new StrVariablePoint();
            point2.Description = "Description";
            point2.Label = "Label";
            point2.AutoManual = AutoManualEnum.Manual;
            point2.DigitalAnalog = DigitalAnalogEnum.Analog;
            point2.Control = ControlEnum.On;
            point2.Units = UnitsEnum.degC;
            
            //The latter. Depends on the units.
            point2.ValueString = "5.000";

            StrVariableAreEqual(point2, point);
            BytesAssert.AreEqual(point2.ToBytes(), point.ToBytes());
        }
    }
}
