using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using WiringPi;

namespace T3000.I2C
{


    /**************************************************************************/
    //3 commands between BOT and TOP
    //G_TOP_CHIP_INFO  -- return information of TOP. Hardware rev and firmware rev and so on. It is not important.
    //G_ALL -- return switch status (24 * 1 bytes)and input value( 32 * 2 bytes) and high speed counter( 6 * 4bytes)
    //S_ALL -- send LED status to TOP. Communication LED( 2 bytes) + output led( 24 * 1byte) + input led( 32 * 1) + flag of high speed counter( 6 * 1)
    /***************************************************************************/
    ////Any kind of panel have same format.
    ////For BB.  // 24 outputs + 32 inputs
    ////G_ALL  switch status (24 * 1 bytes) +  input value( 32 * 2 bytes)  +  high speed counter( 6 * 4bytes)
    ////S_ALL -- Communication LED( 2 bytes) + output led( 24 * 1byte) + input led( 32 * 1) + flag of high speed counter( 6 * 1)

    ////For LB  // 10 outputs + 16 inputs
    ////G_ALL  switch status(10 * 1 bytes) + Reserved bytes(14 bytes) +  input value( 16 * 2 bytes) + Reserved bytes(32 bytes)  +  high speed counter( 6 * 4bytes)
    ////S_ALL -- Communication LED( 2 bytes) + output led( 10 * 1byte) + Reserved bytes(14 bytes) + input led( 16 * 1)  + Reserved bytes(16 bytes)  +  flag of high speed counter( 6 * 1)

    ////For TB  new ARM version, no SPI communication


    //Original File???
     enum COMMANDS
    {
        /*  send  */
        C_INITIAL = 0,

        S_OUTPUT_LED = 0x10,  /* 0x10 + 24 bytes */
        S_INPUT_LED = 0x11,   /* 0x11 + 32 bytes */
        S_HI_SP_FLAG = 0x12,    /* 0x12 + 6 bytes  */
        S_COMM_LED = 0x013,  /* 0x13 + 6 bytes  */
        S_ALL = 0x14,      //  64

        /* get */
        G_SWTICH_STATUS = 0x20, /* 0x20 + 24 bytes */
        G_INPUT_VALUE = 0x21, /* 0x21 + 64 bytes */
        G_TOP_CHIP_INFO = 0x23, /* 0x21 + 12 bytes */
        G_SPEED_COUNTER = 0x30,  // 112
        G_ALL = 0x24,

        C_MINITYPE = 0x80,
        C_ASIX_ISP = 0X81,
        C_END = 255

    };

    /*
#define 	GPIO_Pin_0   ((uint16_t)0x0001)
#define 	GPIO_Pin_1   ((uint16_t)0x0002)
#define 	GPIO_Pin_2   ((uint16_t)0x0004)
#define 	GPIO_Pin_3   ((uint16_t)0x0008)
#define 	GPIO_Pin_4   ((uint16_t)0x0010)
#define 	GPIO_Pin_5   ((uint16_t)0x0020)
#define 	GPIO_Pin_6   ((uint16_t)0x0040)
#define 	GPIO_Pin_7   ((uint16_t)0x0080)
#define 	GPIO_Pin_8   ((uint16_t)0x0100)
#define 	GPIO_Pin_9   ((uint16_t)0x0200)
#define 	GPIO_Pin_10   ((uint16_t)0x0400)
#define 	GPIO_Pin_11   ((uint16_t)0x0800)
#define 	GPIO_Pin_12   ((uint16_t)0x1000)
#define 	GPIO_Pin_13   ((uint16_t)0x2000)
#define 	GPIO_Pin_14   ((uint16_t)0x4000)
#define 	GPIO_Pin_15   ((uint16_t)0x8000)
#define 	GPIO_Pin_All   ((uint16_t)0xFFFF) */


    //enum GPIO_pins_define
    //{
    //    GPIO_Pin_0 = 0x0001,
    //    GPIO_Pin_1 = 0x0002,
    //    GPIO_Pin_2 = 0x0004,
    //    GPIO_Pin_3 = 0x0008,
    //    GPIO_Pin_4 = 0x0010,
    //    GPIO_Pin_5 = 0x0020,
    //    GPIO_Pin_6 = 0x0040,
    //    GPIO_Pin_7 = 0x0080,
    //    GPIO_Pin_8 = 0x0100,
    //    GPIO_Pin_9 = 0x0200,
    //    GPIO_Pin_10 = 0x0400,
    //    GPIO_Pin_11 = 0x0800,
    //    GPIO_Pin_12 = 0x1000,
    //    GPIO_Pin_13 = 0x2000,
    //    GPIO_Pin_14 = 0x4000,
    //    GPIO_Pin_15 = 0x8000,
    //    GPIO_Pin_All = 0xFFFF
    //}

    //enum GPIOMode_TypeDef
    //{
    //    GPIO_Mode_AIN = 0x0, GPIO_Mode_IN_FLOATING = 0x04, GPIO_Mode_IPD = 0x28, GPIO_Mode_IPU = 0x48,
    //    GPIO_Mode_Out_OD = 0x14, GPIO_Mode_Out_PP = 0x10, GPIO_Mode_AF_OD = 0x1C, GPIO_Mode_AF_PP = 0x18
    //}

