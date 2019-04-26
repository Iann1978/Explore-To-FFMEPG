using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace CSPlayer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }
        
        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
        }

        private void buttonInitializeGL_Click(object sender, EventArgs e)
        {   
            LibPlayer.InitializeGL(Handle);
            output.Text = "InitializeGL";
        }

        private void buttonReleaseGL_Click(object sender, EventArgs e)
        {
            LibPlayer.ReleaseGL();
        }

        private void buttonCreatePlayer_Click(object sender, EventArgs e)
        {
            LibPlayer.CreatePlayer();
            timerForPlaying.Start();
        }

        private void buttonRenderOneFrame_Click(object sender, EventArgs e)
        {
            LibPlayer.RenderOneFrame();
        }

        private void buttonDestroyPlayer_Click(object sender, EventArgs e)
        {
            timerForPlaying.Stop();
            LibPlayer.DestroyPlayer();
        }

        private void Timer_Render(object sender, EventArgs e)
        {
            LibPlayer.RenderOneFrame();
            //label1.Text = (++num).ToString();
            //Thread.Sleep(3000);
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "e:\\Movies";
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    //Get the path of specified file
                    string filePath = openFileDialog.FileName;
                    output.Text = filePath;
                }
            }
        }
    }
}
