#ifndef CESAR_ENCRYPTION_TOOLS_H
#define CESAR_ENCRYPTION_TOOLS_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <clocale>
#include <codecvt>
#include <locale>
#include <vector>
#include <Windows.h>

inline bool isASCIILetter(char letter)
{
    int16_t lowerBorderCapitalAlfabets = 64;
    int16_t upperBorderCapitalAlfabets = 91;
    int16_t lowerBorderAlfabets = 96;
    int16_t upperBorderAlfabets = 123;
    return (((lowerBorderCapitalAlfabets < (int)letter) && ((int)letter < upperBorderCapitalAlfabets))
        || ((lowerBorderAlfabets < (int)letter) && ((int)letter < upperBorderAlfabets)));
}

inline std::string GetLastErrorAsString()
{
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0)
        return std::string("No error"); //No error message has been recorded

    LPWSTR messageBuffer = nullptr;
    size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, NULL);

    std::wstring wmessage(messageBuffer, size);
    LocalFree(messageBuffer);

    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string message = converter.to_bytes( wmessage );

    return converter.to_bytes( wmessage );
}

#endif // CESAR_ENCRYPTION_TOOLS_H
