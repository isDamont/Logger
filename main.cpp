#include "Logger.h"

int main(){
    Logger::loggerOpen OpenFile;
    OpenFile.OpenLogFile("log.txt"); //Create the Log

    Logger::ProxyLogger WriteFile;
    WriteFile.WriteToLog("Logger TEST"); //Write to the Log

    Logger::ProxyLogger WriteFile2; //Singleton inside
    WriteFile2.WriteToLog("Logger TEST_2");

    Logger::loggerClose CloseFile; //Close the Log
    CloseFile.CloseLogFile();
//============================================================================

    std::string string_test;
    std::ifstream test("log.txt", std::ios::in);
    getline(test, string_test, '\f');
    std::cout<<string_test;
    std::cout<<"----"<<std::endl;
    if(string_test.find("Logger TEST") != std::string::npos){
        std::cout<<"test 1: OK !!!"<<std::endl;
    }else{
        std::cout<<"test 1: something wrong !!!"<<std::endl;
    }
    if(string_test.find("Logger TEST_2") != std::string::npos){
        std::cout<<"test 2: OK !!!"<<std::endl;
    }else{
        std::cout<<"test 2: something wrong !!!"<<std::endl;
    }

    return 0;
}
