#ifndef VIDEO_H
#define VIDEO_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Multimedia.h"

using namespace std;

class Video : public Multimedia
{
private:
    int duration = 0;

public:
    Video(std::string fileName, std::string filePath, int duration) : Multimedia(fileName, filePath), duration(duration) {}

    virtual void setDuration(long duration) {this->duration = duration;}
    virtual long getDuration() {return duration;}
    virtual void print(std::ostream& s) override {s << this->getFileName() <<' '<< this->getFilePath() <<' '<< this->duration << std::endl;}
    virtual void play() override {system(("mpv " + this->getFilePath() + this->getFileName() + " &").c_str());}
        
    void write(std::ofstream& f) override {f << "Video" <<" " << this->fileName << " " << this->filePath << " " << this->duration << "\n";}
};

#endif // VIDEO_H
