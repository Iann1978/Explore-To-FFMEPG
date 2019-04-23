﻿using System;
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

        //获取窗口标题
        [DllImport("user32", SetLastError = true)]
        public static extern int GetWindowText(
        IntPtr hWnd, //窗口句柄
        StringBuilder lpString, //标题
        int nMaxCount  //最大值
        );
        //获取类的名字
        [DllImport("user32.dll")]
        private static extern int GetClassName(
            IntPtr hWnd, //句柄
            StringBuilder lpString, //类名
            int nMaxCount //最大值
        );
        //根据坐标获取窗口句柄
        [DllImport("user32")]
        private static extern IntPtr WindowFromPoint(
        Point Point  //坐标
        );


        ////根据坐标获取窗口句柄
        //[DllImport("OpenGLDll")]
        //private static extern int GetDllVersion();

        ////根据坐标获取窗口句柄
        //[DllImport("OpenGLDll")]
        //private static extern int CreateGL(IntPtr hwnd);

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            int x = Cursor.Position.X;
            int y = Cursor.Position.Y;
            Point p = new Point(x, y);
            IntPtr formHandle = WindowFromPoint(p);//得到窗口句柄
            StringBuilder title = new StringBuilder(256);
            GetWindowText(formHandle, title, title.Capacity);//得到窗口的标题
            StringBuilder className = new StringBuilder(256);
            GetClassName(formHandle, className, className.Capacity);//得到窗口的句柄

            int ver = LibPlayer.GetDllVersion();
            int err = LibPlayer.CreateGL(formHandle);
            this.textBox1.Text = "窗口句柄:" + formHandle.ToString() + Environment.NewLine + "窗口标题:" + title + Environment.NewLine + "类名:" + className + ", OpenGLDll Version:" + ver + ", err:" + err;

        }
    }
}
