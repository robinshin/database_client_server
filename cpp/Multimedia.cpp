#include "Multimedia.h"
#include <iostream>
using namespace std;

Multimedia::Multimedia()
{
    this->fileName = "default";
    this->filePath = "";
}

Multimedia::Multimedia(string fileName, string filePath) {
    this->fileName = fileName;
    this->filePath = filePath;
}

void Multimedia::setFileName(string fileName) {
    this->fileName = fileName;
}

void Multimedia::setFilePath(string filePath) {
    this->filePath = filePath;
}

string Multimedia::getFileName() {
    return fileName;
}

string Multimedia::getFilePath() {
    return filePath;
}

void Multimedia::print(ostream& s) {
    s << this->fileName <<' '<< this->filePath << endl;
}
