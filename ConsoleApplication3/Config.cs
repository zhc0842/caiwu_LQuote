using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Resources;

namespace Calculator
{
    public class Config
    {
        static bool replay = false;
        static bool printLog = false;

        static int currentDate = int.Parse(DateTime.Today.ToString("yyyyMMdd"));

        public static int CurrentDate
        {
            set
            {
                currentDate = value;
            }
            get
            {
                return currentDate;
            }
        }

        public static bool Replay
        {
            set
            {
                replay = value;
            }
            get
            {
                return replay;
            }
        }

        public static bool PrintLog
        {
            set
            {
                printLog = value;
            }
            get
            {
                return printLog;
            }
        }

        public static Properties.Settings Setting
        {
            get
            {
                return Properties.Settings.Default;
            }
        }

        public static void SaveConfig(string quoteIP,int quotePort,string quoteUser,string quotePsw)
        {
            Setting.QuoteIP = quoteIP;
            Setting.QuotePort = quotePort;
            Setting.QuoteUser = quoteUser;
            Setting.QuotePsw = quotePsw;

            Setting.Save();
        }
    }
}
