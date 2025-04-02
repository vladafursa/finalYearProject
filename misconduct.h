#ifndef MISCONDUCT_H
#define MISCONDUCT_H

#include <string>
#include <iostream>


class Misconduct
{
private:
    std::string caseID;
    std::string studentNumber;
    std::string type;
    std::string outcome;
public:
    //constructors
    Misconduct();
    Misconduct(std::string providedCaseID, std::string providedStudentNumber, std::string providedType, std::string providedOutcome);

    //getters
    std::string getCaseID() const;
    std::string getStudentNumber() const;
    std::string getType() const;
    std::string getOutcome() const;

    //setters
    void setCaseID(std::string providedCaseID);
    void setStudentNumber( std::string providedStudentNumber);
    void setType(std::string providedType);
    void setOutcome(std::string providedOutcome);
};

#endif // MISCONDUCT_H
