#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include <string>
#include <fstream>
#include "Multimedia.h"

using namespace std;

class Photo : public Multimedia
{
private:
    long width = 0, height = 0;
    
public:
    Photo(std::string fileName, std::string filePath, long width, long height) : Multimedia(fileName, filePath), width(width), height(height) {}
    
    virtual void setWidth(long width) {this->width = width;}
    virtual void setHeight(long height) {this->height = height;}
    virtual long getWidth() {return width;}
    virtual long getHeight() {return height;}
    void print(std::ostream& s) override {s << this->getFileName() <<' '<< this->getFilePath() <<' '<< this->width <<' '<< this->height << std::endl;}
    void play() override {system(("imagej " + this->getFilePath() + this->getFileName() + " &").c_str());}
    void write(std::ofstream& f) override {f << "Photo" << " " << this->fileName << " " << this->filePath << " " << this->width << " " << this->height << "\n";}
};
        
#endif // PHOTO_H
