#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <time.h>
//#undef NDEBUG                  // uncomment to enable asserts
namespace LOGGER
{
        void Logger::WriteLog(LogLevel logLevel, std::string message)
        {
            std::ofstream logFile("Logfile.txt", std::ios::app);
            time_t currentTime;
            struct tm* timeInfo;
            char buffer[30];
            std::time(&currentTime);
            timeInfo = localtime(&currentTime);
            strftime(buffer, 30, "%H:%M:%S: ", timeInfo);
            logFile << buffer;
            std::cout << buffer;

            if (logLevel == LogLevel::Info)
            {
                logFile << message << "\n";
            }
            if (logLevel == LogLevel::Debug)
            {
                logFile << message << "\n";
                std::cout << message << "\n";
            }
            if (logLevel == LogLevel::Warning)
            {
                logFile << "Warning: " << message << "\n";
                std::cout << "Warning: " << message << "\n";
            }
            if (logLevel == LogLevel::Error)
            {
                logFile << "Error: " << message << "\n";
                logFile.close();
                std::cerr << "Error: " << message << "\n";
                assert(0);
            }
            logFile.close();
        }

        void Logger::ShowLog()
        {
            std::ifstream logFile("Logfile.txt");
            if (logFile.is_open())
            {
                std::string tmp;
                while (!logFile.eof())
                {
                    std::getline(logFile, tmp);
                    std::cout << tmp << std::endl;
                }
                logFile.close();
            }
            else
                std::cout << "Log file doesn't exist\n";
           
        }
        void Logger::GetTime(std::string message, bool writeToConsole, int unit)
        {
            // writeToConsole = 0 - won't write in console, 1 - will write; unit = 1 - seconds, 0 - ms
            auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - time).count();
            ResetTimer();
            if (unit == 1)
                timeDiff = timeDiff / 1000;
            std::string tmp = message + "\n" + std::to_string(timeDiff);
            if (unit == 1)
                tmp += " s passed.\n";
            else
                tmp += " ms passed.\n";
            LogLevel logLevel = LogLevel::Info;
            if (writeToConsole)
                logLevel = LogLevel::Debug;
            WriteLog(logLevel, tmp);
        }
}

int main()
{
    unsigned long long sum[3] = { 0, 0 };
    LOGGER::Logger* logger = LOGGER::Logger::GetInstance();
    logger->ClearLogFile();
    logger->WriteLog(LOGGER::LogLevel::Info, "LOGGER started work");
    logger->WriteLog(LOGGER::LogLevel::Warning, "Show Warning");
  //  logger->WriteLog(LOGGER::LogLevel::Error, "Show Error");
 //   logger->WriteLog(LOGGER::LogLevel::Warning, "Show Warning");
    LOGGER::Logger::GetInstance()->ResetTimer();
    for (long i = 0; i < LONG_MAX; i++)
    {
        sum[0] += i;
    }
    LOGGER::Logger::GetInstance()->GetTime("Vremya summirovaniya do LONG_MAX", true);
    std::cout << "Result is " << sum[0] << std::endl;
    for (int i = 0; i < INT32_MAX; i++)
    {
        sum[1] += i;
    }
    LOGGER::Logger::GetInstance()->GetTime("Vremya summirovaniya do INT32_MAX", true);
    std::cout << "Result is " << sum[1] << std::endl;
 //   std::cout << "Some code\n";
    std::cout << "\n\n\nShow log file:\n";
    LOGGER::Logger::GetInstance()->ShowLog();
    system("pause");
    return 0;
}
