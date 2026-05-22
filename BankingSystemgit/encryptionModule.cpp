#include "encryptionModule.h"
#include <iostream>
#include <stdexcept>

std::string EncryptionModule::enCryption(std::string &password, enum EncryptionStatus status_){
    std::string result;
    if(status_ == Encrp1){
        for(char a : password){
            char n = a + ENCRYPTION_[Encrp1]; // [0]
            result.push_back(n);
        }
    }
    else if (status_ == EncrpConformation)
    {
        for(char a : password){
            char n = a + ENCRYPTION_[EncrpConformation]; // [1]
            result.push_back(n);
        }
    }
    else if (status_ == EncrpRecovery)
    {
        for(char a : password){
            char n = a + ENCRYPTION_[EncrpRecovery]; // [2]
            result.push_back(n);
        }
    }
    return result;
}

std::string EncryptionModule::deCryption(std::string &enCryptedPassword, enum EncryptionStatus status_){
    std::string result;
    if(status_ == Encrp1){
        for(char a : enCryptedPassword){
            char n = a - ENCRYPTION_[Encrp1]; // [0]
            result.push_back(n);
        }
    }
    else if (status_ == EncrpConformation)
    {
        for(char a : enCryptedPassword){
            char n = a - ENCRYPTION_[EncrpConformation]; // [1]
            result.push_back(n);
        }
    }
    else if (status_ == EncrpRecovery)
    {
        for(char a : enCryptedPassword){
            char n = a - ENCRYPTION_[EncrpRecovery]; // [2]
            result.push_back(n);
        }
    }
    return result;
}

std::string EncryptionModule::getDeCryptedPassword(){
    std::string Checker[3];
    Checker[0] = deCryption(TestPassword[0],Encrp1);
    Checker[1] = deCryption(TestPassword[1],EncrpConformation);
    Checker[2] = deCryption(TestPassword[2],EncrpConformation);
    if ((Checker[0] == Checker[1]))
    {
        return Checker[0];
    } else if (Checker[0] == Checker[2])
    {
        return Checker[0];
    } else if(Checker[1] == Checker[2]){
        return Checker[1];
    }
    return "failed";
}

std::string EncryptionModule::getDeCryptedPassword( std::array<std::string,3> EncrPassword){
    std::string Checker[3];
    Checker[0] = deCryption(EncrPassword[0],Encrp1);
    Checker[1] = deCryption(EncrPassword[1],EncrpConformation);
    Checker[2] = deCryption(EncrPassword[2],EncrpConformation);
    if ((Checker[0] == Checker[1]))
    {
        return Checker[0];
    } else if (Checker[0] == Checker[2])
    {
        return Checker[0];
    } else if(Checker[1] == Checker[2]){
        return Checker[1];
    }
    return "failed";
}

void EncryptionModule::setEnCryptionPassword(std::string password){
    this->TestPassword[0] = enCryption(password,Encrp1);
    this->TestPassword[1] = enCryption(password,EncrpConformation);
    this->TestPassword[2] = enCryption(password,EncrpRecovery);
}

std::array<std::string,3> EncryptionModule::getEncryptedPassword(){  
    std::array<std::string,3> results;
    results[0] = TestPassword[0];
    results[1] = TestPassword[1];
    results[2] = TestPassword[2];
    return results;
}