#include "userDB.h"
#include "encryptionModule.h"
#include <array>
    int UserDB::userInDBCounter = 0;
    

    void UserDB::counterSetterFunction(){
        if(!allUsers.empty()){
        userInDBCounter = allUsers.size();
        }
    }

    void UserDB::Initializedb(){
        while (true)
        {
            if (fileExistsCheck())
            {
                if (fileEmptyCheck()){
                    AdminCreation();
                    break;
                }
                else{
                    fileDataRead();
                    break;
                }
            }
            else{
                Filedb.open("database.txt",std::ios::out);
                Filedb.close();
            }
        }
//_________TRANSACTION_LOG_________________________________
        while (true)
        {
            if (fileExistsCheckL())
            {
                if (fileEmptyCheckL()){
                    break;
                }
                else{
                    fileDataReadL();
                    break;
                }
            }
            else{
                TransactionFile.open(transacFileLoc,std::ios::out);
                TransactionFile.close();
            }
        }
    }

    std::array<std::string,3>UserDB::GetEncryptedPassword(std::string password){
        EncryptionModule adminPass;
        adminPass.setEnCryptionPassword(password);
        return adminPass.getEncryptedPassword();
    }

    void UserDB::AdminCreation(){
        Filedb.open("database.txt",std::ios::app);
        userInDBCounter++;
        Filedb << userInDBCounter << std::endl;
        Filedb << admin.index << "|" <<admin.type << "|" << admin.username << "|" << admin.password[0] << "|" << admin.password[1] << "|"<< admin.password[2] << "|\n";
        Filedb.close();
    }

    bool UserDB::fileExistsCheck(){
        std::ifstream file("database.txt");
        if (file)
        {
            file.close();
            return true;
        }
        file.close();
        return false; 
    }

    bool UserDB::fileExistsCheckL(){
        std::ifstream file(transacFileLoc);
        if (file)
        {
            file.close();
            return true;
        }
        file.close();
        return false; 
    }


    bool UserDB::fileEmptyCheck(){
        std::ifstream file("database.txt",std::ios::ate);
        if(file.tellg() == 0){
            file.close();
            return true;
        }
        file.close();
        return false;    
    }

    bool UserDB::fileEmptyCheckL(){
        std::ifstream file(transacFileLoc,std::ios::ate);
        if(file.tellg() == 0){
            file.close();
            return true;
        }
        file.close();
        return false;    
    }

    void UserDB::CounterLoad(){
        Filedb.open("database.txt",std::ios::in);
        std::string counterString;
        getline(Filedb,counterString,'\n');
        userInDBCounter = stoi(counterString);
        Filedb.close();
    }