    //enum GPIOSpeed_TypeDef { GPIO_Speed_10MHz = 1, GPIO_Speed_2MHz, GPIO_Speed_50MHz }

    public class WrapperI2C
    {



        static bool UsingINITEND = false;

        static int Frequency = 10000000 ; //10Mhz
        static byte TestByte = 0xA;

        public static int RunTestSPI(int Channel)
        {

            int fd;
            //Init WiringPi library
            int result = Init.WiringPiSetup();

            if (result == -1)
            {
                Debug.WriteLine("WiringPi init failed!");
                return result;
            }

            //Init WiringPi SPI library
            fd = WiringPi.SPI.wiringPiSPISetup(Channel,Frequency);


            if (fd == -1)
            {
                MessageBox.Show("SPI init failed!");
                Debug.WriteLine("SPI init failed!");
                return result;
            }

            MessageBox.Show($"SPI init completed, using channel {Channel}");
            Debug.WriteLine($"SPI init completed, using channel  {Channel}");

            result = SPIWrite(Channel);

            MessageBox.Show($"Finished");

            return 0;
        }


        /// <summary>
        /// TEST using I2C
        /// </summary>
        /// <returns></returns>
        public static int RunTestI2C(byte deviceID)
        {
            int fd;
            //Init WiringPi library
            int result = Init.WiringPiSetup();

            if (result == -1)
            {
                Debug.WriteLine("WiringPi init failed!");
                return result;
            }

            //Init WiringPi I2C library
            fd = WiringPi.I2C.wiringPiI2CSetup(deviceID);

            if (fd == -1)
            {
                MessageBox.Show("I2C init failed!");
                Debug.WriteLine("I2C init failed!");
                return result;
            }

            MessageBox.Show($"I2C init completed, using device id  {deviceID}");
            Debug.WriteLine($"I2C init completed, using device id  {deviceID}");

            result = I2CWrite(fd);

            //for (int i = 0; i < 0x0000ffff; i++)
            //{
            //    // I tried using the "fast write" command, but couldn't get it to work.  
            //    // It's not entirely obvious what's happening behind the scenes as
            //    // regards to endianness or length of data sent.  I think it's only 
            //    // sending one byte, when we really need two.
            //    //
            //    // So instead I'm doing a 16 bit register access.  It appears to 
            //    // properly handle the endianness, and the length is specified by the 
            //    // call.  The only question was the register address, which is the 
            //    // concatenation of the command (010x = write DAC output) 
            //    // and power down (x00x = power up) bits.
            //    result = WiringPi.I2C.wiringPiI2CWrite(fd,  (i & 0xfff));

            //    if (result != -1)
            //    {
            //        MessageBox.Show($"Success {(i & 0xfff)} -   {result}");
            //        Debug.WriteLine($"Success {(i & 0xfff)} -   {result}");
            //    }
            //}

            MessageBox.Show($"Finished");

            return 0;
        }


        static int I2CWrite(int fd)
        {
            int result = 0;
            if (UsingINITEND)
            {
                result = WiringPi.I2C.wiringPiI2CWrite(fd, (int)COMMANDS.C_INITIAL);
                Thread.Sleep(2000);
            }
            result = WiringPi.I2C.wiringPiI2CWrite(fd, (int) COMMANDS.S_INPUT_LED);
            for(int i = 0; i < 32; i++)
            {
                result = WiringPi.I2C.wiringPiI2CWrite(fd, TestByte);
            }
            if (UsingINITEND)
            {
                Thread.Sleep(2000);
                result = WiringPi.I2C.wiringPiI2CWrite(fd, (int)COMMANDS.C_END);
            }
            return result;
        }


        unsafe static int SPIWrite(int Channel)
        {
            int result = 0;

            byte* buffer = stackalloc byte[128];
            int Len = 65;

            result = SPI.wiringPiSPIDataRW(Channel, buffer, 32);

            if (UsingINITEND)
            {
                buffer[0] = (byte)COMMANDS.C_INITIAL;
                result = SPI.wiringPiSPIDataRW(Channel, buffer, 1);
                Thread.Sleep(2000); 
            }

            buffer[0] = (byte)COMMANDS.S_ALL;
            for (int i = 0; i < 64; i++)
            {
                buffer[1 + i] = (byte)TestByte;
            }

            result = SPI.wiringPiSPIDataRW(Channel, buffer , Len);
           

            if (UsingINITEND)
            {
                Thread.Sleep(2000);
                buffer[0] = (byte)COMMANDS.C_END;
                result = SPI.wiringPiSPIDataRW(Channel, buffer, 1);
                Thread.Sleep(2000); 

            }
            

            return result;
        }

        ////For all the following functions, if the return value is negative then an error has happened and you should consult errno.

        ////int wiringPiI2CRead(int fd);
        ////Simple device read.Some devices present data when you read them without having to do any register transactions.

        ////int wiringPiI2CWrite(int fd, int data);
        ////Simple device write.Some devices accept data this way without needing to access any internal registers.

        ////int wiringPiI2CWriteReg8(int fd, int reg, int data);
        ////int wiringPiI2CWriteReg16(int fd, int reg, int data);
        ////These write an 8 or 16-bit data value into the device register indicated.


        ////int wiringPiI2CReadReg8 (int fd, int reg) ;
        ////int wiringPiI2CReadReg16(int fd, int reg);
        ////These read an 8 or 16-bit value from the device register indicated.







    }
}
