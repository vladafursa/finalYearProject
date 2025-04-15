#include "examboard.h"

examBoard::examBoard()
{

}

std::vector<Assessment> examBoard::retrieveAssessments() {
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM assessment");

            assessments.reserve(result.size());

            for (const auto& row : result) {
                std::string id = row["id"].c_str();
                std::string type = row["type"].c_str();
                std::string name = row["name"].c_str();

                assessments.emplace_back(id, type, name);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return assessments;
}

std::vector<NEC> examBoard::retrieveNec(){
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM nec");

            modules.reserve(result.size());

            for (const auto& row : result) {
                std::string referenceNumber = row["referenceNumber"].c_str();
                std::string studentNumber = row["studentNumber"].c_str();
                bool upheld = row["upheld"].as<bool>();
                 std::string type = row["type"].c_str();

                nec.emplace_back(referenceNumber, studentNumber, upheld, type);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return nec;
}

std::vector<Module> examBoard::retrieveModules(){
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM module");

            modules.reserve(result.size());

            for (const auto& row : result) {
                std::string code = row["code"].c_str();
                std::string name = row["name"].c_str();
                int credits = row["credits"].as<int>();

                modules.emplace_back(code, name, credits);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return modules;

}

 const Assessment& examBoard::retrieveAssessmentByID(std::string providedID) {

    auto it = std::find_if(assessments.begin(), assessments.end(), [&providedID](const Assessment& a) {
        return a.getId() == providedID;
    });
    return *it;

}


 const Module& examBoard::retrieveModuleByCode(std::string providedCode){
    auto it = std::find_if(modules.begin(), modules.end(), [&providedCode](const Module& m) {
        return m.getCode() == providedCode;
    });
    return *it;
 }

 const NEC* examBoard::retrieveNecForStudent(std::string referenceNumber) {
    auto it = std::find_if(nec.begin(), nec.end(), [&referenceNumber](const NEC& n) {
        return n.getReferenceNumber() == referenceNumber;
    });

    if (it != nec.end()) {
        return &(*it);
    } else {
        return nullptr;
    }
 }





 std::string examBoard::retrieveModuleType(std::string studentNumber, std::string moduleCode){
    std::string optionality;
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params(
                "SELECT mc.optionality "
                "FROM moduleCourse mc "
                "JOIN student st ON st.course = mc.courseCode "
                "JOIN moduleAttempt ma ON ma.studentNumber = st.studentNumber "
                "AND ma.code = mc.moduleCode "
                "WHERE ma.code = $1 AND ma.studentNumber = $2;",
                moduleCode, studentNumber
                );
            optionality = result[0]["optionality"].c_str();

        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return optionality;
 }



 std::vector<AssessmentAttempt> examBoard::retrieveAssessmentAttemptsForStudent(std::string studentNumber) {
    std::vector<AssessmentAttempt> attempts;
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT * FROM assessmentAttempt WHERE studentNumber = $1", studentNumber);

            attempts.reserve(result.size());

            for (const auto& row : result) {
                std::string studentNumber = row["studentNumber"].c_str();
                std::string assessmentId = row["id"].c_str();
                int numberOfAttempt = row["number"].as<int>();
                bool submittedLate = row["submittedLate"].as<bool>();
                int gradePoints = row["gradePoints"].as<int>();
                std::string optionalCode = row["optionalCode"].c_str();
                std::string necReferenceNumber = row["necReferenceNumber"].c_str();
                std::string misconductID = row["misconductID"].c_str();
                std::string originalAttemptID = row["originalAttemptID"].c_str();
                std::string finalCode = row["finalCode"].c_str();

                const Assessment& retrievedAssessment = retrieveAssessmentByID(assessmentId);


                const Assessment* assessmentPtr = nullptr;
                const AssessmentCode* providedCode=nullptr;
                 const AssessmentCode* fCode=nullptr;
                const NEC* providedNec = nullptr;
                const Misconduct* providedMisconduct = nullptr;
                if (!originalAttemptID.empty()) {
                    const Assessment& assessmentRef = retrieveAssessmentByID(originalAttemptID);
                    assessmentPtr = &assessmentRef;
                }
                if (!necReferenceNumber.empty()){
                    providedNec=retrieveNecForStudent(necReferenceNumber);
                }
                if (!optionalCode.empty()){
                    providedCode= AssessmentCodes::findAssessmentCodeById(optionalCode);

                }
                if (!optionalCode.empty()){
                    providedCode= AssessmentCodes::findAssessmentCodeById(optionalCode);

                }

                AssessmentAttempt attempt(studentNumber, retrievedAssessment, numberOfAttempt, submittedLate, gradePoints,
                                          providedCode, providedNec, providedMisconduct, assessmentPtr);

                if (!finalCode.empty()) {
                    fCode = AssessmentCodes::findAssessmentCodeById(finalCode);
                    attempt.setFinalCode(fCode);
                }

                attempts.push_back(attempt);
            }

        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return attempts;
 }

 /*
    AssessmentAttempt(std::string providedStudentNumber,

            const AssessmentCode* providedCode = nullptr,//optional
            const NEC* providedNec = nullptr,//optional
            const Misconduct* providedMisconduct = nullptr,
            const Assessment* providedOriginalAttempt = nullptr);//optional
*/



std::vector<Student> examBoard::retrieveStudents() {

    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM student");

            students.reserve(result.size());

            for (const auto& row : result) {
                std::string studentNumber = row["studentNumber"].c_str();
                std::string name =  row["name"].c_str();
                std::string course = row["course"].c_str();
                bool fullyEnrolled = row["fullyEnrolled"].as<bool>();
                std::string dateEnrolled = row["dateEnrolled"].as<std::string>();
                bool T4 = row["T4"].as<bool>();
                bool international = row["international"].as<bool>();
                students.emplace_back(studentNumber, name, course, fullyEnrolled, dateEnrolled, T4, international);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return students;
}



std::vector<std::shared_ptr<AssessmentAttempt>> examBoard::retrieveAssessmentAttemptsForStudentForSpecificMpdule(  std::string studentNumber, std::string code)
{
    std::vector<std::shared_ptr<AssessmentAttempt>> attemptPtrs;

    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params(
                "SELECT DISTINCT aA.studentNumber, aA.id, aA.number, aA.gradePoints, aA.grade, aA.optionalCode, "
                "aA.finalCode, aA.necReferenceNumber, aA.misconductID, aA.originalAttemptId, aA.submittedLate "
                "FROM assessmentAttempt aA "
                "JOIN listOfAssessmentAndModuleAttempts lma ON aA.id = lma.id "
                "JOIN moduleAttempt ma ON ma.code = lma.code "
                "WHERE aA.studentNumber = $1 AND ma.code = $2",
                studentNumber, code
                );

            for (const auto& row : result) {
                const Assessment& retrievedAssessment = retrieveAssessmentByID(row["id"].c_str());

                auto attemptPtr = std::make_shared<AssessmentAttempt>(
                    studentNumber, retrievedAssessment,
                    row["number"].as<int>(),
                    row["submittedLate"].as<bool>(),
                    row["gradePoints"].as<int>(),
                    nullptr, nullptr, nullptr, nullptr
                    );

                attemptPtrs.push_back(attemptPtr);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return attemptPtrs;
}



std::vector<ModuleAttempt> examBoard::retrieveModuleAttemptsForStudent(std::string studentNumber) {
    std::vector<ModuleAttempt> attempts;

    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT * FROM moduleAttempt WHERE studentNumber = $1", studentNumber);

            attempts.reserve(result.size());

            for (const auto& row : result) {
                std::string studentNumber = row["studentNumber"].c_str();
                std::string moduleCode = row["code"].c_str();
                int numberOfAttempt = row["number"].as<int>();
                std::string year = row["year"].c_str();
                std::vector<std::shared_ptr<AssessmentAttempt>> attemptPtrs =
                    retrieveAssessmentAttemptsForStudentForSpecificMpdule(studentNumber, moduleCode);

                Module retrievedModule = retrieveModuleByCode(moduleCode);
                AssessmentWeightsMap weights = retrieveAssessmentWeightsForModule(moduleCode, year);

                retrievedModule.setAssessmentWeights(weights);

                retrievedModule.setType(retrieveModuleType(studentNumber, moduleCode));

                attempts.push_back(ModuleAttempt(studentNumber, retrievedModule, numberOfAttempt, year, attemptPtrs));


            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return attempts;
}


std::shared_ptr<const Assessment> examBoard::retrieveAssessmentPointerByID(std::string providedID) {
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT * FROM assessment WHERE ID = $1", providedID);

            if (!result.empty()) {
                const auto& row = result[0];
                std::string id = row["id"].c_str();
                std::string type = row["type"].c_str();
                std::string name = row["name"].c_str();

                return std::make_shared<const Assessment>(id, type, name);
            } else {
                throw std::runtime_error("No Assessment found for ID: " + providedID);
            }
        } else {
            throw std::runtime_error("Connection to database failed.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

Assessment examBoard::retrieveAssessmentObjectById(std::string providedID) {
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT * FROM assessment WHERE ID = $1", providedID);

            if (!result.empty()) {
                const auto& row = result[0];
                std::string id = row["id"].c_str();
                std::string type = row["type"].c_str();
                std::string name = row["name"].c_str();

                return Assessment(id, type, name);
            } else {
                throw std::runtime_error("No Assessment found for ID: " + providedID);
            }
        } else {
            throw std::runtime_error("Connection to database failed.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

AssessmentWeightsMap examBoard::retrieveAssessmentWeightsForModule(const std::string moduleCode, const std::string year) {
    AssessmentWeightsMap weightsMap;

    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params(
                "SELECT id, weight FROM public.assessmentmoduleweights WHERE code = $1",
                moduleCode
                );

            for (const auto& row : result) {
                std::string id = row["id"].c_str();

                int weight = row["weight"].as<int>();

                Assessment assessment = retrieveAssessmentObjectById(id);

                weightsMap.emplace(assessment, weight);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error retrieving weights: " << e.what() << std::endl;
    }

    return weightsMap;
}


std::vector<Module> examBoard::retrieveSpecificForStageModules(std::string stageId){
    std::vector<Module> stageModules;
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT m.code, m.name, m.credits FROM stageContent sc "
                                                  "JOIN module m ON sc.code = m.code "
                                                  "WHERE id = $1", stageId);

            stageModules.reserve(result.size());

            for (const auto& row : result) {
                std::string code = row["code"].c_str();
                std::string name = row["name"].c_str();
                int credits = row["credits"].as<int>();

                stageModules.emplace_back(code, name, credits);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return stageModules;
}

std::vector<Stage> examBoard::retrieveStages(){
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM stage");

            stages.reserve(result.size());

            for (const auto& row : result) {
                std::string id = row["id"].c_str();
                int year = row["year"].as<int>();
                int level = row["level"].as<int>();
                int compensationLimit = row["compensationLimit"].as<int>();
                int credits = row["credits"].as<int>();
                std::vector<std::shared_ptr<Module>> sharedModules;

                // Reserve space for efficiency
                sharedModules.reserve(retrieveSpecificForStageModules(id).size());

                // Iterate through the original vector and create shared pointers
                for (const auto& module : retrieveSpecificForStageModules(id)) {
                    sharedModules.push_back(std::make_shared<Module>(module));
                }

                stages.emplace_back(id, credits, year, level, sharedModules, compensationLimit);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return stages;
}

const Stage& examBoard::retrieveStageByID(std::string providedID){
    auto it = std::find_if(stages.begin(), stages.end(), [&providedID](const Stage& a) {
        return a.getId() == providedID;
    });
    return *it;
}

std::vector<std::shared_ptr<ModuleAttempt>> examBoard::retrieveModuleAttemptsForStudentForSpecificStage(
    std::string studentNumber, std::string stageId) {

    std::vector<std::shared_ptr<ModuleAttempt>> sharedModuleAttempts;
    std::vector<ModuleAttempt> attempts; // Fix: corrected syntax for `std::vector<ModuleAttempt>`

    try {
        // Establish the connection
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            // Execute the query
            pqxx::result result = txn.exec_params(
                "SELECT DISTINCT m.studentNumber, m.code, m.number, m.year, m.grade, m.finalCode, m.creditsEarned "
                "FROM moduleAttempt m "
                "JOIN stageContent sc ON sc.code = m.code "
                "JOIN stageAttempt sa ON sc.id = sa.id "
                "WHERE sa.studentNumber = $1 AND sa.id = $2",
                studentNumber, stageId
                );



            for (const auto& row : result) {
                std::string studentNumber = row["studentNumber"].c_str();
                std::string moduleCode = row["code"].c_str();
                int numberOfAttempt = row["number"].as<int>();
                std::string year = row["year"].c_str();
                std::vector<std::shared_ptr<AssessmentAttempt>> attemptPtrs =
                    retrieveAssessmentAttemptsForStudentForSpecificMpdule(studentNumber, moduleCode);

                Module retrievedModule = retrieveModuleByCode(moduleCode);
                AssessmentWeightsMap weights = retrieveAssessmentWeightsForModule(moduleCode, year);

                retrievedModule.setAssessmentWeights(weights);

                retrievedModule.setType(retrieveModuleType(studentNumber, moduleCode));

                attempts.push_back(ModuleAttempt(studentNumber, retrievedModule, numberOfAttempt, year, attemptPtrs));
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Convert ModuleAttempt objects to shared pointers
    sharedModuleAttempts.reserve(attempts.size()); // Reserve space for efficiency
    for (const auto& attempt : attempts) {
        sharedModuleAttempts.push_back(std::make_shared<ModuleAttempt>(attempt));
    }


    return sharedModuleAttempts;
}


std::vector<StageAttempt> examBoard::retrieveStageAttemptsForStudent(std::string studentNumber){
    std::vector<StageAttempt> attempts;

    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT * FROM stageAttempt WHERE studentNumber = $1", studentNumber);

            attempts.reserve(result.size());

            for (const auto& row : result) {
                std::string studentNumber = row["studentNumber"].c_str();



                std::string id = row["id"].c_str();



                std::vector<std::shared_ptr<ModuleAttempt>> attemptPtrs =
                    retrieveModuleAttemptsForStudentForSpecificStage(studentNumber, id);
                attempts.push_back(StageAttempt(studentNumber, retrieveStageByID(id),attemptPtrs));


            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return attempts;
}

const Course& examBoard::retrieveCourseByID(std::string providedID){
    auto it = std::find_if(courses.begin(), courses.end(), [&providedID](const Course& a) {
        return a.getCode() == providedID;
    });
    return *it;
}

std::vector<Stage> examBoard::retrieveSpecificForCourseStages(std::string courseCode){
    std::vector<Stage> stagesForCourse;


    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT s.id, s.year, s.level, s.compensationLimit, s.credits "
                                                   "FROM stage s "
                                                    "JOIN possibleStagesForCourse ps ON ps.id = s.id "
                                                    "JOIN course c ON ps.code = c.code "
                                                    "WHERE c.code = $1", courseCode);

            stagesForCourse.reserve(result.size());

            for (const auto& row : result) {
                std::string id = row["id"].c_str();
                int year = row["year"].as<int>();
                int level = row["level"].as<int>();
                int compensationLimit = row["compensationLimit"].as<int>();
                int credits = row["credits"].as<int>();
                std::vector<std::shared_ptr<Module>> sharedModules;


                sharedModules.reserve(retrieveSpecificForStageModules(id).size());


                for (const auto& module : retrieveSpecificForStageModules(id)) {
                    sharedModules.push_back(std::make_shared<Module>(module));
                }

                stagesForCourse.emplace_back(id, credits, year, level, sharedModules, compensationLimit);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return stagesForCourse;
}


std::vector<Course> examBoard::retrieveCourses(){

    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM course");

            courses.reserve(result.size());

            for (const auto& row : result) {
                std::string code = row["code"].c_str();
                std::string name = row["name"].c_str();
                 std::string startClassification = row["degreeLevel"].c_str();
                 std::string type = row["studyMode"].c_str();
                std::vector<std::shared_ptr<Stage>> sharedStages;

                // Reserve space for efficiency
                sharedStages.reserve(retrieveSpecificForCourseStages(code).size());

                // Iterate through the original vector and create shared pointers
                for (const auto& stage : retrieveSpecificForCourseStages(code)) {
                    sharedStages.push_back(std::make_shared<Stage>(stage));
                }

                courses.emplace_back(code, name, sharedStages, startClassification, type);
            }
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return courses;
}


CourseAttempt* examBoard::retrieveStudentCourseAttept(std::string studentNumber) {


    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec_params("SELECT * FROM courseAttempt WHERE studentNumber = $1", studentNumber);

            if (result.empty()) {

                return nullptr;
            }

            const auto& row = result[0];
            std::string studentNumberFromRow = row["studentNumber"].c_str();
            std::string code = row["code"].c_str();


            std::vector<std::shared_ptr<StageAttempt>> sharedStages;
            auto originalStages = retrieveStageAttemptsForStudent(studentNumberFromRow);
            sharedStages.reserve(originalStages.size());

            for (const auto& stage : originalStages) {
                sharedStages.push_back(std::make_shared<StageAttempt>(stage));
            }




            if (sharedStages.empty()) {

                return nullptr;
            }



            return new CourseAttempt(studentNumberFromRow, retrieveCourseByID(code), sharedStages);
        } else {
            std::cerr << "Connection to database failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return nullptr;
}



void examBoard::preLoadInfoData(){
    retrieveAssessments();
    retrieveModules();
    retrieveStages();
    retrieveCourses();
    retrieveStudents();
}
std::vector<StudentRecord> examBoard::loadStudentRecords(){
    preLoadInfoData();
    for (const auto& student : students) {
        CourseAttempt* courseAttempt = retrieveStudentCourseAttept(student.getStudentNumber());
        StudentRecord strecord(student, courseAttempt);
        studentRecords.push_back(strecord);
    }
    return studentRecords;
}

