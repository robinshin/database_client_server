#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>
#include <fstream>

class Multimedia
{
protected:
    std::string fileName, filePath;

public:
    Multimedia();
    Multimedia(std::string fileName, std::string filePath);

    virtual ~Multimedia() {}
    virtual void setFileName(std::string fileName);
    virtual void setFilePath(std::string filePath);
    virtual std::string getFileName();
    virtual std::string getFilePath();
    virtual void print(std::ostream& s);
    virtual void play() = 0;
    virtual void write(std::ofstream& f) = 0;
};

#endif // MULTIMEDIA_H
