#ifndef MODULE_H
#define MODULE_H
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include "assessment.h"
#include "StdExtension.h"

//creating type of map to not copy it all over
using AssessmentWeightsMap = std::unordered_map<std::reference_wrapper<const Assessment>, int,
                                                std::hash<std::reference_wrapper< const Assessment>>,
                                                std::ReferenceWrapperEqual<const Assessment>>;

class Module
{
private:
    std::string code;
    std::string name;
    std::string type;
    int credits;
    AssessmentWeightsMap assessmentsWithWeights;

public:
    Module(std::string providedCode,
           std::string providedName,
           std::string providedType,
           int providedCredits,
           AssessmentWeightsMap providedAssessmentWeights);

    //getters
    std::string getCode() const;
    std::string getName() const;
    std::string getType() const;
    int getCredits() const;
    const AssessmentWeightsMap & getAssessmentsWithWeights() const;

    // setters
    void setCode(std::string providedCode);
    void setName(std::string providedName);
    void setType(std::string providedType);
    void setCredits(int providedCredits);
    void setAssessmentWeights(AssessmentWeightsMap& providedAssessmentWeights);
    void addAssessment(Assessment& assessment, int weight);
};

#endif // MODULE_H
