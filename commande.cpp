#include "commande.h"

using namespace std;

CommandeSupression::CommandeSupression(Orthese& orthese, int id): orthese(orthese), id(id) {
    ancienPoint = dynamic_pointer_cast<Point>(orthese.getElements()[id]);
}

void CommandeSupression::executer() const {
    orthese.supprimerPoint(id);
}

void CommandeSupression::annuler() const {
    orthese.ajouterPoint(ancienPoint);
}

CommandeDeplacement::CommandeDeplacement(Orthese& orthese, int id, int positionX, int positionY):
    orthese(orthese), id(id), nouveauX(positionX), nouveauY(positionY) {
    
    shared_ptr<Point> point = dynamic_pointer_cast<Point>(orthese.getElements()[id]);

    // if (!point) {
    //     cout << "Point avec ID " << id << " non trouvé.\n";
    //     return;
    // }

    ancienX = point->getX();
    ancienY = point->getY();
}

void CommandeDeplacement::executer() const {
    orthese.deplacerPoint(id, nouveauX, nouveauY);
}

void CommandeDeplacement::annuler() const {
    orthese.deplacerPoint(id, ancienX, ancienY);
}

void GestionCommande::executer(shared_ptr<Commande> commande) {
    commande->executer();
    ordreAnnulation.push_back(commande);
    ordreReexecution.clear();
}

void GestionCommande::annuler() {
    if (ordreAnnulation.empty()) {
        return;
    }
    shared_ptr<Commande> commande = ordreAnnulation.back();
    commande->annuler();

    ordreAnnulation.pop_back();
    ordreReexecution.push_back(commande);
}

void GestionCommande::remettre() {
    if (ordreReexecution.empty()) {
        return;
    }
    shared_ptr<Commande> commande = ordreReexecution.back();
    commande->executer();

    ordreReexecution.pop_back();
    ordreAnnulation.push_back(commande);
}