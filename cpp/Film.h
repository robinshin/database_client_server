#ifndef FILM_H
#define FILM_H
#include "Video.h"
#include <fstream>
#include <iostream>

using namespace std;

class Film : public Video
{
private:
    int numberOfChapters = 0;
    int* chapters = new int[numberOfChapters];

public:
    Film(std::string fileName, std::string filePath, int numberOfChapters, int* tab);

    virtual ~Film() {delete [] chapters;}


    virtual int getNumberOfChapters() const {return this->numberOfChapters;}
    virtual int* getChapters() const {return this->chapters;}
    virtual void setChapters(const int* tab, int numberOfChapters);

    virtual void print(std::ostream& s) override;

    void write(std::ofstream& f) override {f << "Film" << " " << this->fileName << " " << this->filePath << " " << this->numberOfChapters << "\n";}
};

#endif // FILM_H
