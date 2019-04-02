using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FileLog;
using T3000.DRIVER;
using WiringPiNet;

namespace TestDriver
{
    class Program
    {

        static void Main(string[] args)
        {
            Test tester = new Test();
            tester.TestSetup(); //Test Passed!!!
            
            //tester.TestClock(); //Test Passed!!!

            //tester.TestInterrupts(); //Test Passed!!! There will be a file lock on log.txt due to concurrent write operations by IRQHandler5

            tester.TestSPI(); //Test passed!! SPI1 is open, test SPI Commands passed!!

            //tester.TestSPI2(); //Test passed!!! with interrupts and SPI Commands

            //tester.TestSPI3();

            //tester.TestI2C();


            return;


        }




    }
}
