namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
    using System.Collections.Generic;

    public class CustomUnits : ICloneable
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

        public object Clone() => new CustomUnits(
            Analog.Select(i=>(CustomAnalogUnitsPoint)i.Clone()).ToList(),
            Digital.Select(i => (CustomDigitalUnitsPoint)i.Clone()).ToList()
        );
    }
}
