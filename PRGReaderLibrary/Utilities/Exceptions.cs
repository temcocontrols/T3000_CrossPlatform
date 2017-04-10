namespace PRGReaderLibrary
{
    using System;

    class FileVersionNotImplementedException : NotImplementedException
    {
        public FileVersionNotImplementedException(FileVersion version)
            : base($@"File version is not implemented.
FileVersion: {version}") { }
    }

    class OffsetException : Exception
    {
        public OffsetException(int offset, int length)
            : base($@"Offset != Length after reading/writing.
Offset: {offset}, Length: {length}") { }
    }
}
