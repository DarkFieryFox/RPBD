#include "Parents.h"

Parents::Parents()
{
}

Parents::~Parents()
{
}

long Parents::getId() const
{
	return this->id;
}

void Parents::setId(long id)
{
	this->id = id;
}


std::string Parents::getName() const
{
	return this->name;
}

void Parents::setName(const std::string& name)
{
	this->name = name;
}

std::string Parents::getSurname() const
{
	return this->surname;
}

void Parents::setSurname(const std::string& surname)
{
	this->surname = surname;
}

std::string Parents::getPatronymic() const
{
	return this->patronymic;
}

void Parents::setPatronymic(const std::string& patronymic)
{
	this->patronymic = patronymic;
}

std::string Parents::getDegree() const
{
	return this->degree;
}

void Parents::setDegree(const std::string& degree)
{
	this->degree = degree;
}

std::string Parents::getAddress() const
{
	return this->address;
}

void Parents::setAddress(const std::string& address)
{
	this->address = address;
}