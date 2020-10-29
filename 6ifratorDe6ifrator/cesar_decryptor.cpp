#include "cesar_decryptor.h"

#include <experimental/filesystem>
#include <fstream>
#include <cctype>

char decrypt(char symbol, size_t shift = 1)
{
    if (symbol == ' ' || symbol == '\n')
      return symbol;

    if (symbol >= 'A' && symbol <= 'Z') {
        symbol += (shift % 26);
        if (symbol > 'Z')
            symbol -= 26;

        return symbol;
    }
    else if (symbol >= 'a' && symbol <= 'z') {
        symbol += (shift % 26);
        if (symbol > 'z')
            symbol -= 26;

        return symbol;
    }
    else if (symbol >= "А"[0] && symbol <= "Я"[0]) {
        symbol += (shift % 33);
        if (symbol > "Я"[0])
            symbol -= 33;

        return symbol;
    }
    else if (symbol >= "а"[0] && symbol <= "я"[0]) {
        symbol += (shift % 33);
        if (symbol > "я"[0])
            symbol -= 33;

        return symbol;
    }

    return symbol;
}

CesarDecryptor::CesarDecryptor(size_t shift)
    : _shift( shift)
{

}

void CesarDecryptor::decrypt(std::string &source, std::string &destination)
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
        auto const decrypted_char = ::decrypt(symbol);
        dest.write(&decrypted_char, 1);
    }
}
