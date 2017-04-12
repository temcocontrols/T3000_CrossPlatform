namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class CustomUnits
    {
        public List<CustomAnalogUnitsPoint> Analog { get; set; } = 
            new List<CustomAnalogUnitsPoint>();

        public List<CustomDigitalUnitsPoint> Digital { get; set; } = 
            new List<CustomDigitalUnitsPoint>();

        public CustomUnits() { }

        public CustomUnits(List<CustomAnalogUnitsPoint> analogUnits,
            List<CustomDigitalUnitsPoint> digitalUnits)
        {
            Analog = analogUnits;
            Digital = digitalUnits;
        }
    }
}
