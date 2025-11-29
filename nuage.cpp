#include "nuage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int Nuage::compteur = 0;

Nuage::Nuage(vector<shared_ptr<Element>>& elements) : elements(elements) {
    texture = texturesDisponibles[compteur++ % texturesDisponibles.size()];

    ajouterTexture(texture);
}

// void Nuage::ajouterChoixTexture(shared_ptr<DecorateurTexture> decor) {
//     texturesDisponibles.push_back(decor);
// }

void Nuage::afficherInfo() const {
    cout << id << ": Nuage '" << texture->getTexture() << "' contient les points: ";
    int taille = elements.size();
    for (int i = 0; i < taille; ++i) {
        cout << elements[i]->getId();
        if (i < taille - 1) {
            cout << ", ";
        }
    }
    cout << '\n';
}

void Nuage::supprimerPoint(int id) {
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        if ((*it)->getId() == id) {
            elements.erase(it);
            return;
        }
    }
}

void Nuage::ajouterPoint(shared_ptr<Point> point) {
    int pointId = point->getId();
    int posPoint = -1;

    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->getId() > pointId) {
            posPoint = i;
            break;
        }
    }
    if (posPoint == -1) {
        posPoint = elements.size();
    }

    elements.insert(elements.begin() + posPoint, point);
}

vector<shared_ptr<Point>> Nuage::getPoints() {
    vector<shared_ptr<Point>> pointsDuNuage;

    for (shared_ptr<Element>& e : elements) {
        if (auto p = dynamic_pointer_cast<Point>(e)) {
            pointsDuNuage.push_back(p);
        } else if (auto n = dynamic_pointer_cast<Nuage>(e)) {
            auto pointsRec = n->getPoints();
            pointsDuNuage.insert(pointsDuNuage.end(), pointsRec.begin(), pointsRec.end());
        }
    }

    return pointsDuNuage;
}

vector<shared_ptr<Element>> Nuage::getElements() {
    return elements;
}

void Nuage::ajouterTexture(shared_ptr<DecorateurTexture> decor) {
    for (shared_ptr<Element>& p : elements)
        p->ajouterTexture(decor);
}

vector<shared_ptr<DecorateurTexture>> Nuage::texturesDisponibles = {
    make_shared<TextureO>(),
    make_shared<TextureHash>(),
    make_shared<TextureDollar>(),
    make_shared<TextureStar>()
};