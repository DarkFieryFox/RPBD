#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef DataBase_HEADER
#define DataBases_HEADER
#include <iostream>
#include "windows.h"
#include <sql.h>
#include <sqlext.h>
#include <string>

using namespace std;
class DataBase {

private:
	SQLHENV environment;
	SQLHDBC connection;
	SQLHSTMT statement;

private:
	void connect();

public:
	
	DataBase();
	~DataBase();

	const SQLHSTMT& execute(const char* sql);
	const wchar_t* getWChar(const char* sql);
	void createTables();

};

#endif