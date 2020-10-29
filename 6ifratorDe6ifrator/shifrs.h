#ifndef SHIFRS_H
#define SHIFRS_H

#include <unordered_map>
#include <string>


enum class Shifrs
{
    Cesar = 0,
    MonoAlphabet
};


static std::unordered_map<Shifrs, std::string> shifrs{
    { Shifrs::Cesar, "Шифр Цезаря" },
    { Shifrs::MonoAlphabet, "Наименее значащий бит" }
};

#endif // SHIFRS_H
