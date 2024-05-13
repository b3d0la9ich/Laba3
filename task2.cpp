#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <map>

using namespace std;

int getRandomNumber(int min, int max) {  //генерация случайного числа в заданном диапазоне
    return rand() % (max - min + 1) + min;
}

void Eratosfen(vector<int>& Prost500) {  //решето Эратосфена

    for (int i = 2; i <= 500; i++) { //закидываем все числа от 2 до 500
        Prost500.push_back(i);
    }

    for (int i = 0; i <= sqrt(Prost500.size()); i++) {
        int j = i + 1;
        while (j < Prost500.size()) {
            if (Prost500[j] % Prost500[i] == 0) {
                for (int k = j; k < Prost500.size() - 1; k++) {  //если число непростое
                    Prost500[k] = Prost500[k + 1];               //затираем сдвигом
                }
                Prost500.pop_back();                             //и удаляем последнюю пустую позицию
            }
            else {
                j++;                                        //если простое, идем дальше
            }
        }
    }
}

int modPow(int a, int q, int n) {  // Функция для возведения в степень по модулю
    int result = 1;
    while (q > 0) {
        if (q % 2 == 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        q /= 2;
    }
    return result;
}

int factorizeCanonical(int n, vector<int>& qi) {//раскладываем число n-1 на каноническое разложение (= m)
    map<int, int> factors;

    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
            qi.push_back(i);// собираем делители
        }
    }
    if (n > 1) {
        factors[n]++; // добавляем последний делитель, если такой есть
    }

    // Вычислите каноническую форму n
    int m = 1;
    for (const auto& factor : factors) {
        m *= pow(factor.first, factor.second);
    }

    return m / 2;
}

// Функция для вычисления значения функции Эйлера φ(n) Для нахождения вероятности
int phi(int n) {
    int result = n; // Изначально, φ(n) равно n
    // Ищем все простые делители n
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            // p - простой делитель, уменьшаем φ(n)
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    // Если n > 1, то оно простое и мы еще не уменьшили φ(n)
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

bool TestMiller(int n, int t, vector<int>& qi) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;

    int n_minus_1 = n - 1;
    int m = factorizeCanonical(n_minus_1, qi);
int result, result1;
    
    if (n_minus_1 = 2 * m) {
        for (int j : qi) {
            for (int i = 0; i < t; i++) {
                int a = getRandomNumber(2, n - 1); //случайное число a в диапазоне от 2 до n-2

                if (modPow(a, n_minus_1, n) == 1) { //первое условие
                    result1 = 1;
                }
                else return false;

                if (modPow(a, n_minus_1, n) == 1) { //первое условие
                    result1 = 1;
                }
                else return false;

                //второе условие
                int q_part = n_minus_1 / j; //(a^((n-1)/q)) mod n //Выбрать рандомное qi
                result1 = modPow(a, q_part, n);
                if(result != 1 || result1 != 1) break;;
            }
        }
    }
    return true;
}

int NOD(int a, int b) {
    if (b == 0) return a;
    return NOD(b, a % b);
}

int factorizeCanonicalFFF(int n, vector<int>& qi, int F, int& R) { // вычисление F и R   
    for (size_t i = qi.size() - 1; i + 1 > 0; i--) {
        if (F <= sqrt(n) - 1) {
            F *= qi[i];
        }
        else {
            R *= qi[i];
            if(R % 2 !=0){
                R -=1 ;
            }
        }
    }
    return F;
}


bool TestPoklingtona(int n, int t, vector<int>& qi, int F, int R) {
    if (n == 2 || n==5) return true;
    if (n < 2 || n % 2 == 0) return false;

    bool Proverka = false;
    for (int j=0; j < t; j++) {
        int a = getRandomNumber(2,n-1);
        if (modPow(a,n-1,n) != 1) {
            return false;
        }
    
         for (int q : qi) {
                 if (modPow(a, (n-1)/q, n) == 1){
                Proverka = false;
                break;
            }
            else {
                Proverka = true;
            }
        }
        if (Proverka==true) return true; //вернёт составное
    }
    return false;// вернёт простое
}

bool GOST(int t, int q1, int& p) {
    p = 0;
    while (true) {
        int N1 = ceil(pow(2, t - 1) / q1);
        int N2 = ceil(pow(2, t - 1) * 0 / (q1));

        double N = N1 + N2;
        if (static_cast<int>(round(N)) % 2 != 0) {
            N++;
        }

        for (int u = 0; pow(2, t) >= (N + u) * q1 + 1; u += 2) {
            p = (N + u) * q1 + 1;
            if ((modPow(2, p - 1, p) == 1) && (modPow(2, N + u, p) != 1)) {
                return true;
            }
        }
    }

    return false;
}

bool TestVeroyatnost(int n, int t, int R, int F) {

    if (NOD(R, F) == 1) {
        double VerMiller = (static_cast<double>(phi(n - 1)) / static_cast<double>(n - 1)) * t;
        double VerPoglint = (static_cast<double>(phi(n)) / static_cast<double>(n)) * t;
        double result = 1 - VerMiller - VerPoglint;
        return(result <= 0.1);
    }
    else {
        double VerMiller = static_cast<double>(phi(n - 1)) / static_cast<double>(n) * t;
        double result = 1 - VerMiller;
        return(result <= 0.1);
    }
}

void InPut(int n, bool testResult, int k) {
    if (testResult && k <= 5) {
        cout << n << " \t\t" << "+" << " \t\t" << k << endl;
    }
    else {
        cout << n << " \t\t" << "-" << " \t\t" << k << endl;
    }
}

int main() {
    srand(time(0));
    vector<int> Prost500;
    Eratosfen(Prost500);

    int t1 = 5;
    int k = 0;
    int p;
    int t = 7;
    int q1 = 13;

    cout << "Number|\tProbabilistic test|\tCount rejected numbers" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < 10; i++) {
        vector <int> qi;
        int F = 1;

        int n = getRandomNumber(2, 500 - 1);
        int n_minus_1 = n - 1;
        int R = 1;
        F = factorizeCanonicalFFF(n_minus_1, qi, F, R);

        bool millerResult = TestMiller(n, t1, qi);
        bool poklingtonResult = TestPoklingtona(n, t1, qi, R,F);

        if (!millerResult || !poklingtonResult) {
            k++;
            i--;
            continue;
        }
        bool gostResult = GOST(t, q1, p);

        bool veroyatnostResult = TestVeroyatnost(n, t1, R, F);
        InPut(n, veroyatnostResult, k);

        if (millerResult && poklingtonResult) {
            k = 0;
        }
    }
    cout << "GOST: " << p;
    return 0;
}
