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



        // Render相关的接口
        [DllImport("LibPlayer")]
        public static extern IntPtr CreateRender(IntPtr hwnd);

        [DllImport("LibPlayer")]
        public static extern int DestroyRender(IntPtr render);

        // Player相关的接口
        [DllImport("LibPlayer")]
        public static extern int CreatePlayer();
        
        [DllImport("LibPlayer")]
        public static extern int DestroyPlayer();

        [DllImport("LibPlayer")]
        public static extern int Player_Open(string url);

        [DllImport("LibPlayer")]
        public static extern int Player_Play();

        [DllImport("LibPlayer")]
        public static extern int Player_Pause();

        [DllImport("LibPlayer")]
        public static extern int Player_Close();


        // 其它接口
        [DllImport("LibPlayer")]
        public static extern int RenderOneFrame(IntPtr render);



    }
}
