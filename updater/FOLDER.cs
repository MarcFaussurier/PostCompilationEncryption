using System;
using System.Collections.Generic;

namespace Shaiya_Updater2
{
    public class FOLDER
    {
        public string FolderName;

        public List<FILE> Files;

        public List<FOLDER> Folders;

        public FOLDER Parent;

        public FOLDER()
        {
            this.Files = new List<FILE>();
            this.Folders = new List<FOLDER>();
            this.Parent = null;
        }

        public FOLDER(string FolderName, FOLDER Parent)
        {
            this.FolderName = FolderName;
            this.Files = new List<FILE>();
            this.Folders = new List<FOLDER>();
            this.Parent = Parent;
        }

        public FOLDER(string FolderName, List<FILE> Files, List<FOLDER> Folders, FOLDER Parent)
        {
            this.FolderName = FolderName;
            this.Files = Files;
            this.Folders = Folders;
            this.Parent = Parent;
        }

        public bool ContainsFile(string FileName)
        {
            bool flag;
            List<FILE>.Enumerator enumerator = this.Files.GetEnumerator();
            try
            {
                while (enumerator.MoveNext())
                {
                    if (enumerator.Current.FileName.ToLowerInvariant() != FileName.ToLowerInvariant())
                    {
                        continue;
                    }
                    flag = true;
                    return flag;
                }
                return false;
            }
            finally
            {
                ((IDisposable)enumerator).Dispose();
            }
            return flag;
        }

        public bool ContainsFolder(string FolderName)
        {
            bool flag;
            List<FOLDER>.Enumerator enumerator = this.Folders.GetEnumerator();
            try
            {
                while (enumerator.MoveNext())
                {
                    if (enumerator.Current.FolderName.ToLowerInvariant() != FolderName.ToLowerInvariant())
                    {
                        continue;
                    }
                    flag = true;
                    return flag;
                }
                return false;
            }
            finally
            {
                ((IDisposable)enumerator).Dispose();
            }
            return flag;
        }

        public FILE GetFileByName(string FileName)
        {
            FILE fILE;
            List<FILE>.Enumerator enumerator = this.Files.GetEnumerator();
            try
            {
                while (enumerator.MoveNext())
                {
                    FILE current = enumerator.Current;
                    if (current.FileName.ToLowerInvariant() != FileName.ToLowerInvariant())
                    {
                        continue;
                    }
                    fILE = current;
                    return fILE;
                }
                return null;
            }
            finally
            {
                ((IDisposable)enumerator).Dispose();
            }
            return fILE;
        }

        public int GetFileCount()
        {
            int count = this.Files.Count;
            foreach (FOLDER folder in this.Folders)
            {
                count += folder.GetFileCount();
            }
            return count;
        }

        public FOLDER GetFolderByName(string FolderName)
        {
            FOLDER fOLDER;
            List<FOLDER>.Enumerator enumerator = this.Folders.GetEnumerator();
            try
            {
                while (enumerator.MoveNext())
                {
                    FOLDER current = enumerator.Current;
                    if (current.FolderName.ToLowerInvariant() != FolderName.ToLowerInvariant())
                    {
                        continue;
                    }
                    fOLDER = current;
                    return fOLDER;
                }
                return null;
            }
            finally
            {
                ((IDisposable)enumerator).Dispose();
            }
            return fOLDER;
        }

        public string GetFullName()
        {
            if (this.Parent == null)
            {
                return "Data";
            }
            return string.Concat(this.Parent.GetFullName(), "\\", this.FolderName);
        }
    }
}