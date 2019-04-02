using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WiringPiNet;
using WiringPiNet.Wrapper;
using T3000.DRIVER;


namespace TestDriver
{
    class Test
    {
        public RPIDriver rpi;

        public void TestSetup()
        {
            rpi = new RPIDriver();
            Console.WriteLine(rpi.ReadAllPins());

            rpi.Log.Add("PiBoard rev. = " + WiringPi.PiBoardRev().ToString());
            //Test GPIO readall

            Console.WriteLine(rpi.ReadAllPins());

        }

        public void TestClock()
        {
            rpi.StartGPIOClock();
            rpi.StartWatcher();
            WiringPi.Delay(1000);
            rpi.StopGPIOClock();
            rpi.StopWatcher();

        }

        public void TestPWM()
        {
            rpi.SetDefaultAOControl();
            for (int i = 1; i <= 5; i++)
            {
                for (int j = 1; j >= 0; j--)
                {
                    rpi.Log.Add($"{((AOPinConfig)i).ToString()} {j}");
                    rpi.SetAOControlValues((AOPinConfig)i, (j == 1 ? true : false)); //see if OUT13 blinks
                    //TestI2C();
                }

            }

        }



        public void TestInterrupts()
        {
            rpi.StopGPIOClock();

            rpi.SetInterrupt();
            rpi.StartGPIOClock();
            WiringPi.Delay(2000); //Let see how many times interrupts in a second.
            rpi.StopGPIOClock();
        }

        internal void TestOutputsGPIO()
        {



        }


        /// <summary>
        /// SPI test polling and watching pin 28
        /// </summary>
        public void TestSPI()
        {
            rpi.SPIx = SPIChannels.SPI1;

            rpi.StartSPI();
            rpi.SPICommand = (byte)T3Commands.G_ALL;
            rpi.StartWatcher();
            
            Console.WriteLine("Here in TestSPI");
            //rpi.SetInterrupt();

            string chain = "";


            for (int i = 0; i < 500; i++)
            {

                chain += $"SW = {rpi.Log.PrintBytes(rpi.SPIRXBuffer)}";


                //////rpi.IRQHandler();
                ////chain = $"SW = {rpi.Log.PrintBytes(rpi.Switch_Status)}";
                ////rpi.Log.Add(chain);
                ////chain = $"AD = {rpi.Log.PrintBytes(rpi.inputs)}";
                ////rpi.Log.Add(chain);
                ////chain = $"HSC = {rpi.Log.PrintBytes(rpi.high_speed_counter)}";
                ////rpi.Log.Add(chain);

                Console.WriteLine("******{0}*****", i + 1);

            }

            rpi.Log.Add(chain);

            rpi.StopWatcher();
            //rpi.Log.Add("switches \r\n" + rpi.OutputChain);
        }


        /// <summary>
        /// SPI test based or Interrupts
        /// </summary>
        public void TestSPI2()
        {
            rpi.SPIx = SPIChannels.SPI1;

            if(!rpi.SPIConnected)
                rpi.StartSPI();

            rpi.SPICommand = (byte)T3Commands.G_ALL;
            rpi.SPIRXBuffer = new byte[120];
            rpi.SetInterrupt();

            rpi.StartGPIOClock();
            string chain = "";


            for (int i = 0; i < 5; i++)
            {

                chain = $"SPIRX = {rpi.Log.PrintBytes(rpi.SPIRXBuffer)}";
                rpi.Log.Add(chain);
                Console.WriteLine("******{0}*****", i + 1);

            }
            rpi.StopGPIOClock();


            //rpi.Log.Add("Final Values are:");
            //chain = rpi.PrintSwitchesStatus();
            //rpi.Log.Add(chain);
            //chain = $"AD = {rpi.Log.PrintBytes(rpi.inputs)}";
            //rpi.Log.Add(chain);
            //chain = $"HSC = {rpi.Log.PrintBytes(rpi.high_speed_counter)}";
            //rpi.Log.Add(chain);

            //var outstr = "cat log.txt".Bash();


            //rpi.Log.Add("switches \r\n" + rpi.OutputChain);
        }



