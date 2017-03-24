using System.Drawing;

namespace T3000.Utilities
{
    using System.Windows.Forms;

    public class BaseForm : Form
    {
        public override Font Font { get; set; } = SystemFonts.CaptionFont;
    }
}
