#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
int lireEntier(std::string_view invite, int min, int max)
{
    while (true)
    {
        std::cout << invite;

        std::string ligne{};

        if (!std::getline(std::cin, ligne))
        {
            return min;
        }

        std::istringstream flux(ligne);

        int valeur{0};
        char reste{0};

        if (!(flux >> valeur) || (flux >> reste))
        {
            std::cout << "Saisie invalide.\n";
        }
        else if (valeur < min || valeur > max)
        {
            std::cout << "La valeur doit etre comprise entre "
                      << min << " et " << max << ".\n";
        }
        else
        {
            return valeur;
        }
    }
}
double lireNote(std::string_view invite)
{
    while (true)
    {
        std::cout << invite;

        std::string ligne{};

        if (!std::getline(std::cin, ligne))
        {
            return 0.0;
        }

        for (char& c : ligne)
        {
            if (c == ',')
            {
                c = '.';
            }
        }

        std::istringstream flux(ligne);

        double note{};
        char reste{};

        if (!(flux >> note) || (flux >> reste))
        {
            std::cout << "Saisie invalide.\n";
        }
        else if (note < 0.0 || note > 20.0)
        {
            std::cout << "La note doit etre comprise entre 0 et 20.\n";
        }
        else
        {
            return note;
        }
    }
}
namespace carnet
{
    enum class Ordre
    {
        Croissant,
        Decroissant
    };

    struct Statistiques
    {
        double minimum{};
        double maximum{};
        double moyenne{};
        int nbValidees{};
    };
    [[nodiscard]]
    Statistiques calculerStatistiques(
        const std::vector<double>& notes)
    {
       const auto mini =
    *std::min_element(notes.begin(), notes.end());

const auto maxi =
    *std::max_element(notes.begin(), notes.end());

        double somme{0.0};
        int validees{0};

        for (double n : notes)
        {
            somme += n;

            if (n >= 10.0)
            {
                ++validees;
            }
        }

        return {
            mini,
            maxi,
            somme / static_cast<double>(notes.size()),
            validees
        };
    }
       void appliquerBonus(
    std::vector<double>& notes,
    double bonus)
{
    for (double& n : notes)
    {
        n = std::clamp(
            n + bonus,
            0.0,
            20.0);
    }
}
       void trier(
    std::vector<double>& notes,
    Ordre ordre)
{
    if (ordre == Ordre::Croissant)
    {
        std::sort(notes.begin(), notes.end());
    }
    else
    {
        std::sort(
            notes.begin(),
            notes.end(),
            [](double a, double b)
            {
                return a > b;
            });
    }
}
void afficherNotes(const std::vector<double>& notes)
{
    if (notes.empty())
    {
        std::cout << "Aucune note.\n";
        return;
    }

    for (std::size_t i{0}; i < notes.size(); ++i)
    {
        std::cout << i + 1
                  << ". "
                  << notes[i]
                  << "\n";
    }
}
void ajouter(std::vector<double>& notes)
{
    notes.push_back(
        lireNote("Note a ajouter : "));
}
void modifier(std::vector<double>& notes)
{
    if (notes.empty())
    {
        std::cout << "Aucune note a modifier.\n";
        return;
    }

    afficherNotes(notes);

    const int rang =
        lireEntier(
            "Numero de la note : ",
            1,
            static_cast<int>(notes.size()));

    notes[static_cast<std::size_t>(rang - 1)]
        = lireNote("Nouvelle valeur : ");
}
void supprimer(std::vector<double>& notes)
{
    if (notes.empty())
    {
        std::cout << "Aucune note a supprimer.\n";
        return;
    }

    afficherNotes(notes);

    const int rang =
        lireEntier(
            "Numero de la note : ",
            1,
            static_cast<int>(notes.size()));

    notes.erase(
        notes.begin() + (rang - 1));
}
void afficherStatistiques(
    const std::vector<double>& notes)
{
    if (notes.empty())
    {
        std::cout << "Aucune note.\n";
        return;
    }

    const auto stats =
        calculerStatistiques(notes);

    std::cout
        << "Min : "
        << stats.minimum
        << " | Max : "
        << stats.maximum
        << " | Moyenne : "
        << stats.moyenne
        << " | Validees : "
        << stats.nbValidees
        << "/"
        << notes.size()
        << "\n";
}
int afficherMenu()
{
    std::cout << "\n=== Carnet de notes ===\n";

    std::cout << "1. Ajouter une note\n";
    std::cout << "2. Afficher les notes\n";
    std::cout << "3. Modifier une note\n";
    std::cout << "4. Supprimer une note\n";
    std::cout << "5. Trier les notes\n";
    std::cout << "6. Statistiques\n";
    std::cout << "7. Appliquer un bonus\n";
    std::cout << "0. Quitter\n";

    return lireEntier(
        "Votre choix : ",
        0,
        7);
}}

int main()
{
    std::vector<double> notes;

    int choix{};

    do
    {
        choix = carnet::afficherMenu();

        switch (choix)
        {
            case 1:
                carnet::ajouter(notes);
                break;

            case 2:
                carnet::afficherNotes(notes);
                break;

            case 3:
                carnet::modifier(notes);
                break;

            case 4:
                carnet::supprimer(notes);
                break;

            case 5:
            {
                const int sens =
                    lireEntier(
                        "1. Croissant 2. Decroissant : ",
                        1,
                        2);

                carnet::trier(
                    notes,
                    sens == 1
                        ? carnet::Ordre::Croissant
                        : carnet::Ordre::Decroissant);

                break;
            }

            case 6:
                carnet::afficherStatistiques(notes);
                break;

            case 7:
                carnet::appliquerBonus(
                    notes,
                    lireNote("Bonus : "));
                break;

            case 0:
                break;

            default:
                break;
        }
    }
    while (choix != 0);

    return 0;
}
