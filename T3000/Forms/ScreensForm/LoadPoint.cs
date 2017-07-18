using System.Data.SQLite;
using System.Data;
using System.Windows.Forms;

namespace T3000.Forms
{
    class LoadPoint
    {


       private int __screenid;
       private int __prgfileid;
        DataTable tb;
        SqliteConnect conn;

        public LoadPoint(int param_fileid,int param_screen)
        {
            Prgfileid = param_fileid;
            Screenid = param_screen;
            string query = "SELECT id_a,lbl_name, lbl_text, point_x, point_y,type,image,link FROM AtributosLabels WHERE id_prg = " + Prgfileid+" AND screen_id ="+Screenid;
            //MessageBox.Show(query);
            conn = new SqliteConnect();

            if (conn.Sqlite_Connect())
            {
                try
                {
                    SQLiteDataAdapter adapter = new SQLiteDataAdapter(query, conn.Conexion);
                    tb = new DataTable();
                    adapter.Fill(tb);

                }
                catch (SQLiteException ex)
                {
                   
                    System.Windows.Forms.MessageBox.Show(ex.Message, "Error !");
                }
            }
           
           


        }


        public int Prgfileid { get => Prgfileid1; set => Prgfileid1 = value; }
        public int Screenid { get => __screenid; set => __screenid = value; }
        public int Prgfileid1 { get => __prgfileid; set => __prgfileid = value; }
        public DataTable Tb { get => tb; set => tb = value; }
    }
}
