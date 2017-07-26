using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SQLite;
namespace T3000.Forms
{
    class SqliteConnect
    {
        private SQLiteConnection conexion;
        public Boolean Sqlite_Connect()
        {
            var path = AppDomain.CurrentDomain.BaseDirectory;
            
            Boolean flag = false;
            try
            {
                Conexion = new SQLiteConnection("URI=file:"+path+"db.sqlite");
                Conexion.Open();
                flag = true;

            }
            catch (SQLiteException ex)
            {
                flag = false;
                System.Windows.Forms.MessageBox.Show(ex.Message, "Error !");
            }


            return flag;
        }

        public SQLiteConnection Conexion { get { return conexion; } private set { conexion = value; } }
    }
}
