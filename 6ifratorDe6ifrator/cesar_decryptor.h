#ifndef CESARDECRYPTOR_H
#define CESARDECRYPTOR_H

#include "decryptor.h"
#include "cesar_encryption_tools.h"

class CesarDecryptor
        : public Decryptor
{
public:
    CesarDecryptor(size_t shift);
    void decrypt(std::string const &source, std::string const &destination) override;
private:
    size_t _shift;
};

#endif // CESARDECRYPTOR_H
