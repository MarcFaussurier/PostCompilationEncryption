using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Shaiya_Updater2
{
    public class SAH
    {
        public bool IsValid;

        public string SahPath;

        public string SafPath;

        public int TotalFileCount;

        public FOLDER RootFolder;

        public SAH(string Path)
        {
            this.SahPath = Path;
            this.SafPath = string.Concat(this.SahPath.Substring(0, this.SahPath.Length - 3), "saf");
            this.Read();
        }
        public static byte[] Buffer = { 242, 65, 46, 78, 149, 79, 46, 0, 31, 47, 42, 65, 98, 78 };

        private byte ROL(byte value, byte count)
        {
            return (byte)(value << (count & 31) | value >> (8 - count & 31));
        }

        private byte[] DecryptBuffer(byte[] Buffer)
        {
            for (int i = 0; i < (int)Buffer.Length; i++)
            {
                byte buffer = (byte)(Buffer[i] ^ (byte)i);
                buffer = (byte)(this.ROR(buffer, 1) ^ 127);
                Buffer[i] = this.ROR(buffer, 3);
            }
            return Buffer;
        }

        private byte ROR(byte value, byte count)
        {
            return (byte)(value >> (count & 31) | value << (8 - count & 31));
        }

        /*
        public static byte decr(byte b, int i)
        {
            int r = b ^ 420 * i;
            for (int y = 0; y < (int)Buffer.Length; y++)
            {
                byte num = ROL2(Buffer[y], 3);
                num = ROL2((byte)(num ^ 127), 1);
                Buffer[y] = (byte)(num ^ (byte)i);
            }
            return (byte)((r + 7 - i));

        }
        */
        public static byte ROL2(byte value, byte count)
        {
            return (byte)(value << (count & 31) | value >> (8 - count & 31));
        }


        private byte[] EncryptBuffer(byte[] Buffer)
        {
            for (int i = 0; i < (int)Buffer.Length; i++)
            {
                byte num = this.ROL(Buffer[i], 3);
                num = this.ROL((byte)(num ^ 127), 1);
                Buffer[i] = (byte)(num ^ (byte)i);
            }
            return Buffer;
        }

        /*
        public static byte encr(byte b, int i)
        {
            int po = (420 * i);
            for (int y = 0; y < (int)Buffer.Length; y++)
            {
                byte num = ROL2(Buffer[y], 3);
                num = ROL2((byte)(num ^ 127), 1);
                Buffer[y] = (byte)(num ^ (byte)i);
            }
            return (byte)((b - 7 + i) ^ po);
        }
        */

        private byte ROR2(byte value, byte count)
        {
            return (byte)(value >> (count & 31) | value << (8 - count & 31));
        }


        public void Patch(SAH Patch)
        {
            try
            {
                using (BinaryReader binaryReader = new BinaryReader(File.Open(Patch.SafPath, FileMode.Open, FileAccess.Read, FileShare.Read)))
                {
                    using (BinaryWriter binaryWriter = new BinaryWriter(File.Open(this.SafPath, FileMode.Open, FileAccess.Write, FileShare.None)))
                    {
                        FOLDER rootFolder = this.RootFolder;
                        if (Patch.RootFolder.Files.Count > 0)
                        {
                            foreach (FILE file in Patch.RootFolder.Files)
                            {
                                if (rootFolder.ContainsFile(file.FileName))
                                {
                                    this.PatchUpdateFile(rootFolder.GetFileByName(file.FileName), file, binaryReader, binaryWriter);
                                }
                                else
                                {
                                    this.PatchInsertFile(file, rootFolder, binaryReader, binaryWriter);
                                }
                            }
                        }
                        if (Patch.RootFolder.Folders.Count > 0)
                        {
                            foreach (FOLDER folder in Patch.RootFolder.Folders)
                            {
                                if (!rootFolder.ContainsFolder(folder.FolderName))
                                {
                                    rootFolder.Folders.Add(new FOLDER()
                                    {
                                        FolderName = folder.FolderName,
                                        Parent = rootFolder
                                    });
                                }
                                this.PatchMergeFolder(folder, rootFolder, binaryReader, binaryWriter);
                            }
                        }
                    }
                }
                this.Save();
            }
            catch (Exception exception)
            {
                ExceptionManager.Submit(exception);
            }
        }

        private void PatchInsertFile(FILE File, FOLDER CurrentFolder, BinaryReader PatchReader, BinaryWriter ClientWriter)
        {
            FILE fILE = new FILE()
            {
                FileName = File.FileName,
                Offset = ClientWriter.BaseStream.Length,
                Length = File.Length,
                Version = 0,
                Parent = CurrentFolder
            };
            PatchReader.BaseStream.Position = File.Offset;
            ClientWriter.BaseStream.Position = fILE.Offset;
            int num = 0;
            int num1 = 0;
            byte[] numArray = new byte[4096];
            while (num1 < File.Length)
            {
                num = PatchReader.Read(numArray, 0, Math.Min((int)numArray.Length, File.Length - num1));
                ClientWriter.Write(numArray, 0, num);
                num1 += num;
            }
            CurrentFolder.Files.Add(fILE);
        }

        private void PatchMergeFolder(FOLDER Folder, FOLDER CurrentFolder, BinaryReader PatchReader, BinaryWriter ClientWriter)
        {
            CurrentFolder = CurrentFolder.GetFolderByName(Folder.FolderName);
            if (Folder.Files.Count > 0)
            {
                foreach (FILE file in Folder.Files)
                {
                    if (CurrentFolder.ContainsFile(file.FileName))
                    {
                        this.PatchUpdateFile(CurrentFolder.GetFileByName(file.FileName), file, PatchReader, ClientWriter);
                    }
                    else
                    {
                        this.PatchInsertFile(file, CurrentFolder, PatchReader, ClientWriter);
                    }
                }
            }
            if (Folder.Folders.Count > 0)
            {
                foreach (FOLDER folder in Folder.Folders)
                {
                    if (!CurrentFolder.ContainsFolder(folder.FolderName))
                    {
                        CurrentFolder.Folders.Add(new FOLDER()
                        {
                            FolderName = folder.FolderName,
                            Parent = CurrentFolder
                        });
                    }
                    this.PatchMergeFolder(folder, CurrentFolder, PatchReader, ClientWriter);
                }
            }
            CurrentFolder = CurrentFolder.Parent;
        }

        private void PatchUpdateFile(FILE File, FILE NewFile, BinaryReader PatchReader, BinaryWriter ClientWriter)
        {
            PatchReader.BaseStream.Position = NewFile.Offset;
            ClientWriter.BaseStream.Position = (File.Length < NewFile.Length ? ClientWriter.BaseStream.Length : File.Offset);
            File.FileName = NewFile.FileName;
            File.Offset = ClientWriter.BaseStream.Position;
            File.Length = NewFile.Length;
            File.Version++;
            int num = 0;
            int num1 = 0;
            byte[] numArray = new byte[4096];
            while (num1 < File.Length)
            {
                num = PatchReader.Read(numArray, 0, Math.Min((int)numArray.Length, File.Length - num1));
                ClientWriter.Write(numArray, 0, num);
                num1 += num;
            }
        }

        private void Read()
        {
            byte[] numArray;
            try
            {
                int numArrayLen = (int)0;
                using (BinaryReader binaryReader = new BinaryReader(File.OpenRead(this.SahPath)))
                {
                    numArrayLen = (int) binaryReader.BaseStream.Length;
                    numArray = binaryReader.ReadBytes((int)binaryReader.BaseStream.Length);
                }
              /*  int y = 0;
                while (y < numArrayLen)
                {
                    numArray[y] = decr(numArray[y], y);
                    y += 1;
                }*/
              //  numArray = this.DecryptBuffer(numArray);
                this.TotalFileCount = BitConverter.ToInt32(numArray, 7);
                int num = 51;
                int num1 = BitConverter.ToInt32(numArray, num);
                num += 4;
                string str = Encoding.ASCII.GetString(numArray, num, num1).Replace("\0", "");
                num += num1;
                this.RootFolder = new FOLDER(str, null);
                int num2 = BitConverter.ToInt32(numArray, num) ^ 0x6D;
                num += 4;
                if (num2 > 0)
                {
                    for (int i = 0; i < num2; i++)
                    {
                        FILE fILE = new FILE();
                        int num3 = BitConverter.ToInt32(numArray, num);
                        num += 4;
                        fILE.FileName = Encoding.ASCII.GetString(numArray, num, num3).Replace("\0", "");
                        num += num3;
                        fILE.Offset = BitConverter.ToInt64(numArray, num);
                        num += 8;
                        fILE.Length = BitConverter.ToInt32(numArray, num);
                        num += 4;
                        fILE.Version = BitConverter.ToInt32(numArray, num);
                        num += 4;
                        fILE.Parent = this.RootFolder;
                        this.RootFolder.Files.Add(fILE);
                    }
                }
                int num4 = BitConverter.ToInt32(numArray, num);
                num += 4;
                if (num4 > 0)
                {
                    for (int j = 0; j < num4; j++)
                    {
                        this.RootFolder.Folders.Add(this.ReadFolder(this.RootFolder, numArray, ref num));
                    }
                }
                this.IsValid = true;
            }
            catch (Exception exception)
            {
                ExceptionManager.Submit(exception);
            }
        }

        private FOLDER ReadFolder(FOLDER Parent, byte[] FileData, ref int Offset)
        {
            FOLDER fOLDER = new FOLDER()
            {
                Parent = Parent
            };
            int num = BitConverter.ToInt32(FileData, Offset);
            Offset += 4;
            fOLDER.FolderName = Encoding.ASCII.GetString(FileData, Offset, num).Replace("\0", "");
            Offset += num;
            // this should be the len :
            int num1 = BitConverter.ToInt32(FileData, Offset) ^ 0x6D;
            Offset += 4;
            if (num1 > 0)
            {
                for (int i = 0; i < num1; i++)
                {
                    FILE fILE = new FILE();
                    int num2 = BitConverter.ToInt32(FileData, Offset);
                    Offset += 4;
                    fILE.FileName = Encoding.ASCII.GetString(FileData, Offset, num2).Replace("\0", "");
                    Offset += num2;
                    fILE.Offset = BitConverter.ToInt64(FileData, Offset);
                    Offset += 8;
                    fILE.Length = BitConverter.ToInt32(FileData, Offset);
                    Offset += 4;
                    fILE.Version = BitConverter.ToInt32(FileData, Offset);
                    Offset += 4;
                    fILE.Parent = Parent;
                    fOLDER.Files.Add(fILE);
                }
            }
            int num3 = BitConverter.ToInt32(FileData, Offset);
            Offset += 4;
            if (num3 > 0)
            {
                for (int j = 0; j < num3; j++)
                {
                    fOLDER.Folders.Add(this.ReadFolder(fOLDER, FileData, ref Offset));
                }
            }
            return fOLDER;
        }

      

        public void Save()
        {
            this.TotalFileCount = this.RootFolder.GetFileCount();
            this.WriteDataFile();
        }

        private void WriteDataFile()
        {
            try
            {
                List<byte> nums = new List<byte>();
                nums.AddRange(Encoding.ASCII.GetBytes("fff"));
                nums.AddRange(BitConverter.GetBytes(0));
                nums.AddRange(BitConverter.GetBytes(this.TotalFileCount));
                nums.AddRange(new byte[40]);
                this.WriteDataFile_Folder(this.RootFolder, ref nums);
                byte[] array = nums.ToArray();
             /*
                int y = 0;
                while (y < array.Length)
                {
                    array[y] = encr(array[y], y);
                    y += 1;
                }
             */
              //  array = this.EncryptBuffer(array);
                using (BinaryWriter binaryWriter = new BinaryWriter(File.Open(this.SahPath, FileMode.Create, FileAccess.Write, FileShare.None)))
                {
                    binaryWriter.Write(array);
                }
            }
            catch (Exception exception)
            {
                ExceptionManager.Submit(exception);
            }
        }

        private void WriteDataFile_File(FILE File, ref List<byte> Buffer)
        {
            Buffer.AddRange(BitConverter.GetBytes(File.FileName.Length + 1));
            Buffer.AddRange(Encoding.ASCII.GetBytes(string.Concat(File.FileName, "\0")));
            Buffer.AddRange(BitConverter.GetBytes(File.Offset));
            Buffer.AddRange(BitConverter.GetBytes(File.Length));
            Buffer.AddRange(BitConverter.GetBytes(File.Version));
        }

        private void WriteDataFile_Folder(FOLDER Folder, ref List<byte> Buffer)
        {
            Buffer.AddRange(BitConverter.GetBytes(Folder.FolderName.Length + 1));
            Buffer.AddRange(Encoding.ASCII.GetBytes(string.Concat(Folder.FolderName, "\0")));
            Buffer.AddRange(BitConverter.GetBytes(Folder.Files.Count ^ 0x6D));
            if (Folder.Files.Count > 0)
            {
                foreach (FILE file in Folder.Files)
                {
                    this.WriteDataFile_File(file, ref Buffer);
                }
            }
            Buffer.AddRange(BitConverter.GetBytes(Folder.Folders.Count));
            if (Folder.Folders.Count > 0)
            {
                foreach (FOLDER folder in Folder.Folders)
                {
                    this.WriteDataFile_Folder(folder, ref Buffer);
                }
            }
        }
    }
}