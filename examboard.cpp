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

std::vector<Module> examBoard::retrieveModules(){
    try {
        pqxx::connection conn("dbname=examinationboard user=master password=password host=board.cv2888uq44nv.eu-north-1.rds.amazonaws.com port=5432");

        if (conn.is_open()) {
            pqxx::nontransaction txn(conn);

            pqxx::result result = txn.exec("SELECT * FROM module");

            assessments.reserve(result.size());

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
                std::string assessmentId =  row["id"].c_str();
                int numberOfAttempt = row["number"].as<int>();
                bool submittedLate = row["submittedLate"].as<bool>();
                int gradePoints = row["gradePoints"].as<int>();
                std::string optionalCode = row["optionalCode"].c_str();
                std::string necReferenceNumber = row["necReferenceNumber"].c_str();
                std::string misconductID = row["misconductID"].c_str();
                std::string originalAttemptID = row["originalAttemptID"].c_str();
                const Assessment& retrievedAssessment = retrieveAssessmentByID(assessmentId);
                attempts.emplace_back(studentNumber, retrievedAssessment, numberOfAttempt, submittedLate, gradePoints, nullptr, nullptr, nullptr, nullptr);
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

