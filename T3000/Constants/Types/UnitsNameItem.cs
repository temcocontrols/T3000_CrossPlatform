namespace PRGReaderLibrary
{
    public class UnitsNameItem
    {
        public string Text { get; set; }
        public object Value { get; set; }

        public UnitsNameItem(object value, string text = "")
        {
            Value = value;
            Text = text;
        }

        public override string ToString()
        {
            return Text;
        }
    }
}