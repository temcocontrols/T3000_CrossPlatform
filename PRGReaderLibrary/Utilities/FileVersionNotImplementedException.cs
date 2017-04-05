namespace PRGReaderLibrary
{
    using System;

    class FileVersionNotImplementedException : NotImplementedException
    {
        public FileVersionNotImplementedException(FileVersion version)
            : base($@"File version is not implemented.
FileVersion: {version}") { }
    }
}
