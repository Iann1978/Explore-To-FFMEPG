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
        }

        private void buttonReleaseGL_Click(object sender, EventArgs e)
        {
            LibPlayer.ReleaseGL();
        }

        private void buttonCreatePlayer_Click(object sender, EventArgs e)
        {
            LibPlayer.CreatePlayer();
        }

        private void buttonRenderOneFrame_Click(object sender, EventArgs e)
        {
            LibPlayer.RenderOneFrame();
        }

        private void buttonDestroyPlayer_Click(object sender, EventArgs e)
        {
            LibPlayer.DestroyPlayer();
        }
    }
}
