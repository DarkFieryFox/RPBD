#pragma once
#ifndef Parents_HEADER
#define Parents_HEADER
#include <iostream>
#include <string>

class Parents
{
private:
	long id;
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string degree;
	std::string address;

public:
	Parents();
	~Parents();

	long getId() const;
	void setId(long);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getSurname() const;
	void setSurname(const std::string& surname);

	std::string getPatronymic() const;
	void setPatronymic(const std::string& patronymic);

	std::string getDegree() const;
	void setDegree(const std::string& degree);

	std::string getAddress() const;
	void setAddress(const std::string& address);

};

#endif
