#include "Exception.h"

Exception::Exception()
{
    message = "Exception occurred!";            //generic message
}

Exception::Exception(std::string message)   //this will be used when creating exceptions 
{
    this->message = message;
}

const std::string Exception::getMessage() const             //returns the message 
{
    return message;
}

