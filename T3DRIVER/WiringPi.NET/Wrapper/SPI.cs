using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WiringPiNet.Wrapper
{
    public class SPI
    {
        [DllImport("libwiringPi.so", EntryPoint = "wiringPiSPIGetFd")]
        public static extern int WiringPiSPIGetFd(SPIChannels channel);

        [DllImport("libwiringPi.so", EntryPoint = "wiringPiSPIDataRW")]
        public static extern int WiringPiSPIDataRW(SPIChannels channel, byte[] data, int len);

        [DllImport("libwiringPi.so", EntryPoint = "wiringPiSPISetup")]
        public static extern int WiringPiSPISetup(SPIChannels channel, int speed);

        [DllImport("libwiringPi.so", EntryPoint = "wiringPiSPISetupMode")]
        public static extern int wiringPiSPISetupMode(SPIChannels channel, int speed, int mode);
    }
}
