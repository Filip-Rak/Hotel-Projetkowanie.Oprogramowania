#pragma once
#include <iostream>
#include <list>
#include "databaseEntry.h"

std::string path = "";

class Database  //Klasa abstrakcyjna Database
{
protected:
    std::string filename;   //nazwa pliku
    std::list<DatabaseEntry*> entries;  //lista instancji obiektów

    Database(){};

public:
    virtual bool loadData()  //wczytuje dane z pliku
    { 
        //std::cout << "called loadData()\n"; 
        return false;
    }  

    virtual bool saveData()     //zapisuje dane do pliku
    { 
        //std::cout << "called saveData()\n"; 
        return false;
    } 

    bool addEntry(DatabaseEntry* newEntry) 
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

    bool deleteEntry(std::string id) 
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

    bool editEntry(DatabaseEntry* newEntry) 
    { 
        DatabaseEntry* previous = this->getEntry(newEntry->getID());
        if (previous)
        {
            *previous = *newEntry;
            this->saveData();
            return true;
        }
        
        return false;
    }

    DatabaseEntry* getEntry(std::string id) //zwraca rekord, je¿eli istnieje
    {
        for (DatabaseEntry* entry : this->entries)
        {
            if (entry->getID() == id)
                return entry;
        }

        return nullptr;
    }
};

class RoomDatabase  : public Database
{
private:
    RoomDatabase() { this->filename = path + "rooms.txt"; }

public:
    static RoomDatabase& getInstance() //implementacja singletona
    {
        static RoomDatabase instance;
        return instance;
    }

    ~RoomDatabase() {}
};
