#ifndef CESAR_ENCRYPTOR_H
#define CESAR_ENCRYPTOR_H

#include "encryptor.h"
#include "cesar_encryption_tools.h"

class CesarEncryptor
        : public Encryptor
{
public:
    CesarEncryptor(size_t shift);
    void encrypt(std::string &source, std::string &destination) override;
private:
    size_t _shift;
};

#endif // CESAR_ENCRYPTOR_H
