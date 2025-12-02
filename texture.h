#include "point.h"

class DecorateurTexture : public Point {
protected:
    shared_ptr<Point> point;

public:
    DecorateurTexture(shared_ptr<Point> point): point(point), Point(point->getId()) {}
    virtual ~DecorateurTexture() = default;

    int getX() const override {
        return point->getX();
    }

    int getY() const override {
        return point->getY();
    }

    string getTexture() const override {
        return "";
    }

    void afficherInfo() const override {
        cout << id << ":" << " (" << getX() << "," << getY() << ") texture: '"
            << getTexture() << "'\n";
    }

    void deplacerPoint(int id, int nouvelleX, int nouvelleY) override {
        point->deplacerPoint(id, nouvelleX, nouvelleY);
    }
};

class TextureO : public DecorateurTexture {
public:
    TextureO(shared_ptr<Point> point): DecorateurTexture(point) {}
    string getTexture() const override { return point->getTexture() + "o"; }
};

class TextureHash : public DecorateurTexture {
public:
    TextureHash(shared_ptr<Point> point): DecorateurTexture(point) {}
    string getTexture() const override { return point->getTexture() + "#"; }
};

class TextureDollar : public DecorateurTexture {
public:
    TextureDollar(shared_ptr<Point> point): DecorateurTexture(point) {}
    string getTexture() const override { return point->getTexture() + "$"; }
};