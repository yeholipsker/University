using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Net;
using System.Net.Sockets;
using Newtonsoft.Json.Linq;

namespace Vlc.DotNet.Wpf.Samples
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        // Consts
        public const String PATH = @"\..\..\VLC\";
        public const int MAX_NUMBER_OF_WINDOWS = 4;
        public const int VIDEO_SIZE = 400;

        // Data member.
        public delegate void createWindowCallback(String sdpPath);
        private int numberOfWindows = 0;
        TcpListener listener = null;

        // The main window of the receive part.
        public MainWindow()
        {
            InitializeComponent();
            // Start listen for clients requests.
            IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse("0.0.0.0"), 8000);
            listener = new TcpListener(endPoint);
            listener.Start();
        }

        // 'Add new' button method.
        private void AddNewWindow(String sdpPath)
        {
            // Don't allow more the MAX_NUMBER_OF_WINDOWS windows.
            if (numberOfWindows <= MAX_NUMBER_OF_WINDOWS)
            {
                // Change the screen respectively to the number of windows.
                switch (numberOfWindows)
                {
                    case 1:
                        // Add new VlcPlayer.
                        vlcPlayer.MediaPlayer.VlcLibDirectory = new DirectoryInfo(Directory.GetCurrentDirectory() + PATH);
                        vlcPlayer.MediaPlayer.EndInit();
                        vlcPlayer.MediaPlayer.Play(new FileInfo(sdpPath));
                        break;
                    case 2:
                        // Split the screen into right & left.
                        ColumnDefinition newColTop = new ColumnDefinition();
                        newColTop.Width = new GridLength(VIDEO_SIZE);
                        ScreenGridTop.ColumnDefinitions.Add(newColTop);

                        // Resize the window.
                        Receiver.Width += 400;

                        // Add new VlcPlayer.
                        vlcPlayer2.MediaPlayer.VlcLibDirectory = new DirectoryInfo(Directory.GetCurrentDirectory() + PATH);
                        vlcPlayer2.MediaPlayer.EndInit();
                        vlcPlayer2.MediaPlayer.Play(new FileInfo(sdpPath));
                        break;
                    case 3:
                        // Split the screen into top & bottom.
                        RowDefinition newRow = new RowDefinition();
                        newRow.Height = new GridLength(VIDEO_SIZE);
                        ScreenGrid.RowDefinitions.Add(newRow);

                        // Resize the window.
                        Receiver.Height += VIDEO_SIZE;

                        // Add new VlcPlayer.
                        vlcPlayer3.MediaPlayer.VlcLibDirectory = new DirectoryInfo(Directory.GetCurrentDirectory() + PATH);
                        vlcPlayer3.MediaPlayer.EndInit();
                        vlcPlayer3.MediaPlayer.Play(new FileInfo(sdpPath));
                        break;
                    case 4:
                        // Split the bottom half of the screen.
                        ColumnDefinition newColDown = new ColumnDefinition();
                        newColDown.Width = new GridLength(VIDEO_SIZE);
                        ScreenGridDown.ColumnDefinitions.Add(newColDown);

                        // Add new VlcPlayer.
                        vlcPlayer4.MediaPlayer.VlcLibDirectory = new DirectoryInfo(Directory.GetCurrentDirectory() + PATH);
                        vlcPlayer4.MediaPlayer.EndInit();
                        vlcPlayer4.MediaPlayer.Play(new FileInfo(sdpPath));
                        break;
                    default:
                        break;
                }
            }
        }

        // Listen to client - add a new member to the conversation.
        private void ListenButton_Click(object sender, RoutedEventArgs e)
        {
            // Accept the client.
            TcpClient client = listener.AcceptTcpClient();
            
            using (NetworkStream stream = client.GetStream())
            using (BinaryReader reader = new BinaryReader(stream))
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                // Get the new client connection details.
                String details = reader.ReadString();
                JObject streamDetails = JObject.Parse(details);
                numberOfWindows++;
                /* Create sdp file with the client IP address & Port.
                 * The Vlc player will read the file and get all the require information from it.
                 */
                using (var tw = new StreamWriter("connectionDetails" + numberOfWindows + ".sdp", false))
                {
                    tw.Write("v=0\n");
                    tw.Write("o=- 49452 4 IN IP4 " + streamDetails["IP"] + "\n");
                    tw.Write("s=Test MP3 session\n");
                    tw.Write("i=Parameters for the session streamed by \"testMP3Streamer\"\n");
                    tw.Write("t=0 0\n");
                    tw.Write("a=tool:testMP3Streamer\n");
                    tw.Write("a=type:broadcast\n");
                    tw.Write("m=audio " + streamDetails["Port"] + " RTP/AVP 14\n");
                    tw.Write("c=IN IP4 127.0.0.1\n");
                    tw.Write("m=video " + (Convert.ToInt32(streamDetails["Port"]) + 2) + " RTP/AVP 96\n");
                    tw.Write("c=IN IP4 127.0.0.1\n");
                    tw.Write("a=rtpmap:96 H264/90000\n");
                    tw.Write("a=fmtp:96 packetization-mode=1");
                }
                // Add the new client video to the screen.
                AddNewWindow("connectionDetails" + numberOfWindows + ".sdp");                
            }
        }
    }
}