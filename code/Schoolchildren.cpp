#include "Schoolchildren.h"


Schoolchildren::Schoolchildren()
{
}

Schoolchildren::~Schoolchildren()
{
}

long Schoolchildren::getId() const
{
	return this->id;
}

void Schoolchildren::setId(long id)
{
	this->id = id;
}

std::string Schoolchildren::getName() const
{
	return this->name;
}

void Schoolchildren::setName(const std::string& name)
{
	this->name = name;
}

std::string Schoolchildren::getSurname() const
{
	return this->surname;
}

void Schoolchildren::setSurname(const std::string& surname)
{
	this->surname = surname;
}
std::string Schoolchildren::getPatronymic() const
{
	return this->patronymic;
}

void Schoolchildren::setPatronymic(const std::string& patronymic)
{
	this->patronymic = patronymic;
}

int Schoolchildren::getYear_admission() const
{
	return this->year_admission;
}
void Schoolchildren::setYear_admission(int year_admission)
{
	this->year_admission = year_admission;
}

Date Schoolchildren::getDate() const
{
	return this->birthday;
}

void Schoolchildren::setDate(Date date)
{
	this->birthday.day = date.day;
	this->birthday.month = date.month;
	this->birthday.year = date.year;
}

std::string Schoolchildren::toStringDate() const
{
	return std::to_string(this->birthday.year) +
		"-" + std::to_string(this->birthday.month) +
		"-" + std::to_string(this->birthday.day);
}

Date Schoolchildren::setStringDate(std::string& date)
{
	Date strDate;
	std::stringstream in(date);
	std::getline(in, date, '-');
	strDate.year = stoi(date);
	std::getline(in, date, '-');
	strDate.month = stoi(date);
	std::getline(in, date, '-');
	strDate.day = stoi(date);

	return strDate;
}
std::string Schoolchildren::getAddress() const
{
	return this->address;
}

void Schoolchildren::setAddress(const std::string& address)
{
	this->address = address;
}
std::vector<Parents*> Schoolchildren::getParents() const
{
	return this->parentss;
}

void Schoolchildren::setParents(const std::vector<Parents*> parentss)
{
	this->parentss = parentss;
}

std::vector<Progress*> Schoolchildren::getProgress() const
{
	return this->progress;
}

void Schoolchildren::setProgress(const std::vector<Progress*> progress)
{
	this->progress = progress;
}
