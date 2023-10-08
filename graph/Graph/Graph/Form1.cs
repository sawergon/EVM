using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graph
{
    public partial class Form1 : Form
    {
        private GraphList _graph = null;
        private int _vn = 0, _vk = 0, _error_way = -1, _error_graph = -2, _cnt = 0;
        private Reb _r1, _r2;
        private LinkedList<LinkedList<int>> _ways;

        public Form1()
        {
            _r1 = new Reb(0, 0);
            _r2 = new Reb(0, 0);
            InitializeComponent();
        }

        private PictureBox pictureBox1 = new PictureBox();

// Cache font instead of recreating font objects each time we paint.
        private Font fnt = new Font("Arial", 10);

        private void Form1_Load(object sender, System.EventArgs e)
        {
            // Dock the PictureBox to the form and set its background to white.
            pictureBox1.Dock = DockStyle.Fill;
            pictureBox1.BackColor = Color.White;
            // Connect the Paint event of the PictureBox to the event handler method.
            pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);

            // Add the PictureBox control to the Form.
            this.Controls.Add(pictureBox1);
        }

        private void pictureBox1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            // Create a local version of the graphics object for the PictureBox.
            var g = e.Graphics;

            // // Draw a string on the PictureBox.
            // g.DrawString("This is a diagonal line drawn on the control",
            //     fnt, System.Drawing.Brushes.Blue, new Point(30,30));
            // Draw a line in the PictureBox.
            if (_graph != null)
            {
                int left = 200,
                    top = 130,
                    right = 530,
                    bottom = 430,
                    width = right - left,
                    height = width,
                    p = 10,
                    ver = _graph.Len();
                int[] ver_x = new int [ver], ver_y = new int [ver];

                for (var i = 0; i < ver; ++i)
                {
                    ver_x[i] = Convert.ToInt32(width * 0.4 * (Math.Cos(2 * Math.PI / ver * i) + 2.5));
                    ver_y[i] = Convert.ToInt32(height * 0.4 * (Math.Sin(2 * Math.PI / ver * i) + 1.5));
                }

                var pen = Pens.Black;
                var way = new LinkedList<int>();
                if (_ways != null)
                {
                    var h = 0;
                    foreach (var tmp in _ways)
                    {
                        if (_cnt == h)
                        {
                            way = tmp;
                            _cnt++;
                            break;
                        }

                        h++;
                    }
                    place_way(_cnt, way);
                }

                var edges = _graph.GetEdgesWithWay(way);

                foreach (var edge in edges)
                {
                    pen = edge.Marked ? Pens.Red : Pens.Black;
                    g.DrawLine(pen, ver_x[edge.Left] - 5, ver_y[edge.Left] + p + 5, ver_x[edge.Right] - 5,
                        ver_y[edge.Right] + p + 5);
                }

                for (int i = 0; i < ver; i++)
                {
                    g.DrawEllipse(Pens.Black, ver_x[i] - p, ver_y[i] + p, p, p);
                    g.DrawString(i.ToString(), fnt, Brushes.Black, ver_x[i] - 4, ver_y[i] - 8);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                _vn = Convert.ToInt32(textBox1.Text);
                _vk = Convert.ToInt32(textBox2.Text);
                _r1.Left = Convert.ToInt32(textBox3.Text);
                _r1.Right = Convert.ToInt32(textBox4.Text);
                _r2.Left = Convert.ToInt32(textBox5.Text);
                _r2.Right = Convert.ToInt32(textBox6.Text);
                _error_way = 0;
            }
            catch (FormatException)
            {
                _error_way = 1;
                label5.Text = "Неверный ввод вершин или ребер";
                // MessageBox.Show("Неверный ввод вершин или ребер", "ОШИБКА", MessageBoxButtons.OK);
            }

            if (_error_way != _error_graph) return;
            _cnt = 0;
            _ways = _graph.FindPaths(_r1, _r2, _vn, _vk);
            if (_ways.Count < 1) label5.Text = "Нет путей";
            else pictureBox1.Refresh();
        }

        private void сКлавиатурыToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var data = richTextBox1.Text;
            char[] sep = { ' ', '\n', '\t' };
            var mData = data.Split(sep);
            var quantity = 0;
            try
            {
                quantity = Convert.ToInt32(mData[0]);
                _graph = new GraphList(quantity);
                if (mData.Length % 2 == 0) throw new FormatException();
                else
                {
                    for (var i = 1; i < mData.Length; i += 2)
                    {
                        _graph.AddLink(Convert.ToInt32(mData[i]), Convert.ToInt32(mData[i + 1]));
                    }

                    _error_graph = 0;
                    _error_way = -1;
                    _ways = null;
                    _cnt = 0;
                    label5.Text = "";
                    pictureBox1.Refresh();
                }
            }
            catch (FormatException)
            {
                _error_graph = 2;
                label5.Text = "Неверный ввод графа. Вводите только целые числа";
                // MessageBox.Show("Неверный ввод графа", "ОШИБКА", MessageBoxButtons.OK);
            }
            catch (NullReferenceException)
            {
                _error_graph = 2;
                label5.Text = "Неверный ввод графа. Вершин больше " + quantity + " нет";
                // MessageBox.Show("Неверный ввод графа", "ОШИБКА", MessageBoxButtons.OK);
            }
        }

        private void place_way(int no, LinkedList<int> way)
        {
            var k = "Всего путей " + _ways.Count + ":\n№";
            k +=  no + ": ";
            k = way.Aggregate(k, (current, vertex) => current + (vertex.ToString() + ' '));

            label5.Text = k;
        }
        
        private void button2_Click(object sender, EventArgs e)
        {
            if (_graph == null || _error_graph != _error_way) return;
            if (_cnt >= _ways.Count)
            {
                _cnt = 0;
                pictureBox1.Refresh();
            }
            else
            {
                pictureBox1.Refresh();
            }
        }

        private void выходToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void изФайлаToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var fileContent = string.Empty;
            var filePath = string.Empty;

            using (var openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "C:\\Users\\Alex\\RiderProjects\\EVM\\graph";
                openFileDialog.Filter = "Graph files (*.graph)|*.graph";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() != DialogResult.OK) return;
                //Get the path of specified file
                filePath = openFileDialog.FileName;

                //Read the contents of the file into a stream
                var fileStream = openFileDialog.OpenFile();

                using (var reader = new StreamReader(fileStream))
                {
                    fileContent = reader.ReadToEnd();
                }
                char[] sep = { ' ', '\n', '\t' };
                var mData = fileContent.Split(sep);
                var quantity = 0;
                try
                {
                    quantity = Convert.ToInt32(mData[0]);
                    _graph = new GraphList(quantity);
                    if (mData.Length % 2 == 0) _error_graph = 2;
                    else
                    {
                        for (var i = 1; i < mData.Length; i += 2)
                        {
                            _graph.AddLink(Convert.ToInt32(mData[i]), Convert.ToInt32(mData[i + 1]));
                        }

                        _error_graph = 0;
                        _error_way = -1;
                        _ways = null;
                        _cnt = 0;
                        label5.Text = "";
                        pictureBox1.Refresh();
                    }
                }
                catch (FormatException)
                {
                    _error_graph = 2;
                    label5.Text = "Неверный ввод графа. Вводите только целые числа";
                    // MessageBox.Show("Неверный ввод графа", "ОШИБКА", MessageBoxButtons.OK);
                }
                catch (NullReferenceException)
                {
                    _error_graph = 2;
                    label5.Text = "Неверный ввод графа. Вершин больше " + quantity + " нет";
                    // MessageBox.Show("Неверный ввод графа", "ОШИБКА", MessageBoxButtons.OK);
                }
            }
        }
    }
}