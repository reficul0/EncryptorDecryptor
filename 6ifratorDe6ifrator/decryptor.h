#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <string>

class Decryptor
{
public:
    virtual ~Decryptor() = default;
    virtual void decrypt(std::string const &source, std::string const &destination) = 0;
};

#endif // DECRYPTOR_H
