using System;
using System.Windows;

namespace Shaiya_Updater2
{
    public static class ExceptionManager
    {
        public static void Submit(Exception e)
        {
            Console.WriteLine(string.Concat(e.Message, "\r\n\r\n", e));
        }
    }
}