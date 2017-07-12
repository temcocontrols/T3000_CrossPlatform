using System;
using System.Data;
using System.Data.SQLite;
using System.Windows.Forms;

namespace T3000.Forms
{
    class prgfilename
    {

       private  SqliteConnect conn;
       private  String __prgfilename;
       private  int __prgfileid;

        public prgfilename(String param_file)
        {

            Prgfilename = param_file;

            conn = new SqliteConnect();

            if (conn.Sqlite_Connect())
            {
                if (!FindPrgFile())
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "insert into Prgfile (file_name,creation_date,modification_date) values ('" + Prgfilename + "','" + localDate.ToString("MM/dd/yyyy HH:mm") + "','" + localDate.ToString("MM/dd/yyyy HH:mm") + "')";
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();

                    sql = "select MAX(id) as prgid from Prgfile";
                    command = new SQLiteCommand(sql, conn.Conexion);
                    string getValue = command.ExecuteScalar().ToString();
                    if (getValue != null)
                    {
                        Prgfileid = int.Parse(getValue);


                    }
                }
                else
                {
                    string sql = "select id as prgid from Prgfile where file_name ='" + Prgfilename + "'";
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    string getValue = command.ExecuteScalar().ToString();
                    if (getValue != null)
                    {
                        Prgfileid = int.Parse(getValue);


                    }
                }
            }


            
        }

        public string Prgfilename { get => __prgfilename; set => __prgfilename = value; }
        public int Prgfileid { get => __prgfileid; set => __prgfileid = value; }

        private Boolean FindPrgFile()
        {
            Boolean flag = false;
            
            string sql = "select count(*) as count from Prgfile where file_name ='" + Prgfilename + "'";
            SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
            string getValue = command.ExecuteScalar().ToString();
            if (getValue!=null)
            {
                if (int.Parse(getValue)==1)
                {
                    flag = true;
                }

            }

            return flag;

        }

        
    }
}
