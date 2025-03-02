#ifndef CONSTANTS_H
#define CONSTANTS_H

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

#endif // CONSTANTS_H
