﻿namespace CSPlayer
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
            this.buttonOpen = new System.Windows.Forms.Button();
            this.buttonPlay = new System.Windows.Forms.Button();
            this.buttonPause = new System.Windows.Forms.Button();
            this.videopath = new System.Windows.Forms.Label();
            this.process = new System.Windows.Forms.TrackBar();
            this.buttonClose = new System.Windows.Forms.Button();
            this.output = new System.Windows.Forms.RichTextBox();
            this.duation = new System.Windows.Forms.Label();
            this.buttonGetDuation = new System.Windows.Forms.Button();
            this.curpos = new System.Windows.Forms.Label();
            this.buttonGetCurpos = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.process)).BeginInit();
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
            // buttonOpen
            // 
            this.buttonOpen.Location = new System.Drawing.Point(36, 655);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(75, 33);
            this.buttonOpen.TabIndex = 7;
            this.buttonOpen.Text = "Open";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
            // 
            // buttonPlay
            // 
            this.buttonPlay.Location = new System.Drawing.Point(140, 655);
            this.buttonPlay.Name = "buttonPlay";
            this.buttonPlay.Size = new System.Drawing.Size(75, 33);
            this.buttonPlay.TabIndex = 8;
            this.buttonPlay.Text = "Play";
            this.buttonPlay.UseVisualStyleBackColor = true;
            this.buttonPlay.Click += new System.EventHandler(this.buttonPlay_Click);
            // 
            // buttonPause
            // 
            this.buttonPause.Location = new System.Drawing.Point(246, 655);
            this.buttonPause.Name = "buttonPause";
            this.buttonPause.Size = new System.Drawing.Size(75, 33);
            this.buttonPause.TabIndex = 9;
            this.buttonPause.Text = "Pause";
            this.buttonPause.UseVisualStyleBackColor = true;
            this.buttonPause.Click += new System.EventHandler(this.buttonPause_Click);
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
            // process
            // 
            this.process.Location = new System.Drawing.Point(36, 703);
            this.process.Name = "process";
            this.process.Size = new System.Drawing.Size(1139, 69);
            this.process.TabIndex = 11;
            this.process.Value = 1;
            this.process.Scroll += new System.EventHandler(this.process_Scroll);
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(353, 655);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 33);
            this.buttonClose.TabIndex = 12;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // output
            // 
            this.output.Location = new System.Drawing.Point(36, 744);
            this.output.Name = "output";
            this.output.Size = new System.Drawing.Size(1139, 96);
            this.output.TabIndex = 14;
            this.output.Text = "";
            // 
            // duation
            // 
            this.duation.AutoSize = true;
            this.duation.Location = new System.Drawing.Point(1045, 682);
            this.duation.Name = "duation";
            this.duation.Size = new System.Drawing.Size(98, 18);
            this.duation.TabIndex = 15;
            this.duation.Text = "videopath:";
            // 
            // buttonGetDuation
            // 
            this.buttonGetDuation.Location = new System.Drawing.Point(459, 655);
            this.buttonGetDuation.Name = "buttonGetDuation";
            this.buttonGetDuation.Size = new System.Drawing.Size(131, 33);
            this.buttonGetDuation.TabIndex = 16;
            this.buttonGetDuation.Text = "GetDuation";
            this.buttonGetDuation.UseVisualStyleBackColor = true;
            this.buttonGetDuation.Click += new System.EventHandler(this.buttonGetDuation_Click);
            // 
            // curpos
            // 
            this.curpos.AutoSize = true;
            this.curpos.Location = new System.Drawing.Point(1045, 625);
            this.curpos.Name = "curpos";
            this.curpos.Size = new System.Drawing.Size(62, 18);
            this.curpos.TabIndex = 17;
            this.curpos.Text = "curpos";
            // 
            // buttonGetCurpos
            // 
            this.buttonGetCurpos.Location = new System.Drawing.Point(620, 655);
            this.buttonGetCurpos.Name = "buttonGetCurpos";
            this.buttonGetCurpos.Size = new System.Drawing.Size(131, 33);
            this.buttonGetCurpos.TabIndex = 18;
            this.buttonGetCurpos.Text = "GetCurpos";
            this.buttonGetCurpos.UseVisualStyleBackColor = true;
            this.buttonGetCurpos.Click += new System.EventHandler(this.buttonGetCurpos_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1222, 852);
            this.Controls.Add(this.buttonGetCurpos);
            this.Controls.Add(this.curpos);
            this.Controls.Add(this.buttonGetDuation);
            this.Controls.Add(this.duation);
            this.Controls.Add(this.output);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.process);
            this.Controls.Add(this.videopath);
            this.Controls.Add(this.buttonPause);
            this.Controls.Add(this.buttonPlay);
            this.Controls.Add(this.buttonOpen);
            this.Controls.Add(this.buttonDestroyPlayer);
            this.Controls.Add(this.buttonRenderOneFrame);
            this.Controls.Add(this.buttonCreatePlayer);
            this.Controls.Add(this.buttonReleaseGL);
            this.Controls.Add(this.buttonInitializeGL);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            ((System.ComponentModel.ISupportInitialize)(this.process)).EndInit();
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
        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.Button buttonPlay;
        private System.Windows.Forms.Button buttonPause;
        private System.Windows.Forms.Label videopath;
        private System.Windows.Forms.TrackBar process;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.RichTextBox output;
        private System.Windows.Forms.Label duation;
        private System.Windows.Forms.Button buttonGetDuation;
        private System.Windows.Forms.Label curpos;
        private System.Windows.Forms.Button buttonGetCurpos;
    }
}

