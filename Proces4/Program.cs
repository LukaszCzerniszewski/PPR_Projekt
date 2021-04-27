using Horizon.XmlRpc.Server;
using Horizon.XmlRpc.Client;
using System;
using System.Net;
using System.Collections.Generic;
using System.Text;
//using Common;
using Horizon.XmlRpc.Core;



namespace ConsoleApp2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Proces 4");
            var service = new AddService();
            var listener = new HttpListener();
            listener.Prefixes.Add("http://127.0.0.1:10004/");
            listener.Start();

            while (true)
            {
                var context = listener.GetContext();
                service.ProcessRequest(context);
                
            }
        }
    }

    internal class AddService : XmlRpcListenerService, IAddService
    {
        public string AddNumbers(string numberB)
        {
            string decString = numberB;
            Console.WriteLine("Proces 4 otrzymal wiadomosc :"+ numberB);
            byte[] bytes = Encoding.Default.GetBytes(decString);
            string hexString = BitConverter.ToString(bytes);
            hexString = hexString.Replace("-", "");
            Console.WriteLine(hexString);
            return numberB;
        }
    }
    
    public interface IAddService
    {
        [XmlRpcMethod("Demo.addNumbers")]
        string AddNumbers( string S);
    }
}