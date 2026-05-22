#ifndef USER_DB_H
#define USER_DB_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "encryptionModule.h"
#include "Logs.h"

struct users{
    std::string username;
    std::string type;
    std::array<std::string,3> password;
    double balance = 0;
    int index;
};
struct UserLogs{
    std::string username;
    double balance = 0;
    std::vector<double> transactions;
};

class UserDB
{
private:
    std::string dbFileLoc = "database.txt";
    std::string transacFileLoc = "TransacLog.txt";
    std::fstream Filedb;
    std::fstream TransactionFile;
    users admin = {"admin", "A",GetEncryptedPassword("admin123"),0,1};
    std::vector<users> allUsers;
    std::vector<UserLogs> allUserLogs;
    
    static int userInDBCounter;
    std::array<std::string,3>GetEncryptedPassword(std::string password); 
    
    // suffix L functions are for transaction logs functions.

    void counterSetterFunction();
    bool fileExistsCheck();
    bool fileEmptyCheck();

    bool fileExistsCheckL();
    bool fileEmptyCheckL();

    void AdminCreation();

    void fileDataRead();
    void fileDataReadL();

    void CounterLoad();

public:

    Logs logger;

    void Initializedb();
    void fileWriteData();
    
    void newUserCreation(std::string username_, std::string password_);
    
    bool userNameChecker(std::string &username_);
    bool userAdminChecker(std::string &adminstr);
    bool passwordChecker(std::string &username, std::string &password);

    int usernameFinderLogs(std::string &username);
    int usernameFinderUsers(std::string &username);

    void deposit(double value,const int &index,const int &LogIndex);
    void withdrawal(double value,const int &index,const int &LogIndex);
    void getBalance(const int &index);
    void getTransactionHistory(const int &index);

    void userTest();
};
#endif