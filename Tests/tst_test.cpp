#include <QtTest>
#include <QCoreApplication>
#include <QtTest/QtTest>

#include <../6ifratorDe6ifrator/cesar_decryptor.h>
#include <../6ifratorDe6ifrator/cesar_encryptor.h>

#include <fstream>

// add necessary includes here

class Test : public QObject
{
    Q_OBJECT

public:
    Test() = default;
    ~Test() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_encryption_decryption();
    void test_encryptor_file_search_exception_detecting();
    void test_decryptor_file_search_exception_detecting();
};

void Test::initTestCase()
{

}

void Test::cleanupTestCase()
{

}

void Test::test_encryption_decryption()
{
    CesarEncryptor encryptor(1);
    CesarDecryptor decryptor(1);
    {
        int i = 0;
        std::ofstream sourse("decrypted_ceasar.txt", std::ios::binary | std::ios::trunc);
        sourse << "abvgd1263671236172\ndhjfakjsdhfgakjh!adsfjhjkl!";
    }
    try
    {
        encryptor.encrypt(
            "decrypted_ceasar.txt",
            "encrypted_ceasar1.txt"
        );
        decryptor.decrypt(
            "encrypted_ceasar1.txt",
            "decrypted_ceasar1.txt"
        );
    } catch(std::ios::failure e)
    {
        std::cout << e.what();
        QTEST_ASSERT(false);
    }

    std::ifstream sourse("decrypted_ceasar.txt");
    std::ifstream decrypted("decrypted_ceasar1.txt");

    char source_char;
    char decrypted_char;
    while(sourse.get(source_char))
    {
        decrypted.get(decrypted_char);
        QTEST_ASSERT(source_char == decrypted_char);
    }
    QTEST_ASSERT(!decrypted.get(decrypted_char));
}

void Test::test_encryptor_file_search_exception_detecting()
{
    CesarEncryptor encryptor(1);
    bool exception_detected = false;
    try
    {
        encryptor.encrypt(
            "asdasdawerqreqw1",
            "encrypted_ceasar1.txt"
        );
    } catch(std::ios::failure e)
    {
        exception_detected = true;
    }
    QTEST_ASSERT(exception_detected);
}

void Test::test_decryptor_file_search_exception_detecting()
{
    CesarDecryptor decryptor(1);
    bool exception_detected = false;
    try
    {
        decryptor.decrypt(
            "asdasdawerqreqw1",
            "encrypted_ceasar1.txt"
        );
    } catch(std::ios::failure e)
    {
        exception_detected = true;
    }
    QTEST_ASSERT(exception_detected);
}

QTEST_MAIN(Test)

#include "tst_test.moc"
