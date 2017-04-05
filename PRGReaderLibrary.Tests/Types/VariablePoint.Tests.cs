namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.Collections.Generic;

    [TestFixture]
    public class VariablePoint_Tests
    {
        public void BaseTest(byte[] actualBytes, VariablePoint expected, FileVersion version, List<DigitalCustomUnitsPoint> customUnits = null)
        {
            var actual = new VariablePoint(actualBytes, 0, version);
            actual.Value.CustomUnits = customUnits;
            BytesAssert.AreEqual(actual.ToBytes(), expected.ToBytes());
            BytesAssert.AreEqual(actualBytes, expected.ToBytes());
            ObjectAssert.AreEqual(actual, expected);
        }

        [Test]
        public void VariablePoint_Dos_Analog()
        {
            var list = new List<byte>();
            list.AddRange("Description".ToBytes(21));
            list.AddRange("Label".ToBytes(9));
            list.AddRange(((uint)5000).ToBytes());//Value
            list.Add(new [] {true,true,true}.ToBits()); //AutoManual DigitalAnalog Control
            list.Add((byte)Units.DegreesC);//Units

            var expected = new VariablePoint("Description", "Label", FileVersion.Dos);
            expected.Value = new VariableValue("5.000", Units.DegreesC);
            expected.AutoManual = AutoManual.Manual;
            expected.DigitalAnalog = DigitalAnalog.Analog;
            expected.Control = Control.On;

            BaseTest(list.ToArray(), expected, FileVersion.Dos);
        }

        [Test]
        public void VariablePoint_Current_Digital()
        {
            var list = new List<byte>();
            list.AddRange("START TEST FLAG\0\0\0\0\0\0INIT\0\0\0\0\0".ToBytes());
            list.AddRange(((uint)0).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(0);//DigitalAnalog
            list.Add(0);//Control
            list.Add(2);//Unused
            list.Add(1);//Units

            var expected = new VariablePoint("START TEST FLAG", "INIT");
            expected.Value = new VariableValue("Off", Units.OffOn);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Digital;
            expected.Control = Control.Off;

            BaseTest(list.ToArray(), expected, FileVersion.Current);
        }

        [Test]
        public void VariablePoint_Current_Analog()
        {
            var list = new List<byte>();
            list.AddRange("PUMP SPEED\0\0\0\0\0\0\0\0\0\0\0PMPSPEED\0".ToBytes());
            list.AddRange(((uint)40000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(1);//DigitalAnalog
            list.Add(0);//Control
            list.Add(2);//Unused
            list.Add(22);//Units

            var expected = new VariablePoint("PUMP SPEED", "PMPSPEED");
            expected.Value = new VariableValue("40.000", Units.Percents);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Analog;
            expected.Control = Control.Off;

            BaseTest(list.ToArray(), expected, FileVersion.Current);
        }

        [Test]
        public void VariablePoint_Current_Time()
        {
            var list = new List<byte>();
            list.AddRange("TEST RUN TIMER\0\0\0\0\0\0\0TESTTIM\0\0".ToBytes());
            list.AddRange(((uint)13509000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(1);//DigitalAnalog
            list.Add(1);//Control
            list.Add(2);//Unused
            list.Add(20);//Units

            var expected = new VariablePoint("TEST RUN TIMER", "TESTTIM");
            expected.Value = new VariableValue("03:45:09", Units.Time);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Analog;
            expected.Control = Control.On;

            BaseTest(list.ToArray(), expected, FileVersion.Current);
        }

        [Test]
        public void VariablePoint_CustomDigital()
        {
            var list = new List<byte>();
            list.AddRange("TEST CUS UNITS\0\0\0\0\0\0\0TESTCUS\0\0".ToBytes());
            list.AddRange(((uint)2000).ToBytes());//Value
            list.Add(0);//AutoManual
            list.Add(0);//DigitalAnalog
            list.Add(1);//Control
            list.Add(2);//Unused
            list.Add(23);//Units
            var actual = list.ToArray();

            var customUnits = new List<DigitalCustomUnitsPoint>();
            customUnits.Add(new DigitalCustomUnitsPoint(false, "TEST1", "TEST2"));

            var expected = new VariablePoint("TEST CUS UNITS", "TESTCUS");
            expected.Value = new VariableValue("TEST2", Units.CustomDigital1, customUnits);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Digital;
            expected.Control = Control.On;

            //BaseTest(actual, expected, FileVersion.Current, customUnits);
        }
    }
}
