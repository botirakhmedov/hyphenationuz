using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hyphenation_splitter
{
    internal class Transform
    {
        private string vowels = "aeiou";
        private string specials = "‘’'`’";
        public void Proccess(string fileName)
        {
            SplitToSyllable(fileName);
            /*if (File.Exists(fileName))
            {
                IEnumerable<string> files = File.ReadAllLines(fileName);
                if (files != null && files.Any())
                {
                    string outFile = "hyphenation.txt";
                    using (StreamWriter writer = new(outFile))
                    {
                        foreach (string file in files)
                        {
                            writer.WriteLine("asdasd");
                        }
                    }
                }
            }
            else
            {
                Console.WriteLine("File not exsists!");
            }*/

        }

        private List<string> SplitToSyllable(string input_word)
        {
            List<string> retVal = new();
            string result = string.Empty;
            var chars = input_word.ToCharArray();
            var builder = new StringBuilder();
            char currentChar;
            char nextChar = char.MinValue;
            for(int i = 0; i < chars.Length; i++)
            {
                int nextIndex = i + 1;
                currentChar = chars[i];
                if(nextIndex < chars.Length)
                {
                    nextChar = chars[nextIndex];
                }
                builder.Append(currentChar);
                if(specials.Contains(currentChar))
                {
                    continue;
                }

                if(vowels.Contains(currentChar))
                {
                    if(vowels.Contains(nextChar))
                }

            }
            result = builder.ToString();
            
            return retVal;
        }
    }
}
