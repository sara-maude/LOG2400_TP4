#include "nuage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
int Nuage::compteur = 0;

Nuage::Nuage(vector<shared_ptr<Element>>& nouveauxElements, int id) : elements(nouveauxElements), Element(id) {
    int index = compteur++;
    ajouterTexture(index);
    texture = getPoints()[0]->getTexture().back();
}

void Nuage::afficherInfo() const {
    cout << id << ": Nuage '" << texture << "' contient les elements:";
    int taille = elements.size();
    for (int i = 0; i < taille; ++i) {
        cout << " " << elements[i]->getId();
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

    for (shared_ptr<Element>& element : elements) {
        if (shared_ptr<Point> point = dynamic_pointer_cast<Point>(element)) {
            pointsDuNuage.push_back(point);
        } else if (shared_ptr<Nuage> nuage = dynamic_pointer_cast<Nuage>(element)) {
            auto pointsRec = nuage->getPoints();
            pointsDuNuage.insert(pointsDuNuage.end(), pointsRec.begin(), pointsRec.end());
        }
    }

    return pointsDuNuage;
}

vector<shared_ptr<Element>> Nuage::getElements() {
    return elements;
}

void Nuage::ajouterTexture(int index) {
    auto appliquerTexture = texturesDisponibles[index % texturesDisponibles.size()];
    for (shared_ptr<Element>& element: elements) {
        if (shared_ptr<Point> point = dynamic_pointer_cast<Point>(element)) {
            element = appliquerTexture(point);
        } else {
            shared_ptr<Nuage> nuage = dynamic_pointer_cast<Nuage>(element);
            nuage->ajouterTexture(index);
        }
    }
}

vector<function<shared_ptr<Element>(shared_ptr<Point>)>> Nuage::texturesDisponibles = {
    [](shared_ptr<Point> point){ return make_shared<TextureO>(point); },
    [](shared_ptr<Point> point){ return make_shared<TextureHash>(point); },
    [](shared_ptr<Point> point){ return make_shared<TextureDollar>(point); }
};