using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleAppServer
{
    class Program
    {
        static void Main(string[] args)
        {
            IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8000);
            TcpListener listener = new TcpListener(ep);
            listener.Start();
            Console.WriteLine("Waiting for client connections...");
            TcpClient client = listener.AcceptTcpClient();
            Console.WriteLine("Client connected");
            int sentNum = 0;
            int acceptedNum = 0;
            using (NetworkStream stream = client.GetStream())
            using (BinaryReader reader = new BinaryReader(stream))
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                Console.WriteLine("Waiting for a number");
                acceptedNum = reader.ReadInt32();
                Console.WriteLine("Number accepted");
                writer.Write(acceptedNum);
            
                Task readTask = new Task(() => {
                    while (true)
                    {
                        acceptedNum = reader.ReadInt32();
                        Console.WriteLine("Number accepted");
                        Console.WriteLine(acceptedNum);
                    }
                });
                readTask.Start();
                Task writeTask = new Task(() => {
                    while (true)
                    {
                        Console.WriteLine("Please enter a number: ");
                        sentNum = int.Parse(Console.ReadLine());
                        writer.Write(sentNum);
                        Console.Write("number: ");
                        Console.WriteLine(sentNum);
                    }
                });
                writeTask.Start();
                while (acceptedNum != 1)
                {

                }
            }
                client.Close();
                listener.Stop();
            Console.ReadKey();
        }
    }
}
