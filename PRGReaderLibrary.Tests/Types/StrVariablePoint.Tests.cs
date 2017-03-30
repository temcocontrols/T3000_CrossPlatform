namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System.Collections.Generic;

    [TestFixture]
    public class StrVariablePoint_Tests
    {
        public void BaseTest(byte[] bytes, StrVariablePoint expected, FileVersion version)
        {
            var actual = new StrVariablePoint(bytes, 0, version);
            ObjectAssert.AreEqual(expected, actual);
            BytesAssert.AreEqual(expected.ToBytes(), actual.ToBytes());
            BytesAssert.AreEqual(bytes, expected.ToBytes());
        }

        [Test]
        public void StrVariablePoint_Dos_Analog()
        {
            var list = new List<byte>();
            list.AddRange("Description".ToBytes(21));
            list.AddRange("Label".ToBytes(9));
            list.AddRange(((uint)5000).ToBytes());//Value
            list.Add(new [] {true,true,true}.ToBits()); //AutoManual DigitalAnalog Control
            list.Add((byte)Units.DegreesC);//Units

            var expected = new StrVariablePoint("Description", "Label", FileVersion.Dos);
            expected.Value = new VariableVariant("5.000", Units.DegreesC);
            expected.AutoManual = AutoManual.Manual;
            expected.DigitalAnalog = DigitalAnalog.Analog;
            expected.Control = Control.On;

            BaseTest(list.ToArray(), expected, FileVersion.Dos);
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

            var expected = new StrVariablePoint("START TEST FLAG", "INIT");
            expected.Value = new VariableVariant("Off", Units.OffOn);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Digital;
            expected.Control = Control.Off;

            BaseTest(list.ToArray(), expected, FileVersion.Current);
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

            var expected = new StrVariablePoint("PUMP SPEED", "PMPSPEED");
            expected.Value = new VariableVariant("40.000", Units.Percents);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Analog;
            expected.Control = Control.Off;

            BaseTest(list.ToArray(), expected, FileVersion.Current);
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

            var expected = new StrVariablePoint("TEST RUN TIMER", "TESTTIM");
            expected.Value = new VariableVariant("03:45:09", Units.Time);
            expected.AutoManual = AutoManual.Automatic;
            expected.DigitalAnalog = DigitalAnalog.Analog;
            expected.Control = Control.On;

            BaseTest(list.ToArray(), expected, FileVersion.Current);
        }
    }
}
