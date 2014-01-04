#include <exception>
#include <string>

class Exception :
    public std::exception
{
public:
    Exception( const char* message ) throw() : m_Message(message) {}
    Exception( const std::string& message ) throw() : m_Message(message) {}
    ~Exception() throw() {}
    const char* what() const throw() { return m_Message.c_str(); }
private:
    std::string m_Message;
};
