namespace PRGReaderLibrary
{
    using System;

    [AttributeUsage(AttributeTargets.Field)]
    public class NameAttribute : Attribute
    {
        public string Name { get; set; }

        public NameAttribute(string name)
        {
            Name = name;
        }
    }
}