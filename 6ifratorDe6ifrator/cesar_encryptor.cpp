#include "cesar_encryptor.h"

#include <Windows.h>
#include <experimental/filesystem>
#include <fstream>
#include <cctype>

char encrypt(char symbol, size_t shift = 1)
{
    if (symbol == ' ' || symbol == '\n')
      return symbol;

    if (symbol >= 'A' && symbol <= 'Z') {
        symbol -= (shift % 26);
        if (symbol < 'A')
            symbol += 26;
    }
    else if (symbol >= 'a' && symbol <= 'z') {
        symbol -= (shift % 26);
        if (symbol < 'a')
            symbol += 26;
    }
    else if (symbol >= "А"[0] && symbol <= "Я"[0]) {
        symbol -= (shift % 33);
        if (symbol < "А"[0])
            symbol += 33;
    }
    else if (symbol >= "а"[0] && symbol <= "я"[0]) {
        symbol -= (shift % 33);
        if (symbol < "а"[0])
            symbol += 33;
    }

    return symbol;
}

CesarEncryptor::CesarEncryptor(size_t shift)
    : _shift( shift)
{

}

void CesarEncryptor::encrypt(std::string const &source, std::string const &destination)
{
    std::experimental::filesystem::path source_path = std::experimental::filesystem::absolute(source);
    std::ifstream src{source, std::ios::binary, _SH_DENYWR};
    if(!src)
        throw std::ios::failure{"Не удалось открыть файл " + source_path.string() + ", причина: " + GetLastErrorAsString()};

    std::experimental::filesystem::path dest_path = std::experimental::filesystem::absolute(destination);

    std::ofstream dest{dest_path, std::ios::trunc | std::ios::binary, _SH_DENYRD};
    std::string dest_str = dest_path.string();
    if(!dest)
        throw std::ios::failure{"Не удалось открыть файл " + dest_path.string() + ", причина: " + GetLastErrorAsString()};

    char symbol;
    while(src.get(symbol))
    {
        auto const encrypted_char = ::encrypt(symbol, _shift);
        dest.write(&encrypted_char, 1);
    }
}
