 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CSTDFAPI;
using System.Threading;
using CSTDFMIW.Structlevel;
using System.Runtime.InteropServices;
using CSTDFMIW;
using System.IO;
//using FuturesTrading.util;
//using FuturesTrading.futures;
using System.Collections.Concurrent;
using LiveQuote;
//using Calculator.Class;



namespace Calculator
{
    
    public class LQuote
    {
        public static LiveQuote.Main main;


        //static TDFHelper.ON_TDF_RECV_DATA_HANDLER recvHandle;
        //static TDFHelper.ON_TDF_DISCONNECT_HANDLER disHandle;
        //static TDFHelper.ON_TDF_STATUS_CHANGED staHandle;
        //static TDFHelper.ON_TDF_LOGINRESULT_HANDLER logHandle;

        private HTDF _htdf;

        Dictionary<String, int> pid2WindDict=new Dictionary<string,int>();
        Dictionary<int, string> wind2PidDict=new Dictionary<int,string>();

        String prefix;
        String suffix;

          

        private static ConcurrentDictionary<string, string> validPids = new ConcurrentDictionary<string, string>();


        public LQuote()
        {
             
            main = new Main();
            main.LogEvent += new Log(log);
            //main.OnLiveArrivedEvent += new OnLiveArrived(onLiveArrived);
            main.OnMarketDataArrivedEvent += new OnMarketDataArrived(onMarketDataArrived);
            main.OnTradeArrivedEvent += new OnTradeArrived(onTradeArrived);

            
        }

 

        public  bool Run()
        {

            try
            {
                main.Start();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            return true;
        }
        public bool stop()
        {

            try
            {
                main.Stop();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            return true;
        }





        //public void OnTradeArrived(string pid, uint price, int ntime, int openIndex)
        //{
        //    Notify(new object[] { pid, price, ntime, openIndex });
        //}

        //public void OnQuoteArrived(string pid, uint openPrice, uint preClosePrice, uint highLimitedPrice, uint lowLimitedPrice, uint[] bids, uint[] bidVols, uint[] asks, uint[] askVols, int ntime, int status)
        //{
        //    Notify(new object[] { pid, openPrice, preClosePrice, highLimitedPrice, lowLimitedPrice, bids, bidVols, asks, askVols, ntime, status });
        //}


        public void onLiveArrived(string pid, double lastPrice, long lastVolue, double[] bids, long[] bidSizes, double[] asks, long[] askSizes)
        {
           
            //Quoting.OnQuoteArrived(pid, lastPrice, lastVolue, 0, 0, 0, 0, bids, bidSizes, asks, askSizes);



            //bids = new double[10];
            //bidSizes = new long[10];
            //asks = new double[10];
            //askSizes = new long[10];
            //while (true)
            //{
            //    Thread.Sleep(500);
            //    Random rd=new Random(400);
            //    int temp = 2500;
            //    for (int i = 0; i < 5; i++)
            //    {
            //        asks[i] = rd.Next(temp, temp+5*i);
            //        bids[i] = asks[i] + 25;
            //        askSizes[i] = rd.Next(1, 10);
            //        bidSizes[i] = rd.Next(1, 10);

            //    }

            //    Quoting.OnQuoteArrived("IF1303", lastPrice, lastVolue, 0, 0, 0, 0, bids, bidSizes, asks, askSizes);

            //}
             
        }
        public void onMarketDataArrived(string pid, double[] bids, long[] bidSizes, double[] asks, long[] askSizes)
        {
            Console.WriteLine(pid + "----" + bids + "-----" + bidSizes + "------" + asks + "-----" + askSizes);
    
 

             
        }
        public void onTradeArrived(string pid, double lastPrice, long lastVolue)
        {
            Console.WriteLine(pid+"----"+lastPrice+"-----"+lastVolue);
   
        }

        public void log(string msg)
        {
            Console.WriteLine(msg);
        }













    }
}
