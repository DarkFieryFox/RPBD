#pragma once
#ifndef Schoolchildren_Mapper_HEADER
#define Schoolchildren_Mapper_HEADER
#include "DB_Operations.h"
#include "Schoolchildren.h"
#include "Parents_Mapper.h"
#include "Progress_Mapper.h"


#define ID_LEN 8
#define NAME_LEN 1024

class Schoolchildren_Mapper : public DB_Operations<Schoolchildren, long>
{
private:
	SQLINTEGER id;
	SQLCHAR name[64];
	SQLCHAR surname[64];
	SQLCHAR patronymic[64];
	SQLCHAR address[64];
	SQLCHAR birthday[32];
	SQLINTEGER year_admission;
	Parents_Mapper& parentss_mapper;
	Progress_Mapper& progress_mapper;

public:
	Schoolchildren_Mapper(DataBase& db, Parents_Mapper& parentss_mapper, Progress_Mapper& progress_mapper);
	~Schoolchildren_Mapper();

	void save(const Schoolchildren& schoolchild) override;
	void remove(long id) override;
	Schoolchildren* findById(long id) override;
	std::vector<Schoolchildren*> findAll() override;

	void addParents(long id, long parentsId);
	void addProgress(long id, long progressId);

	void removeParents(long id, long parentsId);
	void removeProgress(long id, long progressId);

};

#endif
