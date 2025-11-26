#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "element.h"
#include "affichage.h"

using namespace std;

class Point: public Element {
private:
    int x, y;
    int id;
    char texture = ' ';
public:
    Point(int x, int y, int id) : x(x), y(y), id(id) {}; 
    Point(const Point& other) = default;
    ~Point() = default;
    int getId() const override { return id; }
    int getX() const { return x; }
    int getY() const { return y; }
    char getTexture() const { return texture; }
    void setId(int nouvelId) { id = nouvelId; }
    
    // "a"
    void afficherInfo() const override;

    // "f", "d" et "s"
    void deplacerPoint(int id, int nouvelleX, int nouvelleY) override;
    void supprimerPoint(int id);

    // "o1" et "o2"
    void afficher() const override {
        cout << id << ":" << " (" << x << "," << y << ") textures: " << texture << "\n ";
    }
    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void afficherLigne() override {
        // Implémentation vide pour Point
    }
};

// Classe abstraite pour le décorateur
class DecorateurTexture {
public:
    virtual char getTexture() const = 0;
    virtual ~DecorateurTexture() = default;
};

// Décorateurs concrets
class TextureO : public DecorateurTexture {
public:
    char getTexture() const override { return 'o'; }
};

class TextureHash : public DecorateurTexture {
public:
    char getTexture() const override { return '#'; }
};

class TextureDollar : public DecorateurTexture {
public:
    char getTexture() const override { return '$'; }
};