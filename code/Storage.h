#pragma once
#ifndef Storage_HEADER
#define Storage_HEADER
#include <map>
#include "Schoolchildren.h"
#include "Parents.h"

#include "Progress.h"

class Storage {
private:
	std::map<long, Schoolchildren> schoolchildren;
	std::map<long, Parents> parentss;

	std::map<long, Progress> progress;

	Storage();
	static Storage* storage;

public:
	Storage(Storage& other) = delete;
	void operator=(const Storage&) = delete;
	static Storage* getInstance();
	Schoolchildren* getSchoolchildren(long);
	Parents* getParents(long);

	Progress* getProgress(long);

	void putSchoolchildren(Schoolchildren &schoolchildren);
	void putParents(Parents &parentss);
	void putProgress(Progress &progress);
};

#endif