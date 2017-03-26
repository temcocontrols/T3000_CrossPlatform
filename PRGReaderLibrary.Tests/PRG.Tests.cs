namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System;
    using System.IO;
    using System.Reflection;

    [TestFixture]
    public class PRGReader_Tests
    {
        private string GetFullPath(string filename) =>
            Path.Combine(
                Path.GetDirectoryName(Path.GetDirectoryName(Path.GetDirectoryName(
                    Assembly.GetExecutingAssembly().Location))
                ),
                "TestFiles", filename);

        public void BaseTest(string name)
        {
            var originalFile = GetFullPath(name);
            var prg = PRG.Load(originalFile);
            PrintVariables(prg);

            var temp = Path.GetTempFileName();

            //Test variables binary load/save compatible
            foreach (var variable in prg.Variables)
            {
                //if (variable.Units == UnitsEnum.degC)
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
            Assert.IsTrue(FileUtilities.FilesIsEquals(originalFile, temp));

            prg = PRG.Load(temp);
            prg.Variables[0].ValueString = "9998.8999";
            prg.Save(temp);
            Assert.IsFalse(FileUtilities.FilesIsEquals(originalFile, temp));
            
            Console.WriteLine(prg.PropertiesText());
        }

        public void UnsupportedTest(string name)
        {
            var exception = Assert.Catch(() =>
            {
                var prg = PRG.Load(GetFullPath(name));

                Console.WriteLine(prg.PropertiesText());
            });
            Console.WriteLine(exception.Message);
        }

        public void PrintVariables(PRG prg)
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
        public void PRG_Asy1()
        {
            BaseTest("asy1.prg");
        }

        [Test]
        public void PRG_Balsam2()
        {
            UnsupportedTest("balsam2.prg");
        }

        [Test]
        public void PRG_90185()
        {
            UnsupportedTest("90185.prg");
        }

        [Test]
        public void PRG_Panel1()
        {
            BaseTest("panel1.prg");
        }

        [Test]
        public void PRG_TestVariables()
        {
            BaseTest("testvariables.prg");
            var prg = PRG.Load(GetFullPath("testvariables.prg"));

            PrintVariables(prg);

            var variable1 = prg.Variables[0];
            Assert.AreEqual("FirstDescription    ", variable1.Description); //20 bytes  
            Assert.AreEqual("FirstLabe", variable1.Label); //9 bytes
            //Assert.AreEqual(5000, variable1.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable1.AutoManual);
            //Assert.AreEqual(false, variable1.IsAnalog);
            //Assert.AreEqual(false, variable1.IsControl);
            Assert.AreEqual(UnitsEnum.degC, variable1.Units);

            var variable2 = prg.Variables[1];
            Assert.AreEqual("SecondDescription   ", variable2.Description); //20 bytes
            Assert.AreEqual("SecondLab", variable2.Label); //9 bytes
            //Assert.AreEqual(true, variable2.Value);
            Assert.AreEqual(AutoManualEnum.Manual, variable2.AutoManual);
            //Assert.AreEqual(false, variable2.IsAnalog);
            //Assert.AreEqual(false, variable2.IsControl);
            Assert.AreEqual(UnitsEnum.OffOn, variable2.Units);

            var variable3 = prg.Variables[2];
            Assert.AreEqual("ThirdDescription    ", variable3.Description); //20 bytes
            Assert.AreEqual("ThirdLabe", variable3.Label); //9 bytes

            //var test = ((int)variable3.Value / 256 / 256 / 256) % 256;
            //var one = ((int) variable3.Value / 256 / 256) % 256;
            //var two = ((int)variable3.Value / 256) % 256;
            //var three = (int)variable3.Value % 256;
            //var dateTime = new TimeSpan(one, two, three);
            //Console.WriteLine($"{test}, {one}, {two}, {three}");
            //Assert.AreEqual(false, variable3.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable3.AutoManual);
            //Assert.AreEqual(false, variable3.IsAnalog);
            //Assert.AreEqual(false, variable3.IsControl);
            Assert.AreEqual(UnitsEnum.Time, variable3.Units);

            Console.WriteLine(prg.PropertiesText());
        }

        [Test]
        public void PRG_Panel11()
        {
            BaseTest("panel11.prg");
        }

        [Test]
        public void PRG_Panel2()
        {
            BaseTest("panel2.prg");
        }

        [Test]
        public void PRG_Temco()
        {
            BaseTest("temco.prg");
        }

        [Test]
        public void PRG_SelfTestRev3()
        {
            UnsupportedTest("SelfTestRev3.prg");
        }
    }
}
