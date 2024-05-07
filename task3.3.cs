using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        Console.WriteLine("Введите температуру среды:");
        double Tsr = double.Parse(Console.ReadLine());
        Console.WriteLine("Введите температуру кофе:");
        double Tc = double.Parse(Console.ReadLine());
        Console.WriteLine("Введите коэффициент охлаждения:");
        double HeatCoef = double.Parse(Console.ReadLine());
        Console.WriteLine("Введите максимальное время охлаждения в минутах:");
        int t = int.Parse(Console.ReadLine());

        List<double> Coffee = new List<double>();
        CoffeeFunction(Tsr, Tc, HeatCoef, t, Coffee);

        Console.WriteLine("Время" + "\t" + "Температура кофе");
        for (int i = 0; i < Coffee.Count; i++)
        {
            Console.WriteLine(i + "\t" + Coffee[i].ToString("0.0000"));
        }

        double a = AApproximation(Coffee);
        double b = BApproximation(Coffee, a);
        double correl = Correlation(Coffee);
        Console.WriteLine("\nЛиния аппроксимации: T = " + a.ToString("0.000") + " * t + " + b.ToString("0.0000"));
        Console.WriteLine("\nКоэффициент корреляции " + correl.ToString("0.00"));
    }

    static void CoffeeFunction(double Tsr, double Tc, double HeatCoef, int t, List<double> Coffee)
    {
        for (int i = 0; i <= t; i++)
        {
            Coffee.Add(Tc);
            Tc = Tc - HeatCoef * (Tc - Tsr);
        }
    }

    static double AApproximation(List<double> Coffee)
    {
        double ET = 0, Et = 0, ETt = 0, ET2 = 0;
        int len = Coffee.Count;
        for (int i = 0; i < len; i++)
        {
            ET += Coffee[i];
            Et += i;
            ETt += Coffee[i] * i;
            ET2 += Coffee[i] * Coffee[i];
        }
        return (len * ETt - (Et * ET)) / (len * ET2 - ET * ET);
    }

    static double BApproximation(List<double> Coffee, double a)
    {
        double ET = 0, Et = 0;
        int len = Coffee.Count;
        for (int i = 0; i < len; i++)
        {
            ET += Coffee[i];
            Et += i;
        }
        return (Et - a * ET) / len;
    }

    static double Correlation(List<double> Coffee)
    {
        double sumTemp = 0;
        foreach (double T in Coffee)
        {
            sumTemp += T;
        }
        int len = Coffee.Count;
        double TMedium = sumTemp / len;
        double tMedium = (len - 1) * len / 2;
        double sumNumbers = 0;
        double tSumSquare = 0;
        double TSumSquare = 0;

        for (int i = 0; i < len; i++)
        {
            sumNumbers += ((i - tMedium) * (Coffee[i] - TMedium));
            tSumSquare += ((i - tMedium) * (i - tMedium));
            TSumSquare += ((Coffee[i] - TMedium) * (Coffee[i] - TMedium));
        }
        return sumNumbers / Math.Sqrt(TSumSquare * tSumSquare);
    }
}