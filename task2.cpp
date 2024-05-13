#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <iomanip>
using namespace std;

int getRandomNumber(int min, int max) {  //генерация случайного числа в заданном диапазоне
    return rand() % (max - min + 1) + min;
}

void Eratosthenes(vector<int>& PrimeNums) {  //решето Эратосфена
    for (int i = 2; i < 500; i++) {  // [2, 500]
        PrimeNums.push_back(i);
    }

    for (int i = 0; i <= sqrt(PrimeNums.size()); i++) {
        int j = i + 1;
        while (j < PrimeNums.size()) {
            if (PrimeNums[j] % PrimeNums[i] == 0) {
                for (int k = j; k < PrimeNums.size() - 1; k++) { //не простое 
                    PrimeNums[k] = PrimeNums[k + 1]; 
                }
                PrimeNums.pop_back(); //удаляем его 
            }
            else {
                j++;                  //если простое, идем дальше
            }
        }
    }
}

int modPow(int a, int p, int randNum) {  // a^p mod RandNum
    int result = 1; // a - основание q - степень 
    while (p > 0) {
        if (p % 2 == 1) {
            result = (result * a) % randNum;
        }
        a = (a * a) % randNum;
        p /= 2;
    }
    return result;
}

int Eiler(int p) { // определяем количество взаимно простых чисел для p 
    int result = p;
    for (int i = 2; i * i <= p; i++) { //проходимся до корня из числа
        if (p % i == 0) { //если число разделилось на i, то мы уменьшаем р на i так как все числа,
            while (p % i == 0) { // которые делятся на i не являются взаимно простыми с p
                p /= i;
            }
            result -= result / i; // из результата вычитаем количество чисел result/i
        }
    }
    if (p > 1) { // если п - простое число, которое не разделилось, то оно простое и результатом
        result -= result / p; // функции будет р-1
    }

    return result;
}
int Canonical(int n, vector<int>& qi) { // для теста миллера и поклингтона 
    vector<pair<int, int>> factors; // (делитель, степень)
    for (int i = 2; i * i <= n; i++) {  // Dсе простые делители числа n-1 и их степени
        if (n % i == 0) {
            int exponent = 0;
            while (n % i == 0) {
                n /= i;
                exponent++;
            }
            factors.emplace_back(i, exponent); // Добавляем делитель и его степень в вектор
            qi.push_back(i); // Добавляем делитель в вектор qi
        }
    }

    // Если остался один простой делитель больше 1 (n простое)
    if (n > 1) {
        factors.emplace_back(n, 1); // Добавляем последний делитель
        qi.push_back(n); // Добавляем последний делитель в вектор qi
    }
    // Вычисляем каноническую форму n (m)
    int m = 1;
    for (const auto& factor : factors) {
        m *= pow(factor.first, factor.second);
    }

    return m / 2;
}
bool TestMiller(int n, int t, vector<int>& qi) {
    if (n == 2) {
        return true;
    }
    if (n < 2 || n % 2 == 0) {
        return false;
    }

    int n_minus_1 = n - 1;
    int m = Canonical(n_minus_1, qi);

    if (n_minus_1 = 2 * m) {
        for (int j : qi) {
            bool MillerF1 = false;
            bool MillerF2 = false;
            int k=0;
            for (int i = 0; i < t; i++) {
                int a = getRandomNumber(2, n - 2); //случайное число a в диапазоне от 2 до n-2

                if (modPow(a, n_minus_1, n) != 1) { //первое условие
                    return false;
                
                }

                //второое условие
                int q_part = n_minus_1 / j; //(a^((n-1)/q)) mod n //Выбрать рандомное qi
                int result = modPow(a, q_part, n);
                if (result != 1){
                    MillerF2 = true;
        
                    break;
                } else {
                    k++;
                }

            }
            if (k==(t-1)){
                return false; //если составное
            }
        }
    }
    return true;
}


// Функция для вычисления F и R в канонической форме числа n
int CanonicalF(int n, vector<int>& qi, int F, int& R) {
    // Проходим по вектору qi в обратном порядке
    for (size_t i = qi.size() - 1; i + 1 > 0; i--) {
        // Если F меньше или равно корню из n минус 1, то умножаем F на qi[i]
        if (F <= sqrt(n) - 1) {
            F *= qi[i];
        }
        // Иначе умножаем R на qi[i]
        else {
            R *= qi[i];
            // Если R делится нацело на 2, то увеличиваем R на 1
            if (R % 2 == 0) {
                R++;
            }
        }
    }
    // Возвращаем F
    return F;
}

