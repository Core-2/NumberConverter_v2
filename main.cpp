#include <constants.h>
#include <iostream>
#include <limits>
#include <Windows.h>


void ignoreLine();
void printConvertedNumber(int);
void convertationCycle(int, int, bool&, bool&);
void convertAndPrintDigit(int, int, int, bool);
void convertAndPrintLargeNumberName(int, int, bool, bool);
bool checkLargeNumberIsZero(int, int, bool);
bool checkNteen(int, int);
bool checkNumberInBounds(int);
bool getContinueOrExit();
int getNumber();
int getNumberLength(int);
int getDigitFromNumber(int, int);
const char* convertDigitToWord(int, int, int, bool);
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
            std::cout << "Введенное число за допустимыми границами! "
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
    return num < 0 ? false : num < max_number;
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
    bool isNteen{false};
    bool isLargeNumberZero{true};

    for(int numIndex{numberLength - 1}; numIndex >= 0; --numIndex)
    {
        convertationCycle(num, numIndex, isNteen, isLargeNumberZero);
    }
}


void convertationCycle(int num, int numIndex, bool& isNteen, bool& isLargeNumberZero)
{
    int digit{getDigitFromNumber(num, numIndex)};
    int position{numIndex % position_calc};

    convertAndPrintDigit(digit, numIndex, position, isNteen);
    isLargeNumberZero = checkLargeNumberIsZero(digit, numIndex, isLargeNumberZero);

    if(position == pos_unit)
    {
        convertAndPrintLargeNumberName(digit, numIndex, isNteen, isLargeNumberZero);
        isLargeNumberZero = true;
    }

    isNteen = checkNteen(digit, position);
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


int getDigitFromNumber(int num, int i)
{
    int pos{1};
    while( i != 0)
    {
        pos *= number_ten;
        --i;
    }

    return ((num / pos) % number_ten);
}


void convertAndPrintDigit(int digit, int numIndex, int position, bool isNteen) {
    const char* word{convertDigitToWord(digit, numIndex, position, isNteen)};

    if(isNteen)
        std::cout << backspace_str;

    std::cout << word << ' ';
}


void convertAndPrintLargeNumberName(int digit, int numIndex, bool isNteen, bool isLargeNumberZero) {
    const char* word = isLargeNumberZero ?
                backspace_str :
                convertLargeNumberToWord(digit, numIndex, isNteen);

    std::cout << word << ' ';
}


const char* convertDigitToWord(int digit, int numIndex, int position, bool isNteen)
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
    return (position == pos_ten) ? digit == 1 : false;
}


bool checkLargeNumberIsZero(int digit, int numIndex, bool check)
{
    bool result{false};
    if(numIndex == index_ruble)
        result = false;
    else if(check)
        result = (digit == 0);

    return result;
}
