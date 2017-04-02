namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System;
    using System.Collections.Generic;
    using System.IO;

    [TestFixture]
    public class PrgReader_Tests
    {
        public void VariableVariantToFromTest(VariableVariant value, List<UnitsElement> customUnits)
        {
            var tempValue = new VariableVariant(value.ToString(), value.Units, customUnits);
            ObjectAssert.AreEqual(value, tempValue,
                $@"Variable value toFrom string test failed.
Value.ToString(): {value.ToString()}
Value.ToFromToString(): {tempValue.ToString()}
");
        }

        public void BaseTest(string name)
        {
            var path = TestUtilities.GetFullPathForTestFile(name);
            var prg = Prg.Load(path);

            var temp = Path.GetTempFileName();

            //Test variables binary load/save compatible

            //Bit to bit compatible supported only for current version
            if (prg.FileVersion == FileVersion.Current)
            {
                foreach (var input in prg.Inputs)
                {
                    VariableVariantToFromTest(input.Value, prg.Units);

                    var bytes = input.ToBytes();
                    var tempVariable = new InputPoint(bytes);
                    ObjectAssert.AreEqual(input, tempVariable,
                        "Input ToFromBytes test failed.");
                    BytesAssert.AreEqual(tempVariable.ToBytes(), input.ToBytes(),
                        "Input ToFromBytes ToBytes test failed.");
                }

                foreach (var output in prg.Outputs)
                {
                    VariableVariantToFromTest(output.Value, prg.Units);

                    var bytes = output.ToBytes();
                    var tempVariable = new OutputPoint(bytes);
                    ObjectAssert.AreEqual(output, tempVariable,
                        "Output ToFromBytes test failed.");
                    BytesAssert.AreEqual(tempVariable.ToBytes(), output.ToBytes(),
                        "Output ToFromBytes ToBytes test failed.");
                }

                foreach (var variable in prg.Variables)
                {
                    VariableVariantToFromTest(variable.Value, prg.Units);

                    var bytes = variable.ToBytes();
                    var tempVariable = new VariablePoint(bytes);
                    ObjectAssert.AreEqual(variable, tempVariable,
                        "Variable ToFromBytes test failed.");
                    BytesAssert.AreEqual(tempVariable.ToBytes(), variable.ToBytes(),
                        "Variable ToFromBytes ToBytes test failed.");
                }

                foreach (var unit in prg.Units)
                {
                    var bytes = unit.ToBytes();
                    var tempVariable = new UnitsElement(bytes);
                    ObjectAssert.AreEqual(unit, tempVariable,
                        "Unit ToFromBytes test failed.");
                    BytesAssert.AreEqual(tempVariable.ToBytes(), unit.ToBytes(),
                        "Unit ToFromBytes ToBytes test failed.");
                }
            }

            prg.Save(temp);
            FileAssert.AreEqual(path, temp, name);

            if (prg.Variables.Count > 0)
            {
                prg = Prg.Load(temp);
                prg.Variables[0].Value = new VariableVariant("9998.8999", Units.DegreesC);
                prg.Save(temp);
                FileAssert.AreNotEqual(path, temp);
            }

            //Not supported while using RawData. 
            //Only updating the file without changing the format is available.
            /*
            //Additional check for upgrade to current
            if (prg.FileVersion != FileVersion.Current)
            {
                prg.Upgrade();
                prg.Save(temp);
                prg = Prg.Load(temp);
                Assert.AreEqual(FileVersion.Current, prg.FileVersion);
            }
            */
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
            foreach (var variable in prg.Variables)
            {
                if (variable.IsEmpty)
                {
                    continue;
                }

                Console.WriteLine("---------------------------");
                Console.Write(variable.PropertiesText());
                Console.WriteLine("---------------------------");
                Console.WriteLine(string.Empty);
            }
        }

        [Test]
        public void Prg_BTUMeter()
        {
            var path = TestUtilities.GetFullPathForTestFile("BTUMeter.prg");
            var prg = Prg.Load(path);

            ObjectAssert.AreEqual(new UnitsElement(false, "TANK1", "TANK2"), prg.Units[0]);
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
            BaseTest("testvariables.prg");
            BaseTest("temco.prg");

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
            Assert.AreEqual(new VariableVariant(5.0, Units.DegreesC), variable1.Value);
            Assert.AreEqual(AutoManual.Automatic, variable1.AutoManual);
            Assert.AreEqual(DigitalAnalog.Analog, variable1.DigitalAnalog);
            Assert.AreEqual(Control.Off, variable1.Control);

            var variable2 = prg.Variables[1];
            Assert.AreEqual("SecondDescription   ", variable2.Description);
            Assert.AreEqual("SecondLab", variable2.Label);
            ObjectAssert.AreEqual(new VariableVariant("On", Units.OffOn).Value, variable2.Value.Value);
            Assert.AreEqual(AutoManual.Manual, variable2.AutoManual);
            Assert.AreEqual(DigitalAnalog.Digital, variable2.DigitalAnalog);
            Assert.AreEqual(Control.Off, variable2.Control);

            var variable3 = prg.Variables[2];
            Assert.AreEqual("ThirdDescription    ", variable3.Description);
            Assert.AreEqual("ThirdLabe", variable3.Label);
            Assert.AreEqual(new VariableVariant(new TimeSpan(0, 22, 22, 22, 0), Units.Time), variable3.Value);
            Assert.AreEqual(AutoManual.Automatic, variable3.AutoManual);
            Assert.AreEqual(DigitalAnalog.Analog, variable3.DigitalAnalog);
            Assert.AreEqual(Control.Off, variable3.Control);
        }
    }
}
