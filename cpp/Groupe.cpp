#include "Groupe.h"

Groupe::Groupe(std::string name)
{
    this->name = name;
}

void Groupe::removeMedia(MultimediaPtr m) {
    for (list<MultimediaPtr>::iterator iterator = begin(); iterator != end(); iterator++)
        if ((*iterator)->getFileName() == m->getFileName())
            erase(iterator);
}

void Groupe::display(ostream &s) const {
    for (list<MultimediaPtr>::const_iterator iterator = begin(); iterator != end(); iterator++)
        (*iterator)->print(s);

}
