#include <string>

#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception{
public:
    Exception();
    Exception(std::string message);
    const std::string getMessage() const;
private:
    std::string message;
};

#endif
