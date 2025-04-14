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
    std::string code;
    std::string name;
    std::vector<std::shared_ptr<Stage>> stages;
    std::string startClassification;
    std::string type;
public:
    //constructors
    Course();
    Course(std::string providedCode, std::string providedName,
           const std::vector<std::shared_ptr<Stage>>& providedStages,
           std::string providedStartClassification,
           std::string providedType);

    //getters
    std::string getCode() const{
        return code;
    }
    std::string getName() const;
    const std::vector<std::shared_ptr<Stage>>& getStages() const;
    std::string getStartClassification() const;
    std::string getType() const;

    //setters
    void setCode(std::string providedCode){
        code = providedCode;
    }
    void setName(std::string providedName);
    void setStages(const std::vector<std::shared_ptr<Stage>>& providedStages);
    void setStartClassification(std::string providedStartClassification);
    void setType( std::string providedType);
};

#endif // COURSE_H
