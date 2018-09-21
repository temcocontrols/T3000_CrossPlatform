using System;
using System.Diagnostics;

/// <summary>
/// Helper that executes a bash command and returns a string with results
/// </summary>
public static class ShellHelper
{
    /// <summary>
    /// Use: var myResults = "ls -l".Bash();
    /// </summary>
    /// <param name="cmd">Bash commnand</param>
    /// <returns></returns>
    public static string Bash(this string cmd)
    {
        var escapedArgs = cmd.Replace("\"", "\\\"");

        var process = new Process()
        {
            StartInfo = new ProcessStartInfo
            {
                FileName = "/bin/bash",
                Arguments = $"-c \"{escapedArgs}\"",
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true,
            }
        };
        process.Start();
        string result = process.StandardOutput.ReadToEnd();
        process.WaitForExit();
        return result;
    }
}