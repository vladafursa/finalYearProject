#ifndef ASSESSMENT_H
#define ASSESSMENT_H
#include <iostream>
#include <string>

class Assessment
{
private:
    std::string id;
    std::string type;
    std::string name;
public:
    //constructors
    Assessment();
    Assessment(std::string assessmentID, std::string assessmentType, std::string assessmentName);

    //setters
    void setID(std::string assessmentID);
    void setType(std::string assessmentType);
    void setName(std::string assessmentName);

    //getters
    std::string getId() const;
    std::string getType() const;
    std::string getName() const;
    bool operator==(const Assessment& other) const {
        return id == other.id && name == other.name && type == other.type;
    }
};

#endif // ASSESSMENT_H
