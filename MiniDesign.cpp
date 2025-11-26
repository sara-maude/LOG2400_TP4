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
    
    // Voici des fonctions utiles pour réaliser le TP. 
    // TODO: Il faudrait les placer dans des classes appropriées.
    vector<Point> points = creerPoints(args);
    Orthese orthese(points);
    
    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    vector<char> texturesNuages = {'o', '#', '$'};
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
    }

    return 0;
}