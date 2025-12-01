#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

#include "point.h"
#include "nuage.h"
#include "grille.h"
// #include "element.h"
class Grille;
class Point;
class Nuage;

using namespace std;

class InterfaceStrategieSurface {
public:
    virtual void tracerSurface(vector<shared_ptr<Point>> points, Grille& grille) const = 0;
    virtual ~InterfaceStrategieSurface() = default;
};

class SurfaceId : public InterfaceStrategieSurface {
public:
    void tracerSurface(vector<shared_ptr<Point>> points, Grille& grille) const override;
};

class SurfaceDistance : public InterfaceStrategieSurface {
public:
    void tracerSurface(vector<shared_ptr<Point>> points, Grille& grille) const override;
};

class Orthese {
private:
    Grille grille;
    shared_ptr<InterfaceStrategieSurface> strategie;
    vector<shared_ptr<Element>> elements;
    int idElement = 0;

public:

    Orthese(const string& ligne); 
    ~Orthese() = default;

    vector<shared_ptr<Element>> getElements() {
        return elements;
    }

    void setStrategie(shared_ptr<InterfaceStrategieSurface> nouvelleStrategie) {
        strategie = nouvelleStrategie;
    }
    
    // "a"
    void afficherInfo();
    
    // "o1" et "o2"
    void afficherAvecTransformation(function<string(Point&)> f);
    void afficherTexture();
    void afficherIndex();

    // "f", "d" et "s"
    void fusionnerPoints(const vector<int>& ids);
    
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
    void supprimerPoint(int id);
    void ajouterPoint(shared_ptr<Point> point, vector<shared_ptr<Nuage>> nuages);

    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void afficherSurface();
};