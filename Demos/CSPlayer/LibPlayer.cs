using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace CSPlayer
{
    class LibPlayer
    {
        //根据坐标获取窗口句柄
        [DllImport("LibPlayer")]
        public static extern int GetDllVersion();



        [DllImport("LibPlayer")]
        public static extern int InitializeGL(IntPtr hwnd);

        [DllImport("LibPlayer")]
        public static extern int ReleaseGL();

        [DllImport("LibPlayer")]
        public static extern int CreatePlayer();

        [DllImport("LibPlayer")]
        public static extern int RenderOneFrame();

        [DllImport("LibPlayer")]
        public static extern int DestroyPlayer();

        [DllImport("LibPlayer")]
        public static extern int Player_Open(string url);


    }
}