void UserDB::fileDataRead(){
    CounterLoad();
    Filedb.open("database.txt",std::ios::in);
    std::string temp;
    getline(Filedb,temp,'\n');
    getline(Filedb,temp,'\n');

    if (userInDBCounter > 0)
    {
        int i = 0;
        std::string indextransfer;
        std::string balancetransfer;
        allUsers.resize(userInDBCounter - 1);
        while (!Filedb.eof())
        {
            if(i >= userInDBCounter - 1){ 
                break; 
            }
            getline(Filedb,indextransfer,'|');
            getline(Filedb,allUsers[i].type,'|');
            getline(Filedb,allUsers[i].username,'|');
            getline(Filedb,allUsers[i].password[0],'|');
            getline(Filedb,allUsers[i].password[1],'|');
            getline(Filedb,allUsers[i].password[2],'|');
            getline(Filedb,balancetransfer,'|');
            allUsers[i].index = stoi(indextransfer);
            allUsers[i].balance = stod(balancetransfer);
            i++;
        }
    }
    Filedb.close();      
}
//___________FOR_USER_TRANSACTION_LOGS________________________________
void UserDB::fileDataReadL(){
    TransactionFile.open(transacFileLoc,std::ios::in);
    // UserLogs temp;
    std::string tempBalance;
    std::string tempforTransac;
    std::vector<std::string>tempTransactions;
    int n = 0;
    if(userInDBCounter > 0){
    allUserLogs.resize(userInDBCounter - 1);
    while (!TransactionFile.eof())
    {
        if(n >= userInDBCounter - 1){ 
                break; 
        }

        getline(TransactionFile,allUserLogs[n].username,'|');
        getline(TransactionFile,tempBalance,'|');
        while (TransactionFile.peek() != '\n' && TransactionFile.peek() != EOF)
        {
            getline(TransactionFile,tempforTransac,'|');
            tempTransactions.push_back(tempforTransac);
        }

        allUserLogs[n].balance = stod(tempBalance);
        for (size_t j = 0; j < tempTransactions.size(); j++)
        {
            allUserLogs[n].transactions.push_back(stod(tempTransactions[j]));
        }
        n++;
    }
    }
    TransactionFile.close();
}

    void UserDB::userTest(){
        for (size_t i = 0; i < allUsers.size(); i++)
        {
            std::cout << "working" << std::endl;
            std::cout << allUsers[i].index << "|" << allUsers[i].type << "|" << allUsers[i].username << "|" << allUsers[i].password[0] << "|" << allUsers[i].password[1]<< "|" << allUsers[i].password[2] << std::endl;
            std::cout << allUserLogs[i].username << "|" << allUserLogs[i].balance << "|" << std::endl;
        }   
    }

    void UserDB::newUserCreation(std::string username_, std::string password_){
            userInDBCounter++;
            users newUser;
            UserLogs newUserLogs;
            EncryptionModule encryptorUser;
                //_____User_______________
                newUser.index = userInDBCounter;
                newUser.type = "U";
                newUser.username = username_;
                encryptorUser.setEnCryptionPassword(password_);
                newUser.password = encryptorUser.getEncryptedPassword();
                newUser.balance = 0;
                //_____UserLogs____________
                newUserLogs.username = username_;
                newUserLogs.balance = 0;
                newUserLogs.transactions.push_back(0.0);

            allUsers.push_back(newUser);
            allUserLogs.push_back(newUserLogs);
    }

    bool UserDB::userNameChecker(std::string &username_){
        if(userAdminChecker(username_)){
            return false;
        }
        else if(!allUsers.empty()){
            for (size_t i = 0; i < allUsers.size(); i++)
            {
                if(username_ == allUsers[i].username){
                    return false;
                }
            }
        }

        return true;
    }

    bool UserDB::userAdminChecker(std::string &adminstr){
        if(adminstr == admin.username){
            return true;
        }
        return false;
    }

    bool UserDB::passwordChecker(std::string &username, std::string &password){
        std::string decrPassword;
        EncryptionModule decrpass;
        if (username == admin.username)
        {
            decrPassword = decrpass.getDeCryptedPassword(admin.password);
            if (decrPassword == password)
            {
                return true;
            }
            else{
                return false;
            }
        }
        for (size_t i = 0; i < allUsers.size(); i++)
        {
            if (username == allUsers[i].username)
            {
                decrPassword = decrpass.getDeCryptedPassword(allUsers[i].password);
                if (decrPassword == password)
                {
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        return false;
    }

void UserDB::fileWriteData(){  
    Filedb.open("database.txt", std::ios::out | std::ios::trunc);
    
        if (!Filedb) {
            std::cout << "File open failed database\n";
            return;
        }
        Filedb << userInDBCounter << std::endl;
        Filedb << admin.index << "|" <<admin.type << "|" << admin.username << "|" << admin.password[0] << "|" << admin.password[1] << "|"<< admin.password[2] << "|" << admin.balance << "|\n";
        if (!allUsers.empty())
        {
            for (size_t i = 0; i < allUsers.size(); i++)
            {
                Filedb << allUsers[i].index << "|" << allUsers[i].type << "|" << allUsers[i].username << "|" << allUsers[i].password[0] << "|" << allUsers[i].password[1]<< "|" << allUsers[i].password[2]<< "|" << allUsers[i].balance << "|\n";
            }
        }
    Filedb.close();
//_____FOR_USER_TRANSACTION_LOG_FILES____________________________________________________________
    TransactionFile.open(transacFileLoc,std::ios::out | std::ios::trunc);
        if (!TransactionFile) {
            std::cout << "File open failed transaclog\n";
            return;
        }
        else if(!allUserLogs.empty()){
            for (size_t i = 0; i < allUserLogs.size(); i++)
            {
                TransactionFile << allUserLogs[i].username << "|" << allUserLogs[i].balance << "|";
                for (size_t n = 0; n < allUserLogs[i].transactions.size(); n++)
                {
                    TransactionFile << allUserLogs[i].transactions[n] << "|";
                }
                TransactionFile << "\n";
            }
        }
    TransactionFile.close();
}

    int UserDB::usernameFinderLogs(std::string &username){
        for (size_t i = 0; i < allUserLogs.size(); i++)
        {
            if(allUserLogs[i].username == username){
                return i;
                break;
            }
        }
        return -1;
    }

    int UserDB::usernameFinderUsers(std::string &username){
        for (size_t i = 0; i < allUsers.size(); i++)
        {
            if(allUsers[i].username == username){
                return i;
                break;
            }
        }
        return -1;
    }

    void UserDB::deposit(double value,const int &index,const int &LogIndex){
        double balance = allUsers[index].balance;
        std::cout << balance << " + " << value;
        balance = balance + value;
        std::cout << " => " << balance << std::endl;
        allUsers[index].balance = balance;
        allUserLogs[LogIndex].balance = balance;
        allUserLogs[LogIndex].transactions.push_back(value);
    }


    void UserDB::withdrawal(double value,const int &index,const int &LogIndex){
        if(allUsers[index].balance <= 0){
            std::cout << "you do not have any amount available to withdraw" << std::endl;
            return;
        }
        double balance = allUsers[index].balance;
        std::cout << balance << " - " << value;
        balance = balance - value;
        std::cout << " => " << balance << std::endl;
        if(balance < 0){
            std::cout << "the amount withdrawn is insufficient... cancelling the transaction" << std::endl;
            return;
        }
        allUsers[index].balance = balance;
        allUserLogs[LogIndex].balance = balance;
        allUserLogs[LogIndex].transactions.push_back((value - (value * 2)));
    }


    void UserDB::getBalance(const int &index){
        std::cout << "your current balance = " << allUsers[index].balance << std::endl;
    }

    void UserDB::getTransactionHistory(const int &index){
        if(allUserLogs[index].transactions.size() < 1){
            std::cout << "no transactions performed yet" << std::endl;
        }
        for (size_t i = 1; i < allUserLogs[index].transactions.size(); i++)
        {
            std::cout << "Transaction number [" << i << "]: " <<allUserLogs[index].transactions[i] << std::endl;
        }  
    }

   