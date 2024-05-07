using System;
using System.Collections.Generic;

class Program
{
    static Random rand = new Random();

    static int Random(int min, int max)
    {
        return rand.Next(min, max + 1);
    }

    static int PowMod(int a, int x, int p)
    {
        int res = 1;
        a = a % p;
        while (x > 0)
        {
            if (x % 2 == 1)
            {
                res = (res * a) % p;
            }
            a = (a * a) % p;
            x /= 2;
        }
        return res;
    }

    static void Erat(List<int> prime)
    {
        for (int i = 2; i <= 500; i++)
        {
            prime.Add(i);
        }
        for (int i = 0; i < prime.Count; i++)
        {
            int j = i + 1;
            while (j < prime.Count)
            {
                if (prime[j] % prime[i] == 0)
                {
                    prime.RemoveAt(j);
                }
                else
                {
                    j++;
                }
            }
        }
    }

    static int NoD(int a, int b)
    {
        if (b == 0)
        {
            return a;
        }
        return NoD(b, a % b);
    }

    static int Eiler(int p)
    {
        int res = p;
        for (int i = 2; i <= Math.Sqrt(p); i++)
        {
            if (p % i == 0)
            {
                while (p % i == 0)
                {
                    p /= i;
                }
                res -= res / i;
            }
        }
        if (p > 1)
        {
            res -= res / p;
        }
        return res;
    }

    static int MilerRazl(int m, int n1, List<int> prime, List<int> primeMnUnick, List<int> primeMn)
    {
        for (int i = 0; i < prime.Count; i++)
        {
            int degree = 0;
            if (n1 % prime[i] == 0)
            {
                while (n1 % prime[i] == 0)
                {
                    n1 /= prime[i];
                    degree++;
                    primeMn.Add(prime[i]);
                }
                primeMnUnick.Add(prime[i]);
                m *= (int)Math.Pow(prime[i], degree);
            }
        }
        return m / 2;
    }

    static bool Miler(int n, List<int> primeMnUnick, int t)
    {
        if (n == 2)
        {
            return true;
        }
        if (n < 2 || n % 2 == 0)
        {
            return false;
        }
        bool milerF1 = false;
        bool milerF2 = false;
        for (int j = 0; j < t; j++)
        {
            int a = Random(2, n - 1);
            if (PowMod(a, n - 1, n) != 1)
            {
                milerF1 = false;
            }
            else
            {
                milerF1 = true;
            }
        }
        foreach (int prime in primeMnUnick)
        {
            for (int j = 0; j < t; j++)
            {
                int a = Random(2, n - 1);
                if (PowMod(a, (n - 1) / prime, n) != 1)
                {
                    continue;
                }
                else
                {
                    milerF2 = true;
                }
            }
            if (milerF1 && milerF2)
            {
                return true;
            }
        }
        return false;
    }

    static void PoklinRazl(int n, ref int F, ref int R, List<int> primeMn)
    {
        for (int i = primeMn.Count - 1; i >= 0; i--)
        {
            if (F <= Math.Sqrt(n) - 1)
            {
                F *= primeMn[i];
            }
            else
            {
                R *= primeMn[i];
            }
        }
    }

    static bool Poklin(int n, int F, int R, List<int> primeMnUnick, int t)
    {
        if (n == 2 || n == 5)
        {
            return true;
        }
        if (n < 2 || n % 2 == 0)
        {
            return false;
        }

        bool poklinF1 = false;
        bool poklinF2 = false;

        for (int j = 0; j < t; j++)
        {
            int a = Random(2, n - 1);

            if (PowMod(a, n - 1, n) != 1)
            {
                poklinF1 = false;
            }
            else
            {
                poklinF1 = true;
            }

            foreach (int prime in primeMnUnick)
            {
                if (PowMod(a, (n - 1) / prime, n) == 1)
                {
                    poklinF2 = false;
                    break;
                }
                else
                {
                    poklinF2 = true;
                }
            }

            if (poklinF1 && poklinF2)
            {
                return true;
            }
        }
        return false;
    }

    static bool Gost(int t, int q1, ref int p)
    {
        p = 0;
        while (true)
        {
            int n1 = (int)Math.Ceiling(Math.Pow(2, t - 1) / q1);
            int n2 = (int)Math.Ceiling(Math.Pow(2, t - 1) * 0 / q1);
            double n = n1 + n2;

            if ((int)Math.Round(n) % 2 != 0)
            {
                n++;
            }

            for (int u = 0; Math.Pow(2, t) >= (n + u) * q1 + 1; u += 2)
            {
                p = (int)((n + u) * q1 + 1);

                if ((PowMod(2, p - 1, p) == 1) && (PowMod(2, (int)(n + u), p) != 1))
                {
                    return true;
                }
            }
        }
    }

    static bool VerTest(int n, int t, int R, int F)
    {
        if (NoD(R, F) == 1)
        {
            double vermiler = ((double)Eiler(n - 1) / (double)(n - 1)) * t;
            double verpoklin = ((double)Eiler(n) / (double)n) * t;
            double res = 1 - vermiler - verpoklin;
            return (res <= 0.1);
        }
        else
        {
            double vermiler = ((double)Eiler(n - 1) / (double)(n - 1)) * t;
            double res = 1 - vermiler;
            return (res <= 0.1);
        }
    }

    static void Input(int n, bool vertest, int k)
    {
        if (vertest && k <= 6)
        {
            Console.WriteLine($"{n}\t\t+\t\t{k}");
        }
        else
        {
            Console.WriteLine($"{n}\t\t-\t\t{k}");
        }
    }

    static void Main(string[] args)
    {
        List<int> prime = new List<int>();
        Erat(prime);

        int t = 5;
        int t1 = 6;

        int q1 = 5;

        int k = 0;

        Console.WriteLine("Число|\tРезультат проверки|\tКоличество отвергнутых чисел");
        Console.WriteLine("-------------------------------------------------------");

        for (int i = 0; i < 10; i++)
        {
            List<int> primeMnUnick = new List<int>();
            List<int> primeMn = new List<int>();

            int n = Random(2, 500 - 2);
            int n1 = n - 1;
            int m = 1;

            m = MilerRazl(m, n1, prime, primeMnUnick, primeMn);
            int F = 1;
            int R = 1;

            PoklinRazl(n, ref F, ref R, primeMn);

            if (m * 2 + 1 != n || F * R + 1 != n || !Miler(n, primeMnUnick, t) || !Poklin(n, F, R, primeMnUnick, t))
            {
                k++;
                i--;
                continue;
            }

            Input(n, VerTest(n, t, R, F), k);

            if (Miler(n, primeMnUnick, t) && Poklin(n, F, R, primeMnUnick, t))
            {
                k = 0;
            }
        }

        int p = 0;
        bool GOSTResult = Gost(t1, q1, ref p);

        Console.WriteLine($"Значение переменной теста госта: {p}");
    }
}
