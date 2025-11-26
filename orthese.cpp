#include "orthese.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

Orthese::Orthese(vector<Point>& points) : grille(points){
        for (const Point& p : points) {
            elements.push_back(make_shared<Point>(p));
        }
}

void Orthese::afficherInfo() const {
    for (const auto& element : elements) {
        element->afficherInfo();
    }
}

void Orthese::afficher() const {
    for (const auto& element : elements) {
        element->afficher();
    }
}

void Orthese::fusionnerPoints(vector<int> ids) {
    vector<shared_ptr<Point>> pointsAAjouter;

    for (int id : ids) {
        for (auto& element : elements) {
            if (element->getId() == id) {
                auto point = dynamic_pointer_cast<Point>(element);
                pointsAAjouter.push_back(point);
                break;
            }
        }
    }

    if (!pointsAAjouter.empty()) {
        auto nuage = make_shared<Nuage>(pointsAAjouter, grille);
        elements.push_back(nuage);
    }
}

void Orthese::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    for (auto element : elements) {
        if (element->getId() == id) {
            element->deplacerPoint(id, nouvelleX, nouvelleY);
            return;
        }
    }
    cout << "Point avec ID " << id << " non trouvé.\n";
}

void Orthese::supprimerPoint(int id) {
    bool trouve = false;

    // Supprimer le point global
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        if ((*it)->getId() == id) {
            elements.erase(it);
            trouve = true;
            break;
        }
    }

    // Supprimer le point dans tous les Nuages
    for (auto& element : elements) {
        if (element->getId() == -1) { // c'est un Nuage
            auto nuage = dynamic_pointer_cast<Nuage>(element);
            if (nuage) {
                nuage->supprimerPoint(id);
            }
        }
    }

    if (!trouve) {
        cout << "Point avec ID " << id << " non trouvé.\n";
    }

    // Mettre à jour les IDs restants
    for (auto& element : elements) {
        if (element->getId() > id) {
            auto point = dynamic_pointer_cast<Point>(element);
            if (point) point->setId(point->getId() - 1);
        }
    }
}


void Orthese::afficherLigne() {
    grille.imprimerTraceOrdreId();
    grille.afficherGrille();
}