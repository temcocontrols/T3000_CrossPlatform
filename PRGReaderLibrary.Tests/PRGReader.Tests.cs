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
        public void Read_Asy1()
        {
            var originalFile = GetFullPath("asy1.prg");
            var prg = PRG.Load(originalFile);

            var temp = Path.GetTempFileName();
            prg.Save(temp);
            Assert.IsTrue(FileUtilities.FilesIsEquals(originalFile, temp));

            prg = PRG.Load(temp);
            prg.Variables[0].Units = UnitsEnum.CoolHeat;
            prg.Save(temp);
            Assert.IsFalse(FileUtilities.FilesIsEquals(originalFile, temp));

            Console.WriteLine(prg.PropertiesText());
        }

        [Test]
        public void Read_Balsam2()
        {
            //Unsupported
            try
            {
                var prg = PRG.Load(GetFullPath("balsam2.prg"));

                Console.WriteLine(prg.PropertiesText());
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
        }

        [Test]
        public void Read_90185()
        {
            //Unsupported
            try
            {
                var prg = PRG.Load(GetFullPath(@"90185.prg"));

                Console.WriteLine(prg.PropertiesText());
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
        }

        [Test]
        public void Read_Panel1()
        {
            var prg = PRG.Load(GetFullPath("panel1.prg"));

            PrintVariables(prg);
            Console.WriteLine(prg.PropertiesText());
        }

        [Test]
        public void Read_TestVariables()
        {
            var prg = PRG.Load(GetFullPath("testvariables.prg"));

            PrintVariables(prg);

            var variable1 = prg.Variables[0];
            Assert.AreEqual("FirstDescription    \0", variable1.Description); //20 bytes  
            Assert.AreEqual("FirstLabe", variable1.Label); //9 bytes
            //Assert.AreEqual(5000, variable1.Value);
            Assert.AreEqual(AutoManualEnum.Automatic, variable1.AutoManual);
            //Assert.AreEqual(false, variable1.IsAnalog);
            //Assert.AreEqual(false, variable1.IsControl);
            Assert.AreEqual(UnitsEnum.degC, variable1.Units);

            var variable2 = prg.Variables[1];
            Assert.AreEqual("SecondDescription   \0", variable2.Description); //20 bytes
            Assert.AreEqual("SecondLab", variable2.Label); //9 bytes
            //Assert.AreEqual(true, variable2.Value);
            Assert.AreEqual(AutoManualEnum.Manual, variable2.AutoManual);
            //Assert.AreEqual(false, variable2.IsAnalog);
            //Assert.AreEqual(false, variable2.IsControl);
            Assert.AreEqual(UnitsEnum.OffOn, variable2.Units);

            var variable3 = prg.Variables[2];
            Assert.AreEqual("ThirdDescription    \0", variable3.Description); //20 bytes
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
        public void Read_Panel11()
        {
            var prg = PRG.Load(GetFullPath("panel11.prg"));

            Console.WriteLine(prg.PropertiesText());
        }

        [Test]
        public void Read_Panel2()
        {
            var prg = PRG.Load(GetFullPath("panel2.prg"));

            Console.WriteLine(prg.PropertiesText());
        }

        [Test]
        public void Read_Temco()
        {
            var prg = PRG.Load(GetFullPath("temco.prg"));

            Console.WriteLine(prg.PropertiesText());
        }

        [Test]
        public void Read_SelfTestRev3()
        {
            //Unsupported
            try
            {
                var prg = PRG.Load(GetFullPath("SelfTestRev3.prg"));

                Console.WriteLine(prg.PropertiesText());
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
        }
    }
}
