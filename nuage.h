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
    
public:
    Nuage(vector<shared_ptr<Element>>& elements, int id); 
    ~Nuage() = default;

    void afficherInfo() const override;

    void supprimerPoint(int id);
    void ajouterPoint(shared_ptr<Point> point);

    vector<shared_ptr<Point>> getPoints();
    vector<shared_ptr<Element>> getElements();

    void ajouterTexture(int index);
};