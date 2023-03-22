#pragma once
#ifndef Progress_Mapper_HEADER
#define Progress_Mapper_HEADER
#include "DB_Operations.h"
#include "Progress.h"

#define ID_LEN 8
#define NAME_LEN 1024

class Progress_Mapper : public DB_Operations<Progress, long> 
{
private:
	SQLINTEGER id;
	SQLINTEGER year;
	SQLINTEGER quarter;
	SQLINTEGER exam;
	SQLINTEGER finaly;
	SQLINTEGER half_yearly;
	SQLINTEGER yearly;
	SQLCHAR classs[64];
	SQLCHAR subject[64];


public:
	Progress_Mapper(DataBase& db);
	~Progress_Mapper();

	void save(const Progress& progress) override;
	void remove(long id) override;
	Progress* findById(long id) override;
	std::vector<Progress*> findAll() override;
};

#endif