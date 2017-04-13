namespace PRGReaderLibrary
{
    public enum CommandRequest
    {
        ReadOutputs = PointType.OUT + 1,
        ReadInputs,
        ReadVariables,
        ReadControllers,
        ReadWeeklyRoutines,
        ReadAnnualRoutines,
        ReadPrograms,
        ReadTables,
        ReadTotalizers,
        ReadMonitors,
        ReadScreens,
        ReadArrays,
        ReadAlarms,
        ReadUnits,
        ReadUserNames,
        //ReadAlarmSet,
        ReadTimeSchedule = PointType.WR_TIME + 1,
        ReadAnnualSchedule,

        ReadProgramCode = 16,
        ReadGroupElement = 19,
        ReadIndividualPoint = 20,
        ReadTime = 21,
        ReadMonitorData = 22,
        ReadPointIinfoTable = 24,
        ReadGroupElements = 25,  // TODO: Original comment: read point info

        ClearPanel = 28,
        SendAlarm = 32,
        ReadTStat = 33,
        ReadAnalogCusTable = 34, // TODO: Original comment: read monitor updates
        ReadVarUnit = 36,
        ReadExtIO = 37,
        ReadRemotePoint = 40,

        WriteOutputs = 100 + PointType.OUT + 1,
        WriteInputs,
        WriteVariables,
        /// <summary>
        /// PID
        /// </summary>
        WriteControllers,
        /// <summary>
        /// Schedules
        /// </summary>
        WriteWeeklyRoutines,
        /// <summary>
        /// Holidays
        /// </summary>
        WriteAnnualRoutines,
        WritePrograms,
        WriteTables,
        WriteTotalizers,
        WriteMonitors,
        WriteScreens,
        WriteArrays,
        WriteAlarms,
        WriteUnits,
        WriteUserNames,
        //WriteAlarmSet,
        WriteTimeSchedule = 100 + ReadTimeSchedule,
        WriteAnnualSchedule,
        WriteProgramCode = 100 + ReadProgramCode,
        WriteIndividualPoint = 100 + ReadIndividualPoint,
        WriteTStat_T3000 = 100 + ReadTStat,

        Command50 = 50,
        ReadCommand50 = 50,
        WriteCommand50 = 150,

        /// <summary>
        /// 450 length
        /// </summary>
        ReadAT = 90,
        ReadGraphicLabel = 91,
        ReadPIC = 95,
        ReadMISC = 96,
        ReadRemoteDeviceDB = 97,
        ReadSetting = 98,
        GetSerialNumberInfo = 99,
        PanelInfo1 = 110,
        PanelInfo2 = 111,
        MiniCommInfo = 112,
        PanelID = 113,
        IconNameTable = 114,
        WriteDataMini = 116,
        SendCodeMini = 117,
        SendDataMini = 118,
        ReadFlashStatus = 119,
        ReadStatusWriteFlash = 120,
        ReadArtMini = 121,
        WritePrgFlash = 122,
        WriteAnalogCustomTable = 134,
        WriteVarUnit = 136,
        WriteExtIO = 137,
        WriteRemotePoint = 140,
        /// <summary>
        /// 100 length
        /// </summary>
        WriteAT = 190,
        WriteGraphicLabel = 191,

        WritePIC = 195,
        WriteMISC = 196,
        WriteSpecial = 197,
        WriteSetting = 198,
        WriteSubIDByHand = 199,
        DeleteMonitorDatabase = 200
    }
}
