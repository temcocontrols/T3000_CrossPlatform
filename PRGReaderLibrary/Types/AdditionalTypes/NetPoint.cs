namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class NetPoint : T3000Point, IBinaryObject
    {
        public int SubPanel { get; set; }
        public int Network { get; set; }

        public NetPoint(int number = 0,
            PanelType type = PanelType.T3000,
            int panel = 0,
            int subPanel = 0,
            int network = 0,
            FileVersion version = FileVersion.Current)
            : base(number, type, panel, version)
        {
            SubPanel = subPanel;
            Network = network;
        }

        public override int GetHashCode() =>
            base.GetHashCode() ^ SubPanel.GetHashCode() ^ Network.GetHashCode();

        #region Binary data

        /// <summary>
        /// FileVersion.Current - Need 5 bytes array
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public NetPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    SubPanel = bytes.ToByte(3 + offset);
                    Network = bytes.ToByte(4 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - 5 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.Add((byte)SubPanel);
                    bytes.Add((byte)Network);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}