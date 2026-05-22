#ifndef BANK_INTERFACE_H
#define BANK_INTERFACE_H

#include <iostream>
#include "userDB.h"
#include "Logs.h"

class BankInterface
{
private:
    enum USERROLE{
        ADMIN,
        USER,
        FAIL
    };
    UserDB user;
    // Logs logger;
    bool sizeValidation(std::string &option_);
    bool InputValidation(std::string str);
//_______CreateHelpers___________________________
    void CreateAccount();
    void UserPasswordInputChecker(bool &createOrNot,std::string &username_,std::string &password_);
//_______LoginHelpers____________________________    
    void LoginAccount();
    USERROLE LoginAuth(std::string &username,std::string &password);
    void UserChecker(std::string &username,std::string &password,bool &adminOptions, bool &loginFail);

    //______User_________________
    void userAccess(std::string &username);
    void userAccessWelcomeStruct(int &option);
    void DepositInterface(const int &userIndex,const int &userLogIndex);
    void WithdrawInterface(const int &userIndex,const int &userLogIndex);
    bool AmountValidation(std::string amount);

    //_______admin____________
    void adminAccess();
    void adminAccessWelcomeStruct(int &optionsInt);
    
    
//_______RunHelpers______________________________
    void WelcomeFunction(std::string &option_);

public:
    void Run();
};

#endif