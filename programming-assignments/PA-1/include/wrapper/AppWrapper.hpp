#ifndef APP_WRAPPER_HPP
#define APP_WRAPPER_HPP

#include "./../imports.hpp"

class AppWrapper {
private:
    AppWrapper();
    
    bool ParseArgs(const int argumentCount, const char* const* argumentVector, string& sequenceFilePath, string& parameterConfigFilePath, int& alignmentFlag);
public:
    static AppWrapper& GetInstance();

    void Run(const int argumentCount, const char* const* argumentVector);

    AppWrapper(const AppWrapper&) = delete;

    AppWrapper& operator=(const AppWrapper&) = delete;
};

#endif