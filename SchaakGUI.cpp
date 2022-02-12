//
// Created by toonc on 12/17/2021.
//

#include <iostream>
#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"

// Constructor
SchaakGUI::SchaakGUI() : ChessWindow(nullptr) {
    update();
}

bool already_clicked = false;
int prev_r;
int prev_k;
std::vector<std::pair<int, int>> prev_geldig;
zw color_to_move = wit;
SchaakStuk *geklikt;

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    if (not already_clicked) { // we klikken op het stuk dat we willen bewegen
        prev_r = r;
        prev_k = k;
        geklikt = this->g.getPiece(r, k);
        if (geklikt == nullptr) {
            return;
        } else if (color_to_move == wit && geklikt->getKleur() != wit) {
            message("White to move!");
            return;
        } else if (color_to_move == zwart && geklikt->getKleur() != zwart) {
            message("Black to move!");
            return;
        }

        setTileSelect(r, k, true);

        if (displayMoves()) {
            SchaakStuk *s = g.getPiece(r, k);
            zw kleur = s->getKleur();

            std::vector<std::pair<int, int>> geldig = s->geldige_zetten(g);
            prev_geldig = geldig;

            std::vector<std::vector<SchaakStuk *>> prev_bord = g.getSpeelbord();
            int old_row = s->cur_row;
            int old_col = s->cur_col;
            bool prev_bewogen = s->getBewogen();


            for (std::pair<int, int> m: geldig) {
                // geen enkele legale move kan de koning in gevaar brengen, dus we hoeven niet op threats te letten
                if (Koning* _ = dynamic_cast<Koning *>(s)) {
                    if (g.check_move(s, m.first, m.second)) {
                        setTileFocus(m.first, m.second, true);
                        continue;
                    }
                }
                if (g.move_wo_delete(s, m.first, m.second)) {
                    // loop over alle geldige moves van de stukken met tegengestelde kleur
                    // als er moves zijn die overeenkomen met de geldige moves van het geselecteerde stuk
                    // markeer die moves met setTileThreat
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            SchaakStuk *stuk = g.getPiece(i, j);
                            if (stuk != nullptr && stuk->getKleur() != kleur) {
                                std::vector<std::pair<int, int>> allowed = stuk->geldige_zetten(g);
                                if (Pion *_ = dynamic_cast<Pion *>(stuk)) { // de twee moves naar voor van een pion zijn geen aanvallende moves
                                    // de 2 schuine moves van een pion zullen niet gezien worden als geldig omdat er nog geen stukken staan
                                    if (stuk->getKleur() == wit) {
                                        std::pair<int, int> eenLinksVoor;
                                        eenLinksVoor.first = stuk->cur_row - 1;
                                        eenLinksVoor.second = stuk->cur_col - 1;
                                        if (eenLinksVoor.first == m.first && eenLinksVoor.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                        std::pair<int, int> eenRechtsVoor;
                                        eenRechtsVoor.first = stuk->cur_row - 1;
                                        eenRechtsVoor.second = stuk->cur_col + 1;
                                        if (eenRechtsVoor.first == m.first && eenRechtsVoor.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                    } else {
                                        std::pair<int, int> eenLinksVoor;
                                        eenLinksVoor.first = stuk->cur_row + 1;
                                        eenLinksVoor.second = stuk->cur_col - 1;
                                        if (eenLinksVoor.first == m.first && eenLinksVoor.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                        std::pair<int, int> eenRechtsVoor;
                                        eenRechtsVoor.first = stuk->cur_row + 1;
                                        eenRechtsVoor.second = stuk->cur_col + 1;
                                        if (eenRechtsVoor.first == m.first && eenRechtsVoor.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                    }
                                    continue;
                                }
                                for (std::pair<int, int> a: allowed) {
                                    if (g.check_move(stuk, a.first, a.second)) {
                                        if (a.first == m.first && a.second == m.second) {
                                            setTileThreat(a.first, a.second, true);
                                            continue;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    setTileFocus(m.first, m.second, true);

                    g.setSpeelbord(prev_bord);
                    s->cur_col = old_col;
                    s->cur_row = old_row;
                    s->setBewogen(prev_bewogen);

                    continue;
                    }
                }
            }
        already_clicked = true;
        return;
    }
    else { // we hebben al een piece aangeklikt, nu moeten we klikken naar waar we het stuk willen bewegen
        if (r == geklikt->cur_row && k== geklikt->cur_col) { // we klikken weer hetzelfde stuk aan, dus we willen niets doen
            already_clicked = false;
            setTileSelect(prev_r, prev_k, false);
            for (std::pair<int, int> g: prev_geldig) {
                setTileFocus(g.first, g.second, false);
                already_clicked = false;
            }
            return;
        }
        bool success = this->g.move(geklikt, r, k);
        if (not success) {
            message("Deze move is ongeldig");

            setTileSelect(prev_r, prev_k, false);

            for (std::pair<int, int> g: prev_geldig) {
                setTileFocus(g.first, g.second, false);
            }

            already_clicked = false;
            return;
        }

        // we resetten de mogelijke en_passants van de andere kleur
        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                SchaakStuk* s = g.getPiece(i, j);
                if (s != nullptr && s->getKleur() != color_to_move) {
                    if (s->isEnPassantable()) {
                        s->setEnPassantable(false);
                    }
                }
            }
        }

        color_to_move == wit ? color_to_move = zwart : color_to_move = wit;

        clearBoard();

        setTileSelect(prev_r, prev_k, false);
        for (std::pair<int, int> g: prev_geldig) {
            setTileFocus(g.first, g.second, false);
            already_clicked = false;
        }

        update();


        if (g.schaak(wit)) {
            if (g.schaakmat(wit)) {
                message("Wit staat schaakmat, zwart wint!");
            } else {
                message("Wit staat schaak!");
            }
        } else if (g.pat(wit)) {
            message("Wit staat pat, gelijkspel!");
        }

        if (g.schaak(zwart)) {
            if (g.schaakmat(zwart)) {
                message("Zwart staat schaakmat, wit wint!");
            } else {
                message("Zwart staat schaak!");
            }
        } else if (g.pat(zwart)) {
            message("Zwart staat pat, gelijkspel!");
        }

    }
}

void SchaakGUI::newGame() {}


void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb")
            << QString("Hb") << QString("Rb");
        for (int i = 0; i < 8; i++) {
            out << QString("Pb");
        }
        for (int r = 3; r < 7; r++) {
            for (int k = 0; k < 8; k++) {
                out << QString(".");
            }
        }
        for (int i = 0; i < 8; i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw")
            << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r = 0; r < 8; r++) {
                for (int k = 0; k < 8; k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status() != QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString &Q) {
            message(Q);
        }
    }
    update();
}


void SchaakGUI::undo() {
    message("Je hebt undo gekozen");
}

void SchaakGUI::redo() {}


void SchaakGUI::visualizationChange() {
    QString visstring =
            QString(displayMoves() ? "T" : "F") + (displayKills() ? "T" : "F") + (displayThreats() ? "T" : "F");
    message(QString("Visualization changed : ") + visstring);
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    // eerst resetten we al de threats van de vorige scene
    for (int r = 0; r < 8; r++) {
        for (int k = 0; k < 8; k++) {
            setPieceThreat(r, k, false);
            setTileThreat(r, k, false);
        }
    }
    for (int r = 0; r < 8; r++) {
        for (int k = 0; k < 8; k++) {
            // we zetten het bord klaar
            SchaakStuk *schaakstuk = g.getPiece(r, k);
            if (schaakstuk != nullptr) {
                setItem(r, k, schaakstuk);
            }

            if (displayKills()) {
                // loop over alle geldige moves van de witte stukken
                // als daar een zwart stuk staat
                // duid dat stuk aan met setPieceThreat()
                SchaakStuk *s = g.getPiece(r, k);
                if (s != nullptr && s->getKleur() == wit) {
                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(g);
                    for (std::pair<int, int> m: geldig) {
                        if (g.check_move(s, m.first, m.second)) {
                            SchaakStuk *stuk = g.getPiece(m.first, m.second);
                            if (stuk != nullptr && stuk->getKleur() == zwart) {
                                setPieceThreat(m.first, m.second, true);
                            }
                        }
                    }
                }
            }
            if (displayThreats()) {
                // loop over alle geldige moves van de zwarte stukken
                // als daar een wit stuk staat
                // duid dat stuk aan met setPieceThreat()
                SchaakStuk *s = g.getPiece(r, k);
                if (s != nullptr && s->getKleur() == zwart) {
                    std::vector<std::pair<int, int>> geldig = s->geldige_zetten(g);
                    for (std::pair<int, int> m: geldig) {
                        if (g.check_move(s, m.first, m.second)) {
                            SchaakStuk *stuk = g.getPiece(m.first, m.second);
                            if (stuk != nullptr && stuk->getKleur() == wit) {
                                setPieceThreat(m.first, m.second, true);
                            }
                        }
                    }
                }
            }
        }
    }
}


