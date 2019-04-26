namespace CSPlayer
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.buttonInitializeGL = new System.Windows.Forms.Button();
            this.buttonReleaseGL = new System.Windows.Forms.Button();
            this.buttonCreatePlayer = new System.Windows.Forms.Button();
            this.buttonRenderOneFrame = new System.Windows.Forms.Button();
            this.buttonDestroyPlayer = new System.Windows.Forms.Button();
            this.timerForPlaying = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.output = new System.Windows.Forms.Label();
            this.buttonOpen = new System.Windows.Forms.Button();
            this.buttonPlay = new System.Windows.Forms.Button();
            this.buttonStop = new System.Windows.Forms.Button();
            this.videopath = new System.Windows.Forms.Label();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonInitializeGL
            // 
            this.buttonInitializeGL.Location = new System.Drawing.Point(1036, 64);
            this.buttonInitializeGL.Name = "buttonInitializeGL";
            this.buttonInitializeGL.Size = new System.Drawing.Size(139, 41);
            this.buttonInitializeGL.TabIndex = 1;
            this.buttonInitializeGL.Text = "InitializeGL";
            this.buttonInitializeGL.UseVisualStyleBackColor = true;
            this.buttonInitializeGL.Click += new System.EventHandler(this.buttonInitializeGL_Click);
            // 
            // buttonReleaseGL
            // 
            this.buttonReleaseGL.Location = new System.Drawing.Point(1036, 394);
            this.buttonReleaseGL.Name = "buttonReleaseGL";
            this.buttonReleaseGL.Size = new System.Drawing.Size(139, 41);
            this.buttonReleaseGL.TabIndex = 2;
            this.buttonReleaseGL.Text = "ReleaseGL";
            this.buttonReleaseGL.UseVisualStyleBackColor = true;
            this.buttonReleaseGL.Click += new System.EventHandler(this.buttonReleaseGL_Click);
            // 
            // buttonCreatePlayer
            // 
            this.buttonCreatePlayer.Location = new System.Drawing.Point(1036, 139);
            this.buttonCreatePlayer.Name = "buttonCreatePlayer";
            this.buttonCreatePlayer.Size = new System.Drawing.Size(139, 41);
            this.buttonCreatePlayer.TabIndex = 3;
            this.buttonCreatePlayer.Text = "CreatePlayer";
            this.buttonCreatePlayer.UseVisualStyleBackColor = true;
            this.buttonCreatePlayer.Click += new System.EventHandler(this.buttonCreatePlayer_Click);
            // 
            // buttonRenderOneFrame
            // 
            this.buttonRenderOneFrame.Location = new System.Drawing.Point(1036, 224);
            this.buttonRenderOneFrame.Name = "buttonRenderOneFrame";
            this.buttonRenderOneFrame.Size = new System.Drawing.Size(166, 41);
            this.buttonRenderOneFrame.TabIndex = 4;
            this.buttonRenderOneFrame.Text = "RenderOneFrame";
            this.buttonRenderOneFrame.UseVisualStyleBackColor = true;
            this.buttonRenderOneFrame.Click += new System.EventHandler(this.buttonRenderOneFrame_Click);
            // 
            // buttonDestroyPlayer
            // 
            this.buttonDestroyPlayer.Location = new System.Drawing.Point(1036, 309);
            this.buttonDestroyPlayer.Name = "buttonDestroyPlayer";
            this.buttonDestroyPlayer.Size = new System.Drawing.Size(166, 41);
            this.buttonDestroyPlayer.TabIndex = 5;
            this.buttonDestroyPlayer.Text = "DestroyPlayer";
            this.buttonDestroyPlayer.UseVisualStyleBackColor = true;
            this.buttonDestroyPlayer.Click += new System.EventHandler(this.buttonDestroyPlayer_Click);
            // 
            // timerForPlaying
            // 
            this.timerForPlaying.Interval = 33;
            this.timerForPlaying.Tick += new System.EventHandler(this.Timer_Render);
            // 
            // output
            // 
            this.output.AutoSize = true;
            this.output.Location = new System.Drawing.Point(12, 825);
            this.output.Name = "output";
            this.output.Size = new System.Drawing.Size(35, 18);
            this.output.TabIndex = 6;
            this.output.Text = "d\\n";
            // 
            // buttonOpen
            // 
            this.buttonOpen.Location = new System.Drawing.Point(36, 705);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(75, 33);
            this.buttonOpen.TabIndex = 7;
            this.buttonOpen.Text = "Open";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
            // 
            // buttonPlay
            // 
            this.buttonPlay.Location = new System.Drawing.Point(140, 705);
            this.buttonPlay.Name = "buttonPlay";
            this.buttonPlay.Size = new System.Drawing.Size(75, 33);
            this.buttonPlay.TabIndex = 8;
            this.buttonPlay.Text = "Play";
            this.buttonPlay.UseVisualStyleBackColor = true;
            // 
            // buttonStop
            // 
            this.buttonStop.Location = new System.Drawing.Point(246, 705);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(75, 33);
            this.buttonStop.TabIndex = 9;
            this.buttonStop.Text = "Stop";
            this.buttonStop.UseVisualStyleBackColor = true;
            // 
            // videopath
            // 
            this.videopath.AutoSize = true;
            this.videopath.Location = new System.Drawing.Point(12, 9);
            this.videopath.Name = "videopath";
            this.videopath.Size = new System.Drawing.Size(98, 18);
            this.videopath.TabIndex = 10;
            this.videopath.Text = "videopath:";
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(36, 753);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(1139, 69);
            this.trackBar1.TabIndex = 11;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1222, 852);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.videopath);
            this.Controls.Add(this.buttonStop);
            this.Controls.Add(this.buttonPlay);
            this.Controls.Add(this.buttonOpen);
            this.Controls.Add(this.output);
            this.Controls.Add(this.buttonDestroyPlayer);
            this.Controls.Add(this.buttonRenderOneFrame);
            this.Controls.Add(this.buttonCreatePlayer);
            this.Controls.Add(this.buttonReleaseGL);
            this.Controls.Add(this.buttonInitializeGL);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button buttonInitializeGL;
        private System.Windows.Forms.Button buttonReleaseGL;
        private System.Windows.Forms.Button buttonCreatePlayer;
        private System.Windows.Forms.Button buttonRenderOneFrame;
        private System.Windows.Forms.Button buttonDestroyPlayer;
        private System.Windows.Forms.Timer timerForPlaying;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Label output;
        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.Button buttonPlay;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.Label videopath;
        private System.Windows.Forms.TrackBar trackBar1;
    }
}

