#include "affichage.h"
#include "point.h"
#include "orthese.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string args;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    
    vector<Point> points = creerPoints(args); //mettre dans le constructeur Orthese
    Orthese orthese(points);
    
    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
                  << "c1 - Créer les surfaces selon l'ordre des IDs\n"
                  << "c2 - Créer les surfaces selon la distance minimale\n"
                  << "q  - Quitter\n> ";
        getline(std::cin, cmd);

        if (cmd == "q") break;
        if (cmd == "d") {
            cout << "ID du point à déplacer: ";
            int id;
            cin >> id;
            cout << "Nouvelle position x y: ";
            int x, y;
            cin >> x >> y;
            orthese.deplacerPoint(id, x, y);
        }
        if (cmd == "s") {
            cout << "ID du point à supprimer: ";
            int id;
            cin >> id;
            orthese.supprimerPoint(id);
        }
        if (cmd == "f") {
            cout << "IDs des points à fusionner (séparés par des espaces): ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            vector<int> ids;
            int id;
            while (iss >> id) {
                ids.push_back(id);
            }
            orthese.fusionnerPoints(ids);
        }
        if (cmd == "a") {
            orthese.afficherInfo();
        }
        if (cmd == "o1") {
            orthese.afficherTexture();
        }
        if (cmd == "o2") {
            orthese.afficherIndex();
        }
        if (cmd == "c1") {
            SurfaceId strategieId;
            orthese.afficherSurface(strategieId);
        }
        if (cmd == "c2") {
            SurfaceDistance strategieDistance;
            orthese.afficherSurface(strategieDistance);
        }
    }

    return 0;
}