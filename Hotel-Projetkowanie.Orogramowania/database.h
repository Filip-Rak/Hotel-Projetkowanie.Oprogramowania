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

    virtual ~Database() //destruktor usuwa obiekty listy i liste
    {
        for (DatabaseEntry* pointer : this->entries)
            delete pointer;

        this->entries.clear();
    }

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
        else  //je¿eli nie, mo¿esz dodaæ rekord
        {
            entries.push_back(newEntry);
            this->saveData();   //zaktualizuj plik
            return true;
        }
    }

    bool deleteEntry(std::string id)
    {
        for (auto i = this->entries.begin(); i != this->entries.end(); )  //przejdŸ przez wszystkie obiekty
        {
            if ((*i)->getID() == id)    //Znaleziono cel
            {
                delete *i;  //usuñ obiekt na wskaŸniku
                i = this->entries.erase(i);  //usuñ element listy
                this->saveData();   //zaktualizuj plik
                return true;
            }
            else
                ++i;  //zinkrementuj, je¿eli nic nie usuniêto
            
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
};
