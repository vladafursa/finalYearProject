#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include "stage.h"
#include "StdExtension.h"
using namespace std;

class Course
{
private:
    std::string name;
    std::vector<std::reference_wrapper<Stage>> stages;
    std::string startClassification;
    std::string type;
public:
    //constructors
    Course();
    Course(std::string providedName,
           const std::vector<std::reference_wrapper<Stage>>& providedStages,
           std::string providedStartClassification,
           std::string providedType);

    //getters
    std::string getName() const;
    const std::vector<std::reference_wrapper<Stage>>& getStages() const;
    std::string getStartClassification() const;
    std::string getType() const;

    //setters
    void setName(std::string providedName);
    void setStages(const std::vector<std::reference_wrapper<Stage>>& providedStages);
    void setStartClassification(std::string providedStartClassification);
    void setType( std::string providedType);
};

#endif // COURSE_H
