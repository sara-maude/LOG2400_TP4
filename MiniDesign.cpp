// #include "affichage.h"
#include "point.h"
#include "nuage.h"
#include "orthese.h"
#include "commande.h"
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
    
    Orthese orthese(args);
    GestionCommande gestionnaire;

    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points/nuages dans un nouveau nuage\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
                  << "u  - Annuler la dernière commande (undo)\n"
                  << "r  - Réappliquer la dernière commande annulée (redo)\n"
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
            if (id > orthese.getElements().size() - 1) {
                cout << "Le id est invalide\n";
            } else if (dynamic_pointer_cast<Nuage>(orthese.getElements()[id])) {
                cout << "Il est impossible de deplacer un nuage\n";
            } else {
                shared_ptr<CommandeDeplacement> deplacement = make_shared<CommandeDeplacement>(orthese, id, x, y);
                gestionnaire.setCommande(deplacement);
                gestionnaire.executer();
            }
        }
        if (cmd == "s") {
            cout << "ID du point à supprimer: ";
            int id;
            cin >> id;
            if (id > orthese.getElements().size() - 1) {
                cout << "Le id est invalide\n";
            } else if (dynamic_pointer_cast<Nuage>(orthese.getElements()[id])) {
                cout << "Il est impossible de supprimer un nuage\n";
            } else {
                shared_ptr<CommandeSupression> supression = make_shared<CommandeSupression>(orthese, id);
                gestionnaire.setCommande(supression);
                gestionnaire.executer();
            }
        }
        if (cmd == "u") {
            gestionnaire.annuler();
        }
        if (cmd == "r") {
            gestionnaire.remettre();
        }
        if (cmd == "f") {
            cout << "IDs des points ou nuages à fusionner (ex: 0 1 2): ";
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
            shared_ptr<SurfaceId> strategieId = make_shared<SurfaceId>();
            orthese.setStrategie(strategieId);
            orthese.tracerSurface();
        }
        if (cmd == "c2") {
            shared_ptr<SurfaceDistance> strategieDistance = make_shared<SurfaceDistance>();
            orthese.setStrategie(strategieDistance);
            orthese.tracerSurface();
        }
    }

    return 0;
}