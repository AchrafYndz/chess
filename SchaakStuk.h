//  Student: Achraf Yandouzi
//  Rolnummer: s0211812
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>

class Game;

enum zw{zwart, wit};


class SchaakStuk {
public:
    SchaakStuk(zw kleur) : kleur(kleur) {}

    virtual Piece piece() const = 0;      // Verander deze functie niet!
    // Deze functie wordt gebruikt door
    // setItem(x,y,SchaakStuk*) van
    // SchaakGUI

    zw getKleur() const { return kleur; }

    // zelf geschreven:
    virtual std::vector<std::pair<int, int>> geldige_zetten(Game &g) = 0;

    int cur_row = 0;
    int cur_col = 0;

    virtual void setBewogen(bool b) {};

    virtual bool getBewogen() {return true;};

    virtual void setEnPassantable(bool b) {};

    virtual bool isEnPassantable() {return false;};

private:
    zw kleur;

};

class Pion : public SchaakStuk {
public:
    Pion(zw kleur) : SchaakStuk(kleur) {}

    virtual Piece piece() const override {
        return Piece(Piece::Pawn, getKleur() == wit ? Piece::White : Piece::Black);
    }

    // zelf geschreven:
    std::vector<std::pair<int, int>> geldige_zetten(Game &g) override;;

    void setBewogen(bool b) override;

    bool getBewogen();

    void setEnPassantable(bool b) override;

    bool isEnPassantable() override;
private:
    bool bewogen = false;
    bool en_passantable = false;
};

class Toren : public SchaakStuk {
public:
    Toren(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook, getKleur() == wit ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> geldige_zetten(Game &g) override;;

    void setBewogen(bool b) override;

    bool getBewogen() override;;

private:
    bool bewogen = false;
};

class Paard : public SchaakStuk {
public:
    Paard(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight, getKleur() == wit ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> geldige_zetten(Game &g) override;;
};

class Loper : public SchaakStuk {
public:
    Loper(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop, getKleur() == wit ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> geldige_zetten(Game &g) override;;
};

class Koning : public SchaakStuk {
public:
    Koning(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King, getKleur() == wit ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> geldige_zetten(Game &g) override;;

    void setBewogen(bool b) override;

    bool getBewogen() override;;

private:
    bool bewogen;
};

class Koningin : public SchaakStuk {
public:
    Koningin(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen, getKleur() == wit ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> geldige_zetten(Game &g) override;;
};

#endif //SCHAKEN_SCHAAKSTUK_H
