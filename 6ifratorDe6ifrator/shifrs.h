#ifndef SHIFRS_H
#define SHIFRS_H

#include <unordered_map>
#include <string>


enum class Shifrs
{
    Cesar = 0,
};


static std::unordered_map<Shifrs, std::string> shifrs{
    { Shifrs::Cesar, "Шифр Цезаря" }
};

#endif // SHIFRS_H
