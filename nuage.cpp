#include "nuage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Nuage::Nuage(vector<shared_ptr<Point>>& points, int index) : points(points) {
    texture = texturesDisponibles[index % texturesDisponibles.size()];

    for (auto& p : points)
        p->ajouterTexture(texture);
}

void Nuage::ajouterTextures(shared_ptr<DecorateurTexture> decor) {
    texturesDisponibles.push_back(decor);
}

void Nuage::afficherInfo() const {
    cout << "Nuage '" << texture->getTexture() << "' contient les points: ";
    for (int i = 0; i < points.size(); ++i) {
        cout << points[i]->getId();
        if (i < points.size() - 1) {
            cout << ", ";
        }
    }
    cout << '\n';
}

void Nuage::supprimerPoint(int id) {
    for (auto it = points.begin(); it != points.end(); ++it) {
        if ((*it)->getId() == id) {
            points.erase(it);
        }
    }
}