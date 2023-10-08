using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graph
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // var gr = new GraphList(10);
            // gr.AddLink(0, 1);
            // gr.AddLink(0, 4);
            // gr.AddLink(0, 5);
            // gr.AddLink(1, 2);
            // gr.AddLink(1, 6);
            // gr.AddLink(2, 3);
            // gr.AddLink(2, 7);
            // gr.AddLink(3, 8);
            // gr.AddLink(3, 4);
            // gr.AddLink(4, 9);
            // gr.AddLink(5, 7);
            // gr.AddLink(5, 8);
            // gr.AddLink(6, 8);
            // gr.AddLink(6, 9);
            // gr.AddLink(7, 9);
            //
            //
            // Reb r1 = new Reb(1, 2), r2 = new Reb(3, 4);
            // int vn = 0, vk = 5;
            //
            // var res = gr.FindPaths(r1, r2, vn, vk);
            //
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}