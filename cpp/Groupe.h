#ifndef GROUPE_H
#define GROUPE_H
#include <iostream>
#include <list>
#include <string>
#include "Multimedia.h"
#include <memory>

using namespace std;

typedef std::shared_ptr<Multimedia> MultimediaPtr;

class Groupe : public list<MultimediaPtr>
{
private :
    std::string name;
public :
    Groupe(std::string name);

    virtual inline std::string getName() const {return name;}
    virtual inline void setName(std::string name) {this->name = name;}
    virtual inline void addMedia(MultimediaPtr m) {this->push_back(m);}

    virtual void removeMedia(MultimediaPtr m);
    virtual void display(ostream& s) const;
};

#endif // GROUPE_H
