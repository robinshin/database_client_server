#include "Tables.h"
#include <sstream>
#include <iostream>
#include <fstream>

Tables::Tables()
{
    std::ifstream is;
    filebuf* fileBufferer = is.rdbuf();
    try {
        fileBufferer->open("tables.txt", std::ios::in);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Erreur dans l'ouverture/la lecture/la fermeture du fichier\n";
    }

    std::istream f(fileBufferer);
    std::string fileType = "";
    std::string fileName = "";
    std::string filePath = "";

    f >> fileType;
    while(f.good()) {
        if (fileType == "Photo") {
            double width = 0, height = 0;
            f >> fileName >> filePath >> width >> height;
            this->createPhoto(fileName, filePath, width, height);
        }
        
        else if (fileType == "Video") {
            int duration = 0;
            f >> fileName >> filePath >> duration;
            this->createVideo(fileName, filePath, duration);
        }
        
        else if (fileType == "Film") {
            int numberOfChapters;
            f >> fileName >> filePath >> numberOfChapters;
            this->createFilm(fileName, filePath, numberOfChapters, new int[numberOfChapters]);
        }
        getline(f, fileType);
        f >> fileType;
    }
    fileBufferer->close();
    std::cout << "La table a été crée à partir du fichier tables.txt" << endl;
}

Tables::~Tables() {
    std::ofstream textFile("tables.txt", ios::out | ios::trunc);

    if (textFile) {
        for (auto iterator : tableMultimedia) {
            MultimediaPtr pointeur = get<1>(iterator);
            pointeur->write(textFile);
        }
        textFile.close();
        cout << "La table a été sauvegardée dans le fichier tables.txt" << endl;
    }
    else {
        std::cerr << "Erreur dans l'ouverture/la lecture/la fermeture du fichier\n";
    }
}

MultimediaPtr Tables::createPhoto(std::string fileName, std::string filePath, long width, long height) {
    MultimediaPtr photo(new Photo(fileName, filePath, width, height));
    tableMultimedia[fileName] = photo;
    return photo;
}

MultimediaPtr Tables::createVideo(std::string fileName, std::string filePath, int duration) {
    MultimediaPtr video(new Video(fileName, filePath, duration));
    tableMultimedia[fileName] = video;
    return video;
}

MultimediaPtr Tables::createFilm(std::string fileName, std::string filePath, int numberOfChapters, int* tab) {
    MultimediaPtr film(new Film(fileName, filePath, numberOfChapters, tab));
    tableMultimedia[fileName] = film;
    return film;
}

GroupePtr Tables::createGroupe(std::string name) {
    GroupePtr groupe(new Groupe(name));
    tableGroupe[name] = groupe;
    return groupe;
}

void Tables::deleteMultimediaItem(std::string name) {
    tableMultimedia.erase(name);
}

void Tables::deleteGroupeItem(std::string name) {
    tableGroupe.erase(name);
}

bool Tables::findItem(std::string name) {
    bool isFound = false;
    auto searchMultimedia = tableMultimedia.find(name);
    if (searchMultimedia != tableMultimedia.end()) {
        std::cout << "Found : " << '\n';
        searchMultimedia->second->print(std::cout);
        isFound = true;
    }
    else {
        auto searchGroupe = tableGroupe.find(name);
        if (searchGroupe != tableGroupe.end()) {
            std::cout << "Found : " << '\n' << "Nom du groupe : " << searchGroupe->second->getName() << '\n' << "Le groupe contient : " << '\n';
            searchGroupe->second->display(std::cout);
            isFound = true;
        }
        else
            cout << "Not found" << '\n';
    }
    return isFound;
}

void Tables::play(std::string name) {
    auto searchMultimedia = tableMultimedia.find(name);
    if (searchMultimedia != tableMultimedia.end())
        searchMultimedia->second->play();
    else {
        auto searchGroupe = tableGroupe.find(name);
        if (searchGroupe != tableGroupe.end()) {
            std::cout << "Error : item is a group" << '\n';
        }
        else
            std::cout << "Item can't be found" << '\n';
    }
}
