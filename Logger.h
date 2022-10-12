#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>


namespace Logger{
class FileLogger{
private:
    std::ofstream logOut;
   static FileLogger* FileLogger_;
   explicit FileLogger(const std::string& FN) {logOut.open(FN, std::ios_base::out);}
public:
    static std::ofstream& GetLogout();
    static FileLogger* getInstance(const std::string& FN);
    FileLogger(FileLogger& obj) = delete;
    void operator=(FileLogger&) = delete;

};

class IloggerOpen{
public:
    virtual void __fastcall OpenLogFile(const std::string& FN) = 0;
};

class IloggerClose{
public:
    virtual void CloseLogFile() = 0;
    };

class IloggerWrite{
public:
   virtual void __fastcall WriteToLog(const std::string& str) = 0;
   virtual void __fastcall WriteToLog(const std::string& str, int n) = 0;
   virtual void __fastcall WriteToLog(const std::string& str, double d) = 0;
    };

    class loggerOpen : public IloggerOpen{
public:
        void __fastcall OpenLogFile(const std::string& FN) override;
};
    class loggerClose : public IloggerClose{
    public:
        void CloseLogFile() override;
    };

    class loggerWrite :  public IloggerWrite{
    private:
        static std::string GetCurDateTime();
    public:
        loggerWrite() = default;
        void __fastcall WriteToLog(const std::string& str) override;
        void __fastcall WriteToLog(const std::string& str, int n) override;
        void __fastcall WriteToLog(const std::string& str, double d) override;
    };

    class ProxyLogger : IloggerWrite{
    private:
        loggerWrite* Write;
        static void addNumber();

    public:
        ProxyLogger() : Write(new loggerWrite){}
        void __fastcall WriteToLog(const std::string& str) override;
        void __fastcall WriteToLog(const std::string& str, int n) override;
        void __fastcall WriteToLog(const std::string& str, double d) override;
    };


}