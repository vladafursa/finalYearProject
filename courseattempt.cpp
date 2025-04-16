#include "courseattempt.h"

CourseAttempt::CourseAttempt(std::string providedStudentNumber,
            const Course& providedCourse,
            std::vector<std::shared_ptr<StageAttempt>>& providedAttempts):course(providedCourse){
    studentNumber = providedStudentNumber;
    attempts = providedAttempts;
}

std::string CourseAttempt::getStudentNumber() const{
    return studentNumber;
}

const Course& CourseAttempt::getCourse() const{
    return course;
}

const std::vector<std::shared_ptr<StageAttempt>>& CourseAttempt::getAttempts() const{
    return attempts;
}

double CourseAttempt::getWeightedAwarsClassification() const{
    return weightedAwarsClassification;
}
const AwardCode* CourseAttempt::getFinalCode() const{
    return finalCode;
}

const std::vector<AwardCode*>& CourseAttempt::getPossibleCodes() const{
    return posibleCodes;
}

std::string CourseAttempt::getGrade(){
    return grade;
}

//setters
void CourseAttempt::setStudentNumber(std::string providedStudentNumber){
    studentNumber = providedStudentNumber;
}

void CourseAttempt::setAtempts(std::vector<std::shared_ptr<StageAttempt>>& providedAttempts){
    attempts=providedAttempts;
}

void CourseAttempt::setWeightedAwarsClassification(double providedWeightedAwarsClassification){
    weightedAwarsClassification = providedWeightedAwarsClassification;
}

void CourseAttempt::setFinalCode(const AwardCode* providedProgressionCode){
    finalCode=providedProgressionCode;
}

void CourseAttempt::setPossibleCodes(std::vector<AwardCode*>& providedPosibleCodes){
    posibleCodes=providedPosibleCodes;
}
void CourseAttempt::setGrade(std::string providedGrade){
    grade = providedGrade;
}


void CourseAttempt::calculateProgression(){
    for(const auto& attempt : attempts){
        if(attempt->getStage().getLevel()==4 && attempt->getCreditsEarned()<120){
            if(attempt->getStage().getLevel()==5){
                if(classification == "Bachelor"){
                    std::vector<const ProgressionCode*> thoughtCodes;
                    thoughtCodes.push_back(&ProgressionCodes::FC);
                    thoughtCodes.push_back(&ProgressionCodes::FD);
                    thoughtCodes.push_back(&ProgressionCodes::DF);
                    thoughtCodes.push_back(&ProgressionCodes::RE);
                    thoughtCodes.push_back(&ProgressionCodes::RP);
                    thoughtCodes.push_back(&ProgressionCodes::PG);
                    attempt->setPossibleCodes(thoughtCodes);//mayb third attempt for level 4 assessment
                }
            }
        }
    }
}

void CourseAttempt::generateCode(){
    grade = gradeSystem.assignGrade(calculateAggregate());
    for(const auto& attempt : attempts){
        if (attempt->getStage().getLevel()==6){
            if(attempt->getCreditsEarned()==360){
                if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                    setFinalCode(&AwardCodes::C10);
                }
                else if (gradeSystem.isGreaterThanThreshold(grade, "21LOW")){
                    setFinalCode(&AwardCodes::C21);
                }
                else if (gradeSystem.isGreaterThanThreshold(grade, "22LOW")){
                    setFinalCode(&AwardCodes::C22);
                }
                else {
                    setFinalCode(&AwardCodes::C30);
                }
                attempt->setFinalCode(&ProgressionCodes::PA);
            }
            else if (attempt->getCreditsEarned()>=300 && attempt->getCreditsEarned()<360){
                if (classification == "ordinary"){
                    if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                        setFinalCode(&AwardCodes::DD);
                    }
                    else{
                        setFinalCode(&AwardCodes::DN);
                    }
                    attempt->setFinalCode(&ProgressionCodes::PA);
                }
                else{
                    attempt->setFinalCode(&ProgressionCodes::RD);
                }
            }
            else if (attempt->getCreditsEarned()>=240 && attempt->getCreditsEarned()<300){
                if(classification == "DipHE"){
                    if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                        setFinalCode(&AwardCodes::ID);
                    }
                    else{
                        setFinalCode(&AwardCodes::A2);
                    }
                    attempt->setFinalCode(&ProgressionCodes::PA);
                }else{
                    attempt->setFinalCode(&ProgressionCodes::RN);
                }
            }
            else{
                if (attempt->getCreditsEarned()>=120 && attempt->getCreditsEarned()<240)
                    if(classification=="CertHE"){
                      if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                          setFinalCode(&AwardCodes::CD);
                        }
                        else{
                        setFinalCode(&AwardCodes::A1);
                        }
                        attempt->setFinalCode(&ProgressionCodes::PA);
                    }
                    else{
                        attempt->setFinalCode(&ProgressionCodes::WD);
                }
            }
        }
    }
}

double CourseAttempt::calculateAggregate(){
    double aggregate = 0;
    for(const auto& attempt : attempts){
        int gradePoints = std::ceil(attempt->getAggregate());
        if (attempt->getStage().getLevel()==6){
            aggregate+=0.8*gradePoints;
        }
        if (attempt->getStage().getLevel()==5){
              aggregate+=0.2*gradePoints;
        }
        aggregate = gradeSystem.round(aggregate);
        return aggregate;
    }
}


