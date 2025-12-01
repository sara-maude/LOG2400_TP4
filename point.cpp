#include "point.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void PointConcret::afficherInfo() const {
    cout << id << ":" << " (" << x << "," << y << ") textures: '";
    cout << getTexture();
    cout << "'\n";
}

string PointConcret::getTexture() const {
    return "";
}

void PointConcret::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    x = nouvelleX;
    y = nouvelleY;
}