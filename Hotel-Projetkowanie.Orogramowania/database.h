#pragma once
#include <iostream>
#include <list>
#include "databaseEntry.h"

class Database  //Klasa abstrakcyjna Database
{
protected:
    std::string filename;   //nazwa pliku
    std::list<DatabaseEntry*> entries;  //lista instancji obiektów

    Database(){};

    DatabaseEntry* getEntry(std::string id) //zwraca rekord, je¿eli istnieje
    {
        for (DatabaseEntry* entry : this->entries)
        {
            if (entry->getID() == id)
                return entry;
        }

        return nullptr;
    }

public:
    virtual bool loadData() 
    { 
        //std::cout << "called loadData()\n"; 
        return false;
    }

    virtual bool saveData() 
    { 
        //std::cout << "called saveData()\n"; 
        return false;
    }

    virtual bool addEntry(DatabaseEntry* newEntry) 
    { 

        if (this->getEntry(newEntry->getID()))  //sprawdŸ czy takie ID ju¿ istnieje
            return false;
        else  //jez¿eli nie, mo¿esz dodaæ rekord
        {
            entries.push_back(newEntry);
            this->saveData();   //zaktualizuj plik
            return true;
        }
    }

    virtual bool deleteEntry(std::string id) 
    { 
        for (auto i = this->entries.begin(); i != this->entries.end(); i++)  //przejrzyj kazdy obiekt
        {
            if ((*i)->getID() == id)    //znaleziono cel
            {
                this->entries.erase(i);
                this->saveData();   //po usuniêciu, zaktualizuj plik
                return true;
            }
        }

        return false;
    }

    virtual bool editEntry(int id) 
    { 
        std::cout << "called editEntry()\n"; 
        return false;
    }

    virtual void getEntryInfo(int id) { std::cout << "called getEntryInfo()\n"; }
};


class RoomDatabase  : public Database
{
private:
    RoomDatabase() {}

public:
    static RoomDatabase& getInstance() //implementacja singletona
    {
        static RoomDatabase instance;
        return instance;
    }

    ~RoomDatabase() {}
};
