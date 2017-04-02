namespace PRGReaderLibrary
{
    public class UnitsPoint : BasePoint
    {
        public VariableVariant Value { get; set; }
        public AutoManual AutoManual { get; set; }
        public DigitalAnalog DigitalAnalog { get; set; }
        public Control Control { get; set; }

        public UnitsPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        {}

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(Description) &&
            string.IsNullOrWhiteSpace(Label);

        #region Binary data

        public UnitsPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {}

        #endregion
    }
}