// Функция для тестирования числа на простоту по тесту Поклингтона
bool TestPoklingtona(int n, int t, vector<int>& qi, int F, int R) {
    // Если число n равно 2 или 5, то оно является простым
    if (n == 2 || n == 5) return true;
    // Если число n меньше 2 или четное, то оно не является простым
    if (n < 2 || n % 2 == 0) return false;

    // Флаг для отслеживания условия теста Поклингтона
    bool PoklingF2 = false;

    // Проходимся по количеству итераций t
    for (int j = 0; j < t; j++) {
        // Генерируем случайное число a в диапазоне от 2 до n-1
        int a = getRandomNumber(2, n - 1);
        // Проверяем первое условие теста Поклингтона: a^(n-1) mod n должно быть не равно 1
        if (modPow(a, n - 1, n) != 1) {
            return false;
        }

        // Проверяем второе условие теста Поклингтона для всех делителей qi
        for (size_t i = 0; i < qi.size(); i++) {
            // Если a^((n-1)/qi) mod n равно 1, то число n составное
            if (modPow(a, (n - 1) / qi[i], n) == 1) {
                PoklingF2 = false;
                break;
            } else {
                // Если условие не выполняется, то число n может быть простым
                PoklingF2 = true;
            }
        }
        // Если условие выполняется хотя бы для одного делителя, то число n простое
        if (PoklingF2 == true) return true;
    }
    // Если условие не выполнилось ни разу, то число n составное
    return false;
}

int GOST(int t, int q1) {
    int p = 0;

    while (true) {
        int N1 = ceil(pow(2, t - 1) / q1);
        int N2 = ceil(pow(2, t - 1) * 0/ (q1));

        double N = N1 + N2;
        if (static_cast<int>(round(N)) % 2 != 0) {
            N++;
        }

        for (int u = 0; pow(2, t) >= (N + u) * q1 + 1; u += 2) {
            p = (N + u) * q1 + 1;
            if ((modPow(2, p - 1, p) == 1) && (modPow(2, N + u, p) != 1)) {
                return p;
            }
        }
    }
    return 0;
}
int NOD(int a, int b) { // наибольший общий делитель
if (b == 0) return a;
return NOD(b, a % b);
}

bool VerTest(int RandNum, int t, int R, int F) {
    if (NOD(R, F) == 1) { 
        double verMiller = (static_cast<double>(Eiler(RandNum - 1)) / static_cast<double>(RandNum - 1)) * t;
        double verPoklington = (static_cast<double>(Eiler(RandNum)) / static_cast<double>(RandNum)) * t;
        double result = 1 - verMiller - verPoklington;
        return (result <= 0.1);
    }
    else {
        /*Если нод не равен 1, то поклингтон бесполезен*/
        double verMiller = (static_cast<double>(Eiler(RandNum - 1)) / static_cast<double>(RandNum - 1)) * t;
        double result = 1 - verMiller;
        return (result <= 0.1);
    }
}

void InPut(int RandNum, bool testResult, int k, int gostResult, bool millerResult, bool poklingtonResult) {
    cout  << RandNum << setw(20); 

    if (testResult && k <= 5) {
        cout << "+" << setw(20); 
    }
    else {
        cout << "-" << setw(20);
    }

    cout << k << setw(20) << gostResult << setw(20) << millerResult << setw(20) << poklingtonResult <<  endl; 
}
int main() {
    // Инициализация генератора случайных чисел текущим временем, чтобы получить разные последовательности случайных чисел при каждом запуске программы
    srand(time(0));

    // Создание вектора для хранения простых чисел
    vector<int> Prime;

    // Заполнение вектора простыми числами с помощью решета Эратосфена
    Eratosthenes(Prime);

    // Количество итераций для тестов Миллера-Рабина и Поклингтона
    int t1 = 5;

    // Количество отвергнутых чисел в тесте
    int k = 0;

    // Количество итераций для теста ГОСТа
    int t = 9;

    // Неизвестный параметр для теста ГОСТа
    int q1 = 23;

    // Вывод заголовка таблицы
    cout << "Число\tВероятностный тест\tЧисло отвергнутых чисел\t\tГОСТ\t\t\tMiller\t\tPoklington" << endl;
    cout << "_________________________________________________________________________________________________" << endl;

    // Главный цикл для генерации и тестирования 10 простых чисел
    for (int i = 0; i < 10; i++) {
        // Создание вектора для хранения простых делителей числа n-1
        vector <int> qi;

        // Инициализация начального значения для F
        int F = 1;

        // Генерация случайного числа n в диапазоне от 2 до 500 - 2
        int n = getRandomNumber(2, 500 - 2);

        // Вычисление n - 1
        int n_minus_1 = n - 1;

        // Инициализация начального значения для R
        int R = 1;

        // Вычисление F и R в канонической форме числа n
        F = CanonicalF(n_minus_1, qi, F, R);

        // Выполнение теста Миллера-Рабина для числа n
        bool millerResult = TestMiller(n, t1, qi);

        // Выполнение теста Поклингтона для числа n
        bool poklingtonResult = TestPoklingtona(n, t1, qi, R, F);

        // Если тесты не прошли, увеличиваем счетчик отвергнутых чисел и повторяем итерацию
        if (!millerResult || !poklingtonResult) {
            k++;
            i--;
            continue;
        }

        // Генерация простого числа по алгоритму ГОСТа
        int gostResult = GOST(t, q1);

        // Проверка вероятности ошибки тестов Миллера-Рабина и Поклингтона
        bool veroyatnostResult = VerTest(n, t1, R, F);

        // Вывод результатов тестов и генерации простого числа по ГОСТу
        InPut(n, veroyatnostResult, k, gostResult, millerResult, poklingtonResult);

        // Если оба теста прошли успешно, сбрасываем счетчик отвергнутых чисел
        if (millerResult && poklingtonResult) {
            k = 0;
        }
    }
    // Возврат кода успешного завершения программы
    return 0;
}
