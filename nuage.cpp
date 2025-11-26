#include "nuage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void Nuage::afficherInfo() const {
    cout << "Nuage '" << points[0]->getTexture() << "' contient les points: ";
    for (const auto& point : points) {
        cout << point->getId() << " ";
    }
}

void Nuage::afficher() const {
    for (const auto& point : points) {
        point->afficher();
    }
}

void Nuage::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    for (const auto& point : points) {
        if (point->getId() == id) {
            point->deplacerPoint(id, nouvelleX, nouvelleY);
            return;
        }
    }
}

bool Nuage::supprimerPoint(int id) {
    for (auto it = points.begin(); it != points.end(); ++it) {
        if ((*it)->getId() == id) {
            points.erase(it);
            return true;
        }
    }
    return false;
}

void Nuage::afficherLigne() {
    grille.imprimerTraceOrdreId();
    grille.afficherGrille();
}