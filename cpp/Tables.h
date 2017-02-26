#ifndef TABLES_H
#define TABLES_H
#include "Multimedia.h"
#include "Video.h"
#include "Photo.h"
#include "Groupe.h"
#include "Film.h"
#include <map>
#include <iostream>
#include <memory>

using namespace std;
typedef std::shared_ptr<Multimedia> MultimediaPtr;
typedef std::shared_ptr<Groupe> GroupePtr;

class Tables
{
private:
    std::map<std::string, MultimediaPtr> tableMultimedia;
    std::map<std::string, GroupePtr> tableGroupe;

public:
    Tables();
    virtual ~Tables();

    virtual inline std::map<std::string, MultimediaPtr> getTableMultimedia() const {return tableMultimedia;}
    virtual inline std::map<std::string, GroupePtr> getTableGroupe() const {return tableGroupe;}

    virtual MultimediaPtr createPhoto(std::string fileName, std::string filePath, long width, long height);
    virtual MultimediaPtr createVideo(std::string fileName, std::string filePath, int duration);
    virtual MultimediaPtr createFilm(std::string fileName, std::string filePath, int numberOfChapters, int* tab);
    virtual GroupePtr createGroupe(std::string name);

    virtual void deleteMultimediaItem(std::string name);
    virtual void deleteGroupeItem(std::string name);

    virtual bool findItem(std::string name);

    virtual void play(std::string name);
};

#endif // TABLES_H
