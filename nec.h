#ifndef NEC_H
#define NEC_H
#include <string>
#include <iostream>

class NEC
{
private:
    std::string referenceNumber;
    std::string studentNumber;
    bool upheld;
    std::string type;
public:
    NEC();
    NEC(std::string providedReferenceNumber, std::string providedStudentNumber, bool providedUpheld, std::string providedType);
    // getters
    std::string getReferenceNumber() const;
    std::string getStudentNumber() const;
    bool getUphend() const;
    std::string getType() const;

    // setters
    void setReferenceNumber(std::string providedReferenceNumber);
    void setStudentNumber(std::string providedStudentNumber);
    void setUphend(bool providedUphed);
    void setType(std::string providedType);
};

#endif // NEC_H
