#include "Logger.h"


using namespace Logger;

FileLogger* FileLogger::FileLogger_ = nullptr;

FileLogger *FileLogger::getInstance(const std::string &FN) {
    if(FileLogger_ == nullptr){
FileLogger_ = new FileLogger(FN);
    }
    return FileLogger_;
}

std::ofstream &FileLogger::GetLogout() {
    if(FileLogger_ != nullptr){
    return FileLogger_->logOut;
    }else{
        throw std::invalid_argument("LogFile is not open !!!");
    }
}

void __fastcall loggerOpen::OpenLogFile(const std::string &FN) {
   FileLogger::getInstance(FN);
}

void loggerClose::CloseLogFile(){
        if (FileLogger::GetLogout().is_open()){
            FileLogger::GetLogout().close();
        }
}

std::string loggerWrite::GetCurDateTime() {
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char buf[64] = { 0 };
    ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
    return std::string(buf);
}


void __fastcall loggerWrite::WriteToLog(const std::string &str) {
    if (FileLogger::GetLogout().is_open())
    {
        FileLogger::GetLogout() << GetCurDateTime() << " - " << str << std::endl;
    }
}


void __fastcall loggerWrite::WriteToLog(const std::string &str, int n) {
    if (FileLogger::GetLogout().is_open())
    {
        FileLogger::GetLogout() << GetCurDateTime() << " - " << str << n << std::endl;
    }
}

void __fastcall loggerWrite::WriteToLog(const std::string &str, double d) {
    if (FileLogger::GetLogout().is_open())
    {
        FileLogger::GetLogout() << GetCurDateTime() << " - " << str << d << std::endl;
    }
}

void ProxyLogger::addNumber() {
    static int num = 0;
    if (FileLogger::GetLogout().is_open())
    {
        FileLogger::GetLogout() << ++num << ") ";
    }
}

void __fastcall ProxyLogger::WriteToLog(const std::string &str) {
    addNumber();
    Write->WriteToLog(str);
}

void __fastcall ProxyLogger::WriteToLog(const std::string &str, int n) {
    addNumber();
    Write->WriteToLog(str, n);
}

void __fastcall ProxyLogger::WriteToLog(const std::string &str, double d) {
    addNumber();
    Write->WriteToLog(str, d);
}
