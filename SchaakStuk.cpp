//  Student: Achraf Yandouzi
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"

std::vector<std::pair<int, int>> Pion::geldige_zetten(Game &g) {
    std::vector<std::pair<int, int>> moves;
    if (getKleur() == zwart) {
        std::pair<int, int> eenNaarVoor;
        eenNaarVoor.first = cur_row + 1;
        eenNaarVoor.second = cur_col;
        if (eenNaarVoor.first > 7);
        else if (g.getPiece(eenNaarVoor.first, eenNaarVoor.second) == nullptr ) {
            moves.push_back(eenNaarVoor);
        }
        // als pion nog niet bewogen is en daar (zowel een voor als twee voor) geen stukken staan
        std::pair<int, int> tweeNaarVoor;
        tweeNaarVoor.first = cur_row + 2;
        tweeNaarVoor.second = cur_col;
        if (tweeNaarVoor.first > 7);
        else if (g.getPiece(tweeNaarVoor.first, tweeNaarVoor.second) == nullptr && g.getPiece(eenNaarVoor.first, eenNaarVoor.second) == nullptr && !bewogen) {
            moves.push_back(tweeNaarVoor);
        }
        // als een stuk van het andere kleur daar staat of er staat een pion voor die net 2 posities naar voor bewogen is
        std::pair<int, int> eenLinksVoor;
        eenLinksVoor.first = cur_row + 1;
        eenLinksVoor.second = cur_col - 1;
        if (eenLinksVoor.second < 0 || eenLinksVoor.first > 7);
        else if (g.getPiece(eenLinksVoor.first, eenLinksVoor.second) == nullptr) {
            if (Pion *_ = dynamic_cast<Pion *>(g.getPiece(eenLinksVoor.first - 1, eenLinksVoor.second))) {
                SchaakStuk *pion = g.getPiece(eenLinksVoor.first - 1, eenLinksVoor.second);
                if (pion->isEnPassantable()) {
                    moves.push_back(eenLinksVoor);
                }
            }
        }
        else if (g.getPiece(eenLinksVoor.first, eenLinksVoor.second) != nullptr && g.getPiece(eenLinksVoor.first, eenLinksVoor.second) ->getKleur() == wit) {
            moves.push_back(eenLinksVoor);
        }
        // als een stuk van het andere kleur daar staat
        std::pair<int, int> eenRechtsVoor;
        eenRechtsVoor.first = cur_row + 1;
        eenRechtsVoor.second = cur_col + 1;
        if (eenRechtsVoor.second > 7 || eenRechtsVoor.first > 7);
        else if (g.getPiece(eenRechtsVoor.first, eenRechtsVoor.second) == nullptr) {
            if (Pion *_ = dynamic_cast<Pion *>(g.getPiece(eenRechtsVoor.first - 1, eenRechtsVoor.second))) {
                SchaakStuk *pion = g.getPiece(eenRechtsVoor.first - 1, eenRechtsVoor.second);
                if (pion->isEnPassantable()) {
                    moves.push_back(eenRechtsVoor);
                }
            }
        }
        else if (g.getPiece(eenRechtsVoor.first, eenRechtsVoor.second) != nullptr && g.getPiece(eenRechtsVoor.first, eenRechtsVoor.second)->getKleur() == wit) {
            moves.push_back(eenRechtsVoor);
        }
    }
    else if (getKleur() == wit) {
        // als daar geen stukken staan
        std::pair<int, int> eenNaarVoor;
        eenNaarVoor.first = cur_row - 1;
        eenNaarVoor.second = cur_col;
        if (eenNaarVoor.first < 0);
        else if (g.getPiece(eenNaarVoor.first, eenNaarVoor.second) == nullptr && eenNaarVoor.first >= 0) {
            moves.push_back(eenNaarVoor);
        }
        // als pion nog niet bewogen is en daar (zowel een voor als twee voor) geen stukken staan
        std::pair<int, int> tweeNaarVoor;
        tweeNaarVoor.first = cur_row - 2;
        tweeNaarVoor.second = cur_col;
        if (tweeNaarVoor.first < 0);
        else if (g.getPiece(tweeNaarVoor.first, tweeNaarVoor.second) == nullptr && g.getPiece(eenNaarVoor.first, eenNaarVoor.second) == nullptr && !bewogen) {
            moves.push_back(tweeNaarVoor);
        }
        // als een stuk van het andere kleur daar staat
        std::pair<int, int> eenLinksVoor;
        eenLinksVoor.first = cur_row - 1;
        eenLinksVoor.second = cur_col - 1;
        if (eenLinksVoor.second < 0 || eenLinksVoor.first < 0);
        else if (g.getPiece(eenLinksVoor.first, eenLinksVoor.second) == nullptr) {
            if (Pion *_ = dynamic_cast<Pion *>(g.getPiece(eenLinksVoor.first + 1, eenLinksVoor.second))) {
                SchaakStuk *pion = g.getPiece(eenLinksVoor.first + 1, eenLinksVoor.second);
                if (pion->isEnPassantable()) {
                    moves.push_back(eenLinksVoor);
                }
            }
        }
        else if (g.getPiece(eenLinksVoor.first, eenLinksVoor.second) != nullptr && g.getPiece(eenLinksVoor.first, eenLinksVoor.second) ->getKleur() == zwart) {
            moves.push_back(eenLinksVoor);
        }
        // als een stuk van het andere kleur daar staat
        std::pair<int, int> eenRechtsVoor;
        eenRechtsVoor.first = cur_row - 1;
        eenRechtsVoor.second = cur_col + 1;
        if (eenRechtsVoor.second > 7 || eenRechtsVoor.first < 0);
        else if (g.getPiece(eenRechtsVoor.first, eenRechtsVoor.second) == nullptr) {
            if (Pion *_ = dynamic_cast<Pion *>(g.getPiece(eenRechtsVoor.first + 1, eenRechtsVoor.second))) {
                SchaakStuk *pion = g.getPiece(eenRechtsVoor.first + 1, eenRechtsVoor.second);
                if (pion->isEnPassantable()) {
                    moves.push_back(eenRechtsVoor);
                }
            }
        }
        else if (g.getPiece(eenRechtsVoor.first, eenRechtsVoor.second) != nullptr && g.getPiece(eenRechtsVoor.first, eenRechtsVoor.second)->getKleur() == zwart) {
            moves.push_back(eenRechtsVoor);
        }
    }
    return moves;
}