        /// <summary>
        /// Only 0x23 and 0x24 are returning values
        /// </summary>
        public void TestSPI3()
        {
            rpi.SPIx = SPIChannels.SPI1;

            if(!rpi.SPIConnected)
                rpi.StartSPI();


            for (byte cmd = 0x01; cmd < 0xFF; cmd++)
            {
                byte[] buffer = new byte[120];
                buffer[0] = cmd;
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("0x" + buffer[0].ToString("X2") + " ");
                Console.ForegroundColor = ConsoleColor.White;
                for (int i = 0; i < 120; i++)
                {

                    SPI.WiringPiSPIDataRW(rpi.SPIx, buffer, 1);
                    if (buffer[0] != 0xAA)
                        Console.ForegroundColor = ConsoleColor.Green;
                    Console.Write("0x" + buffer[0].ToString("X2") + " ");
                    Console.ForegroundColor = ConsoleColor.White;
                    buffer[0] = 0;

                }
                Console.WriteLine();
            }



            ////buffer[0] = (byte)T3Commands.S_ALL;
            ////Console.ForegroundColor = ConsoleColor.Blue;
            ////Console.WriteLine("S_ALL");
            ////Console.ForegroundColor = ConsoleColor.White;
            ////Console.Write("0x" + buffer[0].ToString("X2") + " ");
            ////for (int i = 0; i < 10; i++)
            ////{

            ////    SPI.WiringPiSPIDataRW(rpi.SPIx, buffer, 300);
            ////    if (buffer[0] == 0x55)
            ////        Console.ForegroundColor = ConsoleColor.Magenta;
            ////    //Console.Write("0x" + buffer[0].ToString("X2") + " ");
            ////    Console.Write(rpi.Log.PrintBytes(buffer));
            ////    Console.ForegroundColor = ConsoleColor.White;
            ////    buffer[0] = (byte) T3Commands.S_ALL;

            ////}
            ////Console.WriteLine();

            ////buffer[0] = (byte)T3Commands.G_TOP_CHIP_INFO;
            ////Console.WriteLine("G_TOP_CHIP_INFO");
            ////Console.Write("0x" + buffer[0].ToString("X2") + " ");
            ////for (int i = 0; i < 120; i++)
            ////{

            ////    SPI.WiringPiSPIDataRW(rpi.SPIx, buffer, 1);
            ////    Console.Write("0x" + buffer[0].ToString("X2") + " ");
            ////    buffer[0] = 0;

            ////}
            ////Console.WriteLine();

            ////buffer[0] = (byte)T3Commands.C_MINITYPE;
            ////Console.WriteLine("C_MINITYPE");
            ////Console.Write("0x" + buffer[0].ToString("X2") + " ");
            ////for (int i = 0; i < 120; i++)
            ////{

            ////    SPI.WiringPiSPIDataRW(rpi.SPIx, buffer, 1);
            ////    Console.Write("0x" + buffer[0].ToString("X2") + " ");
            ////    buffer[0] = 0;

            ////}
            ////Console.WriteLine();

        }


        public void TestI2C()
        {
            try
            {
                rpi.SetupI2C(0x51);

                //for (int i = 0; i < 0x0000FFFF; i++)
                //{
                //    I2C.WiringPiI2CWriteReg16(rpi.I2CFD, 0x60, i & 0x00FF);
                //}

                //I2C.WiringPiI2CWriteReg16(rpi.I2CFD, 0xC1, 0x020F);
                //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg8(rpi.I2CFD, 0xC0, 0x020F).ToString("X2"));
                //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg8(rpi.I2CFD, 0xC1, 0x020F).ToString("X2"));
                //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg16(rpi.I2CFD, 0xC0, 0x030C).ToString("X2"));
                //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg16(rpi.I2CFD, 0xC1, 0x030C).ToString("X2"));

                //I2C.WiringPiI2CWrite(rpi.I2CFD, 0x02);
                //I2C.WiringPiI2CWrite(rpi.I2CFD, 0xFF);
                //I2C.WiringPiI2CWrite(rpi.I2CFD, 0x03);
                //I2C.WiringPiI2CWrite(rpi.I2CFD, 0x0F);

                int i = 0xC1;
                I2C.WiringPiI2CWriteReg16(rpi.I2CFD, i, 0x02FF);
                //I2C.WiringPiI2CWriteReg16(rpi.I2CFD, i, 0xFF);
                I2C.WiringPiI2CWriteReg16(rpi.I2CFD, i, 0x030C);
                //I2C.WiringPiI2CWriteReg16(rpi.I2CFD, i, 0x0C);



                //for (i = 0; i < 32; i++)
                //{
                //    Console.Write("0x" + I2C.WiringPiI2CRead(rpi.I2CFD).ToString("X2") + ",");
                //    //Console.Write("0x" + I2C.wiringPiI2CReadReg16(rpi.I2CFD,0xC0).ToString("X4") + ",");
                //    //Console.Write("0x" + I2C.WiringPiI2CReadReg8(rpi.I2CFD, 0xC0).ToString("X4") + ",");
                //    //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg8(rpi.I2CFD, 0xC0, 0x00).ToString("X2"));
                //    //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg8(rpi.I2CFD, 0xC1, 0x00).ToString("X2"));
                //    //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg16(rpi.I2CFD, 0xC0, 0x030C).ToString("X2"));
                //    //rpi.Log.Add("0x" + I2C.WiringPiI2CWriteReg16(rpi.I2CFD, 0xC1, 0x030C).ToString("X2"));
                //}



            }
            catch (Exception ex)
            {

                throw ex;
            }
        }
    }
}
