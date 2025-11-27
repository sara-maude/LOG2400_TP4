#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "orthese.h"
#include "point.h"
// #include "element.h"
#include "affichage.h"
#include "grille.h"
class Grille;
class Point;
class DecorateurTexture;

using namespace std;

class Nuage {
private:
    vector<shared_ptr<Point>> points;
    shared_ptr<DecorateurTexture> texture;

    // static vector avec les textures possibles pour plus de flexibilité

public:
    Nuage(vector<shared_ptr<Point>>& points, int index); 
    ~Nuage() = default;
    
    // "a"
    void afficherInfo() const;

    // Supprime un point du nuage. Retourne true si un point a été supprimé.
    bool supprimerPoint(int id);

    // Accès aux points contenus (pour réindexation depuis Orthese)
    vector<shared_ptr<Point>>& getPoints() { return points; }
};