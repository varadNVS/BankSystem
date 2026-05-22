#ifndef LOGS_H
#define LOGS_H

#include <iostream>
#include <vector>
#include <fstream>

class Logs
{
private:
    std::fstream fileLog;
    std::vector<std::string> Logfile;
    std::string sessionEnd = "_________  " + getCurrentDateTime() + "  ____________________";

    bool fileEmptyCheck();
    bool fileExistsCheck();
    
public:
    std::string getCurrentDateTime();
    
    void LogsReceiver(std::string logstr);
    void LogsGetter();
    ~Logs();
};

#endif