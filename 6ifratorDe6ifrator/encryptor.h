#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>

class Encryptor
{
public:
    virtual ~Encryptor() = default;
    virtual void encrypt(std::string const &source, std::string const &destination) = 0;
};

#endif // ENCRYPTOR_H
