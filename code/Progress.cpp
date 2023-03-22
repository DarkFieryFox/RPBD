#include "Progress.h"

Progress::Progress()
{
}

Progress::~Progress()
{
}

long Progress::getId() const
{
	return this->id;
}

void Progress::setId(long id)
{
	this->id = id;
}

std::string Progress::getClasss() const
{
	return this->classs;
}

void Progress::setClasss(const std::string& classs)
{
	this->classs = classs;
}
std::string Progress::getSubject() const
{
	return this->subject;
}

void Progress::setSubject(const std::string& subject)
{
	this->subject = subject;
}

int Progress::getYear() const
{
	return this->year;
}
void Progress::setYear(int year)
{
	this->year = year;
}

int Progress::getYearly() const
{
	return this->yearly;
}
void Progress::setYearly(int yearly)
{
	this->yearly = yearly;
}

int Progress::getQuarter() const
{
	return this->quarter;
}
void Progress::setQuarter(int quarter)
{
	this->quarter = quarter;
}

int Progress::getHalf_yearly() const
{
	return this->half_yearly;
}
void Progress::setHalf_yearly(int half_yearly)
{
	this->half_yearly = half_yearly;
}

int Progress::getExam() const
{
	return this->exam;
}
void Progress::setExam(int exam)
{
	this->exam = exam;
}

int Progress::getFinaly() const
{
	return this->finaly;
}
void Progress::setFinaly(int finaly)
{
	this->finaly = finaly;
}