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
        private int get_id;

        public int Get_id { get { return get_id; } set { get_id = value; } }

        public Boolean Insert_point(int param_idprg,String param_lblname,String param_lbltext, int param_screenid, int param_pointx, int param_pointy, int param_type,int param_link)
        {
            conn = new SqliteConnect();
            Boolean flag = false;
            if (conn.Sqlite_Connect())
            {


                try
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "INSERT INTO AtributosLabels(id_prg,lbl_name,lbl_text,screen_id,point_x,point_y,type,link) VALUES(" + param_idprg + ",'" + param_lblname + "','" + param_lbltext + "'," + param_screenid + "," + param_pointx + "," + param_pointy + "," + param_type + ","+param_link+")";
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();

                    sql = "select MAX(id_a) as id from AtributosLabels";
                    command = new SQLiteCommand(sql, conn.Conexion);
                    string getValue = command.ExecuteScalar().ToString();
                    if (getValue != null)
                    {
                        Get_id = int.Parse(getValue);


                    }
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


        public Boolean Insert_point(int param_idprg, String param_lblname, String param_lbltext, int param_screenid, int param_pointx, int param_pointy, int param_type,int param_link, String param_path)
        {
            conn = new SqliteConnect();
            Boolean flag = false;
            if (conn.Sqlite_Connect())
            {


                try
                {
                    DateTime localDate = DateTime.Now;
                    string sql = "INSERT INTO AtributosLabels(id_prg,lbl_name,lbl_text,screen_id,point_x,point_y,type,link,image) VALUES(" + param_idprg + ",'" + param_lblname + "','" + param_lbltext + "'," + param_screenid + "," + param_pointx + "," + param_pointy + "," + param_type + ","+ param_link + ",'"+ param_path + "')";
                    SQLiteCommand command = new SQLiteCommand(sql, conn.Conexion);
                    command.ExecuteNonQuery();
                    sql = "select MAX(id_a) as id from AtributosLabels";
                    command = new SQLiteCommand(sql, conn.Conexion);
                    string getValue = command.ExecuteScalar().ToString();
                    if (getValue != null)
                    {
                        Get_id = int.Parse(getValue);


                    }

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
