#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <chrono>
#include <ctime>
//#undef NDEBUG                  // uncomment to enable asserts in release build

namespace LOGGER
{
    enum class LogLevel
    {
        Info,
        Debug,
        Warning,
        Error
    };

    class Logger {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> time;
        Logger()
        {
            time = std::chrono::high_resolution_clock::now();
            std::ofstream logFile("Logfile.txt", std::ios::app);
            time_t currentTime;
            struct tm* timeInfo;
            char buffer[30];
            std::time(&currentTime);
            timeInfo = localtime(&currentTime);
            strftime(buffer, 30, "%d.%m.%Y %H:%M:%S: ", timeInfo);
            //   for (int i = 0; i < 60; i++)
            //       logFile << "_";
            //   logFile << "\n\n\n" << buffer << "New launch\n";
            logFile.close();
            //   std::cout << buffer << "New launch\n";
        }
        static Logger* logger_;
    public:
        void operator=(const Logger l) = delete;
        static Logger* GetInstance();
        void WriteLog(LogLevel logLevel, std::string message);
        void ShowLog();
        void ResetTimer() { time = std::chrono::high_resolution_clock::now(); }
        void GetTime(std::string message = "", bool writeToConsole = 0, int unit = 0);
        void ClearLogFile()
        {
            std::ofstream logFile("Logfile.txt");
            logFile.close();
        }
    };
    Logger* Logger::logger_ = nullptr;
    Logger* Logger::GetInstance()
    {
        if (logger_ == nullptr)
            logger_ = new Logger();
        return logger_;
    }
}
