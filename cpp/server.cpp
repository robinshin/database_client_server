//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "Tables.h"
using namespace std;
using namespace cppu;

const int PORT = 3331;

class MyBase {
private:
    Tables* table;
public:
    
    MyBase() {
        table = new Tables(); // Initialisation de la table
    }
    
    ~MyBase() {delete table;}
    
    
    bool processRequest(TCPConnection& cnx, const std::string& request, std::string& response)
    {
        std::stringstream stream(request);
        std::string type; // Type de la requête
        stream >> type; // On lit le type de la requête pour savoir si on modifie les données de la table
        
        //// Vérification que le type de la requête existe
        if ((type != "Ajouter") && (type != "Supprimer") && (type != "Rechercher") && (type != "Jouer")) {
            response = "Erreur : requête inconnue (ou mauvaise syntaxe).";
            return true;
        }
        
        bool isChangedTable = false; // Indicateur de modification des données de la table
        
        if ((type == "Ajouter") || (type == "Supprimer"))
            isChangedTable = true;
        
        // Gestion du verrou
        TCPLock lock(cnx, isChangedTable);
        
        
        std::string fileName = ""; //Nom du fichier
        std::string filePath = ""; //Chemin du fichier
        std::string fileType = ""; //Type de fichier
        
        if (type == "Ajouter") {
            stream >> fileType >> fileName;
            //On teste si le nom entré est déjà utilisé
            for (auto iterator : table->getTableMultimedia())
                if (get<1>(iterator)->getFileName() == fileName) {
                    response = "Erreur : nom de fichier déjà utilisé.";
                    return true;
                }
            
            if (fileType == "Photo") {
                long width = 0, height = 0;
                stream >> filePath >> width >> height;
                table->createPhoto(fileName, filePath, width, height);
                
                response = "OK : photo ajoutée.";
            }
            else if (fileType == "Video") {
                int duration = 0;
                stream >> filePath >> duration;
                table->createVideo(fileName, filePath, duration);
                response = "OK : vidéo ajoutée.";
            }
            
            else if (fileType == "Film") {
                int numberOfChapters;
                stream >> filePath >> numberOfChapters;
                int* chapters = new int[numberOfChapters];
                for (int i = 0 ; i < numberOfChapters; i++)
                    stream >> chapters[i];
                table->createFilm(fileName, filePath, numberOfChapters, chapters);
                response = "OK : film ajouté.";
            }
            
            else if (fileType == "Groupe") {
                table->createGroupe(fileName);
                response = "OK : groupe ajouté.";
            }
            
            else
                response = "Erreur : type de média inconnu.";
        }
        
        else if (type == "Supprimer") {
            stream >> fileType;
            
            if ((fileType == "Photo") || (fileType == "Video") || (fileType == "Film")) {
                stream >> fileName;
                table->deleteMultimediaItem(fileName);
                response = "OK : " + fileName + " a été effacé.";
            }
            
            else if (fileType == "Groupe") {
                stream >> fileName;
                table->deleteGroupeItem(fileName);
                response = "OK : " + fileName + " a été effacé.";
            }
            
            else
                response = "Erreur : type de média inconnu.";
        }
        
        else if (type == "Rechercher") {
            stream >> fileName;
            bool isFound = table->findItem(fileName);
            
            if (isFound)
                response = "OK : trouvé.";
            
            else
                response = "Erreur : non trouvé.";
        }
        
        else if (type ==  "Jouer") {
            stream >> fileName;
            bool hasBeenFound = table->findItem(fileName);
            if (hasBeenFound) {
            table->play(fileName);
            response = "OK : " + fileName + " a été joué.";
            }
        }
        
        else
            response = "Erreur : requête inconnue (ou mauvaise syntaxe).";
        
        return true;
    }
};


int main(int argc, char* argv[])
{
    // cree le TCPServer
    shared_ptr<TCPServer> server(new TCPServer());
    
    // cree l'objet qui gère les données
    shared_ptr<MyBase> base(new MyBase());
    
    // le serveur appelera cette méthode chaque fois qu'il y a une requête
    server->setCallback(*base, &MyBase::processRequest);
    
    // lance la boucle infinie du serveur
    cout << "Starting Server on port " << PORT << endl;
    int status = server->run(PORT);
    
    // en cas d'erreur
    if (status < 0) {
        cerr << "Could not start Server on port " << PORT << endl;
        return 1;
    }
    
    return 0;
}

