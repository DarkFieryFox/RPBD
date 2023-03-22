#pragma once
#ifndef DB_Operations_HEADER
#define DB_Operations_HEADER

#include "DataBase.h"
#include <vector>

template<class T, class TypeID>
class DB_Operations {
protected:
	DataBase& db;

public:
	DB_Operations(DataBase& db);
	virtual void save(const T& date) = 0;
	virtual void remove(TypeID typeID) = 0;
	virtual T* findById(TypeID typeID) = 0;
	virtual std::vector<T*> findAll() = 0;
};

template<class T, class TypeID>
DB_Operations<T, TypeID>::DB_Operations(DataBase& db) : db(db) {}

#endif