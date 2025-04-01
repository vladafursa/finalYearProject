#ifndef CODE_H
#define CODE_H
#include <string>
#include <iostream>

class Code
{
protected:
    std::string code;
    std::string description;

public:
    //constructor
    Code();
    Code(const std::string providedCode, std::string providedDescription);

    //getters
    std::string getCode() const;
    std::string getDescription();

    //setters
    void setCode(const std::string providedCode);
    void setDescription(const std::string& providedDescription);

    //debug display
    virtual void display() const;

    //destructor
    virtual ~Code() = default;
};

#endif // CODE_H
