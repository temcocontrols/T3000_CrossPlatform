namespace T3000
{
    using System.Drawing;

    class ColorConstants
    {
        //Change to SystemColors.Window for disable valid color
        public static readonly Color ValidColor = Color.LightGreen;
        public static readonly Color NotValidColor = Color.MistyRose;

        public static Color GetValidationColor(bool isValidated) =>
            isValidated ? ValidColor : NotValidColor;
    }
}
