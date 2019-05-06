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
        IntPtr render;
        IntPtr player;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            render = LibPlayer.CreateRender(Handle);
            Log("CreateRender");
            player = LibPlayer.CreatePlayer();
            Log("CreatePlayer");
            timerForPlaying.Start();
            Log("StartTimer");
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            timerForPlaying.Stop();
            Log("StopTimer");
            LibPlayer.DestroyPlayer(player);
            Log("DestroyPlayer");
            LibPlayer.DestroyRender(render);
            Log("DestroyRender");
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
        }

        private void buttonInitializeGL_Click(object sender, EventArgs e)
        {   
            render = LibPlayer.CreateRender(Handle);
            Log("CreateRender");
        }

        private void buttonReleaseGL_Click(object sender, EventArgs e)
        {
            LibPlayer.DestroyRender(render);
            Log("DestroyRender");
        }

        private void buttonCreatePlayer_Click(object sender, EventArgs e)
        {
            player = LibPlayer.CreatePlayer();
            Log("CreatePlayer");
            timerForPlaying.Start();
            Log("StartTimer");
        }

        private void buttonRenderOneFrame_Click(object sender, EventArgs e)
        {
            LibPlayer.RenderOneFrame(render, player);
        }

        private void buttonDestroyPlayer_Click(object sender, EventArgs e)
        {
            timerForPlaying.Stop();
            Log("StopTimer");
            LibPlayer.DestroyPlayer(player);
            Log("DestroyPlayer");
        }

        private void Timer_Render(object sender, EventArgs e)
        {
            LibPlayer.RenderOneFrame(render, player);
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
                    Log(filePath);
                    

                    LibPlayer.Player_Open(player, filePath);
                }
            }
        }

        private void buttonPlay_Click(object sender, EventArgs e)
        {
            LibPlayer.Player_Play(player);
            Log("Play");
        }

        private void buttonPause_Click(object sender, EventArgs e)
        {
            LibPlayer.Player_Pause(player);
            Log("Pause");
        }

        //List<string> loglist = new List<string>();
        private void buttonClose_Click(object sender, EventArgs e)
        {
            LibPlayer.Player_Close(player);
            Log("Close");
        }

        private void Log(string str)
        {
            output.Focus();
            //设置光标的位置到文本尾 
            output.Select(output.TextLength, 0);
            //滚动到控件光标处 
            output.ScrollToCaret();
            output.AppendText("\n"+str);
        }

       
    }
}
