#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "grille.h"
#include "point.h"
#include "nuage.h"
#include "element.h"
#include "affichage.h"
class Grille;
class Point;
class Nuage;

using namespace std;

class InterfaceStrategieSurface {
public:
    virtual void tracerSurface(vector<shared_ptr<Point>>& points, Grille& grille) const = 0;
    virtual ~InterfaceStrategieSurface() = default;
};

class SurfaceId : public InterfaceStrategieSurface {
public:
    void tracerSurface(vector<shared_ptr<Point>>& points, Grille& grille) const override;
};

class SurfaceDistance : public InterfaceStrategieSurface {
public:
    void tracerSurface(vector<shared_ptr<Point>>& points, Grille& grille) const override;
};

class Orthese {
private:
    vector<shared_ptr<Point>> points;
    vector<unique_ptr<Nuage>> nuages;
    Grille grille;
    int prochainIdNuage = 0;

public:
    Orthese(vector<Point>& points); 
    ~Orthese() = default;
    
    // "a"
    void afficherInfo();
    
    // "o1" et "o2"
    void afficherAvecTransformation(function<vector<char>(const Point&)> f);
    void afficherTexture();
    void afficherIndex();

    // "f", "d" et "s"
    void fusionnerPoints(vector<int> ids);
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
    void supprimerPoint(int id);

    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void afficherSurface(const InterfaceStrategieSurface& strategie);
};