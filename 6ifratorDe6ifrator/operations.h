#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <unordered_map>
#include <string>

enum Operations
{
    Shifr = 0,
    Deshifr = 1
};

static std::unordered_map<Operations, std::string> operations{
    { Operations::Shifr, "Шифровка" },
    { Operations::Deshifr, "Дешифровка" }
};

#endif // OPERATIONS_H
