using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace T3000.I2C
{
    public partial class TestI2C : Form
    {
        public TestI2C()
        {
            InitializeComponent();
        }

        private void TestSPI_Load(object sender, EventArgs e)
        {
            //numSpeed.Value = 50000000;
        }

        private void cmdStartSPITest_Click(object sender, EventArgs e)
        {
            I2C.WrapperI2C.RunTestSPI(0);
            I2C.WrapperI2C.RunTestSPI(1);
            I2C.WrapperI2C.RunTestI2C(0x51);

        }

    }
}
