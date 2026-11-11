#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };
constexpr std::size_t nbMentions = 5;

constexpr double noteMin = 0.0;
constexpr double noteMax = 20.0;
constexpr double seuilValidation = 10.0;

Mention mentionPour(double note) {
    if (note < seuilValidation) { return Mention::Ajourne; }
    if (note < 12.0) { return Mention::Passable; }
    if (note < 14.0) { return Mention::AssezBien; }
    if (note < 16.0) { return Mention::Bien; }
    return Mention::TresBien;
}

std::string_view libelle(Mention m) {
    using enum Mention;
    switch (m) {
        case Ajourne:   return "Ajourne";
        case Passable:  return "Passable";
        case AssezBien: return "Assez bien";
        case Bien:      return "Bien";
        case TresBien:  return "Tres bien";
    }
    return "Inconnue";
}

int lireEntier(std::string_view invite, int min, int max) {
    while (true) {
        std::cout << invite;
        std::string ligne{};
        if (!std::getline(std::cin, ligne)) { return min; }
        std::istringstream flux(ligne);
        int valeur{0};
        char reste{0};
        if (!(flux >> valeur) || (flux >> reste)) {
            std::cout << "Saisie invalide.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "La valeur doit etre comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
}

double lireNote(std::string_view invite) {
    while (true) {
        std::cout << invite;
        std::string ligne{};
        if (!std::getline(std::cin, ligne)) { return noteMin; }
        // Accepter la virgule decimale : 12,5 -> 12.5
        for (char &c : ligne) {
            if (c == ',') { c = '.'; }
        }
        std::istringstream flux(ligne);
        double note{0.0};
        char reste{0};
        if (!(flux >> note) || (flux >> reste)) {
            std::cout << "Saisie invalide.\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "La note doit etre comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
}

int main() {
    std::cout << "Nom de l'UE : ";
    std::string ue{};
    std::getline(std::cin, ue);

    const int nb = lireEntier("Nombre d'etudiants (1 a 200) : ", 1, 200);

    std::vector<double> notes{};
    for (int i{1}; i <= nb; ++i) {
        notes.push_back(lireNote("Note de l'etudiant " + std::to_string(i) + " : "));
    }

    double minimum{noteMax};
    double maximum{noteMin};
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{};

    for (double n : notes) {
        minimum = std::min(minimum, n);
        maximum = std::max(maximum, n);
        somme += n;
        if (n >= seuilValidation) { ++admis; }
        ++repartition[static_cast<std::size_t>(mentionPour(n))];
    }

    const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts{0.0};
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    const double ecartType = std::sqrt(sommeEcarts / taille);

    std::cout << "\nStatistiques - " << ue << " (" << nb << " etudiants)\n";
    std::cout << std::string(58, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(18) << "Note minimale" << " : " << std::right << std::setw(6) << minimum << "\n";
    std::cout << std::left << std::setw(18) << "Note maximale" << " : " << std::right << std::setw(6) << maximum << "\n";
    std::cout << std::left << std::setw(18) << "Moyenne"       << " : " << std::right << std::setw(6) << moyenne << "\n";
    std::cout << std::left << std::setw(18) << "Ecart-type"    << " : " << std::right << std::setw(6) << ecartType << "\n";
    std::cout << std::left << std::setw(18) << "Admis" << " : " << std::right << std::setw(6) << admis
              << " (" << std::setprecision(1) << 100.0 * admis / taille << " %)\n";

    std::cout << "\nRepartition par mention\n";
    for (std::size_t i{0}; i < nbMentions; ++i) {
        const auto m = static_cast<Mention>(i);
        std::cout << std::left << std::setw(12) << libelle(m) << " "
                  << std::string(static_cast<std::size_t>(repartition[i]), '*')
                  << " (" << repartition[i] << ")\n";
    }
    return 0;
}
