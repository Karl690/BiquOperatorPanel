using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Imaging;

namespace png2c
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = AppContext.BaseDirectory +  "..\\Images";
            string[] pngfiles = Directory.GetFiles(path, "*.png");
            foreach(var pngfile in pngfiles)
            {
                ConvertToCFile(pngfile);
            }

        }

        static void ConvertToCFile(string pngfile)
        {
            string targetPath = Path.GetDirectoryName(pngfile) + "/../BiquOperatorPanel/Icons";
            if (!Directory.Exists(targetPath)) Directory.CreateDirectory(targetPath);
            string variable = Path.GetFileNameWithoutExtension(pngfile);
            targetPath += "/icon_" + variable + ".c";

            Bitmap png = new Bitmap(pngfile);
            //Bitmap bmp565 = png.Clone(new Rectangle(0, 0, png.Width, png.Height), PixelFormat.Format16bppRgb565);
            var bmpData = png.LockBits(new Rectangle(0, 0, png.Width, png.Height), ImageLockMode.ReadOnly, PixelFormat.Format16bppRgb565);
            int bytes = Math.Abs(bmpData.Stride) * png.Height;
            byte[] rgbValues = new byte[bytes];

            System.Runtime.InteropServices.Marshal.Copy(bmpData.Scan0, rgbValues, 0, bytes);
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("#include \"icons.h\"");
            sb.AppendLine($"const uint8_t Icon_{variable}[] = " + "{");
            int cnt = 0;
            int cols = 25;
            foreach (var rgb in rgbValues)
            {
                if (cnt < bytes)
                {
                    if (cnt % cols == 0 && cnt != 0) sb.Append("\n");
                    if (cnt + 1 < bytes) sb.Append($"0x{rgb:X2}, ");
                    else sb.Append($"0x{rgb:X2} ");
                }

                cnt++;
            }
            sb.AppendLine("};");
            sb.AppendLine($"ICONINFO IconStart = {"{"}{png.Width}, {png.Height}, (uint8_t*)Icon_{variable}{"}"};");
            File.WriteAllText(targetPath, sb.ToString());
        }
    }
}
