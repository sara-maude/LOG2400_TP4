#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "orthese.h"
#include "point.h"
#include "element.h"
// #include "affichage.h"
#include "grille.h"
class Grille;
class Point;
class DecorateurTexture;

using namespace std;

class Nuage: public Element {
private:
    static int compteur;
    vector<shared_ptr<Element>> elements;
    shared_ptr<DecorateurTexture> texture;

    // static vector avec les textures possibles pour plus de flexibilité
    static vector<shared_ptr<DecorateurTexture>> texturesDisponibles;

public:
    Nuage(vector<shared_ptr<Element>>& elements); 
    ~Nuage() = default;

    // static void ajouterChoixTexture(shared_ptr<DecorateurTexture> decor);
    
    // "a"
    void afficherInfo() const;

    // Supprime un point du nuage.
    void supprimerPoint(int id);
    void ajouterPoint(shared_ptr<Point> point);

    // Accès aux points contenus (pour réindexation depuis Orthese)
    vector<shared_ptr<Point>> getPoints();
    vector<shared_ptr<Element>> getElements();

    void ajouterTexture(shared_ptr<DecorateurTexture> decor) override;
};