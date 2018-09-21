using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WiringPiNet.Wrapper
{
    public class Shift
    {

        [DllImport("libwiringPi.so", EntryPoint = "shiftIn")]
        public static extern IntPtr ShiftIn(IntPtr dPin, IntPtr cPin, IntPtr order);

        [DllImport("libwiringPi.so", EntryPoint = "shiftOut")]
        public static extern IntPtr ShiftOut(IntPtr dPin, IntPtr cPin, IntPtr order, IntPtr val);
    }
}
