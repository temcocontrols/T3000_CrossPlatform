namespace PRGReaderLibrary
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Explicit)]
    struct PanelInfo1
    {
        [FieldOffset(0)]
        Byte panel_type;

        [FieldOffset(1)]
        UInt32 active_panels;

        [FieldOffset(5)]
        UInt16 des_length;

        [FieldOffset(7)]
        Int32 version;

        [FieldOffset(11)]
        Byte panel_number;

        [FieldOffset(12)]
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = Constants.NameSize)]
        string panel_name;

        [FieldOffset(12 + Constants.NameSize)]
        UInt16 network;

        [FieldOffset(12 + Constants.NameSize + 2)]
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = Constants.NameSize)]
        string network_name;
    }
}