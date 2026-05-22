#include "BankInterface.h"

void BankInterface::Run(){
    enum options{
        CREATE_ACCOUNT = 1,
        LOGIN_ACCOUNT,
        EXIT = 0
    };
    user.Initializedb();
    std::string inputString;
    int inputInt;
    bool exit = false;
    
        while (!exit)
        {
            WelcomeFunction(inputString);
            inputInt = stoi(inputString);
            switch (inputInt)
            {
            case CREATE_ACCOUNT:
                CreateAccount();
                user.fileWriteData();
                break;
            case LOGIN_ACCOUNT:
                LoginAccount();
                user.fileWriteData();
                break;
            case EXIT:
                std::cout << "exiting..." << std::endl;
                user.fileWriteData();
                exit = true;
                break;
            default:
                std::cout << "please select from the options" << std::endl;
                break;
            }
        }
}

bool BankInterface::sizeValidation(std::string &option_){
        if(option_.size() > 1){
            return false;
        }
        return true;
}

void BankInterface::WelcomeFunction(std::string &option_){
    bool selection = false;
    do
    {
        std::cout << "welcome to CHITRAGUPT BANKING SYSTEM" << std::endl;
        std::cout << "Do you want to:" << std::endl;
        std::cout << "   Create account (type 1)" << std::endl;
        std::cout << "   Login account  (type 2)" << std::endl;
        std::cout << "   EXIT           (type 0)" << std::endl;
        getline(std::cin,option_);
        if(!sizeValidation(option_)){
            std::cout << "Please type single character only" << std::endl;
            
        }
        else if(option_ == " "){
                std::cout << "dont leave empty space" << std::endl;
        }
        else if((option_ == "0" || option_ == "1" || option_ == "2")){
            selection = true;
        }
        else{
            option_ = "3";
            selection = true;
        }
    } while (!selection);
}

//______________Login Account Block__________________

void BankInterface::LoginAccount(){
    BankInterface::USERROLE ROLE;
    std::string username;
    std::string password;
    ROLE = LoginAuth(username,password);

    if(ROLE == ADMIN){
        adminAccess();           
    }
    else if(ROLE == USER){
        userAccess(username);
    }
    else{
        std::cout << "exiting..." << std::endl;
        return;
    }
}

BankInterface::USERROLE BankInterface::LoginAuth(std::string &username,std::string &password){
    
    bool adminOptions;
    bool loginFail;
    UserChecker(username,password,adminOptions,loginFail);
    if (adminOptions == true && loginFail == false)
    {
        user.logger.LogsReceiver(username + "logged in");
        return ADMIN;
    }
    else if(adminOptions == false && loginFail == false)
    {
        user.logger.LogsReceiver(username + "logged in");
        return USER;
    }
    else if(loginFail == true)
    {
        user.logger.LogsReceiver("login failed");
        return FAIL;
    }
    return FAIL;
}

void BankInterface::UserChecker(std::string &username,std::string &password,bool &adminOptions, bool &loginFail){
    while (true)
    {
        std::cout << "enter username: ";
        getline(std::cin, username);
        std::cout << std::endl;
            if(user.userNameChecker(username)){
                std::cout << "sorry username does not exist" << std::endl;
            }
        else{
            if(user.userAdminChecker(username)){
                adminOptions = true;
            }
            int countdown = 2;
            for (size_t i = 0; i < 3; i++,countdown--)
            {
                std::cout << "enter password: ";
                getline(std::cin, password);

                if (user.passwordChecker(username,password)){
                    std::cout << "successfully logged in" << std::endl;
                    break;
                }
                else if(!user.passwordChecker(username,password)){
                    
                    std::cout << "write correct password please" << std::endl;
                    std::cout << countdown << " tries remaining" << std::endl;
                    if (i >= 2){
                    std::cout << "3 tries done. exiting..." << std::endl;
                    loginFail = true;
                    break;
                }
                }
            }
            break;
        }
    }
}
//_____admin_access->Login()____________________________
void BankInterface::adminAccess(){
    bool exit = false;
    enum AdminOptions{
        LOGOUT = 0,
        CHECK_LOGS,
        FAIL
    };
    int optionsInt;
        while (!exit)
        {
            adminAccessWelcomeStruct(optionsInt);
            switch (optionsInt)
            {
            case CHECK_LOGS:
                user.logger.LogsGetter();
                user.logger.LogsReceiver("admin checked logs");
                break;
            case LOGOUT:
                std::cout << "Logout..." << std::endl;
                user.logger.LogsReceiver("admin logged out");
                exit = true;
                break;
            case FAIL:
                continue;
            default:
                exit = true;
                break;
            }
        }            
}

void BankInterface::adminAccessWelcomeStruct(int &optionsInt){
    std::string option;
        std::cout << "WELCOME TO ADMIN ACCESS" << std::endl;
        std::cout << "Do you want to:" << std::endl;
        std::cout << "   Check Logs     (type 1)" << std::endl;
        std::cout << "   Logout         (type 0)" << std::endl;
            getline(std::cin,option);
            if(!sizeValidation(option)){
                std::cout << "please enter valid option" << std::endl;
                option[0] = '2';
            } else if(option[0] == ' '){
                std::cout << "please enter valid option" << std::endl;
                option[0] = '2';
            }else if(option[0] > '1' || option[0] < '0'){
                option[0] = '2';
                std::cout << "please enter option within given numbers" << std::endl;
            }
    optionsInt = stoi(option);
}
//______USer_Access->Login()________________________

