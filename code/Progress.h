#pragma once
#ifndef Progress_HEADER
#define Progress_HEADER
#include <iostream>
#include <sstream>
#include <string>

class Progress
{
private:
	long id;
	std::string classs;
	std::string subject;
	int yearly;
	int quarter;
	int finaly;
	int half_yearly;
	int exam;
	int year;

public:
	Progress();
	~Progress();

	long getId() const;
	void setId(long);

	std::string getClasss() const;
	void setClasss(const std::string& classs);

	std::string getSubject() const;
	void setSubject(const std::string& subject);

	int getYear() const;
	void setYear(int);

	int getQuarter() const;
	void setQuarter(int);

	int getHalf_yearly() const;
	void setHalf_yearly(int);

	int getYearly() const;
	void setYearly(int);

	int getExam() const;
	void setExam(int);

	int getFinaly() const;
	void setFinaly(int);

};

#endif