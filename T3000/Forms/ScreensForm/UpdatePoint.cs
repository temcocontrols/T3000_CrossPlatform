using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SQLite;
namespace T3000.Forms
{
    class UpdatePoint
    {
        private SqliteConnect conn;
        public Boolean Update_point(int param_ida, String param_lblname)
        {
            conn = new SqliteConnect();
            Boolean flag = false;
            if (conn.Sqlite_Connect())
            {


                try
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "UPDATE AtributosLabels SET lbl_name='"+param_lblname+"',lbl_text='"+param_lblname+"' WHERE id_a ="+param_ida;
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();
                    flag = true;
                }
                catch (SQLiteException ex)
                {
                    flag = false;
                    System.Windows.Forms.MessageBox.Show(ex.Message, "Error !");
                }




            }

            return flag;
        }

        public Boolean Update_point_image(int param_idprg, String param_image, int param_screenid)
        {
            conn = new SqliteConnect();
            Boolean flag = false;
            if (conn.Sqlite_Connect())
            {


                try
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "UPDATE AtributosLabels SET image='" + param_image + "' WHERE id_prg =" + param_idprg + " AND link=" + param_screenid;
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();
                    flag = true;
                }
                catch (SQLiteException ex)
                {
                    flag = false;
                    System.Windows.Forms.MessageBox.Show(ex.Message, "Error !");
                }




            }

            return flag;
        }

        public Boolean Update_point(int param_id,int param_x,int param_y)
        {
            conn = new SqliteConnect();
            Boolean flag = false;
            if (conn.Sqlite_Connect())
            {


                try
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "UPDATE AtributosLabels SET point_x=" + param_x + ",point_y=" + param_y +" WHERE  id_a=" + param_id;
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();
                    flag = true;
                }
                catch (SQLiteException ex)
                {
                    flag = false;
                    System.Windows.Forms.MessageBox.Show(ex.Message, "Error !");
                }




            }

            return flag;
        }
    }
}
