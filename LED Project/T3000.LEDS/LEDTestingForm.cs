using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using T3000.LEDS.Controls;

namespace T3000.LEDS
{
    public partial class LEDTestingForm : Form
    {
        List<Led> INS = new List<Led>(); //32
        List<Led> AOUT = new List<Led>(); //12
        List<Led> DOUT = new List<Led>(); //12


        public LEDTestingForm()
        {
            InitializeComponent();
        }


        const int VERT_SPACER = 11;//VERTICAL SPACER
        const int LED_W = 20; // WITH OF LEDS
        const int LED_H = 8; // HEIGHT OF LEDS


        private void LEDTestingForm_Load(object sender, EventArgs e)
        {
            int x = 201, y=135;
            double realx = x;
            double realy = y;
            Color DeactivatedColor = Color.FromArgb(100, 31, 28, 70);
            Color ActivatedColor = Color.LightGreen;
            //Add INPUTS LEDs
            for (int i = 1; i <= 32; i++)
            {

                Led newLed = new Led(ActivatedColor, DeactivatedColor, x, y);
                newLed.Width = LED_W;
                newLed.Height = LED_H;
                newLed.Name = $"IN[{i}]";
                //newLed.Flash = i % 3 == 0 ? true : false;
                newLed.Active = i % 2 == 0 ? true : false;
                newLed.Active = false;

                INS.Add(newLed);
                comboBox1.Items.Add($"IN[{i}]");
                
                
                y += LED_H + VERT_SPACER;
                y = i % 3 == 0 ? y - 1 : y;

            }
            this.Controls.AddRange(INS.ToArray());

            x = 409; y = 135;
            //Add Digital Output LEDs
            for (int i = 1; i <= 12; i++)
            {
                Led newLed = new Led(ActivatedColor, DeactivatedColor, x, y);
                newLed.Width = LED_W;
                newLed.Height = LED_H;
                newLed.Name = $"DO[{i}]";
                //newLed.Flash = i % 3 == 0 ? true : false;
                //newLed.Active = i % 2 == 0 ? true : false;
                newLed.Active = true;
                AOUT.Add(newLed);
                comboBox1.Items.Add($"DO[{i}]");

                y += LED_H + VERT_SPACER;
                y = i % 3 == 0 ? y - 1 : y;

            }
            this.Controls.AddRange(AOUT.ToArray());

           

            y= y - (LED_H + VERT_SPACER) + 23;
           

            //Add Analog Output LEDs
            for (int i = 1; i <= 12; i++)
            {
                Led newLed = new Led(ActivatedColor, DeactivatedColor, x, y);
                newLed.Width = LED_W;
                newLed.Height = LED_H;

                newLed.Flash = i % 3 == 0 ? true : false;
                newLed.Active = i % 2 == 0 ? true : false;
                newLed.Name = $"AO[{i}]";

                DOUT.Add(newLed);
                comboBox1.Items.Add($"AO[{i}]");


                y += LED_H + VERT_SPACER;
                y = i % 3 == 0 ? y - 2 : y;

            }
            
            this.Controls.AddRange(DOUT.ToArray());

            comboBox1.MaxDropDownItems = 5;
        }

        private void chkONOFF_CheckedChanged(object sender, EventArgs e)
        {
            if(comboBox1.SelectedText == null) { return; }
            string objName = comboBox1.SelectedItem.ToString();
            var TestLed = (Led)Controls[Controls.IndexOfKey(objName)];
            if(TestLed.Flash) TestLed.Flash = false;
          
            TestLed.Active = !TestLed.Active;
            
        }

        private void DimPercent_ValueChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedText == null) { return; }
            string objName = comboBox1.SelectedItem.ToString();
            var TestLed = (Led)Controls[Controls.IndexOfKey(objName)];
            if (TestLed.Flash) TestLed.Flash = false;
            TestLed.Active = true;
            var factor = DimPercent.Value / 100;
            if (TestLed.Tag == null) TestLed.Tag = TestLed.ColorOn.ToArgb();
            Color c1 = Color.FromArgb((int)TestLed.Tag);
            Color c2 = Color.FromArgb((int) (c1.A),
        (int)(c1.R * factor), (int)(c1.G * factor), (int)(c1.B * factor));
            TestLed.ColorOn = c2;
        }
    }
}
