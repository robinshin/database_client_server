#include "Film.h"
#include "Video.h"
#include <iostream>
#include <string>

Film::Film(std::string fileName, std::string filePath, int numberOfChapters, int* tab) : Video(fileName, filePath, 0)
{
    this->numberOfChapters = numberOfChapters;

    for (int i = 0; i < numberOfChapters; i++)
        chapters[i] = tab[i];

    int duration = 0;
    for (int i = 0; i < numberOfChapters; i++)
        duration = duration + tab[i];

    this->setDuration(duration);
}

void Film::print(std::ostream& s)
{
    std::string text = "Name : " + this->getFileName() + ", path : " + this->getFilePath() + ", number of chapters : " + std::to_string(this->numberOfChapters);

    for (int i = 0; i < numberOfChapters; i++)
        text +=  "\n  "  + std::to_string(i+1) + ": " + std::to_string(chapters[i]) + " minutes";

    s << text << std::endl;
}


void Film::setChapters(const int* tab, int numberOfChapters)
{
    delete[] chapters;
    int* chapters = new int[numberOfChapters];
    this->numberOfChapters = numberOfChapters;

    for (int i = 0; i < numberOfChapters; i++)
        chapters[i] = tab[i];
}
