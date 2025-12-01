#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "element.h"

using namespace std;

class Point: public Element {
public:
    Point(int id): Element(id) {}
    virtual ~Point() = default;

    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual string getTexture() const = 0;

    virtual void afficherInfo() const = 0;
    virtual void deplacerPoint(int id, int nouvelleX, int nouvelleY) = 0;
};

class PointConcret: public Point {
private:
    int x, y;

public:
    PointConcret(int x, int y, int id) : x(x), y(y), Point(id) {}; 
    PointConcret(const PointConcret& other) = default;
    ~PointConcret() = default;
    int getX() const override { return x; }
    int getY() const override { return y; }

    string getTexture() const override;
    
    // "a"
    void afficherInfo() const override;

    // "f", "d" et "s"
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
};