#pragma once
#ifndef Parents_Mapper_HEADER
#define Parents_Mapper_HEADER
#include "DB_Operations.h"
#include "Parents.h"

#define ID_LEN 8
#define NAME_LEN 1024

class Parents_Mapper : public DB_Operations<Parents, long>
{
private:
	SQLINTEGER id;
	SQLCHAR name[64];
	SQLCHAR surname[64];
	SQLCHAR patronymic[64];
	SQLCHAR degree[64];
	SQLCHAR address[64];


public:
	Parents_Mapper(DataBase& db);
	~Parents_Mapper();

	void save(const Parents& parentss) override;
	void remove(long id) override;
	Parents* findById(long id) override;
	std::vector<Parents*> findAll() override;

};

#endif