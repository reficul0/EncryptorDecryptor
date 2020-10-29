#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <string>

class Decryptor
{
public:
    virtual ~Decryptor() = default;
    virtual void decrypt(std::string &source, std::string &destination) = 0;
};

#endif // DECRYPTOR_H
