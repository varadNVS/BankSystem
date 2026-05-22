#ifndef ENCRYPTION_MODULE_H
#define ENCRYPTION_MODULE_H

#include<string>
#include<array>

class EncryptionModule
{
private:
    std::string TestPassword[3]; // CHANGE IT TO TEMPSTORAGE -> FOR TEMP STORAGE BEFORE SHARING.
    enum EncryptionStatus {
        Encrp1,
        EncrpConformation,
        EncrpRecovery
    };
    const int ENCRYPTION_[3] = {100,101,102};
    
    std::string enCryption(std::string &password, enum EncryptionStatus status_);
    std::string deCryption(std::string &enCryptedpassword, enum EncryptionStatus status_);    
public:

    std::string getDeCryptedPassword();
    std::string getDeCryptedPassword(std::array<std::string,3> EncrPassword);

    void setEnCryptionPassword(std::string password);
    std::array<std::string,3> getEncryptedPassword();
    
};

#endif