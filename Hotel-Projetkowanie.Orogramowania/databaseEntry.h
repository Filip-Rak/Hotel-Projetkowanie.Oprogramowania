#pragma once
#include <iostream>

class DatabaseEntry
{
	std::string id;
public:
	void setID(std::string id) { this->id = id; }
	std::string getID() { return this->id; }
};

class Room : public DatabaseEntry
{
public:
	using DatabaseEntry::setID;
	using DatabaseEntry::getID;
};