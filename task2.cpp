#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>

using namespace std;

int random(int min, int max){
    return rand() % (max - min + 1) + min;
}

int pow_mod(int a, int x, int p){
    // Инициализация переменной res для хранения результата
    int res = 1;
    // Переводим a в вид, не превышающий p
    a = a % p;
    // Пока степень x больше 0
    while (x > 0)
    {
        // Если текущая степень x нечетная
        if (x % 2 == 1)
        {
            // Умножаем res на a и берем остаток от деления на p
            res = (res * a) % p;
        }
        // Возводим a в квадрат и берем остаток от деления на p
        a = (a * a) % p;
        // Уменьшаем степень x вдвое
        x /= 2;
    }
    // Возвращаем результат
    return res;
}

void erat(vector<int>& prime){
    // Заполняем вектор prime числами от 2 до 500
    for(int i = 2; i <= 500; i++)
    {
        prime.push_back(i);
    }
    // Используем алгоритм Решето Эратосфена
    // Перебираем все элементы вектора prime
    for(int i = 0; i <= prime.size(); i++)
    {
        // Инициализируем индекс j, который начинается с i + 1
        int j = i + 1;
        // Пока j не достигнет конца вектора prime
        while(j < prime.size())
        {
            // Если текущий элемент prime[j] делится без остатка на prime[i],
            // это означает, что prime[i] не простое число
            if(prime[j] % prime[i] == 0)
            {
                // Удаляем элемент prime[j] из вектора prime
                for(int k = j; k < prime.size() - 1; k++)
                {
                    prime[k] = prime[k + 1];
                }
                prime.pop_back();
            }
            else
            {
                // Если prime[j] не делится на prime[i], увеличиваем j
                j++;
            }
        }
    }
}

int NoD(int a, int b){
    if(b == 0)
    {
        return a;
    }
    return NoD(b, a % b);
}

int eiler(int p){
    // Инициализация переменной res значением p
    int res = p;
    // Перебор всех чисел от 2 до квадратного корня из p
    for(int i = 2; i <= sqrt(p); i++)
    {
        // Проверка, делится ли p на текущее число i без остатка
        if (p % i == 0)
        {
            // Если делится, выполняется цикл, пока p делится на i без остатка
            while(p % i == 0)
            {
                p /= i;
            }
            // Обновление значения res путем вычитания из него res/i
            res -= res / i;
        }
    }
    // Если после цикла остался остаток p, отличный от 1, обновляем значение res
    if(p > 1)
    {
        res -= res / p;
    }
    // Возвращаем значение функции Эйлера
    return res;
}

int miler_razl(int m, int n1, const vector<int>& prime, vector<int>& primeMnUnick, vector<int>& primeMn){
    // Перебор простых чисел из вектора prime
    for(int i = 0; i < prime.size(); i++)
    {
        // Инициализация счетчика степени для текущего простого числа
        int degree = 0;
        // Проверка, делится ли n1 на текущее простое число без остатка
        if(n1 % prime[i] == 0)
        {
            // Если делится, запускаем цикл, который уменьшает n1 и считает степень числа
            while(n1 % prime[i] == 0)
            {
                n1 /= prime[i];
                degree++;
                // Добавление простого числа в вектор primeMn
                primeMn.push_back(prime[i]);
            }
            // Добавление уникального простого числа в вектор primeMnUnick
            primeMnUnick.push_back(prime[i]);
            // Обновление m путем умножения на текущее простое число в степени degree
            m *= pow(prime[i], degree);
        }
    }
    // Возвращение m, разделенного на 2
    return m/2;
}

