using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PRGReaderLibrary.Types.Enums.Codecs;

namespace PRGReaderLibrary.Utilities
{
    /// <summary>
    /// Decodes array of bytes into plain text Control Basic
    /// </summary>
    public class Decoder
    {
        /// <summary>
        /// Decode a ProgramCode Into Plain Text
        /// </summary>
        /// <param name="PCode">Byte array (encoded program)</param>
        public static string DecodeBytes(byte[] PCode)
        {
            byte[] prgsize = new byte[2];
            string result = "";
            Array.Copy(PCode, 0, prgsize, 0, 2);
            int ProgLenght = BytesExtensions.ToInt16(prgsize);

            int offset; //offset after count of total encoded bytes
            bool isFirstToken = true;

            for (offset=2; offset <= ProgLenght;offset++)
            {
                var tokenvalue = (byte)PCode[offset];
                switch (tokenvalue)
                {
                    case (byte)TYPE_TOKEN.NUMBER:
                        if (isFirstToken)
                        {
                        offset++;
                        short LineNumber = BytesExtensions.ToInt16(PCode, ref offset);
                        result += LineNumber.ToString(); //LINE NUMBER, 2 Bytes
                        }

                        isFirstToken = false;
                        break;

                    case (byte)LINE_TOKEN.REM:
                        result += " " + GetComment(PCode,ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.ASSIGN:
                        result += " " + GetAssigment(PCode,ref offset)+ System.Environment.NewLine;
                        isFirstToken = true;
                        break;
                    
                    default:
                        break;
                }
            }

            return result;
        }

        private static string GetComment(byte[] source, ref int offset)
        {
            string result = "REM ";
            offset++;
            short count = source[offset++];
            
            List<byte> comment = new List<byte>();
            comment = source.ToList().GetRange(offset, count);
            //Array.Copy(source, offset, comment, 0, count);
            result += System.Text.Encoding.Default.GetString(comment.ToArray()) + System.Environment.NewLine;
            offset += count;


            return result;

        }

        private static string GetAssigment(byte[] source,ref int offset)
        {
            return "ASSIGMENT";
        }
    }
}