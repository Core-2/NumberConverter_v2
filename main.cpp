#include <iostream>
#include <Windows.h>

constexpr int MAX_NUMBER{1000000000};   // a number, before which numbers can be converted
constexpr int power_of_ten{3};
constexpr int number_ten{10};

const char* units[] {"\b", "один", "два", "три", "четыре", "пять",
    "шесть", "семь", "восемь", "девять"};

const char* units_alt[]{"\b", "одна", "две", "три", "четыре", "пять",
    "шесть", "семь", "восемь", "девять"};

const char* teens[]{"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать",
    "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};

const char* tens[]{"\b", "\b", "двадцать", "тридцать", "сорок", "пятьдесят",
    "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};

const char* hundreds[]{"\b", "сто", "двести", "триста", "четыреста", "пятьсот",
    "шестьсот", "семьсот", "восемьсот", "девятьсот"};

const char* thousand_default{"тысяч"};
const char* thousand_var1{"тысяча"};
const char* thousand_var2{"тысячи"};

const char* million_default{"миллионов"};
const char* million_var1{"миллион"};
const char* million_var2{"миллиона"};

const char* thousands[]{thousand_default, thousand_var1, thousand_var2,
    thousand_var2, thousand_var2, thousand_default,
    thousand_default, thousand_default, thousand_default,
    thousand_default};

const char* millions[]{million_default, million_var1, million_var2,
    million_var2, million_var2, million_default,
    million_default, million_default, million_default,
    million_default};


int getNumberLength(int number)
{
    int length{0};

    for(; number != 0; number /= 10)
    {
        ++length;
    }

    return length;
}


int getInput()
{
    int input{0};
    std::cout << "Введите положительное число: ";
    std::cin >> input;

    return input;
}


void numberToArray(int* &arr, int num)
{
    int length{getNumberLength(num)};
    arr = new int[static_cast<std::size_t>(length)]{};

    for(int i{length - 1}; i >= 0; --i)
    {
        *(arr + i) = num % 10;
        num /= 10;
    }
}


int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int input{getInput()};
    int numberLength{getNumberLength(input)};
    int* numArr{nullptr};

    numberToArray(numArr, input);

//    for(int i{numberLength - 1}; i >= 0; --i)
//    {
//        *(numArr + i) = input % 10;
//        input /= 10;
//    }

    for(int i{0}; i < numberLength; ++i)
    {
        std::cout << *(numArr + i) << ' ';
    }

    std::cout << '\n';

    delete[] numArr;
    return 0;
}