void Pion::setBewogen(bool b) {
    bewogen = b;
}

bool Pion::getBewogen() {
    return bewogen;
}

void Pion::setEnPassantable(bool b) {
    en_passantable = b;
}

bool Pion::isEnPassantable() {
    return en_passantable;
}

std::vector<std::pair<int, int>> Toren::geldige_zetten(Game &g) {
    std::vector<std::pair<int, int>> moves;
    zw kleur = getKleur();
    // zolang er geen stukken in de kolom staan
    for (int i = cur_row; i <= 7; i++) { // naar boven loopen
        if (i == cur_row) continue;
        std::pair<int, int> kol_b;
        kol_b.first = i;
        kol_b.second = cur_col;
        if (g.getPiece(kol_b.first, kol_b.second) != nullptr) {
            if (g.getPiece(kol_b.first, kol_b.second)->getKleur() != kleur) {
                moves.push_back(kol_b);
            }
            break;
        }
        moves.push_back(kol_b);
    }
    for (int i = cur_row; i>=0; i--) { // naar onder loopen
        if (i == cur_row) continue;
        std::pair<int, int> kol_o;
        kol_o.first = i;
        kol_o.second = cur_col;
        if (g.getPiece(kol_o.first, kol_o.second) != nullptr) {
            if (g.getPiece(kol_o.first, kol_o.second)->getKleur() != kleur) {
                moves.push_back(kol_o);
            }
            break;
        }
        moves.push_back(kol_o);
    }

    // zolang er geen stukken in de rij staan
    for (int i = cur_col; i <= 7; i++) { // naar rechts loopen
        if (i == cur_col) continue;
        std::pair<int, int> rij_r;
        rij_r.first = cur_row;
        rij_r.second = i;
        if (g.getPiece(rij_r.first, rij_r.second) != nullptr) {
            if (g.getPiece(rij_r.first, rij_r.second)->getKleur() != kleur) {
                moves.push_back(rij_r);
            }
            break;
        }
        moves.push_back(rij_r);
    }
    for (int i=cur_col; i>=0; i--) { // naar links loopen
        if (i == cur_col) continue;
        std::pair<int, int> rij_l;
        rij_l.first = cur_row;
        rij_l.second = i;
        if (g.getPiece(rij_l.first, rij_l.second) != nullptr) {
            if (g.getPiece(rij_l.first, rij_l.second)->getKleur() != kleur) {
                moves.push_back(rij_l);
            }
            break;
        }
        moves.push_back(rij_l);
    }
    return moves;
}

void Toren::setBewogen(bool b) {
    bewogen = b;
}

bool Toren::getBewogen() {
    return bewogen;
}

