namespace PRGReaderLibrary
{
    public static class Constants
    {
        public const int NameSize = 17;
        public const int MaxViews = 3;
        public const int MaxTblBank = 15;
        public const int MaxPassw = 10;
        public const int AlarmMessageSize = 58;
        public const int MaxUnits = 8;
        public const int MaxOutsMini = 64;
        public const int MaxInsMini = 64;

        public const string Signature = "!@#$";

        public const int OUT = 0;
        public const int IN = 1;
        public const int VAR = 2;
        public const int CON = 3;
        public const int WR = 4;
        public const int AR = 5;
        public const int PRG = 6;
        public const int TBL = 7;
        public const int DMON = 8;
        public const int AMON = 9;
        public const int GRP = 10;
        public const int AY = 11;   /* table to hold file names */
        public const int ALARMM = 12;
        public const int UNIT = 13;
        public const int USER_NAME = 14;
        public const int ALARMS = 15;
        public const int WR_TIME = 16;
        public const int AR_Y = 17;

    }

    public static class TypesConstants
    {
        public const byte LOCAL_VARIABLE = 0x82;
        public const byte FLOAT_TYPE = 0x83;
        public const byte LONG_TYPE = 0x84;
        public const byte INTEGER_TYPE = 0x85;
        public const byte BYTE_TYPE = 0x86;
        public const byte STRING_TYPE = 0x87;
        public const byte FLOAT_TYPE_ARRAY = 0x88;
        public const byte LONG_TYPE_ARRAY = 0x89;
        public const byte INTEGER_TYPE_ARRAY = 0x8A;
        public const byte BYTE_TYPE_ARRAY = 0x8B;
        public const byte STRING_TYPE_ARRAY = 0x8C;
    }
}