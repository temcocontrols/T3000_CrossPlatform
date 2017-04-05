namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class UserPoint : Version, IBinaryObject
    {
        public string Name { get; set; }
        public string Password { get; set; }
        public int AccessLevel { get; set; }
        public long Rights { get; set; }
        public int DefaultPanel { get; set; }
        public int DefaultGroup { get; set; }
        public byte[] ScreenRights { get; set; }
        public byte[] ProgramRights { get; set; }

        public UserPoint(string name = "", string password = "",
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Name = name;
            Password = password;
        }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 8;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 48;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 48 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public UserPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Name = bytes.GetString(0 + offset, 16).ClearBinarySymvols();
                    Password = bytes.GetString(16 + offset, 9).ClearBinarySymvols();
                    AccessLevel = bytes.ToByte(25 + offset);
                    Rights = bytes.ToUInt32(26 + offset);
                    DefaultPanel = bytes.ToByte(30 + offset);
                    DefaultGroup = bytes.ToByte(31 + offset);
                    ScreenRights = bytes.ToBytes(32 + offset, 8);
                    ProgramRights = bytes.ToBytes(40 + offset, 8);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - 48 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Name.ToBytes(16));
                    bytes.AddRange(Password.ToBytes(9));
                    bytes.Add((byte)AccessLevel);
                    bytes.AddRange(((uint)Rights).ToBytes());
                    bytes.Add((byte)DefaultPanel);
                    bytes.Add((byte)DefaultGroup);
                    bytes.AddRange(ScreenRights ?? new byte[8]);
                    bytes.AddRange(ProgramRights ?? new byte[8]);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}