#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>

class Encryptor
{
public:
    virtual ~Encryptor() = default;
    virtual void encrypt(std::string &source, std::string &destination) = 0;
};

#endif // ENCRYPTOR_H
