namespace PRGReaderLibrary
{
    public static class UnitsExtensions
    {
        public static bool IsAnalog(this Units units) =>
            units < Units.OffOn;

        public static bool IsDigital(this Units units) =>
            !units.IsAnalog();
    }
}
