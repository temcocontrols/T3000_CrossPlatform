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
                    throw new NotImplementedException("File version is not implemented");
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
                    bytes.AddRange(ScreenRights);
                    bytes.AddRange(ProgramRights);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}