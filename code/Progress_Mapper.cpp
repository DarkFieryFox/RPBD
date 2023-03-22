#include "Progress_Mapper.h"
#include "Storage.h"

Progress_Mapper::Progress_Mapper(DataBase& db) : DB_Operations(db)
{

}

Progress_Mapper::~Progress_Mapper()
{
}

void Progress_Mapper::save(const Progress& progress)
{
	char buf[1024];
	if (progress.getId() != -1) {
		sprintf(buf, 
			"UPDATE progress SET classs = '%s', subject = '%s', year = '%d', half_yearly = '%d', quarter = '%d', yearly = '%d', exam = '%d', finaly = '%d' WHERE id = '%d'",
			progress.getClasss().c_str(),
			progress.getSubject().c_str(),
			progress.getYear(),
			progress.getHalf_yearly(),
			progress.getQuarter(),
			progress.getYearly(),
			progress.getExam(),
			progress.getFinaly(),
			progress.getId());

	}
	else {
		sprintf(buf, "INSERT INTO progress(classs, subject, year, half_yearly, quarter, yearly, exam, finaly) VALUES ('%s', '%s', '%d', '%d', '%d', '%d', '%d', '%d')",
			progress.getClasss().c_str(),
			progress.getSubject().c_str(),
			progress.getYear(),
			progress.getHalf_yearly(),
			progress.getQuarter(),
			progress.getYearly(),
			progress.getExam(),
			progress.getFinaly());
	}
	db.execute(buf);
}



void Progress_Mapper::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM progress as s WHERE s.id = %d", id);
	db.execute(buf);
}

Progress* Progress_Mapper::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT sp.id, sp.classs, sp.subject, sp.year, sp.half_yearly, sp.quarter, sp.yearly, sp.exam, sp.finaly FROM progress AS sp WHERE sp.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->classs, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->subject, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_LONG, &this->year, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_LONG, &this->half_yearly, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_LONG, &this->quarter, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_LONG, &this->yearly, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 8, SQL_C_LONG, &this->exam, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 9, SQL_C_LONG, &this->finaly, NAME_LEN, nullptr);


	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Progress progress;
		progress.setId(id);
		progress.setClasss(reinterpret_cast<char*>(classs));
		progress.setSubject(reinterpret_cast<char*>(subject));
		progress.setYear(year);
		progress.setHalf_yearly(half_yearly);
		progress.setQuarter(quarter);
		progress.setYearly(yearly);
		progress.setExam(exam);
		progress.setFinaly(finaly);

		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getProgress(progress.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in progress_mapper\n";
	}
	return nullptr;
}

std::vector<Progress*> Progress_Mapper::findAll()
{
	std::vector<Progress*> progress_vector;

	SQLHSTMT statement = db.execute("SELECT sp.id, sp.classs, sp.subject, sp.year, sp.half_yearly, sp.quarter, sp.yearly, sp.exam, sp.finaly FROM progress AS sp ORDER BY sp.id ASC");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &classs, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &subject, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_LONG, &year, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_LONG, &half_yearly, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_LONG, &quarter, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_LONG, &yearly, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 8, SQL_C_LONG, &exam, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 9, SQL_C_LONG, &finaly, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Progress progress;
			progress.setId(id);
			progress.setClasss(reinterpret_cast<char*>(classs));
			progress.setSubject(reinterpret_cast<char*>(subject));
			progress.setYear(year);
			progress.setHalf_yearly(half_yearly);
			progress.setQuarter(quarter);
			progress.setYearly(yearly);
			progress.setExam(exam);
			progress.setFinaly(finaly);

			Storage::getInstance()->putProgress(progress);
			progress_vector.push_back(Storage::getInstance()->getProgress(progress.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching progress_mapper\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return progress_vector;
}