bool miler(int n, const vector<int>& primeMnUnick, int t)
{
    // Проверка, является ли число 2 простым
    if(n == 2)
    {
        // Если число равно 2, возвращаем true
        return true;
    }
    // Проверка на отрицательные числа, нули и четные числа
    if(n < 2 || n % 2 == 0)
    {
        // Если число меньше 2 или четное, возвращаем false
        return false;
    }
    // Инициализация флагов для условий Миллера
    bool milerF1 = false;
    bool milerF2 = false;
    // Проверка условий Миллера t раз
    for(int j = 0; j < t; j++)
    {
        // Генерация случайного числа в диапазоне от 2 до n-1
        int a = random(2, n - 1);
        // Проверка первого условия Миллера
        if(pow_mod(a, n - 1, n) != 1)
        {
            // Если условие не выполняется, устанавливаем флаг milerF1 в false
            milerF1 = false;
        }
        else
        {
            // Если условие выполняется, устанавливаем флаг milerF1 в true
            milerF1 = true;
        }
    }
    // Перебор простых множителей числа n
    for(int i = 0; i < primeMnUnick.size(); i++)
    {
        // Проверка условий Миллера t раз для каждого простого множителя
        for(int j = 0; j < t; j++)
        {
            // Генерация случайного числа в диапазоне от 2 до n-1
            int a = random(2, n - 1);
            // Проверка второго условия Миллера
            if(pow_mod(a, (n - 1)/primeMnUnick[i], n) != 1)
            {
                // Если условие не выполняется, продолжаем перебор
                continue;
            }
            else
            {
                // Если условие выполняется, устанавливаем флаг milerF2 в true
                milerF2 = true;
            }
        }
        // Если оба условия Миллера выполняются, возвращаем true
        if (milerF1 == true && milerF2 == true)
        {
            return true;
        } 
    }
    // Если ни одно из условий Миллера не выполняется, возвращаем false
    return false;   
}

void poklin_razl(int n, int& F, int& R, const vector<int>& primeMn){
    // Начинаем разложение с самого большого простого множителя числа n
    for(int i = primeMn.size() - 1; i + 1 > 0; i--)
    {
        // Если текущий множитель еще должен добавляться в переменную F
        if(F <= sqrt(n) - 1)
        {
            // Умножаем F на текущий простой множитель primeMn[i]
            F *= primeMn[i];
        }
        else
        {
            // Если F уже больше корня из n - 1, добавляем множитель в R
            R *= primeMn[i];
        }
    }
}

bool poklin(int n, int F, int R, const vector<int>& primeMnUnick, int t){
    // Проверка на числа 2 и 5, которые всегда являются простыми
    if(n == 2 || n == 5)
    {
        return true;
    }
    // Проверка на четность и числа меньше 2, они не являются простыми
    if(n < 2 || n % 2 == 0)
    {
        return false;
    }
    
    // Флаги для проверок
    bool poklinF1 = false; // Флаг для первого условия теста Поклингтона
    bool poklinF2 = false; // Флаг для второго условия теста Поклингтона
    
    // Цикл по числу случайных тестов
    for(int j = 0; j < t; j++)
    {
        // Генерация случайного числа a в диапазоне от 2 до n - 1
        int a = random(2, n - 1);
        
        // Проверка первого условия теста Поклингтона
        if(pow_mod(a, n - 1, n) != 1)
        {
            poklinF1 = false;
        }
        else
        {
            poklinF1 = true;
        }
        
        // Проверка второго условия теста Поклингтона для каждого делителя из primeMnUnick
        for(int i = 0; i < primeMnUnick.size(); i++)
        {
            if(pow_mod(a, (n - 1) / primeMnUnick[i], n) == 1)
            {
                poklinF2 = false;
                break;
            }
            else
            {
                poklinF2 = true;
            }
        }
        
        // Если оба условия выполняются, возвращаем true
        if(poklinF1 == true && poklinF2 == true)
        {
            return true;
        }
    }
    // Если ни для одного случайного теста не выполняется оба условия, возвращаем false
    return false;
}

bool gost(int t, int q1, int& p)
{
    p = 0; // Инициализация p
    while(true) // Бесконечный цикл
    {
        // Рассчитываем значения n1 и n2
        int n1 = ceil(pow(2, t - 1) / q1);
        int n2 = ceil(pow(2, t - 1) * 0 / (q1)); // Значение n2 всегда равно 0
        double n = n1 + n2; // Общее значение n

        // Если n нечетное, увеличиваем на 1
        if(static_cast<int>(round(n)) % 2 != 0)
        {
            n++;
        }

        // Поиск простого числа p, удовлетворяющего условиям ГОСТ 34.10-2001
        for(int u = 0; pow(2, t) >= (n + u) * q1 + 1; u += 2)
        {
            p = (n + u) * q1 + 1; // Вычисление значения p

            // Проверка условий ГОСТ 34.10-2001 для простого числа p
            if((pow_mod(2, p - 1, p) == 1) && (pow_mod(2, n + u, p) != 1))
            {
                return true; // Если условия выполняются, возвращаем true
            }
        }
    }
    return false; // Если не удалось найти подходящее простое число, возвращаем false
}

