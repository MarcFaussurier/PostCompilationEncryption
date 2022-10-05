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

namespace Shaiya_Updater2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const string srvRemote = "http://patch-fr.shaiya.ovh";
        const string srvVersionPath = ".srvVersion";
        const string cliVersionPath = "version.ini";// "C:\\shaiyaarchive\\shaiya-us\\original\\Version.ini";
        const string dataPath = "data.sah";//"C:\\shaiyaarchive\\shaiya-us\\original\\data.sah";
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
                
                SAH sAH = new SAH(dataPath);
               
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
              
                CliINI.Write("CurrentVersion", CliVersion.ToString(), "Version");

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
            System.Diagnostics.Process.Start("CONFIG.exe");
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://shaiya.fr");
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("discord://discord.com/channels/YYSsMueGBK");
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {


            String curItem = new String(listBox1.SelectedItem.ToString().Split(" ")[1]);
            if (curItem.Equals("Brazilian"))
                System.Diagnostics.Process.Start("game_BRZ.exe", "$pat7894f+*apfjfe+-");
            else if (curItem.Equals("French"))
                System.Diagnostics.Process.Start("game_FRC.exe", "$pat7894f+*apfjfe+-");
            else if (curItem.Equals("German"))
                System.Diagnostics.Process.Start("game_GER.exe", "$pat7894f+*apfjfe+-");
            else if (curItem.Equals("Italian"))
                System.Diagnostics.Process.Start("game_ITA.exe", "$pat7894f+*apfjfe+-");
            else if (curItem.Equals("Spanish"))
                System.Diagnostics.Process.Start("game_SPN.exe", "$pat7894f+*apfjfe+-");
            else if (curItem.Equals("English"))
                System.Diagnostics.Process.Start("game_USA.exe", "$pat7894f+*apfjfe+-");
            else
                MessageBox.Show("[" + curItem + "] fucking not founddddd");

        }
    }
}
