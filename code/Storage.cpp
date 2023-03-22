#include "Storage.h"

Storage* Storage::storage;

Storage::Storage()
{
}


Storage* Storage::getInstance()
{
	if (storage == nullptr) {
		storage = new Storage();
	}
	return storage;

}


Schoolchildren* Storage::getSchoolchildren(long id)
{
	return &(this->schoolchildren.find(id)->second);
}

Parents* Storage::getParents(long id)
{
	return &(this->parentss.find(id)->second);
}


Progress* Storage::getProgress(long id)
{
	return &(this->progress.find(id)->second);
}


void Storage::putSchoolchildren(Schoolchildren &schoolchildren)
{
	auto it = this->schoolchildren.find(schoolchildren.getId());
	if (it == this->schoolchildren.end()) {
		this->schoolchildren[schoolchildren.getId()] = schoolchildren;
		return;
	}
	auto& m = it->second;
	m.setName(schoolchildren.getName());
}

void Storage::putParents(Parents &parentss)
{
	auto it = this->parentss.find(parentss.getId());
	if (it == this->parentss.end()) {
		this->parentss[parentss.getId()] = parentss;
		return;
	}
	auto& m = it->second;
	m.setName(parentss.getName());

}


void Storage::putProgress(Progress &progress)
{
	auto it = this->progress.find(progress.getId());
	if (it == this->progress.end()) {
		this->progress[progress.getId()] = progress;
		return;
	}
	it->second.setClasss(progress.getClasss());

}
