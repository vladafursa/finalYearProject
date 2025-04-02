#ifndef CODECONSTANTS_H
#define CODECONSTANTS_H
#include <string>
#include "code.h"
#include "assessmentcode.h"
#include "awardcode.h"
#include "modulecode.h"
#include "progressioncode.h"


//Module codes
//Pass codes
namespace ModuleCodes {
const ModuleCode PA("PA", "Pass");
const ModuleCode PC("PC", "Pass with compensation");
const ModuleCode PN("PN", "Pass with Commendation");
const ModuleCode PM("PM", "Pass with Merit");
const ModuleCode PD("PD", "Pass with Distinction");
const ModuleCode PL("PL", "Pass – late submission");
const ModuleCode PR("PR", "Pass following Referral");
const ModuleCode PF("PF", "Pass following Repeat");
const ModuleCode PX("PX", "Pass rpt module after referral");
const ModuleCode PH("PH", "Pass (Previous System)");
const ModuleCode PE("PE", "Excellent Pass");
const ModuleCode PG("PG", "Good Pass");
const ModuleCode PQ("PQ", "Compensated Referred Pass");
const ModuleCode PK("PK", "Compensated pass after repeat");
const ModuleCode PB("PB", "Pass - Module capped");
const ModuleCode PJ("PJ", "Pass – Credit points only");
const ModuleCode NC("NC", "Not competent");
const ModuleCode PO("PO", "Pass – Outstanding");
const ModuleCode PT("PT", "Pass – Competent");
const ModuleCode PV("PV", "Pass - Very Competent");
const ModuleCode PY("PY", "Pass repeat element");

// Referral codes
const ModuleCode RR("RR", "Referred");
const ModuleCode RE("RE", "Referred by exam");
const ModuleCode RK("RK", "Referred by coursework");
const ModuleCode RT("RT", "Referred by test");
const ModuleCode RM("RM", "Referred – contact Module Leader");
const ModuleCode RW("RW", "Referred by reworking exam");
//const ModuleCode RF("RF", "Referred – final attempt");
//const ModuleCode RN("RN", "Referred next academic year");

// Defer codes
const ModuleCode DF("DF", "Defer");

// First Sit codes
const ModuleCode S1("1S", "First sit");
const ModuleCode S2("1A", "First sit in Aug/Sept");
const ModuleCode S3("1N", "First sit next academic year");
const ModuleCode S4("1O", "First sit next opportunity");

// Fail codes
const ModuleCode F0("??", "Provisional fail");
const ModuleCode F1("F?", "Fail after referral");
const ModuleCode FA("FA", "Fail-repeat without attendance");
const ModuleCode FN("FN", "Fail-no more attempts allowed");
const ModuleCode FR("FR", "Fail - repeat module");
const ModuleCode FC("FC", "Fail-repeat for credit only");
const ModuleCode FM("FM", "Repeat module with attendance");
const ModuleCode FO("FO", "Fail – repeat mod or alternative");

// Mark change codes
const ModuleCode EB("EB", "Changed at Exam Board");


// Withdrawn codes
const ModuleCode WD("WD", "Withdrew");
const ModuleCode WA("WA", "Replaced by alternative module to be added after Board");
}

