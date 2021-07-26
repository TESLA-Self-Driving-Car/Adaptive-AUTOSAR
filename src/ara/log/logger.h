#ifndef LOGGER_H
#define LOGGER_H

#include "./log_stream.h"

namespace ara
{
    namespace log
    {
        class Logger
        {
        private:
            std::string mContextId;
            std::string mContextDescription;
            LogLevel mContextDefaultLogLevel;
            Logger();

        public:
            ~Logger() noexcept;
            ClientState RemoteClientState() const noexcept;
            template <typename T>
            Argument<T> Arg(
                T &&arg,
                const char *name = nullptr,
                const char *unit = nullptr) noexcept;
            LogStream LogFatal() const noexcept;
            LogStream LogError() const noexcept;
            LogStream LogWarn() const noexcept;
            LogStream LogInfo() const noexcept;
            LogStream LogDebug() const noexcept;
            LogStream LogVerbose() const noexcept;
            bool IsEnabled(LogLevel logLevel) const noexcept;
            LogStream WithLevel(LogLevel logLevel) const noexcept;
            void Log(const LogStream &logStream) const noexcept;

            static Logger CreateLogger(
                std::string ctxId,
                std::string ctxDescription,
                LogLevel ctxDefLogLevel) noexcept;
        };
    }
}

#endif