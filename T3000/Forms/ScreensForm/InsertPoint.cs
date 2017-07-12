using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SQLite;
namespace T3000.Forms
{
    class InsertPoint
    {
        private SqliteConnect conn;
        public Boolean Insert_point(int param_idprg,String param_lblname,String param_lbltext, int param_screenid, int param_pointx, int param_pointy, int param_type)
        {
            conn = new SqliteConnect();
            Boolean flag = false;
            if (conn.Sqlite_Connect())
            {


                try
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "INSERT INTO AtributosLabels(id_prg,lbl_name,lbl_text,screen_id,point_x,point_y,type) VALUES(" + param_idprg + ",'" + param_lblname + "','" + param_lbltext + "'," + param_screenid + "," + param_pointx + "," + param_pointy + "," + param_type + ")";
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();
                    flag = true;
                }
                catch(SQLiteException ex)
                {
                    flag = false;
                    System.Windows.Forms.MessageBox.Show(ex.Message, "Error !");
                }


             

            }

            return flag;
        }

    }
}
