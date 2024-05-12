using System;
using System.IO;

class Program
{
    static double FirstFragment(double x)
    {
        double res = -0.93 * x * x - 6.47 * x - 9.2;
        if (Math.Abs(res) < 0.000001)
        {
            res = 0.0;
        }
        return res;
    }

    static double SecondFragment(double x)
    {
        double res = -Math.Sqrt(4 - x * x);
        if (Math.Abs(res) < 0.000001)
        {
            res = 0.0;
        }
        return res;
    }

    static double ThirdFragment(double x)
    {
        double res = Math.Log(x - 1, 2);
        if (Math.Abs(res) < 0.000001)
        {
            res = 0.0;
        }
        return res;
    }

    static double FourthFragment(double x)
    {
        double res = -2 * x + 18;
        if (Math.Abs(res) < 0.000001)
        {
            res = 0.0;
        }
        return res;
    }

    static void Main(string[] args)
    {
        double xStart = -6.0;
        double xEnd = 9.0;
        double dx = 0.1;

        using (StreamWriter outfile = new StreamWriter("Output.txt"))
        {
            for (double x = xStart; x <= xEnd; x += dx)
            {
                if (Math.Abs(x) < 0.000001)
                {
                    x = 0.0;
                }
                if (x >= -6.0 && x < -2.0)
                {
                    outfile.WriteLine($"{x,10:F6} {FirstFragment(x),10:F6}");
                }
                if (x >= -2.0 && x < 2.0)
                {
                    outfile.WriteLine($"{x,10:F6} {SecondFragment(x),10:F6}");
                }
                if (x >= 2.0 && x < 8.0)
                {
                    outfile.WriteLine($"{x,10:F6} {ThirdFragment(x),10:F6}");
                }
                if (x >= 8.0 && x <= 9.0)
                {
                    outfile.WriteLine($"{x,10:F6} {FourthFragment(x),10:F6}");
                }
            }
        }
    }
}
