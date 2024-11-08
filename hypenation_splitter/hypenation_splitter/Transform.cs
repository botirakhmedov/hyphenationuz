using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hypenation_splitter
{
    internal class Transform
    {

        public void Proccess(string fileName)
        {
            if (File.Exists(fileName))
            {
                IEnumerable<string> files = File.ReadAllLines(fileName);
                if (files != null || files.Any())
                {
                    string outFile = "hypenation.txt";
                    using (StreamWriter writer = new StreamWriter(outFile))
                    {
                        foreach (string file in files)
                        {

                        }
                    }
                }
            }
            else
            {
                Console.WriteLine("File not exsists!");
            }

        }
    }
}
