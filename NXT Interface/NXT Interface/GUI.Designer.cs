namespace NXT_Interface
{
    partial class GUI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SendField1 = new System.Windows.Forms.TextBox();
            this.SendButton = new System.Windows.Forms.Button();
            this.SendField2 = new System.Windows.Forms.TextBox();
            this.SendField3 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Title = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // SendField1
            // 
            this.SendField1.Location = new System.Drawing.Point(10, 43);
            this.SendField1.Name = "SendField1";
            this.SendField1.Size = new System.Drawing.Size(100, 20);
            this.SendField1.TabIndex = 0;
            // 
            // SendButton
            // 
            this.SendButton.Location = new System.Drawing.Point(10, 121);
            this.SendButton.Name = "SendButton";
            this.SendButton.Size = new System.Drawing.Size(75, 20);
            this.SendButton.TabIndex = 1;
            this.SendButton.Text = "Send";
            this.SendButton.UseVisualStyleBackColor = true;
            this.SendButton.Click += new System.EventHandler(this.SendButton_Click);
            // 
            // SendField2
            // 
            this.SendField2.Location = new System.Drawing.Point(10, 69);
            this.SendField2.Name = "SendField2";
            this.SendField2.Size = new System.Drawing.Size(100, 20);
            this.SendField2.TabIndex = 2;
            // 
            // SendField3
            // 
            this.SendField3.Location = new System.Drawing.Point(10, 95);
            this.SendField3.Name = "SendField3";
            this.SendField3.Size = new System.Drawing.Size(100, 20);
            this.SendField3.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(114, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "X";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(114, 72);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Y";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(114, 98);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(14, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Z";
            // 
            // Title
            // 
            this.Title.AutoSize = true;
            this.Title.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F);
            this.Title.Location = new System.Drawing.Point(4, 9);
            this.Title.Name = "Title";
            this.Title.Size = new System.Drawing.Size(268, 31);
            this.Title.TabIndex = 7;
            this.Title.Text = "Connected on COM5";
            // 
            // GUI
            // 
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.Title);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SendField3);
            this.Controls.Add(this.SendField2);
            this.Controls.Add(this.SendButton);
            this.Controls.Add(this.SendField1);
            this.Name = "GUI";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox SendField1;
        private System.Windows.Forms.TextBox SendField2;
        private System.Windows.Forms.Button SendButton;
        private System.Windows.Forms.TextBox SendField3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label Title;
    }
}

