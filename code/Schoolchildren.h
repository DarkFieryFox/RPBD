#pragma once
#ifndef Schoolchildren_HEADER
#define Schoolchildren_HEADER
#include <iostream>
#include <string>
#include <vector>
#include "Parents.h"
#include "Progress.h"
#include "Date.h"
class Schoolchildren
{
private:
	long id;
	std::string name;
	std::string surname;
	std::string patronymic;
	Date birthday;
	std::string address;
	int year_admission;
	std::vector<Parents*> parentss;
	std::vector<Progress*> progress;

public:
	Schoolchildren();
	~Schoolchildren();

	long getId() const;
	void setId(long);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getSurname() const;
	void setSurname(const std::string& surname);

	std::string getPatronymic() const;
	void setPatronymic(const std::string& patronymic);

	std::string getAddress() const;
	void setAddress(const std::string& address);

	Date getDate() const;
	void setDate(Date);

	std::string toStringDate() const;
	Date setStringDate(std::string& date);

	int getYear_admission() const;
	void setYear_admission(int);

	std::vector<Parents*> getParents() const;
	void setParents(const std::vector<Parents*> parentss);

	std::vector<Progress*> getProgress() const;
	void setProgress(const std::vector<Progress*> progress);

};

#endif