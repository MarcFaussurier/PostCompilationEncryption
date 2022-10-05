using System;

namespace Shaiya_Updater2
{
    public class FILE
    {
        public string FileName;

        public long Offset;

        public int Length;

        public int Version;

        public FOLDER Parent;

        public FILE()
        {
        }

        public FILE(string FileName, long Offset, int Length, int Version, FOLDER Parent)
        {
            this.FileName = FileName;
            this.Offset = Offset;
            this.Length = Length;
            this.Version = Version;
            this.Parent = Parent;
        }
    }
}