#include <iostream>
#include "assessment.h"
#include "assessmentattempt.h"
#include "module.h"
#include "moduleattempt.h"
#include "misconduct.h"
#include "stage.h"
#include "stageattempt.h"
#include "examboard.h"
#include "studentrecord.h"
using namespace std;
int main(){
    examBoard exboard;


    std::cout<<"Time for vector!!!"<<std::endl;

    std::vector<StudentRecord> studentsRecords = exboard.loadStudentRecords();
        for(const auto& sr: studentsRecords){
            sr.prepareData();
        }


    for(const auto& sr: studentsRecords){
        std::cout<<sr.getStudent().getName()<<std::endl;
        std::cout<<sr.getCourseAttempt()->getCourse().getName();




        for (const auto& stageAttemptPtr : sr.getCourseAttempt()->getAttempts()) {
            const Stage& stage = stageAttemptPtr->getStage();
            std::cout << stage.getId()<<std::endl;
            for (const auto& module : stage.getModules()) {
                std::cout << module->getCode() << "        ";
            }
            std::cout << std::endl;

            for (const auto& moduleAttemptPtr : stageAttemptPtr->getAttempts()) {
                const std::shared_ptr<ModuleAttempt> moduleAttempt = moduleAttemptPtr;
                  //std::cout <<moduleAttempt->getModule().getCode()<< "   "<<moduleAttempt->getYear()<< std::endl;

                const Module& module = moduleAttempt->getModule();

                std::cout << "Module Code: " << module.getCode() << std::endl;
/*
                const AssessmentWeightsMap& weights = module.getAssessmentsWithWeights();


                for (const auto& pair : weights) {
                    const Assessment& assessment = pair.first;
                    int weight = pair.second;

                    std::cout << "Assessment ID: " << assessment.getId()
                              << ", Name: " << assessment.getName()
                              << ", Type: " << assessment.getType()
                              << ", Weight: " << weight << std::endl;
                }

*/

                std::cout <<moduleAttempt->getAggregate()<< "    ";
                if(moduleAttempt->getFinalCode()!=nullptr){
                    std::cout<<moduleAttempt->getFinalCode()->getCode()<<std::endl;
                }
                if(moduleAttempt->getPossibleCodes().size()!=0){
                    for(const auto& m : moduleAttempt->getPossibleCodes()){
                        std::cout<<m->getCode()<<" ";
                    }
                }
                std::cout << std::endl;

                for(const auto& assessmentAttempt : moduleAttempt->getFinalattempts()){
                    std::cout<<assessmentAttempt->getAssessment().getId()<< " "<<assessmentAttempt->getGradePoints()<<"  ";
                    if(assessmentAttempt->getCode()!=nullptr){
                        std::cout<< assessmentAttempt->getCode()->getCode()<< "  ";
                    }
                    if(assessmentAttempt->getFinalCode()!=nullptr){
                        std::cout<< assessmentAttempt->getFinalCode()->getCode()<< "  ";
                    }
                    if(assessmentAttempt->getPossibleCodes().size()!=0){
                        for(const auto& a : assessmentAttempt->getPossibleCodes()){
                            std::cout<<a->getCode()<<" ";
                        }
                    }

                    std::cout << std::endl;
                }


                std::cout << std::endl;


            }
        }

        std::cout << std::endl;

    }


}

