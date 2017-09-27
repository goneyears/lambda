using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using System.Security.Cryptography;
namespace Cell4
{
    static class FileSys
    {
        public static void CopyDir(string srcdir, string dstdir)
        {
            bool overwrite = true;
            string todir = Path.Combine(dstdir, Path.GetFileName(srcdir));

            if (!Directory.Exists(todir))
                Directory.CreateDirectory(todir);

            foreach (var s in Directory.GetFiles(srcdir))
                File.Copy(s, Path.Combine(todir, Path.GetFileName(s)), overwrite);

            foreach (var s in Directory.GetDirectories(srcdir))
                CopyDir(s, todir);
        }

        public static bool CopyFiles(string srcdir, string dstdir, List<string> strFiles)
        {
            bool overwrite=true; 
            foreach (var sf in strFiles) {
                string srcfile=Path.Combine(srcdir,sf);
                string dstfile=Path.Combine(dstdir,sf);
                File.Copy(srcfile, dstfile, overwrite);
                if (CompareFileWithMD5(srcfile, dstfile) == false) {
                    return false;
                }
                
            }
            return true;
        }

        public static List<string> GetDirMD5(string dir)
        {
            List<string> md5List = new List<string>();
            foreach (var s in Directory.GetFiles(dir))
            {
                md5List.Add(GetFileMD5(s));
            }

            foreach (var s in Directory.GetDirectories(dir))
            {
                md5List.AddRange(GetDirMD5(s));
            }

            return md5List;
        }

        public static bool CompareDirFilesWithMD5(string srcdir, string dstdir)
        {
            List<string> srcMD5List = new List<string>();
            List<string> dstMD5List = new List<string>();
            srcMD5List = GetDirMD5(srcdir);
            dstMD5List = GetDirMD5(dstdir);

            List<string> diffMD5List = srcMD5List.Except(dstMD5List).ToList();
            return diffMD5List.Count == 0;

        }

        public static bool CompareFileWithMD5(string srcfile, string dstfile)
        {

            return GetFileMD5(srcfile)==GetFileMD5(dstfile);
        }

        public static string GetFileMD5(string path)
        {
            string ctyptStr = "";
            byte[] cryptBytes;
            using (FileStream fs = new FileStream(path, FileMode.Open))
            {
                MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
                cryptBytes = md5.ComputeHash(fs);
            }
            for (int i = 0; i < cryptBytes.Length; i++)
            {
                ctyptStr += cryptBytes[i].ToString("X2");
            }
            return ctyptStr;
        }



    }
}
