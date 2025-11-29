#pragma once
#include <memory>
#include <vector>
#include "orthese.h"

// class Orthese;
// class Point;

using namespace std;

class Commande {
public:
    virtual ~Commande() = default;
    virtual void executer() const = 0;
    virtual void annuler() const = 0;
};

class CommandeSupression: public Commande {
private:
    Orthese& orthese;
    int id;
    shared_ptr<Point> ancienPoint;
    vector<shared_ptr<Nuage>> nuagesContenantPoint;
public:
    CommandeSupression(Orthese& orthese, int id);
    ~CommandeSupression() = default;

    void executer() const override;
    void annuler() const override;
};

class CommandeDeplacement: public Commande {
private:
    Orthese& orthese;
    int id;
    int ancienX, ancienY;
    int nouveauX, nouveauY;
public:
    CommandeDeplacement(Orthese& orthese, int id, int positionX, int positionY);
    ~CommandeDeplacement() = default;

    void executer() const override;
    void annuler() const override;
};

class GestionCommande {
public:
    ~GestionCommande() = default;

    void executer(shared_ptr<Commande> commande);
    void annuler();
    void remettre();

private:
    vector<shared_ptr<Commande>> ordreAnnulation;
    vector<shared_ptr<Commande>> ordreReexecution;
};