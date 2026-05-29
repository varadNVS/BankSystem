#include "Logs.h"

#include <iomanip>
#include <sstream>
#include <ctime>
    
std::string Logs::getCurrentDateTime()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%d-%m-%Y_%H-%M-%S");

    return oss.str();
}


void Logs::LogsReceiver(std::string logstr){
    Logfile.push_back(getCurrentDateTime() +" : " + logstr);
}

void Logs::LogsGetter(){
    for (size_t i = 0; i < Logfile.size(); i++)
    {
        std::cout << Logfile[i] << std::endl;
    }
}

bool Logs::fileExistsCheck(){
    std::ifstream file("Logs.txt");
    if (file)
    {
        file.close();
        return true;
    }
    file.close();
    return false; 
}

bool Logs::fileEmptyCheck(){
    std::ifstream file("Logs.txt",std::ios::ate);
    if(file.tellg() == 0){
        file.close();
        return true;
    }
    file.close();
    return false;   
}

Logs::~Logs(){
    while (true)
    {
        if (fileExistsCheck())
        {
            fileLog.open("Logs.txt",std::ios::app);
            for(size_t i = 0; i < Logfile.size(); i++)
            {
                fileLog << Logfile[i] << std::endl;
            }
            fileLog << std::endl;
            fileLog << sessionEnd + getCurrentDateTime() + sessionEnd << std::endl << std::endl;
            break;
        }
        else {
            fileLog.open("Logs.txt",std::ios::out|std::ios::app);
            for(size_t i = 0; i < Logfile.size(); i++)
            {
                fileLog << Logfile[i] << std::endl;
            }
            fileLog << std::endl;
            fileLog << sessionEnd + getCurrentDateTime() + sessionEnd << std::endl << std::endl;
            break;
        }
    }
    fileLog.close();
}
