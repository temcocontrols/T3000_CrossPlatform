namespace T3000.Controls
{
    using System.Drawing;
    using System.Windows.Forms;

    public class TLockCheckBox : CheckBox
    {
        public Image LockedImage { get; set; }
        public Image UnlockedImage { get; set; }

        protected override void OnPaint(PaintEventArgs pevent)
        {
            var image = Checked ? UnlockedImage : LockedImage;
            if (image == null)
            {
                base.OnPaint(pevent);
                return;
            }

            pevent.Graphics.Clear(Parent.BackColor);
            pevent.Graphics.DrawImage(image, ClientRectangle);
        }
    }
}