std::vector<std::pair<int, int>> Paard::geldige_zetten(Game &g) {
    std::vector<std::pair<int, int>> moves;
    int X[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int Y[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    zw kleur = getKleur();
    for (int i = 0; i < 8; i++) { // een paard heeft 8 mogelijke moves
        std::pair<int, int> L_vorm;
        L_vorm.first = cur_row + X[i];
        L_vorm.second = cur_col + Y[i];
        if (L_vorm.first < 0 || L_vorm.first > 7 || L_vorm.second <0 || L_vorm.second >7) {
            continue;
        }
        if (g.getPiece(L_vorm.first, L_vorm.second) == nullptr || g.getPiece(L_vorm.first, L_vorm.second)->getKleur() != kleur) {
            moves.push_back(L_vorm);
        }
    }
    return moves;
}

std::vector<std::pair<int, int>> Loper::geldige_zetten(Game &g) {
    zw kleur = getKleur();
    std::vector<std::pair<int, int>> moves;
    int linksBoven = std::min(cur_row, cur_col);
    for (int i = 1; i <= linksBoven; i++) {
        std::pair<int, int> dia_lb;
        dia_lb.first = cur_row - i;
        dia_lb.second = cur_col - i;
        if (g.getPiece(dia_lb.first, dia_lb.second) != nullptr) {
            if (g.getPiece(dia_lb.first, dia_lb.second)->getKleur() != kleur) {
                moves.push_back(dia_lb);
            }
            break;
        }
        moves.push_back(dia_lb);
    }
    int rechtsBoven = std::min(cur_row, 7 - cur_col);
    for (int i = 1; i <= rechtsBoven; i++) {
        std::pair<int, int> dia_rb;
        dia_rb.first = cur_row - i;
        dia_rb.second = cur_col + i;
        if (g.getPiece(dia_rb.first, dia_rb.second) != nullptr) {
            if (g.getPiece(dia_rb.first, dia_rb.second)->getKleur() != kleur) {
                moves.push_back(dia_rb);
            }
            break;
        }
        moves.push_back(dia_rb);
    }
    int linksOnder = 7 - std::max(cur_row, 7 - cur_col);
    for (int i = 1; i <= linksOnder; i++) {
        std::pair<int, int> dia_lo;
        dia_lo.first = cur_row + i;
        dia_lo.second = cur_col - i;
        if (g.getPiece(dia_lo.first, dia_lo.second) != nullptr) {
            if (g.getPiece(dia_lo.first, dia_lo.second)->getKleur() != kleur) {
                moves.push_back(dia_lo);
            }
            break;
        }
        moves.push_back(dia_lo);
    }
    int rechtsOnder = 7 - std::max(cur_row, cur_col);
    for (int i = 1; i <= rechtsOnder; i++) {
        std::pair<int, int> dia_ro;
        dia_ro.first = cur_row + i;
        dia_ro.second = cur_col + i;
        if (g.getPiece(dia_ro.first, dia_ro.second) != nullptr) {
            if (g.getPiece(dia_ro.first, dia_ro.second)->getKleur() != kleur) {
                moves.push_back(dia_ro);
            }
            break;
        }
        moves.push_back(dia_ro);
    }
    return moves;
}

std::vector<std::pair<int, int>> Koning::geldige_zetten(Game &g) {
    std::vector<std::pair<int, int>> moves;
    zw kleur = getKleur();
    for (int r = -1; r <= 1; r++) {
        for (int k = -1; k <= 1; k++) {
            if (r == 0 && k == 0) { // we willen niet dezelfde positie als geldige move geven
                continue;
            }
            std::pair<int, int> move;
            move.first = cur_row + r;
            move.second = cur_col + k;
            if (move.first < 0 || move.first > 7 || move.second < 0 || move.second > 7) {
                continue;
            }
            if (g.getPiece(move.first, move.second) == nullptr ||
                g.getPiece(move.first, move.second)->getKleur() != kleur) {
                moves.push_back(move);
            }
        }
    }
    // de castling moves
    if (!bewogen && cur_col == 4) { // de tweede check is hier om te voorkomen dat ik bij update dit als geldige move neem
        SchaakStuk *rechtertoren = g.getPiece(cur_row, cur_col + 3);
        if (Toren *_ = dynamic_cast<Toren *>(rechtertoren)) {
            if (!rechtertoren->getBewogen()) {
                std::pair<int, int> move;
                move.first = cur_row;
                move.second = cur_col + 2;
                moves.push_back(move);
            }
        }
        SchaakStuk *linkertoren = g.getPiece(cur_row, cur_col - 4);
        if (Toren *_ = dynamic_cast<Toren *>(linkertoren)) {
            if (!linkertoren->getBewogen()) {
                std::pair<int, int> move;
                move.first = cur_row;
                move.second = cur_col - 2;
                moves.push_back(move);
            }
        }
    }
    return moves;
}

void Koning::setBewogen(bool b) {
    bewogen = b;
}

bool Koning::getBewogen() {
    return bewogen;
}

std::vector<std::pair<int, int>> Koningin::geldige_zetten(Game &g) {
    zw kleur = getKleur();
    std::vector<std::pair<int, int>> moves;
    // DE 'BISHOP-LIKE' MOVES
    int linksBoven = std::min(cur_row, cur_col);
    for (int i = 1; i <= linksBoven; i++) {
        std::pair<int, int> dia_lb;
        dia_lb.first = cur_row - i;
        dia_lb.second = cur_col - i;
        if (g.getPiece(dia_lb.first, dia_lb.second) != nullptr) {
            if (g.getPiece(dia_lb.first, dia_lb.second)->getKleur() != kleur) {
                moves.push_back(dia_lb);
            }
            break;
        }
        moves.push_back(dia_lb);
    }
    int rechtsBoven = std::min(cur_row, 7 - cur_col);
    for (int i = 1; i <= rechtsBoven; i++) {
        std::pair<int, int> dia_rb;
        dia_rb.first = cur_row - i;
        dia_rb.second = cur_col + i;
        if (g.getPiece(dia_rb.first, dia_rb.second) != nullptr) {
            if (g.getPiece(dia_rb.first, dia_rb.second)->getKleur() != kleur) {
                moves.push_back(dia_rb);
            }
            break;
        }
        moves.push_back(dia_rb);
    }
    int linksOnder = 7 - std::max(cur_row, 7 - cur_col);
    for (int i = 1; i <= linksOnder; i++) {
        std::pair<int, int> dia_lo;
        dia_lo.first = cur_row + i;
        dia_lo.second = cur_col - i;
        if (g.getPiece(dia_lo.first, dia_lo.second) != nullptr) {
            if (g.getPiece(dia_lo.first, dia_lo.second)->getKleur() != kleur) {
                moves.push_back(dia_lo);
            }
            break;
        }
        moves.push_back(dia_lo);
    }
    int rechtsOnder = 7 - std::max(cur_row, cur_col);
    for (int i = 1; i <= rechtsOnder; i++) {
        std::pair<int, int> dia_ro;
        dia_ro.first = cur_row + i;
        dia_ro.second = cur_col + i;
        if (g.getPiece(dia_ro.first, dia_ro.second) != nullptr) {
            if (g.getPiece(dia_ro.first, dia_ro.second)->getKleur() != kleur) {
                moves.push_back(dia_ro);
            }
            break;
        }
        moves.push_back(dia_ro);
    }
    // DE 'ROOK-LIKE' MOVES
    for (int i = cur_row; i <= 7; i++) { // naar boven loopen
        if (i == cur_row) continue;
        std::pair<int, int> kol_b;
        kol_b.first = i;
        kol_b.second = cur_col;
        if (g.getPiece(kol_b.first, kol_b.second) != nullptr) {
            if (g.getPiece(kol_b.first, kol_b.second)->getKleur() != kleur) {
                moves.push_back(kol_b);
            }
            break;
        }
        moves.push_back(kol_b);
    }
    for (int i = cur_row; i>=0; i--) { // naar onder loopen
        if (i == cur_row) continue;
        std::pair<int, int> kol_o;
        kol_o.first = i;
        kol_o.second = cur_col;
        if (g.getPiece(kol_o.first, kol_o.second) != nullptr) {
            if (g.getPiece(kol_o.first, kol_o.second)->getKleur() != kleur) {
                moves.push_back(kol_o);
            }
            break;
        }
        moves.push_back(kol_o);
    }

    // zolang er geen stukken in de rij staan
    for (int i = cur_col; i <= 7; i++) { // naar rechts loopen
        if (i == cur_col) continue;
        std::pair<int, int> rij_r;
        rij_r.first = cur_row;
        rij_r.second = i;
        if (g.getPiece(rij_r.first, rij_r.second) != nullptr) {
            if (g.getPiece(rij_r.first, rij_r.second)->getKleur() != kleur) {
                moves.push_back(rij_r);
            }
            break;
        }
        moves.push_back(rij_r);
    }
    for (int i=cur_col; i>=0; i--) { // naar links loopen
        if (i == cur_col) continue;
        std::pair<int, int> rij_l;
        rij_l.first = cur_row;
        rij_l.second = i;
        if (g.getPiece(rij_l.first, rij_l.second) != nullptr) {
            if (g.getPiece(rij_l.first, rij_l.second)->getKleur() != kleur) {
                moves.push_back(rij_l);
            }
            break;
        }
        moves.push_back(rij_l);
    }
    return moves;
}
