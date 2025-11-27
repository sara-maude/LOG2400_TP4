#include "nuage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Nuage::Nuage(vector<shared_ptr<Point>>& points, int index) : points(points) {
    switch (index % 3) {
        case 0: texture = make_shared<TextureO>(); break;
        case 1: texture = make_shared<TextureHash>(); break;
        case 2: texture = make_shared<TextureDollar>(); break;
    }

    for (shared_ptr<Point>& point : points) {
        point->ajouterTexture(texture);
    }
}

void Nuage::afficherInfo() const {
    cout << "Nuage '" << texture->getTexture() << "' contient les points: ";
    for (shared_ptr<Point> point : points) {
        cout << point->getId() << " ";
    }
    cout << '\n';
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