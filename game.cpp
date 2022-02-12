//  Student: Achraf Yandouzi
//  Rolnummer: s0211812
//  Opmerkingen: (bvb aanpassingen van de opgave)
//
//TODO: - belangrijk: /
//      - extra: meer opties voor promotion

#include <iostream>
#include <utility>
#include "game.h"
#include "SchaakStuk.h"

// zelf aangepast (speelbord geinitializeerd)
Game::Game() {
    std::vector<SchaakStuk *> rij(8, nullptr);
    speelbord[0] = rij;
    for (int r = 0; r < 7; r++) {
        speelbord.push_back(rij);
    }
    setStartBord();
}

Game::~Game() {
    for (int r=0; r<8; r++) {
        for (int k=0; k<8; k++) {
            delete getPiece(r, k);
        }
    }
}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    // we laden eerst alle variabelen
    SchaakStuk *whitePawn1 = new Pion(wit);
    SchaakStuk *whitePawn2 = new Pion(wit);
    SchaakStuk *whitePawn3 = new Pion(wit);
    SchaakStuk *whitePawn4 = new Pion(wit);
    SchaakStuk *whitePawn5 = new Pion(wit);
    SchaakStuk *whitePawn6 = new Pion(wit);
    SchaakStuk *whitePawn7 = new Pion(wit);
    SchaakStuk *whitePawn8 = new Pion(wit);

    SchaakStuk *blackPawn1 = new Pion(zwart);
    SchaakStuk *blackPawn2 = new Pion(zwart);
    SchaakStuk *blackPawn3 = new Pion(zwart);
    SchaakStuk *blackPawn4 = new Pion(zwart);
    SchaakStuk *blackPawn5 = new Pion(zwart);
    SchaakStuk *blackPawn6 = new Pion(zwart);
    SchaakStuk *blackPawn7 = new Pion(zwart);
    SchaakStuk *blackPawn8 = new Pion(zwart);

    SchaakStuk *whiteRook1 = new Toren(wit);
    SchaakStuk *whiteRook2 = new Toren(wit);

    SchaakStuk *blackRook1 = new Toren(zwart);
    SchaakStuk *blackRook2 = new Toren(zwart);

    SchaakStuk *whiteKnight1 = new Paard(wit);
    SchaakStuk *whiteKnight2 = new Paard(wit);

    SchaakStuk *blackKnight1 = new Paard(zwart);
    SchaakStuk *blackKnight2 = new Paard(zwart);

    SchaakStuk *whiteBishop1 = new Loper(wit);
    SchaakStuk *whiteBishop2 = new Loper(wit);

    SchaakStuk *blackBishop1 = new Loper(zwart);
    SchaakStuk *blackBishop2 = new Loper(zwart);

    SchaakStuk *whiteQueen = new Koningin(wit);

    SchaakStuk *blackQueen = new Koningin(zwart);

    SchaakStuk *whiteKing = new Koning(wit);

    SchaakStuk *blackKing = new Koning(zwart);


    // we zetten de zwarte stukken
    setPiece(0, 0, blackRook1);
    setPiece(0, 7, blackRook2);
    setPiece(0, 1, blackKnight1);
    setPiece(0, 6, blackKnight2);
    setPiece(0, 2, blackBishop1);
    setPiece(0, 5, blackBishop2);
    setPiece(0, 3, blackQueen);
    setPiece(0, 4, blackKing);
    setPiece(1, 0, blackPawn1);
    setPiece(1, 1, blackPawn2);
    setPiece(1, 2, blackPawn3);
    setPiece(1, 3, blackPawn4);
    setPiece(1, 4, blackPawn5);
    setPiece(1, 5, blackPawn6);
    setPiece(1, 6, blackPawn7);
    setPiece(1, 7, blackPawn8);
    // we zetten de lege rijen
    for (int r = 2; r < 7; r++) {
        for (int k = 0; k < 8; k++) {
            speelbord[r][k] = nullptr;
        }
    }
    // we zetten de witte stukken
    setPiece(7, 0, whiteRook1);
    setPiece(7, 7, whiteRook2);
    setPiece(7, 1, whiteKnight1);
    setPiece(7, 6, whiteKnight2);
    setPiece(7, 2, whiteBishop1);
    setPiece(7, 5, whiteBishop2);
    setPiece(7, 3, whiteQueen);
    setPiece(7, 4, whiteKing);
    setPiece(6, 0, whitePawn1);
    setPiece(6, 1, whitePawn2);
    setPiece(6, 2, whitePawn3);
    setPiece(6, 3, whitePawn4);
    setPiece(6, 4, whitePawn5);
    setPiece(6, 5, whitePawn6);
    setPiece(6, 6, whitePawn7);
    setPiece(6, 7, whitePawn8);
}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk *s, int r, int k) {
    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
    std::pair<int, int> nieuwe_pos;
    nieuwe_pos.first = r;
    nieuwe_pos.second = k;
    std::vector<std::vector<SchaakStuk*>> prev_bord = this->speelbord;
    if (find(geldig.begin(), geldig.end(), nieuwe_pos) !=
        geldig.end()) {// als de nieuwe positie in de geldige zetten zit
        int old_row = s->cur_row;
        int old_col = s->cur_col;

        // rokeren
        if (Koning *_ = dynamic_cast<Koning *>(s)) { // als een koning gaat bewegen...
            if (abs(s->cur_col-k) > 1) { // en die gaat meer dan 1 vakje naar rechts of links
                if (s->cur_col > k) { // als we naar links rokeren
                    for (int i = 1; i<=s->cur_col; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != s->cur_col && getPiece(s->cur_row, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a=0; a<8; a++) {
                            for (int b=0; b<8; b++) {
                                SchaakStuk* enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getKleur() != s->getKleur()) {
                                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                                    for (auto g: geldig) {
                                        if (check_move(enemy, s->cur_row, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    setPiece(r, k, s); // zet de koning alvast daar
                    SchaakStuk* toren = getPiece(r, 0); // get de linkse toren
                    setPiece(r, k+1, toren); // zet die 1 rechts van de koning
                    setPiece(r, 0, nullptr); // verwijder de toren van zijn vorige positie
                    setPiece(old_row, old_col, nullptr); // verwijder de koning van zijn vorige positie
                    return true;
                }
                else { // als we naar rechts bewegen
                    // analoog als hierboven
                    for (int i=s->cur_col; i<7; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i!= s->cur_col && getPiece(s->cur_row, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a=0; a<8; a++) {
                            for (int b=0; b<8; b++) {
                                SchaakStuk* enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getKleur() != s->getKleur()) {
                                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                                    for (auto g: geldig) {
                                        if (check_move(enemy, s->cur_row, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    setPiece(r, k, s);
                    SchaakStuk* toren = getPiece(r, 7);
                    setPiece(r, k-1, toren);
                    setPiece(r, 7, nullptr);
                    setPiece(old_row, old_col, nullptr);
                    return true;
                }
            }
        }

        // voer en en passant move uit
        if (Pion *_ = dynamic_cast<Pion *>(s)) {
            if (abs(k-s->cur_col)== 1) {
                if (getPiece(r, k) == nullptr) {
                    setPiece(r, k, s);
                    if (s->getKleur() == zwart) {
                        delete getPiece(r-1, k);
                        setPiece(r - 1, k, nullptr);
                    }
                    else {
                        delete getPiece(r+1, k);
                        setPiece(r + 1, k, nullptr);
                    }
                    setPiece(old_row, old_col, nullptr);
                    return true;
                }
            }
        }

        // promotie
        if (Pion *_ = dynamic_cast<Pion *>(s)) {
            if (r==0 || r==7) {
                delete getPiece(r, k);
                setPiece(r, k, new Koningin{s->getKleur()});
                setPiece(old_row, old_col, nullptr);
                return true;
            }
        }

        setPiece(s->cur_row, s->cur_col, nullptr);
        SchaakStuk* prev_piece = getPiece(r, k);
        setPiece(r, k, s);

        if (schaak(s->getKleur())) {
            setPiece(old_row, old_col, s);
            setPiece(r, k, prev_piece);
            return false;
        }

        // maak een pion 'en passantable'
        if (Pion *_ = dynamic_cast<Pion *>(s)) {
            s->setBewogen(true);
            if (abs(r-old_row) == 2) {
                s->setEnPassantable(true);
            }
        }

        if (Toren *_= dynamic_cast<Toren *>(s)) {
            s->setBewogen(true);
        }
        if (Koning *_= dynamic_cast<Koning *>(s)) {
            s->setBewogen(true);
        }

        return true;
    };
    return false;
}

bool Game::move_wo_delete(SchaakStuk *s, int r, int k) {
    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
    std::pair<int, int> nieuwe_pos;
    nieuwe_pos.first = r;
    nieuwe_pos.second = k;
    std::vector<std::vector<SchaakStuk*>> prev_bord = this->speelbord;
    if (find(geldig.begin(), geldig.end(), nieuwe_pos) !=
        geldig.end()) {// als de nieuwe positie in de geldige zetten zit
        int old_row = s->cur_row;
        int old_col = s->cur_col;

        // rokeren
        if (Koning *_ = dynamic_cast<Koning *>(s)) { // als een koning gaat bewegen...
            if (abs(s->cur_col-k) > 1) { // en die gaat meer dan 1 vakje naar rechts of links
                if (s->cur_col > k) { // als we naar links rokeren
                    for (int i = 1; i<=s->cur_col; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != s->cur_col && getPiece(s->cur_row, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a=0; a<8; a++) {
                            for (int b=0; b<8; b++) {
                                SchaakStuk* enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getKleur() != s->getKleur()) {
                                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                                    for (auto g: geldig) {
                                        if (check_move(enemy, s->cur_row, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    setPiece(r, k, s); // zet de koning alvast daar
                    SchaakStuk* toren = getPiece(r, 0); // get de linkse toren
                    setPiece(r, k+1, toren); // zet die 1 rechts van de koning
                    setPiece(r, 0, nullptr); // verwijder de toren van zijn vorige positie
                    setPiece(old_row, old_col, nullptr); // verwijder de koning van zijn vorige positie
                    return true;
                }
                else { // als we naar rechts bewegen
                    // analoog als hierboven
                    for (int i=s->cur_col; i<7; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i!= s->cur_col && getPiece(s->cur_row, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a=0; a<8; a++) {
                            for (int b=0; b<8; b++) {
                                SchaakStuk* enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getKleur() != s->getKleur()) {
                                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                                    for (auto g: geldig) {
                                        if (check_move(enemy, s->cur_row, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    setPiece(r, k, s);
                    SchaakStuk* toren = getPiece(r, 7);
                    setPiece(r, k-1, toren);
                    setPiece(r, 7, nullptr);
                    setPiece(old_row, old_col, nullptr);
                    return true;
                }
            }
        }

        // voer en en passant move uit
        if (Pion *_ = dynamic_cast<Pion *>(s)) {
            if (abs(k-s->cur_col)== 1) {
                if (getPiece(r, k) == nullptr) {
                    setPiece(r, k, s);
                    if (s->getKleur() == zwart) {
                        setPiece(r - 1, k, nullptr);
                    }
                    else {
                        setPiece(r + 1, k, nullptr);
                    }
                    setPiece(old_row, old_col, nullptr);
                    return true;
                }
            }
        }

        // promotie
        if (Pion *_ = dynamic_cast<Pion *>(s)) {
            if (r==0 || r==7) {
                setPiece(r, k, new Koningin{s->getKleur()});
                setPiece(old_row, old_col, nullptr);
                return true;
            }
        }

        setPiece(s->cur_row, s->cur_col, nullptr);
        SchaakStuk* prev_piece = getPiece(r, k);
        setPiece(r, k, s);
        if (s->getKleur() == zwart && schaak(zwart)) {
            setPiece(old_row, old_col, s);
            setPiece(r, k, prev_piece);
            return false;
        }
        if (s->getKleur() == wit && schaak(wit)) {
            setPiece(old_row, old_col, s);
            setPiece(r, k, prev_piece);
            return false;
        }
        // maak een pion 'en passantable'
        if (Pion *_ = dynamic_cast<Pion *>(s)) {
            s->setBewogen(true);
            if (abs(r-old_row) == 2) {
                s->setEnPassantable(true);
            }
        }

        if (Toren *_= dynamic_cast<Toren *>(s)) {
            s->setBewogen(true);
        }
        if (Koning *_= dynamic_cast<Koning *>(s)) {
            s->setBewogen(true);
        }

        return true;
    };
    return false;
}

bool Game::check_move(SchaakStuk *s, int r, int k) {
    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
    std::pair<int, int> nieuwe_pos;
    nieuwe_pos.first = r;
    nieuwe_pos.second = k;
    int old_row = s->cur_row;
    int old_col = s->cur_col;
    std::vector<std::vector<SchaakStuk*>> origineel_bord = this->speelbord;
    if (find(geldig.begin(), geldig.end(), nieuwe_pos) !=
        geldig.end()) {// als de nieuwe positie in de geldige zetten zit
        // rokeren
        if (Koning *_ = dynamic_cast<Koning *>(s)) { // als een koning gaat bewegen...
            if (abs(s->cur_col-k) > 1) { // en die gaat meer dan 1 vakje naar rechts of links
                if (s->cur_col > k) { // als we naar links rokeren
                    for (int i = 1; i<=s->cur_col; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != s->cur_col && getPiece(s->cur_row, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a=0; a<8; a++) {
                            for (int b=0; b<8; b++) {
                                SchaakStuk* enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getKleur() != s->getKleur()) {
                                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                                    for (auto g: geldig) {
                                        if (check_move(enemy, s->cur_row, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    return true;
                }
                else { // als we naar rechts bewegen
                    // analoog als hierboven
                    for (int i=s->cur_col; i<7; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i!= s->cur_col && getPiece(s->cur_row, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a=0; a<8; a++) {
                            for (int b=0; b<8; b++) {
                                SchaakStuk* enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getKleur() != s->getKleur()) {
                                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                                    for (auto g: geldig) {
                                        if (check_move(enemy, s->cur_row, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    return true;
                }
            }
        }


        setPiece(s->cur_row, s->cur_col, nullptr);
        setPiece(r, k, s);
        if (s->getKleur() == zwart && schaak(zwart)) {
            s->cur_col = old_col;
            s->cur_row = old_row;
            this->speelbord = origineel_bord;
            return false;
        }
        if (s->getKleur() == wit && schaak(wit)) {
            s->cur_col = old_col;
            s->cur_row = old_row;
            this->speelbord = origineel_bord;
            return false;
        }
        s->cur_col = old_col;
        s->cur_row = old_row;
        this->speelbord = origineel_bord;
        return true;
    };
    s->cur_col = old_col;
    s->cur_row = old_row;
    this->speelbord = origineel_bord;
    return false;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    // loop over elke piece, als de kleur!KLEUR is, kijk naar zijn geldige moves
    // loop over elke geldige move, gebruik de functie getPiece() om te kijken naar wat daar staat
    // als daar de *kleur* koning staat, return true (nog gwn letten op dubbelchecks, denk ik)
    // anders return false
    for (std::vector<SchaakStuk *> rij: this->speelbord) {
        for (SchaakStuk *s: rij) {
            if (s != nullptr && s->getKleur() != kleur) {
                std::vector<std::pair<int, int>> geldige_moves = s->geldige_zetten(*this);
                for (auto move: geldige_moves) {
                    SchaakStuk *stuk = getPiece(move.first, move.second);
                    if (stuk != nullptr) {
                        if (Koning *_ = dynamic_cast<Koning *>(stuk)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    // loop over alle stukken van 'kleur'
    // loop over al hun geldige moves
    // gebruik de functie move om na te kijken of je daar naar toe kunt bewegen
    // als ik daar niet naartoe kon moven, betekent dat dat ik nog schaak sta na de move
    // dus dan blijven we verder loopen
    // vanaf dat er 1 move is die effectief werkte, returnen we false
    for (std::vector<SchaakStuk *> rij: this->speelbord) {
        for (SchaakStuk *s: rij) {
            if (s != nullptr && s->getKleur() == kleur) {
                std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                for (std::pair <int, int> m: geldig) {
                    if (check_move(s, m.first, m.second)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    // loop over alle stukken
    // als stuk de kleur 'kleur' heeft, loop over al zijn geldige moves
    // gebruik checkMove() om te zien of we daarnaar toe kunnen bewegen
    // vanaf dat dat kan, return false
    // op het einde van de loop, return true
    for (std::vector<SchaakStuk *> rij: this->speelbord) {
        for (SchaakStuk *s: rij) {
            if (s != nullptr && s->getKleur() == kleur) {
                std::vector<std::pair<int, int>> geldig = s->geldige_zetten(*this);
                for (std::pair <int, int> m: geldig) {
                    if (check_move(s, m.first, m.second)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk *Game::getPiece(int r, int k) {
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    SchaakStuk *piece = speelbord.at(r).at(k);
    return piece;
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk *s) {
    // Hier komt jouw code om een stuk neer te zetten op het bord
    speelbord[r][k] = s;
    if (s != nullptr) {
        s->cur_row = r;
        s->cur_col = k;
    }
}

void Game::setSpeelbord(std::vector<std::vector<SchaakStuk *>> s) {
    speelbord = std::move(s);
}

std::vector<std::vector<SchaakStuk *>> Game::getSpeelbord() {
    return speelbord;
}