//Assessment codes
namespace AssessmentCodes {
// Pass codes
const AssessmentCode PC("PC", "Pass with compensation");
const AssessmentCode PL("PL", "Pass – late submission");
const AssessmentCode PR("PR", "Pass following Referral");
const AssessmentCode PQ("PQ", "Compensated Referred Pass");
const AssessmentCode PK("PK", "Compensated pass after repeat");
const AssessmentCode PB("PB", "Pass - Module capped");
const AssessmentCode PJ("PJ", "Pass – Credit points only");
const AssessmentCode PY("PY", "Pass repeat element");

// Referral codes
const AssessmentCode RR("RR", "Referred");
const AssessmentCode RE("RE", "Referred by exam");
const AssessmentCode RK("RK", "Referred by coursework");
const AssessmentCode RT("RT", "Referred by test");
const AssessmentCode RM("RM", "Referred – contact Module Leader");
const AssessmentCode RW("RW", "Referred by reworking exam");
const AssessmentCode RF("RF", "Referred – final attempt");
const AssessmentCode RN("RN", "Referred next academic year");
const AssessmentCode DF("DF", "Defer");

// First Sit codes
const AssessmentCode S1("1S", "First sit");
const AssessmentCode S2("1A", "First sit in Aug/Sept");
const AssessmentCode S3("1N", "First sit next academic year");
const AssessmentCode S4("1O", "First sit next opportunity");

// Fail codes
const AssessmentCode FE("FE", "Fail element after referral");
const AssessmentCode FA("FA", "Fail-repeat without attendance");
const AssessmentCode FN("FN", "Fail-no more attempts allowed");
const AssessmentCode FR("FR", "Fail - repeat module");
const AssessmentCode FW("FW", "Fail – repeat with attendance");
const AssessmentCode FC("FC", "Fail-repeat for credit only");
const AssessmentCode FO("FO", "Fail – repeat mod or alternative");

// Mark change codes
const AssessmentCode OE("OE", "Original entry");
const AssessmentCode EB("EB", "Changed at Exam Board");
const AssessmentCode CA("CA", "Changed by Chair’s Action");
const AssessmentCode CC("CC", "Composite calculation");
const AssessmentCode CR("CR", "Capped resit");
const AssessmentCode DL("DL", "Degraded late");
const AssessmentCode MC("MC", "Mark correction");
const AssessmentCode OG("OG", "Original mark – first sit");
const AssessmentCode RC("RC", "Re-calculated");

// Withdrawn codes
const AssessmentCode WD("WD", "Withdrew");
}

//Progression codes
namespace ProgressionCodes{
const ProgressionCode P0("P0", "Pass Stage 0", true, true, true);
const ProgressionCode P1("P1", "Pass Stage 1", true, true, true);
const ProgressionCode P2("P2", "Pass Stage 2", true, true, true);
const ProgressionCode P3("P3", "Pass Stage 3", true, true, true);
const ProgressionCode PW("PW", "Pass Within Stage", true, false, true);
const ProgressionCode PR("PR", "Proceed - Stage incomplete", true, false, true);
const ProgressionCode PU("PU", "Proceed - same stage/year", true, false, false);
const ProgressionCode PG("PG", "Proceed - limit of Ord degree", true, true, true);
const ProgressionCode PB("PB", "Proceed - limit of Bachelor's", true, true, true);
const ProgressionCode PI("PI", "Proceed – placement incomplete", true, true, true);
const ProgressionCode PL("PL", "Pass Placement", true, true, true);
const ProgressionCode PC("PC", "Pass placement-cannot proceed", true, false, false);
const ProgressionCode PS("PS", "Pass & Proceed to Placement", true, false, true);
const ProgressionCode PP("PP", "Proceed to Placement (Deficit)", true, false, true);
const ProgressionCode PA("PA", "Qualify for Award", false, false, false);
const ProgressionCode PF("PF", "Qualify for Fallback", false, false, false);
const ProgressionCode PN("PN", "Complete Non Award Bearing", false, false, false);
const ProgressionCode PD("PD", "Proceed - make good deficit", true, true, true);
const ProgressionCode RF("RF", "Referred", false, false, false);
const ProgressionCode RA("RA", "Referred in Aug/Sept", false, false, false);
const ProgressionCode RN("RN", "Referred Next Academic Year", true, false, false);
const ProgressionCode RS("RS", "Referred Next Sitting", true, true, true);
const ProgressionCode RP("RP", "Refer for an Ordinary Degree", false, false, false);
const ProgressionCode RR("RR", "Refers/Repeats – Cannot Proceed", false, false, false);
const ProgressionCode RD("RD", "Refer or accept Ordinary Degree", false, false, false);
const ProgressionCode RH("RH", "Referred or accept DipHE", false, false, false);
const ProgressionCode RE("RE", "Referred or accept CertHE", false, false, false);
const ProgressionCode R3("R3", "Referred for a max of a 3rd", false, false, false);
const ProgressionCode R1("R1", "First Sitting in Aug/Sept", false, false, false);
const ProgressionCode DF("DF", "Defer", false, false, false);
const ProgressionCode F1("F1", "First sits next year", true, false, false);
const ProgressionCode FT("FT", "Fail & Terminate Studies", false, false, false);
const ProgressionCode FR("FR", "Fail – repeats permitted next academic year", true, false, false);
const ProgressionCode FA("FA", "Fail & Transfer", true, false, false);
const ProgressionCode FY("FY", "Repeat Year (with some first sittings)", true, false, false);
const ProgressionCode FC("FC", "Fail-award Credit Points only", false, false, false);
const ProgressionCode FD("FD", "Fail & Repeat Mods for Degree", true, false, false);
const ProgressionCode NC("NC", "Assessment Not Yet Complete", false, false, false);
const ProgressionCode NI("NI", "Intercalation (Year Out)", true, false, false);
const ProgressionCode NK("NK", "Result Not Yet Known", false, false, false);
const ProgressionCode SO("SO", "Awaiting Decision", false, false, false);
const ProgressionCode WD("WD", "Withdrawn", false, false, false);
const ProgressionCode WI("WI", "Withdrawn - Internal Transfer", true, false, false);
}

