namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.Collections.Generic;

    [TestFixture]
    public class StrVariablePoint_Tests
    {
        public void BaseTest(byte[] bytes, StrVariablePoint expected, FileVersionEnum version)
        {
            var actual = new StrVariablePoint(bytes, 0, version);
            ObjectAssert.AreEqual(expected, actual);
            BytesAssert.AreEqual(expected.ToBytes(version), actual.ToBytes(version));
            BytesAssert.AreEqual(bytes, expected.ToBytes(version));
        }

        [Test]
        public void StrVariablePoint_Dos_Analog()
        {
            var list = new List<byte>();
            list.AddRange("Description".ToBytes(21));
            list.AddRange("Label".ToBytes(9));
            list.AddRange(((uint)5000).ToBytes());
            list.Add(new [] {true,true,true}.ToBits());
            list.Add((byte)UnitsEnum.DegreesC);

            var expected = new StrVariablePoint();
            expected.Description = "Description";
            expected.Label = "Label";
            expected.Value = new VariableVariant("5.000", UnitsEnum.DegreesC);
            expected.AutoManual = AutoManualEnum.Manual;
            expected.DigitalAnalog = DigitalAnalogEnum.Analog;
            expected.Control = ControlEnum.On;

            BaseTest(list.ToArray(), expected, FileVersionEnum.Dos);
        }

        [Test]
        public void StrVariablePoint_Current_Digital()
        {
            var list = new List<byte>();
            list.AddRange("START TEST FLAG\0\0\0\0\0\0INIT\0\0\0\0\0".ToBytes());
            list.AddRange(((uint)0).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(0);//DigitalAnalog
            list.Add(0);//Control
            list.Add(2);//Unused
            list.Add(1);//Units

            var expected = new StrVariablePoint();
            expected.Description = "START TEST FLAG";
            expected.Label = "INIT";
            expected.Value = new VariableVariant("Off", UnitsEnum.OffOn);
            expected.AutoManual = AutoManualEnum.Automatic;
            expected.DigitalAnalog = DigitalAnalogEnum.Digital;
            expected.Control = ControlEnum.Off;

            BaseTest(list.ToArray(), expected, FileVersionEnum.Current);
        }

        [Test]
        public void StrVariablePoint_Current_Analog()
        {
            var list = new List<byte>();
            list.AddRange("PUMP SPEED\0\0\0\0\0\0\0\0\0\0\0PMPSPEED\0".ToBytes());
            list.AddRange(((uint)40000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(1);//DigitalAnalog
            list.Add(0);//Control
            list.Add(2);//Unused
            list.Add(22);//Units

            var expected = new StrVariablePoint();
            expected.Description = "PUMP SPEED";
            expected.Label = "PMPSPEED";
            expected.Value = new VariableVariant("40.000", UnitsEnum.Percents);
            expected.AutoManual = AutoManualEnum.Automatic;
            expected.DigitalAnalog = DigitalAnalogEnum.Analog;
            expected.Control = ControlEnum.Off;

            BaseTest(list.ToArray(), expected, FileVersionEnum.Current);
        }

        [Test]
        public void StrVariablePoint_Current_Time()
        {
            var list = new List<byte>();
            list.AddRange("TEST RUN TIMER\0\0\0\0\0\0\0TESTTIM\0\0".ToBytes());
            list.AddRange(((uint)13509000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(1);//DigitalAnalog
            list.Add(1);//Control
            list.Add(2);//Unused
            list.Add(20);//Units

            var expected = new StrVariablePoint();
            expected.Description = "TEST RUN TIMER";
            expected.Label = "TESTTIM";
            expected.Value = new VariableVariant("03:45:09", UnitsEnum.Time);
            expected.AutoManual = AutoManualEnum.Automatic;
            expected.DigitalAnalog = DigitalAnalogEnum.Analog;
            expected.Control = ControlEnum.On;

            BaseTest(list.ToArray(), expected, FileVersionEnum.Current);
        }
    }
}
