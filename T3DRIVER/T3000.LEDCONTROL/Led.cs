using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;

namespace T3000.LEDS.Controls {
  /// <summary>
  /// Summary description for UserControl1.
  /// </summary>
  [DesignerCategory("Code")]
  public class Led : System.Windows.Forms.Control { 

    private Timer tick;


    public Led():base() {
      SetStyle(ControlStyles.AllPaintingInWmPaint, true);
      SetStyle(ControlStyles.DoubleBuffer, true);
      SetStyle(ControlStyles.SupportsTransparentBackColor, true);
      SetStyle(ControlStyles.UserPaint, true);
      SetStyle(ControlStyles.ResizeRedraw, true);

      BackColor = Color.Transparent;

      Width  = 17;
      Height = 17;

      tick = new Timer();
      tick.Enabled = false;
      tick.Tick += new System.EventHandler(this._Tick);
    }

    /// <summary>
    /// Constructor for colors and default pos.
    /// </summary>
    /// <param name="pColorOn">On Color</param>
    /// <param name="pColorOff">Off Color</param>
    /// <param name="px">Horizontal position</param>
    /// <param name="py">Vertical position </param>
    public Led(Color pColorOn , Color pColorOff, int px = 10, int py = 10) : this()
        {
            ColorOn = pColorOn;
            ColorOff = pColorOff;
            this.Left = px;
            this.Top = py; 
        }
    
    #region new properties
    private bool _Active = true;
    [Category("Behavior"),
    DefaultValue(true)]
    public bool Active {
      get { return _Active; }
      set { 
        _Active = value; 
        Invalidate();
      }
    }

    private Color _ColorOn = Color.Red;
    [Category("Appearance")]
    public Color ColorOn {
      get { return _ColorOn; }
      set { 
        _ColorOn = value; 
        
        Invalidate();
      }
    }

    private Color _ColorOff = SystemColors.Control;
    [Category("Appearance")]
    public Color ColorOff {
      get { return _ColorOff; }
      set { 
        _ColorOff = value; 
        Invalidate();
      }
    }


    private bool _Flash = false;
    [Category("Behavior"),
    DefaultValue(false)]
    public bool Flash {
      get { return _Flash; }
      set { 
        _Flash = value && (flashIntervals.Length>0); 
        tickIndex = 0;
        tick.Interval = flashIntervals[tickIndex];
        tick.Enabled = _Flash;
        Active = true;
      }
    }

    private string _FlashIntervals="250";
    public int [] flashIntervals = {250};
    [Category("Appearance"),
    DefaultValue("250")]
    public string FlashIntervals {
      get { return _FlashIntervals; }
      set { 
        _FlashIntervals = value; 
        string [] fi = _FlashIntervals.Split(new char[] {',','/','|',' ','\n'});
        flashIntervals = new int[fi.Length];
        for (int i=0; i<fi.Length; i++)
          try {
            flashIntervals[i] = int.Parse(fi[i]);
          } catch {
            flashIntervals[i] = 25;
          }
      }
    }

    private string _FlashColors=string.Empty; 
    public Color [] flashColors;
    [Category("Appearance"),
    DefaultValue("")]
    public string FlashColors {
      get { return _FlashColors; }
      set { 
        _FlashColors = value; 
        if (_FlashColors==string.Empty) {
          flashColors=null;
        } else {
          string [] fc = _FlashColors.Split(new char[] {',','/','|',' ','\n'});
          flashColors = new Color[fc.Length];
          for (int i=0; i<fc.Length; i++)
            try {
              flashColors[i] = (fc[i]!="")?Color.FromName(fc[i]):Color.Empty;
            } catch {
              flashColors[i] = Color.Empty;
            }
        }
      }
    }

    #endregion

    #region helper color functions
    public static Color FadeColor(Color c1, Color c2, int i1, int i2) {
      int r=(i1*c1.R+i2*c2.R)/(i1+i2); 
      int g=(i1*c1.G+i2*c2.G)/(i1+i2); 
      int b=(i1*c1.B+i2*c2.B)/(i1+i2); 

      return Color.FromArgb(r,g,b);
    }

    public static Color FadeColor(Color c1, Color c2) {
      return FadeColor(c1,c2,1,1);
    }
    #endregion

    public new event PaintEventHandler Paint;

    protected override void OnPaint(PaintEventArgs e) {
      if (null!=Paint) Paint(this,e);
      else {
        base.OnPaint(e);
//        e.Graphics.Clear(BackColor);
        if (Enabled) {
          if (Active)
            {
            e.Graphics.FillRectangle (new SolidBrush(ColorOn), 1, 1, Width - 3, Height - 3);

            //e.Graphics.FillEllipse(new SolidBrush(ColorOn),1,1,Width-3,Height-3);
            e.Graphics.DrawArc(new Pen(FadeColor(ColorOn ,Color.White,1,2),2),3,3,Width-7,Height-7,-90.0F,-90.0F);
            //e.Graphics.DrawEllipse(new Pen(FadeColor(ColorOn ,Color.White),1),1,1,Width-3,Height-3);
            e.Graphics.DrawRectangle(new Pen(FadeColor(ColorOn, Color.White), 1), 1, 1, Width - 3, Height - 3);

            }
          else
            {
            //e.Graphics.FillEllipse(new SolidBrush(ColorOff),1,1,Width-3,Height-3);
            e.Graphics.FillRectangle(new SolidBrush(ColorOff), 1, 1, Width - 3, Height - 3);
            //este efecto también queda desabilitado
            //e.Graphics.DrawArc(new Pen(FadeColor(ColorOff,Color.Black,2,1),2),3,3,Width-7,Height-7,0.0F,90.0F);
            //e.Graphics.DrawEllipse(new Pen(FadeColor(ColorOff,Color.Black),1),1,1,Width-3,Height-3);
            //e.Graphics.DrawRectangle(new Pen(FadeColor(ColorOff, Color.Black), 1), 1, 1, Width - 3, Height - 3);
            }
        }
        //else e.Graphics.DrawEllipse(new Pen(System.Drawing.SystemColors.ControlDark,1),1,1,Width-3,Height-3);
        else e.Graphics.DrawRectangle(new Pen(System.Drawing.SystemColors.ControlDark, 1), 1, 1, Width - 3, Height - 3);
            }
    }

    public int tickIndex;
    private void _Tick(object sender, System.EventArgs e) {
      tickIndex=(++tickIndex)%(flashIntervals.Length);
      tick.Interval=flashIntervals[tickIndex];
      try {
        if ((flashColors==null)||(flashColors.Length<tickIndex)||(flashColors[tickIndex]==Color.Empty))
          Active = !Active;
        else {
          ColorOn = flashColors[tickIndex];
          Active=true;
        }
      } catch {
        Active = !Active;
      }
    }

  }
}