//Award codes
namespace AwardCodes{
const AwardCode C10("10", "First Class Honours");
const AwardCode C21("21", "2nd Class Honours-1st Division");
const AwardCode C22("22", "2nd Class Honours-2nd Division");
const AwardCode C30("30", "Third Class Honours");
const AwardCode DN("DN", "Ordinary Degree");
const AwardCode DD("DD", "Ord Degree with Distinction");
const AwardCode AE("AE", "Aegrotat");
const AwardCode AD("AD", "Awarded PGDip");
const AwardCode AP("AP", "Award Professional Certificate");
const AwardCode DA("DA", "PgDip with Distinction");
const AwardCode DC("DC", "PgDip with Commendation");
const AwardCode AC("AC", "Awarded PGCert");
const AwardCode CA("CA", "PgCert with Distinction");
const AwardCode CC("CC", "PgCert with Commendation");
const AwardCode A2("A2", "Awarded Dip HE");
const AwardCode A1("A1", "Awarded Cert HE");
const AwardCode AA("AA", "Awarded Cert of Achievement");
const AwardCode AN("AN", "Awarded Cert");
const AwardCode HC("HC", "Awarded Higher Cert (UFD)");
const AwardCode DB("DB", "PQ Advanced Diploma");
const AwardCode DE("DE", "Adv Diploma with Distinction");
const AwardCode PV("PV", "Cert of Professional Studies");
const AwardCode PP("PP", "Pass for Credit Points");
const AwardCode PC("PC", "Pass with Commendation");
const AwardCode PD("PD", "Pass with Distinction");
const AwardCode PM("PM", "Pass with Merit");
const AwardCode PE("PE", "Excellent Pass");
const AwardCode A3("A3", "Adv Dip in Studies in Sec Edu");
const AwardCode A4("A4", "PG Cert in Studies in Sec Edu");
const AwardCode A5("A5", "Adv Dip in Studies in Prim Edu");
const AwardCode A6("A6", "PG Cert in Studies in Prim Edu");
const AwardCode A0("A0", "Awarded Dip");
const AwardCode BA("BA", "Certificate in Business Admin");
const AwardCode DS("DS", "PG Dip in Studies in Education");
const AwardCode DT("DT", "Prof Dip in Studies in Educ");
const AwardCode DU("DU", "PG Cert in Studies in Educ");
const AwardCode DV("DV", "Prof Cert in Studies in Educ");
const AwardCode HD("HD", "Awarded Higher Cert with Dist");
const AwardCode HM("HM", "Awarded Higher Cert with Comm");
const AwardCode PH("PH", "Pass with Honours");
const AwardCode ID("ID", "DipHE with Distinction");
const AwardCode CD("CD", "CertHE with Distinction");

// Postgraduate Bar Vocational Codes
const AwardCode V1("V1", "Postgraduate Diploma (Outstanding) (Bar Voc)");
const AwardCode V2("V2", "Postgraduate Diploma (Very Competent) (Bar Voc)");
const AwardCode V3("V3", "Postgraduate Diploma (Competent) (Bar Voc)");
const AwardCode V4("V4", "Postgraduate Certificate (Outstanding) (Bar Voc)");
const AwardCode V5("V5", "Postgraduate Certificate (Very Competent) (Bar Voc)");
const AwardCode V6("V6", "Postgraduate Certificate (Competent) (Bar Voc)");
}
#endif // CODECONSTANTS_H
