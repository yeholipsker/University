using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleAppClient
{
    class Program
    {
        static void Main(string[] args)
        {
            int sentNum = 0;
            int acceptedNum = 0;
            IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8000);
            TcpClient client = new TcpClient();
            client.Connect(ep);
            Console.WriteLine("You are connected");
            using (NetworkStream stream = client.GetStream())
            using (BinaryReader reader = new BinaryReader(stream))
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                // Send data to server
                Console.Write("Please enter a number: ");
                sentNum = int.Parse(Console.ReadLine());
                writer.Write(sentNum);
                // Get result from server
                int result = reader.ReadInt32();
                Console.WriteLine("Result = {0}", result);
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
            Console.ReadKey();
        }
    }
}
