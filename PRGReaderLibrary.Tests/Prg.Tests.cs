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
            PrintVariables(prg);

            var temp = Path.GetTempFileName();

            //Test variables binary load/save compatible
            foreach (var variable in prg.Variables)
            {
                //if (variable.Units == UnitsEnum.Time)
                {
                    //variable.Value = variable.Value;
                    //variable.ValueString = variable.ValueString;
                }
                variable.AutoManual = variable.AutoManual;
                variable.DigitalAnalog = variable.DigitalAnalog;
                variable.Control = variable.Control;
                variable.Units = variable.Units;
                variable.Description = variable.Description;
                variable.Label = variable.Label;
            }

            prg.Save(temp);
            FileAssert.AreEqual(path, temp, name);

            if (prg.Variables.Count > 0)
            {
                prg = Prg.Load(temp);
                prg.Variables[0].ValueString = "9998.8999";
                prg.Save(temp);
                FileAssert.AreNotEqual(path, temp);
            }

            Console.WriteLine(prg.PropertiesText());
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
        public void Prg_Asy1()
        {
        }

        [Test]
        public void Prg_BaseTests()
        {
            //Current
            BaseTest("BTUMeter.prg");

            //Dos
            BaseTest("asy1.prg");
            BaseTest("temco.prg");
            BaseTest("panel2.prg");
            BaseTest("panel11.prg");
            BaseTest("testvariables.prg");
            BaseTest("panel1.prg");

            //Unsupported
            UnsupportedTest("balsam2.prg");
            UnsupportedTest("90185.prg");
            UnsupportedTest("SelfTestRev3.prg");
        }

        [Test]
        public void Prg_TestVariables()
        {
            var prg = Prg.Load(TestUtilities.GetFullPathForTestFile("testvariables.prg"));
            PrintVariables(prg);

            var variable1 = prg.Variables[0];
            Assert.AreEqual("FirstDescription    ", variable1.Description);
            Assert.AreEqual("FirstLabe", variable1.Label);
            Assert.AreEqual(5.0F, variable1.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable1.AutoManual);
            Assert.AreEqual(DigitalAnalogEnum.Analog, variable1.DigitalAnalog);
            Assert.AreEqual(ControlEnum.Off, variable1.Control);
            Assert.AreEqual(UnitsEnum.DegreesC, variable1.Units);

            var variable2 = prg.Variables[1];
            Assert.AreEqual("SecondDescription   ", variable2.Description);
            Assert.AreEqual("SecondLab", variable2.Label);
            //Assert.AreEqual(false, variable2.Value);
            Assert.AreEqual(AutoManualEnum.Manual, variable2.AutoManual);
            Assert.AreEqual(DigitalAnalogEnum.Digital, variable2.DigitalAnalog);
            Assert.AreEqual(ControlEnum.Off, variable2.Control);
            Assert.AreEqual(UnitsEnum.OffOn, variable2.Units);

            var variable3 = prg.Variables[2];
            Assert.AreEqual("ThirdDescription    ", variable3.Description);
            Assert.AreEqual("ThirdLabe", variable3.Label);

            Assert.AreEqual(new TimeSpan(0, 22, 22, 22, 0), variable3.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable3.AutoManual);
            Assert.AreEqual(DigitalAnalogEnum.Analog, variable3.DigitalAnalog);
            Assert.AreEqual(ControlEnum.Off, variable3.Control);
            Assert.AreEqual(UnitsEnum.Time, variable3.Units);

            Console.WriteLine(prg.PropertiesText());
        }
    }
}
