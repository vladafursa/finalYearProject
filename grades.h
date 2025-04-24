#ifndef GRADES_H
#define GRADES_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

class Grades
{
private:
    std::map<std::string, std::pair<double, double>> gradeRanges = {
        {"1EXC", {15.5, 16.0}},
        {"1HIGH", {14.5, 15.4}},
        {"1MID", {13.5, 14.4}},
        {"1LOW", {12.5, 13.4}},
        {"21HIGH", {11.5, 12.4}},
        {"21MID", {10.5, 11.4}},
        {"21LOW", {9.5, 10.4}},
        {"22HIGH", {8.5, 9.4}},
        {"22MID", {7.5, 8.4}},
        {"22LOW", {6.5, 7.4}},
        {"3HIGH", {5.5, 6.4}},
        {"3MID", {4.5, 5.4}},
        {"3LOW", {3.5, 4.4}},
        {"FMARG", {2.5, 3.4}},
        {"FMID", {1.5, 2.4}},
        {"FLOW", {0.5, 1.4}},
        {"ZERO", {0.0, 0.4}}
    };

public:
    Grades();
    double round(double gradePoint) const;//round to decimals
    std::string assignGrade(double gradePoint) const;//assign grade's code according to point
    bool isGreaterThanThreshold(std::string grade, std::string threshold);//check if it meets threshold requirement
    double customRound(double value) {
        double fractionalPart = value - std::floor(value);
        if (fractionalPart == 0.5) {
            return std::ceil(value);
        }
        return std::round(value);
    }
};

#endif // GRADES_H
