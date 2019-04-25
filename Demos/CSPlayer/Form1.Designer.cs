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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonInitializeGL = new System.Windows.Forms.Button();
            this.buttonReleaseGL = new System.Windows.Forms.Button();
            this.buttonCreatePlayer = new System.Windows.Forms.Button();
            this.buttonRenderOneFrame = new System.Windows.Forms.Button();
            this.buttonDestroyPlayer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 94);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(760, 28);
            this.textBox1.TabIndex = 0;
            // 
            // buttonInitializeGL
            // 
            this.buttonInitializeGL.Location = new System.Drawing.Point(12, 740);
            this.buttonInitializeGL.Name = "buttonInitializeGL";
            this.buttonInitializeGL.Size = new System.Drawing.Size(139, 41);
            this.buttonInitializeGL.TabIndex = 1;
            this.buttonInitializeGL.Text = "InitializeGL";
            this.buttonInitializeGL.UseVisualStyleBackColor = true;
            this.buttonInitializeGL.Click += new System.EventHandler(this.buttonInitializeGL_Click);
            // 
            // buttonReleaseGL
            // 
            this.buttonReleaseGL.Location = new System.Drawing.Point(727, 740);
            this.buttonReleaseGL.Name = "buttonReleaseGL";
            this.buttonReleaseGL.Size = new System.Drawing.Size(139, 41);
            this.buttonReleaseGL.TabIndex = 2;
            this.buttonReleaseGL.Text = "ReleaseGL";
            this.buttonReleaseGL.UseVisualStyleBackColor = true;
            this.buttonReleaseGL.Click += new System.EventHandler(this.buttonReleaseGL_Click);
            // 
            // buttonCreatePlayer
            // 
            this.buttonCreatePlayer.Location = new System.Drawing.Point(179, 740);
            this.buttonCreatePlayer.Name = "buttonCreatePlayer";
            this.buttonCreatePlayer.Size = new System.Drawing.Size(139, 41);
            this.buttonCreatePlayer.TabIndex = 3;
            this.buttonCreatePlayer.Text = "CreatePlayer";
            this.buttonCreatePlayer.UseVisualStyleBackColor = true;
            this.buttonCreatePlayer.Click += new System.EventHandler(this.buttonCreatePlayer_Click);
            // 
            // buttonRenderOneFrame
            // 
            this.buttonRenderOneFrame.Location = new System.Drawing.Point(346, 740);
            this.buttonRenderOneFrame.Name = "buttonRenderOneFrame";
            this.buttonRenderOneFrame.Size = new System.Drawing.Size(166, 41);
            this.buttonRenderOneFrame.TabIndex = 4;
            this.buttonRenderOneFrame.Text = "RenderOneFrame";
            this.buttonRenderOneFrame.UseVisualStyleBackColor = true;
            this.buttonRenderOneFrame.Click += new System.EventHandler(this.buttonRenderOneFrame_Click);
            // 
            // buttonDestroyPlayer
            // 
            this.buttonDestroyPlayer.Location = new System.Drawing.Point(535, 740);
            this.buttonDestroyPlayer.Name = "buttonDestroyPlayer";
            this.buttonDestroyPlayer.Size = new System.Drawing.Size(166, 41);
            this.buttonDestroyPlayer.TabIndex = 5;
            this.buttonDestroyPlayer.Text = "DestroyPlayer";
            this.buttonDestroyPlayer.UseVisualStyleBackColor = true;
            this.buttonDestroyPlayer.Click += new System.EventHandler(this.buttonDestroyPlayer_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1222, 852);
            this.Controls.Add(this.buttonDestroyPlayer);
            this.Controls.Add(this.buttonRenderOneFrame);
            this.Controls.Add(this.buttonCreatePlayer);
            this.Controls.Add(this.buttonReleaseGL);
            this.Controls.Add(this.buttonInitializeGL);
            this.Controls.Add(this.textBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonInitializeGL;
        private System.Windows.Forms.Button buttonReleaseGL;
        private System.Windows.Forms.Button buttonCreatePlayer;
        private System.Windows.Forms.Button buttonRenderOneFrame;
        private System.Windows.Forms.Button buttonDestroyPlayer;
    }
}