void BankInterface::userAccess(std::string &username){
    enum userOptions{
        DEPOSIT = 1,
        WITHDRAW,
        CHECK_BALANCE,
        TRANSACTION_HISTORY,
        FAIL,
        LOGOUT = 0
    };
    int userdataindex = user.usernameFinderUsers(username);
    int userlogsindex = user.usernameFinderLogs(username);

    int optionsInt;
    bool exit = false;
    while (!exit)
    {
        userAccessWelcomeStruct(optionsInt);
        switch (optionsInt)
        {
        case DEPOSIT:
            user.logger.LogsReceiver(username + " is adding amount");
            DepositInterface(userdataindex,userlogsindex);
            break;
        case WITHDRAW:
            user.logger.LogsReceiver(username + " is taking amount out of the account");
            WithdrawInterface(userdataindex,userlogsindex);
            break;
        case CHECK_BALANCE:
            user.logger.LogsReceiver(username+ " Checked balance");
            user.getBalance(userdataindex);
            break;
        case TRANSACTION_HISTORY:
            user.logger.LogsReceiver(username + " Checked Transaction History");
            user.getTransactionHistory(userlogsindex);
            break;
        case LOGOUT:
            std::cout << "logging out" << std::endl;
            user.logger.LogsReceiver(username + " logged out");
            exit = true;
            break;
        case FAIL:
            continue;
        default:
            exit = true;
            break;
        }
    }
}

void BankInterface::userAccessWelcomeStruct(int &optionsInt){
    std::string option;
    std::cout << "WELCOME TO USER ACCESS" << std::endl;
    std::cout << "Do you want to:" << std::endl;
    std::cout << "   Deposit          (type 1)" << std::endl;
    std::cout << "   Withdraw         (type 2)" << std::endl;
    std::cout << "   Check Balance    (type 3)" << std::endl;
    std::cout << "Transaction History (type 4)" << std::endl;
    std::cout << "   Logout           (type 0)" << std::endl;
    getline(std::cin,option);
    if(!sizeValidation(option)){
        std::cout << "please enter valid option" << std::endl;
        option[0] = '5';
    } else if(option[0] == ' '){
        option[0] = '5';
        std::cout << "please enter valid option" << std::endl;
    } else if(option[0] > '4' || option[0] < '0'){
        option[0] = '5';
        std::cout << "please enter option within given numbers" << std::endl;
    }
    optionsInt = stoi(option);
}

void BankInterface::DepositInterface(const int &userIndex,const int &userLogIndex){
    bool checkFlag = true;
    std::string amount;
    do{
    std::cout << "please add the amount you want to deposit:" << std::endl;
    std::cout << "->";
    getline(std::cin,amount);
    if(!AmountValidation(amount)){
        std::cout << "please enter a valid number. no negative number" << std::endl;
    } else {
        user.deposit(stod(amount),userIndex,userLogIndex);
        user.logger.LogsReceiver("deposited: " + amount);
        checkFlag = false;
    }
    }while(checkFlag);
}

void BankInterface::WithdrawInterface(const int &userIndex,const int &userLogIndex){
    bool checkFlag = true;
    std::string amount;
    do{
    std::cout << "please add the amount you want to withdraw:" << std::endl;
    std::cout << "please put only the amount you want to withdraw no operator signs." << std::endl;
    std::cout << "->";
    getline(std::cin,amount);
    if(!AmountValidation(amount)){
        std::cout << "please enter a valid number." << std::endl;
    } else {
        user.withdrawal(stod(amount),userIndex,userLogIndex);
        user.logger.LogsReceiver("withdrawn: " + amount);
        checkFlag = false;
    }
    }while(checkFlag);
}

//______________Create Account Block_________________

void BankInterface::CreateAccount(){
    std::string username;
    std::string password;
    bool createOrNot = false;

    UserPasswordInputChecker(createOrNot,username,password);      
    if (createOrNot == true)
    {
        user.newUserCreation(username,password);
        std::cout << "user successfully created" << std::endl;
        user.logger.LogsReceiver(username + " created");
    }
}

void BankInterface::UserPasswordInputChecker(bool &validFlag,std::string &username_,std::string &password_){
    while (true){    
        std::cout << "enter username (max 20 characters only numbers and alphabets) " << std::endl;
        std::cout << "-> ";

        getline(std::cin , username_);

        if(InputValidation(username_)){

            if (user.userNameChecker(username_))
            {
                    std::cout << "enter password (max 20 characters only numbers and alphabets) " << std::endl;
                    std::cout << "-> ";
                    getline(std::cin , password_);
                    if (InputValidation(password_))
                    {
                            validFlag = true;
                            break;
                    }
                    else{
                        std::cout << "please enter password under 20 char with no special characters or blank spaces" << std::endl;
                    }
            }
            else{
                std::cout << "sorry Username already exists" << std::endl;
            }
        }
        else{
            std::cout << "please enter username under 20 char with no special characters or blank spaces" << std::endl;
        }
    }
}

bool BankInterface::InputValidation(std::string str){
    int counter = 0;
    for (char a: str)
    {
        if(!isalnum(a)){
            return false;
        }
        counter++;
        if (counter > 20)
        {
            return false;
        }
        if (a == ' ')
        {
            return false;
        }
    }
    return true;
}

    bool BankInterface::AmountValidation(std::string amount){
        int decimalCounter = 0;

        for(char ckr: amount){
            if((ckr > '9' || (ckr < '0')) && (ckr != '.'))
            {
                return false;
            }
            else if(ckr == ' '){
                return false;
            }
            else if (ckr == '.')
            {   
                ++decimalCounter;
                if(decimalCounter > 1){
                    return false;
                }
            }
        }
        return true;
    }

