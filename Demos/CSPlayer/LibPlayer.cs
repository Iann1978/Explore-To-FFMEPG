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

        //根据坐标获取窗口句柄
        [DllImport("LibPlayer")]
        public static extern int CreateGL(IntPtr hwnd);
    }
}