bool vertest(int n, int t, int R, int F){
    // Проверяем взаимно простые ли R и F
    if(NoD(R, F) == 1)
    {
        // Рассчитываем вероятность ошибки для Миллера-Рабина
        double vermiler = (static_cast<double>(eiler(n-1))/static_cast<double>(n-1)) * t;
        // Рассчитываем вероятность ошибки для теста Поклингтона
        double verpoklin = (static_cast<double>(eiler(n))/static_cast<double>(n)) * t;
        // Общая вероятность ошибки
        double res = 1 - vermiler - verpoklin;
        // Возвращаем результат проверки
        return (res <= 0.1);
    }
    else
    {
        // Если R и F не взаимно простые, рассчитываем только вероятность ошибки для Миллера-Рабина
        double vermiler = (static_cast<double>(eiler(n-1))/static_cast<double>(n-1)) * t;
        // Возвращаем результат проверки
        double res = 1 - vermiler;
        return (res <= 0.1);
    }
}

void input(int n, bool vertest, int k){
    // Проверяем, нужно ли учитывать вероятность ошибки и значение k
    if(vertest && k <= 6)
    {
        // Выводим информацию о параметрах с плюсом, если условия выполнены
        cout << n << " \t\t" << "+" << " \t\t" << k << endl;
    }
    else
    {
        // Выводим информацию о параметрах с минусом, если условия не выполнены
        cout << n << " \t\t" << "-" << " \t\t" << k << endl;
    }
}

int main(){
    srand(time(0)); // Инициализация генератора случайных чисел

    // Создание вектора prime и заполнение его простыми числами до 500
    vector<int> prime;
    erat(prime);

    // Установка количества итераций для тестов Миллера-Рабина и Поклингтона
    int t = 5;
    int t1 = 6;

    // Установка значения q1 для теста ГОСТ 34.10-2001
    int q1 = 5;

    // Инициализация счетчика отвергнутых чисел
    int k = 0;

    // Вывод заголовка таблицы
    cout << "Число|\tРезультат проверки|\tКоличество отвергнутых чисел" << endl;
    cout << "-------------------------------------------------------" << endl;

    // Цикл для проверки 10 случайных чисел
    for (int i = 0; i < 10; i++) {
        vector<int> primeMnUnick;
        vector<int> primeMn;

        // Генерация случайного числа n в диапазоне от 2 до 498
        int n = random(2, 500 - 2);
        int n1 = n - 1;
        int m = 1;

        // Разложение числа n-1 на простые множители и вычисление m
        m = miler_razl(m, n1, prime, primeMnUnick, primeMn);
        int F = 1;
        int R = 1;

        // Разложение числа n на множители F и R
        poklin_razl(n, F, R, primeMn);

        // Проверка условий для применения тестов Миллера-Рабина и Поклингтона
        if (m*2 + 1 != n || F*R + 1 != n || !miler(n, primeMnUnick, t) || !poklin(n, F, R, primeMnUnick, t)) {
            k++; // Увеличение счетчика отвергнутых чисел
            i--; // Уменьшение значения i для повторной проверки
            continue; // Переход к следующей итерации цикла
        }

        // Вывод информации о числе, результате верификации и количестве отвергнутых чисел
        input(n, vertest(n, t, R, F), k);

        // Сброс счетчика отвергнутых чисел, если все тесты пройдены успешно
        if (miler(n, primeMnUnick, t) && poklin(n, F, R, primeMnUnick, t)) {
            k = 0;
        }
    }

    int p; // Переменная для хранения значения простого числа из теста ГОСТ 34.10-2001
    bool GOSTResult = gost(t1, q1, p); // Вызов функции теста ГОСТ 34.10-2001

    // Вывод значения простого числа из теста ГОСТ 34.10-2001
    cout << "Значение переменной теста госта: ";
    cout << p << endl;
}