//  Student: Achraf Yandouzi
//  Rolnummer: s0211812
//  Opmerkingen: /

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H
#include <vector>
#include "SchaakStuk.h"

class SchaakStuk;

class Game {
// variabelen om de status van het spel/bord te bewaren

public:
    Game();
    ~Game();


    // vanaf hier volgen functies die ik zelf heb gedefinieerd/aangepast
    SchaakStuk* getPiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool check_move(SchaakStuk* s,int r, int k); // doet hetzelfde als move behalve dat het de moves niet echt uitvoert

    bool move_wo_delete(SchaakStuk *s, int r, int k); // doet hetzelfde als move behalve dat het de pieces niet verwijdert

    bool schaak(zw kleur);

    void setStartBord();

    bool schaakmat(zw kleur);

    void setSpeelbord(std::vector<std::vector<SchaakStuk*>> s);

    std::vector<std::vector<SchaakStuk*>> getSpeelbord();

    bool pat(zw kleur);
private:
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...
    std::vector<std::vector<SchaakStuk*>> speelbord = {{}};


};


#endif //SCHAKEN_GAME_H
