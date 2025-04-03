#include "grades.h"

Grades::Grades()
{

}

double Grades::round(double gradePoint) const{
    //do not round integer variables
    if (std::floor(gradePoint) == gradePoint) {
        return gradePoint;
    } else {
         return std::round((gradePoint + 0.001) * 10.0) / 10.0;
    }
}

std::string Grades::assignGrade(double gradePoint) const{
    gradePoint = round(gradePoint);
    std::string gradeCode="";
    for (const auto& [code, range] : gradeRanges) {
        if (gradePoint >= range.first && gradePoint <= range.second) {
            gradeCode = code;
        }
    }
    return gradeCode;
}

bool Grades::isGreaterThanThreshold(std::string grade, std::string threshold){
    auto gradeIt = gradeRanges.find(grade);
    auto thresholdIt = gradeRanges.find(threshold);

    bool greater = false;
    if (gradeIt != gradeRanges.end() && thresholdIt != gradeRanges.end()) {
        if (gradeIt->second.first >= thresholdIt->second.first) {
            greater = true;
        }
    }

    return greater;
}
