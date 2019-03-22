using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace FileLog
{
    /// <summary>
    /// Simple class to write a log file
    /// </summary>
    public class FileLogger
    {
        /// <summary>
        /// Log file name
        /// </summary>
        public string LogFileName { get; set; } = "log.txt";

        /// <summary>
        /// Try to open and initialize log file
        /// </summary>
        public FileLogger()
        {
            try
            {
                InitLog();

            }
            catch (Exception ex)
            {

                throw ex;
            }
        }

        /// <summary>
        /// Set filename and initialize log file
        /// </summary>
        /// <param name="fileName"></param>
        public FileLogger(string fileName)
        {
            try
            {
                LogFileName = fileName;
                InitLog();

            }
            catch (Exception ex)
            {

                throw ex;
            }

        }


        /// <summary>
        /// Init the log file, append time and date marks
        /// </summary>
        private void InitLog()
        {
            try
            {
                StreamWriter w = File.AppendText(LogFileName);
                w.Write("\r\n Log Entry: ");
                w.WriteLine("{0} {1}", DateTime.Now.ToLongTimeString(), DateTime.Now.ToLongDateString());
                w.WriteLine("--------------------------------------------------------------------------");
                w.WriteLine();
                w.Close();

            }
            catch (Exception ex)
            {

                throw ex;
            }
        }


        /// <summary>
        /// Add log message to file
        /// </summary>
        /// <param name="logMessage"></param>
        public void Add(string logMessage, bool ShowTime = true)
        {
            try
            {
                //Open log file
                StreamWriter w = File.AppendText(LogFileName);
                if(ShowTime)
                    w.WriteLine("{0} => {1}", DateTime.Now.ToLongTimeString(), logMessage);
                else
                    w.WriteLine(logMessage);
                w.Close();
            }
            catch (Exception ex)
            {

                throw ex;
            }

        }

        /// <summary>
        /// Dump log into console
        /// </summary>
        public void DumpLog()
        {

            try
            {
                StreamReader r = File.OpenText(LogFileName);
                string line;
                while ((line = r.ReadLine()) != null)
                {
                    Console.WriteLine(line);
                }
                r.Close();
            }
            catch (Exception ex)
            {

                throw ex;
            }


        }

        /// <summary>
        /// Get a string representing all elements of list
        /// </summary>
        /// <param name="byteList">bytes list</param>
        /// <returns>string</returns>
        public string PrintBytes(List<byte> byteList)
        {
            return PrintBytes(byteList.ToArray());
        }


        /// <summary>
        /// Get a string representing all elements of array
        /// </summary>
        /// <param name="byteArray">byte array</param>
        /// <returns>string</returns>
        public string PrintBytes(byte[] byteArray)
        {
            string result = "{";
            for (int i = 0; i < byteArray.Length - 1; i++)
                result += byteArray[i].ToString("X2") + ", ";
            result += byteArray[byteArray.Length - 1].ToString("X2") + "}";
            return result;
        }


        public string PrintBytes(byte[,] byteArray)
        {
            string result = "{";
            for (int i = 0; i < byteArray.GetLength(0); i++)
            {
                result += "{";
                for( int j = 0; j < byteArray.GetLength(1)-1; j++)
                    result += byteArray[i,j].ToString("X2") + ", ";

                result += byteArray[i, byteArray.GetLength(1)-1].ToString("X2") + "}";

            }
            result += "}";
            return result;
        }

    }
}
