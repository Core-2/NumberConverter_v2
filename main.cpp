#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>
#include <Windows.h>

constexpr int max_number{1000000000};   // a number, before which numbers can be converted
constexpr int power_of_ten{3};

static std::array<std::string_view, 10> units{"\b", "один", "два", "три", "четыре", "пять",
                                              "шесть", "семь", "восемь", "девять"};

static std::array<std::string_view, 10> units_alt{"\b", "одна", "две", "три", "четыре", "пять",
                                              "шесть", "семь", "восемь", "девять"};

static std::array<std::string_view, 10> teens{"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать",
                                               "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};

static std::array<std::string_view, 10> tens{"\b", "\b", "двадцать", "тридцать", "сорок", "пятьдесят",
                                              "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};

static std::array<std::string_view, 10> hundreds{"\b", "сто", "двести", "триста", "четыреста", "пятьсот",
                                                 "шестьсот", "семьсот", "восемьсот", "девятьсот"};

const std::string_view thousand_default{"тысяч"};
const std::string_view thousand_var1{"тысяча"};
const std::string_view thousand_var2{"тысячи"};

const std::string_view million_default{"миллионов"};
const std::string_view million_var1{"миллион"};
const std::string_view million_var2{"миллиона"};

static std::array<std::string_view, 10> thousands{thousand_default, thousand_var1, thousand_var2,
                                             thousand_var2, thousand_var2, thousand_default,
                                             thousand_default, thousand_default, thousand_default,
                                             thousand_default};

static std::array<std::string_view, 10> millions{million_default, million_var1, million_var2,
                                             million_var2, million_var2, million_default,
                                             million_default, million_default, million_default,
                                             million_default};


int getInput() {
    int value{};

    do {
        std::cout << "Введите корректное число: ";
        std::cin >> value;
    }
    while (value < 0 || value >= max_number);

    return value;
}


void separateInputOnNumbers(int i, std::vector<int>& vec) {
    vec.push_back(i % 10);
    int temp{i / 10};

    if(!temp) return;

    separateInputOnNumbers(temp, vec);
}


void printWord(std::array<std::string_view, 10>& arr, int unitIndex) {
    std::cout << arr[unitIndex] << ' ';
}


bool selectAndPrintNumberName(int index, int rest, int blocksOfHundreds, bool isTeen) {
    std::array<std::string_view, 10>* arr;

    switch(rest) {
    case 3:
        arr = &hundreds;
        break;

    case 2:
        isTeen = (index == 1);
        arr = &tens;
        break;

    case 1:
        if(isTeen)
            arr = &teens;
        else if (blocksOfHundreds == 1)
            arr = &units_alt;
        else
            arr = &units;
        break;

    default:
        return isTeen;
    }

    printWord(*arr, index);
    return isTeen;
}


bool selectAndPrintLargeNumberName(int index, int blocksOfHundreds, bool isTeen) {
    std::array<std::string_view, 10>* arr;

    switch(blocksOfHundreds) {
    case 1:
        arr = &thousands;
        break;
    case 2:
        arr = &millions;
        break;
    default:
        return isTeen;
    }

    if(isTeen) {
        index = 0;
        isTeen = false;
    }

    printWord(*arr, index);
    return isTeen;
}


void printNumberInWords(const std::vector<int>& vec) {
    int blocksOfHundreds{static_cast<int>(vec.size()) / power_of_ten};
    int rest{static_cast<int>(vec.size()) % power_of_ten};
    bool isBlockOfHundredsIsEmpty{false};
    bool isTeen{false};

    for(auto num : vec) {
        if(rest == 0) {
            --blocksOfHundreds;
            rest = 3;
            isBlockOfHundredsIsEmpty = true;
        }

        isTeen = selectAndPrintNumberName(num, rest, blocksOfHundreds, isTeen);

        if(num)
            isBlockOfHundredsIsEmpty = false;

        --rest;

        if(rest == 0 && !isBlockOfHundredsIsEmpty) {
            isTeen = selectAndPrintLargeNumberName(num, blocksOfHundreds, isTeen);
        }
    }
}


int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int input{getInput()};

    std::vector<int> inputNumbers{};

    separateInputOnNumbers(input, inputNumbers);
    std::reverse(inputNumbers.begin(), inputNumbers.end());

    printNumberInWords(inputNumbers);

    std::cout << '\n';

    return 0;
}