/*
    std::vector<Student> students = exboard.retrieveStudents();
    for (const auto& student : students) {
        std::cout << "Student Number: " << student.getStudentNumber() << std::endl;


        CourseAttempt* courseAttempt = exboard.retrieveStudentCourseAttept(student.getStudentNumber());


        if (courseAttempt != nullptr) {
            std::cout << "Course Name: " << courseAttempt->getCourse().getName() << std::endl;


            const std::vector<std::shared_ptr<StageAttempt>>& stageAttempts = courseAttempt->getAttempts();


            for (const auto& stageAttemptPtr : stageAttempts) {
                const Stage& stage = stageAttemptPtr->getStage();
                for (const auto& module : stage.getModules()) {
                    std::cout << module->getCode() << "        ";
                }
                std::cout << std::endl;


                for (const auto& moduleAttemptPtr : stageAttemptPtr->getAttempts()) {
                    std::shared_ptr<ModuleAttempt> moduleAttempt = moduleAttemptPtr;
                    std::cout <<moduleAttempt->getModule().getCode()<< "   "<<moduleAttempt->getYear()<< std::endl;
                    moduleAttempt->calculateAggregate();
                    std::cout <<moduleAttempt->getAggregate()<< std::endl;

                    for(const auto& assessmentAttempt : moduleAttempt->getAttempts()){
                        std::cout<<assessmentAttempt->getAssessment().getId()<< " "<<assessmentAttempt->getGradePoints()<<"  ";
                        if(assessmentAttempt->getCode()!=nullptr){
                            std::cout<< assessmentAttempt->getCode()->getCode()<< "  ";
                        }
                        if(assessmentAttempt->getGinalCode()!=nullptr){
                            std::cout<< assessmentAttempt->getGinalCode()->getCode()<< "  ";
                        }
                        assessmentAttempt->populatePossibleDecisions();
                        if(assessmentAttempt->getPossibleCodes().size()!=0){
                            for(const auto& a : assessmentAttempt->getPossibleCodes()){
                                std::cout<<a->getCode()<<" ";
                            }
                        }

                        std::cout << std::endl;
                    }
                std::cout << std::endl;
                }
            }

            std::cout << std::endl;
        }

    }


    Student student1("N111113", "Ann", "SE/3",true,"2024-09-01",false,false);
    CourseAttempt* courseAttempt = exboard.retrieveStudentCourseAttept(student1.getStudentNumber());
    StudentRecord sr1(student1, courseAttempt);
    std::cout<<sr1.getStudent().getName()<<std::endl;
    std::cout<<sr1.getCourseAttempt()->getCourse().getName();
    const std::vector<std::shared_ptr<StageAttempt>>& stageAttempts =sr1.getCourseAttempt()->getAttempts();


    for (const auto& stageAttemptPtr : stageAttempts) {
        const Stage& stage = stageAttemptPtr->getStage();
        for (const auto& module : stage.getModules()) {
            std::cout << module->getCode() << "        ";
        }
        std::cout << std::endl;


        for (const auto& moduleAttemptPtr : stageAttemptPtr->getAttempts()) {
            std::shared_ptr<ModuleAttempt> moduleAttempt = moduleAttemptPtr;
         //   std::cout <<moduleAttempt->getModule().getCode()<< "   "<<moduleAttempt->getYear()<< std::endl;

                const Module& module = moduleAttempt->getModule();

                std::cout << "Module Code: " << module.getCode() << std::endl;

                const AssessmentWeightsMap& weights = module.getAssessmentsWithWeights();


                for (const auto& pair : weights) {
                    const Assessment& assessment = pair.first;
                    int weight = pair.second;

                    std::cout << "Assessment ID: " << assessment.getId()
                              << ", Name: " << assessment.getName()
                              << ", Type: " << assessment.getType()
                              << ", Weight: " << weight << std::endl;
                }



            moduleAttempt->calculateAggregate();
            std::cout <<moduleAttempt->getAggregate()<< std::endl;

            for(const auto& assessmentAttempt : moduleAttempt->getAttempts()){
                std::cout<<assessmentAttempt->getAssessment().getId()<< " "<<assessmentAttempt->getGradePoints()<<"  ";
                if(assessmentAttempt->getCode()!=nullptr){
                    std::cout<< assessmentAttempt->getCode()->getCode()<< "  ";
                }
                if(assessmentAttempt->getGinalCode()!=nullptr){
                    std::cout<< assessmentAttempt->getGinalCode()->getCode()<< "  ";
                }
                assessmentAttempt->populatePossibleDecisions();
                if(assessmentAttempt->getPossibleCodes().size()!=0){
                    for(const auto& a : assessmentAttempt->getPossibleCodes()){
                        std::cout<<a->getCode()<<" ";
                    }
                }

                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
*/







