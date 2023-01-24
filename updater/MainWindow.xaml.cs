using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.IO;
using System.Net;
using System.ComponentModel;
using System.IO.Compression;
using System.Threading;
using System.Runtime.InteropServices;
using System.Diagnostics;

[Flags]
enum MoveFileFlags
{
    MOVEFILE_REPLACE_EXISTING = 0x00000001,
    MOVEFILE_COPY_ALLOWED = 0x00000002,
    MOVEFILE_DELAY_UNTIL_REBOOT = 0x00000004,
    MOVEFILE_WRITE_THROUGH = 0x00000008,
    MOVEFILE_CREATE_HARDLINK = 0x00000010,
    MOVEFILE_FAIL_IF_NOT_TRACKABLE = 0x00000020
}




namespace Shaiya_Updater2
{
  
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        static extern bool MoveFileEx(string lpExistingFileName, string lpNewFileName, MoveFileFlags dwFlags);


        const string srvRemote = "http://patch-fr.shaiya.ovh";
        const string srvVersionPath = ".srvVersion";
        const string cliVersionPath = "version.ini";// "C:\\shaiyaarchive\\shaiya-us\\original\\Version.ini";
        void wc_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            patchProgress.Dispatcher.BeginInvoke(
                   (Action)(() => {
                       patchProgress.Value = e.ProgressPercentage;
                   }));

            //Console.WriteLine(" -- " + e.ProgressPercentage + "%");
        }


        void GetSrvVersion()
        {
            int SrvVersion;
            int CliVersion;

            using (WebClient wc = new WebClient())
            {
                wc.DownloadFile(
                    // Param1 = Link of file
                    new System.Uri(srvRemote + "/Shaiya/UpdateVersion.ini"),
                    // Param2 = Path to save
                    srvVersionPath
                );

              //  Console.WriteLine("File download completed.");
                var SrvINI = new IniFile(srvVersionPath);
                SrvVersion = int.Parse(SrvINI.Read("PatchFileVersion", "Version"));
             //   Console.WriteLine("Server version: " + SrvVersion);
                File.Delete(srvVersionPath);
            }
            var CliINI = new IniFile(cliVersionPath);
            CliVersion = int.Parse(CliINI.Read("CurrentVersion", "Version"));
            //  Console.WriteLine("Current client version: " + CliVersion);
            int newww = 0;
            
            while (CliVersion < SrvVersion)
            {
                newww = 1;
                StateText.Dispatcher.BeginInvoke(
                  (Action)(() => {
                      StateText.Content = "Game is updating...";
                  }));
                PlayBtn.Dispatcher.BeginInvoke(
                 (Action)(() => {
                     PlayBtn.IsEnabled = false;
                 }));
                CliVersion += 1;
                string patchFile = "ps" + CliVersion.ToString().PadLeft(4, '0') + ".patch";
                File.Delete(patchFile);
                using (WebClient wc = new WebClient())
                {
                    // todo:: fix me ??
                    wc.DownloadProgressChanged += new DownloadProgressChangedEventHandler(wc_DownloadProgressChanged);
                    wc.DownloadFile(
                        new System.Uri(srvRemote + "/Shaiya/patch/" + patchFile),
                        patchFile
                        );
                }
                string str2 = System.IO.Path.Combine("update.sah");
                string str3 = System.IO.Path.Combine("update.saf");
                File.Delete(str2);
                File.Delete(str3);

                ZipFile.ExtractToDirectory(patchFile, ".", true);


                if (File.Exists(System.IO.Path.Combine("data.sah")))
                {
                    SAH sAH = new SAH(System.IO.Path.Combine("data.sah"));

                    if (File.Exists(str2) && File.Exists(str3))
                    {
                        SAH sAH1 = new SAH(str2);
                        if (sAH1.IsValid)
                        {
                            sAH.Patch(sAH1);
                        }
                        else
                        {
                            MessageBox.Show("Error: invalid SAH, please re-download or contact support.");
                        }
                        File.Delete(str2);
                        File.Delete(str3);
                    }
                    File.Delete(patchFile);
                }
              
                CliINI.Write("CurrentVersion", CliVersion.ToString(), "Version");

                if (File.Exists("new_updater.exe"))
                { 
                    ProcessStartInfo Info = new ProcessStartInfo();
                    Info.Arguments = "/C ping 127.0.0.1 -n 2 && move /Y new_updater.exe \"" + Process.GetCurrentProcess().MainModule.FileName + "\" && " + "\"" + Process.GetCurrentProcess().MainModule.FileName + "\"";
                    Info.WindowStyle = ProcessWindowStyle.Hidden;
                    Info.CreateNoWindow = true;
                    Info.FileName = "cmd.exe";
                    Process.Start(Info);
                    System.Environment.Exit(0);
                }

                if (File.Exists(System.IO.Path.Combine("update.bat")))
                {
                    System.Diagnostics.Process.Start(System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "update.bat"));
                    ProcessStartInfo Info = new ProcessStartInfo();
                    Info.Arguments = "/C ping 127.0.0.1 -n 2 && del " + "\"" + System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "update.bat") + "\" && rm " + "\"" + System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "update.bat") + "\"";
                    Info.WindowStyle = ProcessWindowStyle.Hidden;
                    Info.CreateNoWindow = true;
                    Info.FileName = "cmd.exe";
                    Process.Start(Info);

                }
                totalProgress.Dispatcher.BeginInvoke(
                    (Action)(() => {
                    totalProgress.Value = (int)(CliVersion * 100 / SrvVersion);
                }));
                //  Console.ReadLine();
                Thread.Sleep(1000);
            }

            if (newww != 0)
            { 
                 StateText.Dispatcher.BeginInvoke(
                (Action)(() => {
                    StateText.Content = "Update done! Have fun :)";
                }));
            
            }
       
            PlayBtn.Dispatcher.BeginInvoke(
                           (Action)(() => {
                            PlayBtn.IsEnabled = true;
            }));
        }

        public MainWindow()
        {
            InitializeComponent();

            Thread t = new Thread(() =>
            {
                GetSrvVersion();
            });
            t.Start();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start(System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, @"CONFIG.exe"));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

            try
            {
                System.Diagnostics.Process.Start(new System.Diagnostics.ProcessStartInfo("https://shaiya.fr") { UseShellExecute = true });
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start(new System.Diagnostics.ProcessStartInfo("https://discord.gg/WjtFDh9c5m") { UseShellExecute = true });
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            try
            {
                String curItem = new String(listBox1.SelectedItem.ToString().Split(" ")[1]);
                // TODO : add multi langue with curItem
                System.Diagnostics.Process.Start(System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, @"game.exe"), "start game");
                System.Environment.Exit(0);
            }
            catch (Exception ex)
            {                 
                MessageBox.Show(ex.Message);
            }
        }
    }
}
