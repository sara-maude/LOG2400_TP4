#include "point.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void Point::afficherInfo() const {
    cout << id << ":" << " (" << x << "," << y << ") textures: '";
    for (const shared_ptr<DecorateurTexture>& decor : textures) {
        cout << decor->getTexture();
    }
    cout << "'\n";
}

vector<char> Point::getTexture() const {
    vector<char> texturesAfficher;
    if (textures.empty()) {
        texturesAfficher.push_back('.');
        return texturesAfficher;
    }
    for (const shared_ptr<DecorateurTexture>& decor : textures) {
        texturesAfficher.push_back(decor->getTexture());
    }
    return texturesAfficher;
}

void Point::ajouterTexture(shared_ptr<DecorateurTexture> decor) {
    textures.push_back(decor);
}

void Point::retirerTexture(shared_ptr<DecorateurTexture> decor) {
    auto it = find(textures.begin(), textures.end(), decor);
    if (it != textures.end()) textures.erase(it);
}

void Point::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    x = nouvelleX;
    y = nouvelleY;
}