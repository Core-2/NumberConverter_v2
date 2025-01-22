#include <iostream>
#include <limits>
#include <Windows.h>

constexpr int max_number{1000000000};
constexpr int position_calc{3};
constexpr int number_ten{10};

constexpr int pos_unit{0};
constexpr int pos_ten{1};
constexpr int pos_hundred{2};

const char* backspace_str{"\b"};
const char* unit_zero{"ноль"};

const char* units[] {backspace_str, "один", "два", "три", "четыре",
    "пять", "шесть", "семь", "восемь", "девять"};

const char* units_alt[]{backspace_str, "одна", "две", "три", "четыре",
    "пять", "шесть", "семь", "восемь", "девять"};

const char* teens[]{"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать",
    "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};

const char* tens[]{backspace_str, "", "двадцать", "тридцать", "сорок",
    "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};

const char* hundreds[]{backspace_str, "сто", "двести", "триста", "четыреста",
    "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};

const char* thousand_default{"тысяч"};
const char* thousand_var1{"тысяча"};
const char* thousand_var2{"тысячи"};
constexpr int index_thousand{3};

const char* million_default{"миллионов"};
const char* million_var1{"миллион"};
const char* million_var2{"миллиона"};
constexpr int index_million{6};

const char* ruble_default{"рублей"};
const char* ruble_var1{"рубль"};
const char* ruble_var2{"рубля"};
constexpr int index_ruble{0};

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


void ignoreLine();
void printConvertedNumber(int);
bool checkLargeNumberIsZero(int, int, bool);
bool checkNteen(int, int);
bool checkNumberInBounds(int);
bool getContinueOrExit();
int getNumber();
int getNumberLength(int);
int* numberToArray(int, int);
const char* convertNumberToWord(int, int, int, bool);
const char* convertLargeNumberToWord(int, int, bool);
const char* getUnitWord(int, int, bool);


int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    do
    {
        int input{getNumber()};
        printConvertedNumber(input);
        std::cout << '\n';
    }
    while(getContinueOrExit());

//    for(int i{1000}; i < 100000; i += 75)
//    {
//        printConvertedNumber(i);
//        std::cout << '\n';
//    }
    return 0;
}


int getNumber()
{
    while(true)
    {
        std::cout << "Введите число от 0 до 1 000 000 000: ";
        int num{};
        std::cin >> num;

        if(std::cin.fail())
        {
            std::cin.clear();
            ignoreLine();
            std::cout << "Неверный ввод! Попробуйте снова.\n";
        }
        else if(!checkNumberInBounds(num))
        {
            ignoreLine();
            std::cout << "Введеное число за допустимыми границами! "
                         "Попробуйте снова.\n";
        }
        else
        {
            ignoreLine();
            return num;
        }
    }
}


bool checkNumberInBounds(int num)
{
    if(num < 0)
        return false;
    else
        return num < max_number;

    //return((num >= 0) && (num < max_number));
}


bool getContinueOrExit()
{
    std::cout << "Введите \"y\", чтобы продолжить, "
                 "или любую клавишу, чтобы выйти: ";
    char answer{};
    std::cin >> answer;
    ignoreLine();

    return (answer == 'y');
}


void ignoreLine()
{
#ifdef max
#undef max
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif
}


void printConvertedNumber(int num)
{
    if(num == 0)
    {
        std::cout << unit_zero << ' ' << ruble_default;
        return;
    }

    int numberLength{getNumberLength(num)};
    int* numArr{numberToArray(num, numberLength)};
    bool isNteen{false};
    bool isLargeNumberZero{true};

    for(int numIndex{numberLength - 1}; numIndex >= 0; --numIndex)
    {
        int digit{numArr[numIndex]};
        int position{numIndex % position_calc};

        const char * word{convertNumberToWord(digit, numIndex, position, isNteen)};

        if(isNteen)
            std::cout << backspace_str;

        std::cout << word << ' ';

        isLargeNumberZero = checkLargeNumberIsZero(digit, numIndex, isLargeNumberZero);

        if(position == pos_unit)
        {
            word = isLargeNumberZero ?
                        backspace_str :
                        convertLargeNumberToWord(digit, numIndex, isNteen);

            std::cout << word << ' ';

            isLargeNumberZero = true;
        }

        isNteen = checkNteen(digit, position);
    }

    delete[] numArr;
}


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


const char* convertNumberToWord(int digit, int numIndex, int position, bool isNteen)
{
    const char* result;

    switch(position)
    {
    case pos_unit:
        result = getUnitWord(digit, numIndex, isNteen);
        break;
    case pos_ten:
        result = tens[digit];
        break;
    case pos_hundred:
        result = hundreds[digit];
        break;
    default:
        result = "UNEXPECTED NUMBER!";
        break;
    }

    return result;
}


const char* getUnitWord(int digit, int numIndex, bool isNteen)
{
    const char* result;
    if(isNteen)
        result = teens[digit];
    else if(numIndex == index_thousand)
        result = units_alt[digit];
    else
        result = units[digit];

    return result;
}


const char* convertLargeNumberToWord(int digit, int numIndex, bool isNteen)
{
    const char* result;

    switch(numIndex)
    {
    case index_ruble:
        result = isNteen ? ruble_default : rubles[digit];
        break;
    case index_thousand:
        result = isNteen ? thousand_default : thousands[digit];
        break;
    case index_million:
        result = isNteen ? million_default : millions[digit];
        break;
    default:
        result = "UNEXPECTED LARGE NUMBER!";
        break;
    }

    return result;
}


bool checkNteen(int digit, int position)
{
    if(position == pos_ten)
        return digit == 1;
    else
        return false;

    //return ((position == pos_ten) && (digit == 1));
}


bool checkLargeNumberIsZero(int digit, int numIndex, bool check)
{
    if(numIndex == index_ruble)
        return false;
    else if(check)
        return (digit == 0);
    else
        return false;

    //return check && (digit == 0);
}
