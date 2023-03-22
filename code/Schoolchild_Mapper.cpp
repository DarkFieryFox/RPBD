#include "Schoolchildren_Mapper.h"
#include "Storage.h"

Schoolchildren_Mapper::Schoolchildren_Mapper(DataBase& db, 
		Parents_Mapper& parentss_mapper, 
		Progress_Mapper& progress_mapper) :
		DB_Operations(db), 
		parentss_mapper(parentss_mapper),
		progress_mapper(progress_mapper)
{

}

Schoolchildren_Mapper::~Schoolchildren_Mapper()
{
}

void Schoolchildren_Mapper::save(const Schoolchildren& schoolchildren)
{
	char buf[1024];
	if (schoolchildren.getId() != -1) {
		sprintf(buf,
			"UPDATE schoolchildren SET name = '%s', surname = '%s', patronymic = '%s', birthday = '%s', address = '%s', year_admission = '%d' WHERE id = '%d'",
			schoolchildren.getName().c_str(),
			schoolchildren.getSurname().c_str(),
			schoolchildren.getPatronymic().c_str(),
			schoolchildren.toStringDate().c_str(),
			schoolchildren.getAddress().c_str(),
			schoolchildren.getYear_admission(),
			schoolchildren.getId());
	}
	else {
		sprintf(buf, "INSERT INTO schoolchildren(name, surname, patronymic, birthday, address, year_admission) VALUES ('%s','%s','%s','%s','%s','%d')",
			schoolchildren.getName().c_str(),
			schoolchildren.getSurname().c_str(),
			schoolchildren.getPatronymic().c_str(),
			schoolchildren.toStringDate().c_str(),
			schoolchildren.getAddress().c_str(),
			schoolchildren.getYear_admission());
	}
	db.execute(buf);
}

void Schoolchildren_Mapper::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM schoolchildren as m WHERE m.id %d", id);
	db.execute(buf);
}

Schoolchildren* Schoolchildren_Mapper::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT m.id, m.name, m.surname, m.patronymic, m.birthday, m.address, m.year_admission FROM schoolchildren AS m WHERE m.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &this->birthday, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &this->address, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_LONG, &this->year_admission, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Schoolchildren schoolchildren;
		schoolchildren.setId(id);
		schoolchildren.setName(reinterpret_cast<char*>(name));
		schoolchildren.setSurname(reinterpret_cast<char*>(surname));
		schoolchildren.setPatronymic(reinterpret_cast<char*>(patronymic));
		std::string str = reinterpret_cast<char*>(birthday);
		schoolchildren.setDate(schoolchildren.setStringDate(str));
		schoolchildren.setAddress(reinterpret_cast<char*>(address));
		schoolchildren.setYear_admission(year_admission);

		SQLFreeStmt(statement, SQL_CLOSE);
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in schoolchildren_mapper\n";
	}
	return nullptr;
}

std::vector<Schoolchildren*> Schoolchildren_Mapper::findAll()
{
	std::vector<Schoolchildren*> schoolchildren_vector;

	SQLHSTMT statement = db.execute("SELECT m.id, m.name, m.surname, m.patronymic, m.birthday, m.address, m.year_admission FROM schoolchildren AS m ORDER BY m.id ASC");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &birthday, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &address, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_LONG, &year_admission, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Schoolchildren schoolchild;
			schoolchild.setId(id);
			schoolchild.setName(reinterpret_cast<char*>(name));
			schoolchild.setSurname(reinterpret_cast<char*>(surname));
			schoolchild.setPatronymic(reinterpret_cast<char*>(patronymic));
			std::string str = reinterpret_cast<char*>(birthday);
			schoolchild.setDate(schoolchild.setStringDate(str));
			schoolchild.setAddress(reinterpret_cast<char*>(address));
			schoolchild.setYear_admission(year_admission);
			Storage::getInstance()->putSchoolchildren(schoolchild);
			schoolchildren_vector.push_back(Storage::getInstance()->getSchoolchildren(schoolchild.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching schoolchild\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return schoolchildren_vector;
}

void Schoolchildren_Mapper::addParents(long id, long parentsId)
{
	char buf[128];
	sprintf(buf, "INSERT INTO schoolchildren_parentss(schoolchildren_id, parentss_id) values (%d, %d)", id, parentsId);
	db.execute(buf);

}

void Schoolchildren_Mapper::addProgress(long id, long progressId)
{
	char buf[128];
	sprintf(buf, "INSERT INTO schoolchildren_progress(schoolchildren_id, progress_id) values (%d, %d)", id, progressId);
	db.execute(buf);
}

void Schoolchildren_Mapper::removeParents(long id, long parentsId)
{
	char buf[128];
	sprintf(buf, "DELETE FROM schoolchildren_parentss WHERE (schoolchildren_id = %d AND parentss_id = %d)", id, parentsId);
	db.execute(buf);
}

void Schoolchildren_Mapper::removeProgress(long id, long progressId)
{
	char buf[128];
	sprintf(buf, "DELETE FROM schoolchildren_progress WHERE (schoolchildren_id = %d AND progress_id = %d)", id, progressId);
	db.execute(buf);
}
