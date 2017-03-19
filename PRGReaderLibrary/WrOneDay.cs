namespace PRGReaderLibrary
{
    public class WrOneDay
    {
        public byte time_on_minutes1 { get; set; }
        public byte time_on_hours1 { get; set; }
        public byte time_off_minutes1 { get; set; }
        public byte time_off_hours1 { get; set; }
        public byte time_on_minutes2 { get; set; }
        public byte time_on_hours2 { get; set; }
        public byte time_off_minutes2 { get; set; }
        public byte time_off_hours2 { get; set; }
        public byte time_on_minutes3 { get; set; }
        public byte time_on_hours3 { get; set; }
        public byte time_off_minutes3 { get; set; }
        public byte time_off_hours3 { get; set; }
        public byte time_on_minutes4 { get; set; }
        public byte time_on_hours4 { get; set; }
        public byte time_off_minutes4 { get; set; }
        public byte time_off_hours4 { get; set; }

        public static WrOneDay FromBytes(byte[] data)
        {
            var day = new WrOneDay();
            day.time_on_minutes1 = data[0];
            day.time_on_hours1 = data[1];
            day.time_off_minutes1 = data[2];
            day.time_off_hours1 = data[3];
            day.time_on_minutes2 = data[4];
            day.time_on_hours2 = data[5];
            day.time_off_minutes2 = data[6];
            day.time_off_hours2 = data[7];
            day.time_on_minutes3 = data[8];
            day.time_on_hours3 = data[9];
            day.time_off_minutes3 = data[10];
            day.time_off_hours3 = data[11];
            day.time_on_minutes4 = data[12];
            day.time_on_hours4 = data[13];
            day.time_off_minutes4 = data[14];
            day.time_off_hours4 = data[15];

            return day;
        }
        public override string ToString() => StringUtilities.ObjectToString(this);
    }
}