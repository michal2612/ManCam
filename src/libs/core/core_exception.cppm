module;

#include <format>
#include <sstream>
#include <source_location>

export module core_exception;

#define EXCEPTION_FORMATTING "{} [{}:{} in {}]"

namespace core_exception
{
    export class coreException : public std::runtime_error
    {
    public:
        explicit coreException(const std::string &exceptionMessage,
                               const std::source_location location = std::source_location::current())
            : runtime_error(formatMessage(exceptionMessage, location))
        {
        }

    private:
        static std::string formatMessage(std::string_view message, const std::source_location &location)
        {
            return std::format(EXCEPTION_FORMATTING,
                               message, location.file_name(), location.line(), location.function_name());
        }
    };
}

