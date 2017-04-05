namespace T3000
{
    using System.Drawing;

    class ColorConstants
    {
        public static readonly Color ValidColor = Color.LightGreen;
        public static readonly Color NotValidColor = Color.MistyRose;

        public static Color GetValidationColor(bool isValidated) =>
            isValidated ? ValidColor : NotValidColor;
    }
}
