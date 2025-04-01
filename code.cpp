#include "code.h"

//constructors
Code::Code()
{

}

Code::Code(const std::string providedCode, std::string providedDescription){
    code=providedCode;
    description=providedDescription;
}

//getters
std::string Code::getCode() const {
    return code;
}

std::string Code::getDescription() const {
    return description;
}

// Setters
void Code::setCode(const std::string providedCode) {
    code=providedCode;
}

void Code::setDescription(const std::string providedDescription) {
    description = providedDescription;
}

// debugging
virtual void Code::display() const {
    std::cout << "code: " << code << ", description: " << description << std::endl;
}
