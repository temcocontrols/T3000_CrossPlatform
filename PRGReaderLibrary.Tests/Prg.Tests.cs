namespace PRGReaderLibrary.Tests
{
    using NUnit.Framework;
    using System;
    using System.IO;

    [TestFixture]
    [Category("PRGReaderLibrary.Prg")]
    public class Prg_Tests
    {
        public void VariableVariantToFromTest(VariableValue value, CustomUnits customUnits)
        {
            var tempValue = new VariableValue(value.ToString(), value.Unit, customUnits, value.MaxRange);
            ObjectAssert.AreEqual(value, tempValue,
                $@"Variable value toFrom string test failed.
Value.ToString(): {value.ToString()}
Value.ToFromToString(): {tempValue.ToString()}
");
        }

        public int GetDifferOffset(Exception exception)
        {
            var text = exception.Message;
            var atOffset = "at offset ";
            var offsetIndex = exception.Message.IndexOf(atOffset);
            var offsetString = exception.Message.Substring(offsetIndex + atOffset.Length,
                text.Length - offsetIndex - atOffset.Length);
            var pointIndex = offsetString.IndexOf(".");
            offsetString = offsetString.Substring(0, pointIndex);

            return int.Parse(offsetString);
        }

        public void BaseTest(string name)
        {
            var path = TestUtilities.GetFullPathForPrgFile(name);
            var prg = Prg.Load(path,null);

            var temp = Path.GetTempFileName();

            //Test variables binary load/save compatible

            //Bit to bit compatible supported only for current version
            if (prg.FileVersion == FileVersion.Current)
            {
                foreach (var input in prg.Inputs)
                {
                    VariableVariantToFromTest(input.Value, prg.CustomUnits);

                    ObjectAssert.AreEqual(input, new InputPoint(input.ToBytes()),
                       $"{nameof(input)} ToFromBytes test failed.");
                }

                foreach (var output in prg.Outputs)
                {
                    VariableVariantToFromTest(output.Value, prg.CustomUnits);

                    ObjectAssert.AreEqual(output, new OutputPoint(output.ToBytes()),
                        $"{nameof(output)} ToFromBytes test failed.");
                }

                foreach (var variable in prg.Variables)
                {
                    VariableVariantToFromTest(variable.Value, prg.CustomUnits);

                    ObjectAssert.AreEqual(variable, new VariablePoint(variable.ToBytes()),
                        $"{nameof(variable)} ToFromBytes test failed.");
                }

                foreach (var program in prg.Programs)
                {
                    ObjectAssert.AreEqual(program, new ProgramPoint(program.ToBytes()),
                        $"{nameof(program)} ToFromBytes test failed.");
                }

                foreach (var controller in prg.Controllers)
                {
                    ObjectAssert.AreEqual(controller, new ControllerPoint(controller.ToBytes()),
                        $"{nameof(controller)} ToFromBytes test failed.");
                }

                foreach (var screen in prg.Screens)
                {
                    ObjectAssert.AreEqual(screen, new ScreenPoint(screen.ToBytes()),
                        $"{nameof(screen)} ToFromBytes test failed.");
                }

                foreach (var graphic in prg.Graphics)
                {
                    ObjectAssert.AreEqual(graphic, new GraphicPoint(graphic.ToBytes()),
                        $"{nameof(graphic)} ToFromBytes test failed.");
                }

                foreach (var user in prg.Users)
                {
                    ObjectAssert.AreEqual(user, new UserPoint(user.ToBytes()),
                        $"{nameof(user)} ToFromBytes test failed.");
                }

                foreach (var unit in prg.CustomUnits.Digital)
                {
                    ObjectAssert.AreEqual(unit, new CustomDigitalUnitsPoint(unit.ToBytes()),
                        $"{nameof(unit)} ToFromBytes test failed.");
                }

                foreach (var table in prg.Tables)
                {
                    ObjectAssert.AreEqual(table, new TablePoint(table.ToBytes()),
                        $"{nameof(table)} ToFromBytes test failed.");
                }

                {
                    var settings = prg.Settings;
                    ObjectAssert.AreEqual(settings, new Settings(settings.ToBytes()),
                        $"{nameof(settings)} ToFromBytes test failed.");
                }

                foreach (var schedule in prg.Schedules)
                {
                    ObjectAssert.AreEqual(schedule, new SchedulePoint(schedule.ToBytes()),
                        $"{nameof(schedule)} ToFromBytes test failed.");
                }

                foreach (var holiday in prg.Holidays)
                {
                    ObjectAssert.AreEqual(holiday, new HolidayPoint(holiday.ToBytes()),
                        $"{nameof(holiday)} ToFromBytes test failed.");
                }

                foreach (var monitor in prg.Monitors)
                {
                    ObjectAssert.AreEqual(monitor, new MonitorPoint(monitor.ToBytes()),
                        $"{nameof(monitor)} ToFromBytes test failed.");
                }

                foreach (var code in prg.ScheduleCodes)
                {
                    ObjectAssert.AreEqual(code, new ScheduleCode(code.ToBytes(), 0),
                        $"{nameof(code)} ToFromBytes test failed.");
                }

                foreach (var code in prg.HolidayCodes)
                {
                    ObjectAssert.AreEqual(code, new HolidayCode(code.ToBytes(), 0),
                        $"{nameof(code)} ToFromBytes test failed.");
                }

                foreach (var code in prg.ProgramCodes)
                {
                    //Currently unsupported
                    //ObjectAssert.AreEqual(code, new ProgramCode(code.ToBytes(), 0),
                    //    $"{nameof(code)} ToFromBytes test failed.");
                }

                foreach (var units in prg.CustomUnits.Analog)
                {
                    ObjectAssert.AreEqual(units, new CustomAnalogUnitsPoint(units.ToBytes()),
                        $"{nameof(units)} ToFromBytes test failed.");
                }
            }

            prg.Save(temp);
            try
            {
                FileAssert.AreEqual(path, temp,
                    $@"Name: {name}. 
See console log for details.
");
            }
            catch (Exception exception)
            {
                var offset = GetDifferOffset(exception);
                Console.WriteLine(DebugUtilities.CompareBytes(File.ReadAllBytes(path),
                    prg.ToBytes(), offset - 35, 70, onlyDif: false, toText: true));
                throw;
            }

            if (prg.Variables.Count > 0)
            {
                prg = Prg.Load(temp,null);
                prg.Variables[0].Value = new VariableValue("9998.8999", Unit.DegreesC);
                prg.Save(temp);
                FileAssert.AreNotEqual(path, temp);
            }

            //Additional check for upgrade to current
            if (prg.FileVersion != FileVersion.Current)
            {
                prg.Upgrade(FileVersion.Current);
                prg.Save(temp);
                prg = Prg.Load(temp,null);
                Assert.AreEqual(FileVersion.Current, prg.FileVersion);
            }
        }

        public void UnsupportedTest(string name)
        {
            var exception = Assert.Catch(() =>
            {
                var prg = Prg.Load(TestUtilities.GetFullPathForPrgFile(name),null);

                Console.WriteLine(prg.PropertiesText());
            });
            Console.WriteLine(exception.Message);
        }

        [Test]
        public void Prg_BTUMeter()
        {
            var path = TestUtilities.GetFullPathForPrgFile("BTUMeter.prg");
            var prg = Prg.Load(path,null);

            ObjectAssert.AreEqual(new CustomDigitalUnitsPoint(false, "TANK1", "TANK2"), prg.CustomUnits.Digital[0]);

            //Inputs
            {
                //IN1
                var expected = new InputPoint
                {
                    Description = "TANK2 TOP",
                    AutoManual = AutoManual.Automatic,
                    Value = new VariableValue(0.683, Unit.PercentsVolts5),
                    CalibrationH = 0.0,
                    CalibrationL = 0.0,
                    CalibrationSign = Sign.Negative,
                    Control = OffOn.On,
                    CustomUnits = null,
                    DigitalAnalog = DigitalAnalog.Analog,
                    FileVersion = FileVersion.Rev6,
                    Filter = 1,
                    Status = InputStatus.Normal,
                    Jumper = Jumper.To5V,
                    Label = "T2_TOP",
                    SubNumber = 0.1,
                    //Decom = 32
                };
                ObjectAssert.AreEqual(expected, prg.Inputs[0]);

                //IN2
                expected = new InputPoint
                {
                    Description = "TANK2 BOT",
                    AutoManual = AutoManual.Automatic,
                    Value = new VariableValue(true, Unit.LowHigh, null, 1000),
                    CalibrationH = 0.0,
                    CalibrationL = 0.0,
                    CalibrationSign = Sign.Negative,
                    Control = OffOn.On,
                    CustomUnits = null,
                    DigitalAnalog = DigitalAnalog.Digital,
                    FileVersion = FileVersion.Rev6,
                    Filter = 1,
                    Status = InputStatus.Normal,
                    Jumper = Jumper.Thermistor,
                    Label = "T2_BOT",
                    SubNumber = 0.1
                };
                ObjectAssert.AreEqual(expected, prg.Inputs[1]);

                //IN3
                expected = new InputPoint
                {
                    Description = "IN 3",
                    AutoManual = AutoManual.Automatic,
                    Value = new VariableValue(19.824, Unit.Psi20),
                    CalibrationH = 0.0,
                    CalibrationL = 0.0,
                    CalibrationSign = Sign.Negative,
                    Control = OffOn.On,
                    CustomUnits = null,
                    DigitalAnalog = DigitalAnalog.Analog,
                    FileVersion = FileVersion.Rev6,
                    Filter = 32,
                    Status = InputStatus.Normal,
                    Jumper = Jumper.Thermistor,
                    Label = "IN3",
                    SubNumber = 0.1
                };
                ObjectAssert.AreEqual(expected, prg.Inputs[2]);
            }

            //Outputs
            {
                //OUT1
                var expected = new OutputPoint()
                {
                    Description = "VALVE LEFT",
                    AutoManual = AutoManual.Manual,
                    HwSwitchStatus = SwitchStatus.Auto,
                    Value = new VariableValue(true, Unit.OffOn, null, 1000),
                    LowVoltage = 0,
                    HighVoltage = 0,
                    PwmPeriod = 0,
                    Control = OffOn.On,
                    CustomUnits = null,
                    DigitalAnalog = DigitalAnalog.Digital,
                    FileVersion = FileVersion.Rev6,
                    Label = "VAL_LEFT",
                    SubNumber = 0.1
                };
                ObjectAssert.AreEqual(expected, prg.Outputs[0]);

                //OUT2
                expected = new OutputPoint()
                {
                    Description = "VALVE RIGHT",
                    AutoManual = AutoManual.Automatic,
                    HwSwitchStatus = SwitchStatus.Auto,
                    Value = new VariableValue(true, Unit.OffOn, null, 1000),
                    LowVoltage = 0,
                    HighVoltage = 0,
                    PwmPeriod = 0,
                    Control = OffOn.On,
                    CustomUnits = null,
                    DigitalAnalog = DigitalAnalog.Digital,
                    FileVersion = FileVersion.Rev6,
                    Label = "VAL_RIT",
                    SubNumber = 0.1
                };
                ObjectAssert.AreEqual(expected, prg.Outputs[1]);
            }

            //Variables
            {
                //VAR1
                var expected = new VariablePoint()
                {
                    Description = "START TEST FLAG",
                    AutoManual = AutoManual.Automatic,
                    Value = new VariableValue(false, Unit.OffOn, null, 1000),
                    Control = OffOn.Off,
                    DigitalAnalog = DigitalAnalog.Digital,
                    FileVersion = FileVersion.Rev6,
                    Label = "INIT"
                };
                ObjectAssert.AreEqual(expected, prg.Variables[0]);

                //VAR10
                expected = new VariablePoint()
                {
                    Description = "NOW FILLING",
                    AutoManual = AutoManual.Automatic,
                    Value = new VariableValue(false, Unit.CustomDigital1, null, 2000),
                    Control = OffOn.Off,
                    DigitalAnalog = DigitalAnalog.Digital,
                    FileVersion = FileVersion.Rev6,
                    Label = "FILLTANK",
                };
                ObjectAssert.AreEqual(expected, prg.Variables[9]);
            }

            //Program codes
            {
                //var expected = new ProgramCode()
                //{
                //    Code = new byte[2000],
                //    FileVersion = FileVersion.Rev6
                //};
                //ObjectAssert.AreEqual(expected, prg.ProgramCodes[0]);

                //Console.WriteLine(prg.ProgramCodes[0].PropertiesText());
                //foreach (var line in prg.ProgramCodes[0].Lines)
                //{
                //Console.WriteLine(line.GetString());
                //}

                //Console.WriteLine(DebugUtilities.CompareBytes(prg.ProgramCodes[0].Code,
                //    prg.ProgramCodes[0].Code, onlyDif: false));
            }
        }

        public void BaseProgramCodeTest(string path, ProgramCode code)
        {
            var expectedCode = File.ReadAllText(
                TestUtilities.GetFullPathForProgramCodeFile(path));
            
            //Console.WriteLine(DebugUtilities.CompareBytes(code.Code, code.Code, 0, 0, false, false, false));
            File.WriteAllBytes("D:/code.code", code.Code);

            var lines = expectedCode.ToLines();
            for (var i = 0; i < lines.Count && i < code.Lines.Count; ++i)
            {
                var line = code.Lines[i];

                Assert.AreEqual(10 * (i + 1), line.Number, "Line numbers not equals");
                Assert.AreEqual(lines[i], line.ToString(), $"Line {i} not equals");
            }
        }

        [Test]
        public void Prg_TemcoPanelRev6()
        {
            #region TestData

            var path = TestUtilities.GetFullPathForPrgFile("BTUMeter.prg");
            var prg = Prg.Load(path,null);

            #endregion

            //Program codes
            BaseProgramCodeTest("BTUMeter1.txt", prg.ProgramCodes[0]);
            //BaseProgramCodeTest("BTUMeter3.txt", prg.ProgramCodes[2]);
            //BaseProgramCodeTest("BTUMeter4.txt", prg.ProgramCodes[3]);
            //BaseProgramCodeTest("BTUMeter5.txt", prg.ProgramCodes[4]);
        }

        [Test]
        public void Prg_BaseTests()
        {
            //Rev6
            BaseTest("BTUMeter.prg");
            BaseTest("CustomAnalogRev6.prg");
            BaseTest("TemcoPanelRev6.prg");
            BaseTest("T3DemoRev6.prg");

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
            var prg = Prg.Load(TestUtilities.GetFullPathForPrgFile("testvariables.prg"),null);

            var variable1 = prg.Variables[0];
            Assert.AreEqual("FirstDescription    ", variable1.Description);
            Assert.AreEqual("FirstLabe", variable1.Label);
            Assert.AreEqual(new VariableValue(5.0, Unit.DegreesC), variable1.Value);
            Assert.AreEqual(AutoManual.Automatic, variable1.AutoManual);
            Assert.AreEqual(DigitalAnalog.Analog, variable1.DigitalAnalog);
            Assert.AreEqual(OffOn.Off, variable1.Control);

            var variable2 = prg.Variables[1];
            Assert.AreEqual("SecondDescription   ", variable2.Description);
            Assert.AreEqual("SecondLab", variable2.Label);
            ObjectAssert.AreEqual(new VariableValue("On", Unit.OffOn).Value, variable2.Value.Value);
            Assert.AreEqual(AutoManual.Manual, variable2.AutoManual);
            Assert.AreEqual(DigitalAnalog.Digital, variable2.DigitalAnalog);
            Assert.AreEqual(OffOn.Off, variable2.Control);

            var variable3 = prg.Variables[2];
            Assert.AreEqual("ThirdDescription    ", variable3.Description);
            Assert.AreEqual("ThirdLabe", variable3.Label);
            Assert.AreEqual(new VariableValue(new TimeSpan(0, 22, 22, 22, 0), Unit.Time), variable3.Value);
            Assert.AreEqual(AutoManual.Automatic, variable3.AutoManual);
            Assert.AreEqual(DigitalAnalog.Analog, variable3.DigitalAnalog);
            Assert.AreEqual(OffOn.Off, variable3.Control);
        }
    }
}
