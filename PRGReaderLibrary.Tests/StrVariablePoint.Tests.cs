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
        public void StrVariablePoint_Dos_Analog()
        {
            var version = FileVersionEnum.Dos;

            var list = new List<byte>();
            list.AddRange("Description".ToBytes(21));
            list.AddRange("Label".ToBytes(9));
            list.AddRange(((uint)5000).ToBytes());
            list.Add(new [] {true,true,true}.ToBits());
            list.Add((byte)UnitsEnum.degC);

            var expected = list.ToArray();
            var point = new StrVariablePoint(expected, 0, version);
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
            BytesAssert.AreEqual(point2.ToBytes(version), point.ToBytes(version));
        }

        [Test]
        public void StrVariablePoint_Current_Digital()
        {
            var version = FileVersionEnum.Current;

            var list = new List<byte>();
            list.AddRange("START TEST FLAG\0\0\0\0\0\0INIT\0\0\0\0\0".ToBytes());
            list.AddRange(((uint)0).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(0);//DigitalAnalog
            list.Add(0);//Control
            list.Add(2);//Unused
            list.Add(1);//Units

            var actual = new StrVariablePoint(list.ToArray(), 0, version);

            var expected = new StrVariablePoint();
            expected.Description = "START TEST FLAG";
            expected.Label = "INIT";
            expected.AutoManual = AutoManualEnum.Automatic;
            expected.DigitalAnalog = DigitalAnalogEnum.Digital;
            expected.Control = ControlEnum.Off;
            expected.Units = UnitsEnum.OffOn;

            //The latter. Depends on the units.
            expected.ValueString = "0";

            StrVariableAreEqual(expected, actual);
            BytesAssert.AreEqual(expected.ToBytes(version), actual.ToBytes(version));
            BytesAssert.AreEqual(list.ToArray(), expected.ToBytes(version));
        }

        [Test]
        public void StrVariablePoint_Current_Analog()
        {
            var version = FileVersionEnum.Current;

            var list = new List<byte>();
            list.AddRange("PUMP SPEED\0\0\0\0\0\0\0\0\0\0\0PMPSPEED\0".ToBytes());
            list.AddRange(((uint)40000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(1);//DigitalAnalog
            list.Add(0);//Control
            list.Add(2);//Unused
            list.Add(22);//Units

            var actual = new StrVariablePoint(list.ToArray(), 0, version);

            var expected = new StrVariablePoint();
            expected.Description = "PUMP SPEED";
            expected.Label = "PMPSPEED";
            expected.AutoManual = AutoManualEnum.Automatic;
            expected.DigitalAnalog = DigitalAnalogEnum.Analog;
            expected.Control = ControlEnum.Off;
            expected.Units = UnitsEnum.Percents;

            //The latter. Depends on the units.
            expected.ValueString = "40.000";

            StrVariableAreEqual(expected, actual);
            BytesAssert.AreEqual(expected.ToBytes(version), actual.ToBytes(version));
            BytesAssert.AreEqual(list.ToArray(), expected.ToBytes(version));
        }

        [Test]
        public void StrVariablePoint_Current_Time()
        {
            var version = FileVersionEnum.Current;

            var list = new List<byte>();
            list.AddRange("TEST RUN TIMER\0\0\0\0\0\0\0TESTTIM\0\0".ToBytes());
            list.AddRange(((uint)13509000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(1);//DigitalAnalog
            list.Add(1);//Control
            list.Add(2);//Unused
            list.Add(20);//Units

            var actual = new StrVariablePoint(list.ToArray(), 0, version);

            var expected = new StrVariablePoint();
            expected.Description = "TEST RUN TIMER";
            expected.Label = "TESTTIM";
            expected.AutoManual = AutoManualEnum.Automatic;
            expected.DigitalAnalog = DigitalAnalogEnum.Analog;
            expected.Control = ControlEnum.On;
            expected.Units = UnitsEnum.Time;

            //The latter. Depends on the units.
            expected.ValueString = "03:45:09";

            StrVariableAreEqual(expected, actual);
            BytesAssert.AreEqual(expected.ToBytes(version), actual.ToBytes(version));
            BytesAssert.AreEqual(list.ToArray(), expected.ToBytes(version));
        }
    }
}
