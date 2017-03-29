namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System;
    using System.IO;

    [TestFixture]
    public class PrgReader_Tests
    {
        public void BaseTest(string name)
        {
            var path = TestUtilities.GetFullPathForTestFile(name);
            var prg = Prg.Load(path);

            var temp = Path.GetTempFileName();

            //Test variables binary load/save compatible
            foreach (var variable in prg.Variables)
            {
                //Additional check for Value
                var tempValue = new VariableVariant(variable.Value.ToString(), variable.Value.Units);
                ObjectAssert.AreEqual(variable.Value, tempValue,
                    $@"Variable value toFrom string test failed.
Value.ToString(): {variable.Value.ToString()}
Value.ToFromToString(): {tempValue.ToString()}
");

                var tempVariable = variable;
                variable.AutoManual = variable.AutoManual;
                variable.DigitalAnalog = variable.DigitalAnalog;
                variable.Control = variable.Control;
                variable.Value = variable.Value;
                variable.Description = variable.Description;
                variable.Label = variable.Label;
                ObjectAssert.AreEqual(tempVariable, variable, "Variable GetSet test failed.");
                BytesAssert.AreEqual(tempVariable.ToBytes(), variable.ToBytes(), "Variable GetSet ToBytes test failed.");
            }

            prg.Save(temp);
            FileAssert.AreEqual(path, temp, name);

            if (prg.Variables.Count > 0)
            {
                prg = Prg.Load(temp);
                prg.Variables[0].Value = new VariableVariant("9998.8999", UnitsEnum.DegreesC);
                prg.Save(temp);
                FileAssert.AreNotEqual(path, temp);
            }
        }

        public void UnsupportedTest(string name)
        {
            var exception = Assert.Catch(() =>
            {
                var prg = Prg.Load(TestUtilities.GetFullPathForTestFile(name));

                Console.WriteLine(prg.PropertiesText());
            });
            Console.WriteLine(exception.Message);
        }

        public void PrintVariables(Prg prg)
        {
            foreach (var var in prg.Variables)
            {
                if (string.IsNullOrWhiteSpace(var.Description))
                {
                    continue;
                }

                Console.WriteLine("---------------------------");
                Console.Write(var.PropertiesText());
                Console.WriteLine("---------------------------");
                Console.WriteLine(string.Empty);
            }
        }

        [Test]
        public void Prg_BaseTests()
        {
            //Current
            BaseTest("BTUMeter.prg");

            //Dos
            BaseTest("asy1.prg");
            BaseTest("panel2.prg");
            BaseTest("panel11.prg");
            BaseTest("panel1.prg");

            //Binaries load/save temporaly not compatible
            //BaseTest("testvariables.prg");
            //BaseTest("temco.prg");

            //Unsupported
            UnsupportedTest("balsam2.prg");
            UnsupportedTest("90185.prg");
            UnsupportedTest("SelfTestRev3.prg");
            UnsupportedTest("ChamberRev5.prg");
        }

        [Test]
        public void Prg_TestVariables()
        {
            var prg = Prg.Load(TestUtilities.GetFullPathForTestFile("testvariables.prg"));

            var variable1 = prg.Variables[0];
            Assert.AreEqual("FirstDescription    ", variable1.Description);
            Assert.AreEqual("FirstLabe", variable1.Label);
            Assert.AreEqual(new VariableVariant(5.0, UnitsEnum.DegreesC), variable1.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable1.AutoManual);
            Assert.AreEqual(DigitalAnalogEnum.Analog, variable1.DigitalAnalog);
            Assert.AreEqual(ControlEnum.Off, variable1.Control);

            var variable2 = prg.Variables[1];
            Assert.AreEqual("SecondDescription   ", variable2.Description);
            Assert.AreEqual("SecondLab", variable2.Label);
            ObjectAssert.AreEqual(new VariableVariant("On", UnitsEnum.OffOn).Value, variable2.Value.Value);
            Assert.AreEqual(AutoManualEnum.Manual, variable2.AutoManual);
            Assert.AreEqual(DigitalAnalogEnum.Digital, variable2.DigitalAnalog);
            Assert.AreEqual(ControlEnum.Off, variable2.Control);

            var variable3 = prg.Variables[2];
            Assert.AreEqual("ThirdDescription    ", variable3.Description);
            Assert.AreEqual("ThirdLabe", variable3.Label);
            Assert.AreEqual(new VariableVariant(new TimeSpan(0, 22, 22, 22, 0), UnitsEnum.Time), variable3.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable3.AutoManual);
            Assert.AreEqual(DigitalAnalogEnum.Analog, variable3.DigitalAnalog);
            Assert.AreEqual(ControlEnum.Off, variable3.Control);
        }
    }
}
