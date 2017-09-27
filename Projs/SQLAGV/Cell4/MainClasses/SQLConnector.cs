using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
namespace Cell4
{
    class SQLConnector
    {
        public SQLConnector(string constr)
        {
            _constr=constr;
        } 
        private string _constr ;
        public DataTable GetNewData(string queryStr)
        {
            SqlConnection con = new SqlConnection(_constr);
            //con.Open();
            SqlDataAdapter da = new SqlDataAdapter(queryStr, con);
            DataTable dt=new DataTable();
            da.Fill(dt);
            con.Close();
            return dt;
        }

        public void SendCommand(string cmdStr)
        {
            SqlConnection con = new SqlConnection(_constr);
            con.Open();
            SqlCommand command = con.CreateCommand();
            command.CommandText = cmdStr;
            command.ExecuteNonQuery();
            con.Close();  
        }

    }
}
