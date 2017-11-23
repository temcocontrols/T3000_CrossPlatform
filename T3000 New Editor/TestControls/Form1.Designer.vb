<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.ctlCodeEditor = New T3000.NewEditor.T3000Editor()
        Me.SuspendLayout()
        '
        'ctlCodeEditor
        '
        Me.ctlCodeEditor.Dock = System.Windows.Forms.DockStyle.Fill
        Me.ctlCodeEditor.Location = New System.Drawing.Point(0, 0)
        Me.ctlCodeEditor.Name = "ctlCodeEditor"
        Me.ctlCodeEditor.Size = New System.Drawing.Size(579, 365)
        Me.ctlCodeEditor.TabIndex = 0
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(579, 365)
        Me.Controls.Add(Me.ctlCodeEditor)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents ctlCodeEditor As T3000.NewEditor.T3000Editor
End Class
