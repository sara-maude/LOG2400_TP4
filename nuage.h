#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "element.h"
#include "grille.h"
#include "texture.h"
class Grille;
class Point;
class DecorateurTexture;

using namespace std;

class Nuage: public Element {
private:
    vector<shared_ptr<Element>> elements;
    char texture;

    static vector<function<shared_ptr<Element>(shared_ptr<Point>)>> texturesDisponibles;
    static int compteur;

    // static vector avec les textures possibles pour plus de flexibilité
    // static vector<shared_ptr<DecorateurTexture>> texturesDisponibles;
    
public:
    Nuage(vector<shared_ptr<Element>>& elements, int id); 
    ~Nuage() = default;

    // void setTexture(char nouvelleTexture) {
    //     texture = nouvelleTexture;
    // }
    
    // "a"
    void afficherInfo() const override;

    // Supprime un point du nuage.
    void supprimerPoint(int id);
    void ajouterPoint(shared_ptr<Point> point);

    // Accès aux points contenus (pour réindexation depuis Orthese)
    vector<shared_ptr<Point>> getPoints();
    vector<shared_ptr<Element>> getElements();

    void ajouterTexture(int index);
};