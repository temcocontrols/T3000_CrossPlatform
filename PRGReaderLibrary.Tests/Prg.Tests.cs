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
                //Bit to bit compatible supported only for current version
                if (prg.FileVersion == FileVersion.Current)
                {
                    //Additional check for Value
                    var tempValue = new VariableVariant(variable.Value.ToString(), variable.Value.Units, variable.CustomUnits);
                    ObjectAssert.AreEqual(variable.Value, tempValue,
                        $@"Variable value toFrom string test failed.
Value.ToString(): {variable.Value.ToString()}
Value.ToFromToString(): {tempValue.ToString()}
");
                }

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

            foreach (var unit in prg.Units)
            {
                unit.Direct = unit.Direct;
                unit.DigitalUnitsOff = unit.DigitalUnitsOff;
                unit.DigitalUnitsOn = unit.DigitalUnitsOn;
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
