#include <iostream>
#include "assessment.h"
#include "assessmentattempt.h"
#include "module.h"
#include "moduleattempt.h"
#include "misconduct.h"
#include "stage.h"
#include "stageattempt.h"
#include "examboard.h"

int main(){
    examBoard exboard;
    exboard.retrieveAssessments();
    exboard.retrieveModules();
    exboard.retrieveStages();
    exboard.retrieveCourses();



    std::vector<Student> students = exboard.retrieveStudents();
    for (const auto& student : students) {
        std::cout << "Student Number: " << student.getStudentNumber() << std::endl;

        // Retrieve CourseAttempt for the student
        CourseAttempt* courseAttempt = exboard.retrieveStudentCourseAttept(student.getStudentNumber());

        // Check if the courseAttempt is valid
        if (courseAttempt != nullptr) {
            std::cout << "Course Name: " << courseAttempt->getCourse().getName() << std::endl;

            // Retrieve the StageAttempts for the student
            const std::vector<std::shared_ptr<StageAttempt>>& stageAttempts = courseAttempt->getAttempts();


            for (const auto& stageAttempt : stageAttempts) {
                std::cout << "Stage ID: " << stageAttempt->getStage().getId() << std::endl;
                for (const auto& module : stageAttempt->getStage().getModules()) {
                    std::cout << module->getCode() << "        ";
                }

                for (const auto& moduleAttemptPtr : stageAttempt->getAttempts()) {
                    std::shared_ptr<ModuleAttempt> moduleAttempt = moduleAttemptPtr;
                    const Module& module = moduleAttempt->getModule();

                    std::cout << "Module Code: " << module.getCode() << std::endl;

                    const AssessmentWeightsMap& weights = module.getAssessmentsWithWeights();
                    std::cout << "Weights size: " << weights.size() << std::endl;

                    for (const auto& pair : weights) {
                        const Assessment& assessment = pair.first;
                        int weight = pair.second;

                        std::cout << "Assessment ID: " << assessment.getId()
                                  << ", Name: " << assessment.getName()
                                  << ", Type: " << assessment.getType()
                                  << ", Weight: " << weight << std::endl;
                    }
                }

            }

            std::cout << std::endl;
        }
    }

}

/*

            // Print module codes in the stage
            for (const auto& module : stageAttempt->getStage().getModules()) {
                std::cout << module->getCode() << "        ";
            }
            std::cout << std::endl;



            for (const auto& moduleAttemptPtr : stageAttempt->getAttempts()) {
                std::shared_ptr<ModuleAttempt> moduleAttempt = moduleAttemptPtr;
                const Module& module = moduleAttempt->getModule();

                std::cout << "Module Code: " << module.getCode() << std::endl;

                const AssessmentWeightsMap& weights = module.getAssessmentsWithWeights();
                std::cout << "Weights size: " << weights.size() << std::endl;

                for (const auto& pair : weights) {
                    const Assessment& assessment = pair.first;
                    int weight = pair.second;

                    std::cout << "Assessment ID: " << assessment.getId()
                              << ", Name: " << assessment.getName()
                              << ", Type: " << assessment.getType()
                              << ", Weight: " << weight << std::endl;
                }
            }


        }
*/




