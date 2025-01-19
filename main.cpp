#include <iostream>
#include <Windows.h>

constexpr int max_number{1000000000};   // a number, before which numbers can be converted
constexpr int position_calc{3};
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

const char* ruble_default{"рублей"};
const char* ruble_var1{"рубль"};
const char* ruble_var2{"рубля"};

const char* thousands[]{thousand_default, thousand_var1, thousand_var2,
    thousand_var2, thousand_var2, thousand_default,
    thousand_default, thousand_default, thousand_default,
    thousand_default};

const char* millions[]{million_default, million_var1, million_var2,
    million_var2, million_var2, million_default,
    million_default, million_default, million_default,
    million_default};

const char* rubles[]{ruble_default, ruble_var1, ruble_var2,
    ruble_var2, ruble_var2, ruble_default,
    ruble_default, ruble_default, ruble_default,
    ruble_default};


int getNumberLength(int number)
{
    int length{0};

    while(number != 0)
    {
        ++length;
        number /= number_ten;
    }

    return length;
}


int getNumber()
{
    int num{0};
    std::cout << "Введите положительное число: ";
    std::cin >> num;

    return num;
}


int* numberToArray(int num, int length)
{
    int* arr{new int[static_cast<std::size_t>(length)]{}};

    for(int i{0}; i < length; ++i)
    {
        arr[i] = num % number_ten;
        num /= number_ten;
    }

    return arr;
}


const char* convertNumberToWord(int digit, int numIndex, int position, bool& isNteen)
{
    const char* result;

    switch(position)
    {
    case 0:
        if(isNteen)
            result = teens[digit];
        else if(numIndex == 3)
            result = units_alt[digit];
        else
            result = units[digit];
        break;
    case 1:
        result = tens[digit];
        isNteen = (digit == 1);
        break;
    case 2:
        result = hundreds[digit];
        break;
    default:
        result = "UNEXPECTED!";
    }

    return result;
}


void printConvertedNumber(int num)
{
    int numberLength{getNumberLength(num)};
    int* numArr{numberToArray(num, numberLength)};
    bool isNteen{false};

    for(int numIndex{numberLength - 1}; numIndex >= 0; --numIndex)
    {
        int digit{numArr[numIndex]};
        int position{numIndex % position_calc};
        const char * word{};

//        switch(position)
//        {
//        case 0:
//            if(numIndex == 3)
//                word = units_alt[digit];
//            else
//                word = units[digit];
//            break;
//        case 1:
//            word = tens[digit];
//            if(digit == 1)
//            {
//                --numIndex;
//                digit = numArr[numIndex];
//                position = numIndex % position_calc;
//                word = teens[digit];
//                isNteen = true;
//            }
//            break;
//        case 2:
//            word = hundreds[digit];
//            break;
//        }

        word = convertNumberToWord(digit,numIndex, position, isNteen);
        std::cout << word << ' ';

        if(position == 0)
        {
            switch(numIndex)
            {
            case 0:
                if(isNteen)
                    word = ruble_default;
                else
                    word = rubles[digit];
                break;
            case 3:
                if(isNteen)
                    word = thousand_default;
                else
                    word = thousands[digit];
                break;
            case 6:
                if(isNteen)
                    word = million_default;
                else
                    word = millions[digit];
                break;
            }

            isNteen = false;

            std::cout << word << ' ';
        }
    }

    delete[] numArr;
}


int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int input{getNumber()};

    printConvertedNumber(input);

    std::cout << '\n';

    return 0;
}
