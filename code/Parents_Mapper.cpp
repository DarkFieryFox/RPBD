#include "Parents_Mapper.h"
#include "Storage.h"

Parents_Mapper::Parents_Mapper(DataBase& db) : DB_Operations(db)
{
}

Parents_Mapper::~Parents_Mapper()
{
}

void Parents_Mapper::save(const Parents& parentss)
{
	char buf[1024];
	if (parentss.getId() != -1) {
		sprintf(buf,
			"UPDATE parentss SET name = '%s', surname = '%s', patronymic = '%s', degree = '%s', address = '%s' WHERE id = '%d'",
			parentss.getName().c_str(),
			parentss.getSurname().c_str(),
			parentss.getPatronymic().c_str(),
			parentss.getDegree().c_str(),
			parentss.getAddress().c_str(),
			parentss.getId());
	}
	else {
		sprintf(buf, "INSERT INTO parentss(name, surname, patronymic, degree, address) VALUES ('%s','%s','%s','%s','%s')",
			parentss.getName().c_str(),
			parentss.getSurname().c_str(),
			parentss.getPatronymic().c_str(),
			parentss.getDegree().c_str(),
			parentss.getAddress().c_str());

	}
	db.execute(buf);
}

void Parents_Mapper::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM parentss as m WHERE m.id %d", id);
	db.execute(buf);
}

Parents* Parents_Mapper::findById(long id)
{
	char buf[1024];
	sprintf(buf, "SELECT m.id, m.name, m.surname, m.patronymic, m.degree, m.address FROM parentss AS m WHERE m.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &this->degree, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &this->address, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	
	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Parents parentss;
		parentss.setId(id);
		parentss.setName(reinterpret_cast<char*>(name));
		parentss.setSurname(reinterpret_cast<char*>(surname));
		parentss.setPatronymic(reinterpret_cast<char*>(patronymic));
		parentss.setDegree(reinterpret_cast<char*>(degree));
		parentss.setAddress(reinterpret_cast<char*>(address));

		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getParents(parentss.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in progre_mapper\n";
	}
	return nullptr;
}

std::vector<Parents*> Parents_Mapper::findAll()
{
	std::vector<Parents*> parentss_vector;

	SQLHSTMT statement = db.execute("SELECT m.id, m.name, m.surname, m.patronymic, m.degree, m.address FROM parentss AS m ORDER BY m.id ASC");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &degree, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &address, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Parents parentss;
			parentss.setId(id);
			parentss.setName(reinterpret_cast<char*>(name));
			parentss.setSurname(reinterpret_cast<char*>(surname));
			parentss.setPatronymic(reinterpret_cast<char*>(patronymic));
			parentss.setDegree(reinterpret_cast<char*>(degree));
			parentss.setAddress(reinterpret_cast<char*>(address));

			//parentss_vector.push_back(&parentss);
			Storage::getInstance()->putParents(parentss);
			parentss_vector.push_back(Storage::getInstance()->getParents(parentss.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching client_mapper\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return parentss_vector;
}
