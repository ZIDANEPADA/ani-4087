
#include "NKImage/Core/NkImage.h"

#include <cstdio>

using namespace nkentseu;

// Retourne la taille réelle d'un fichier en octets.
// Si le fichier ne peut pas être ouvert, retourne -1.
long tailleFichier(const char* chemin)
{
    FILE* fichier = std::fopen(chemin, "rb");

    if (fichier == nullptr)
        return -1;

    if (std::fseek(fichier, 0, SEEK_END) != 0)
    {
        std::fclose(fichier);
        return -1;
    }

    long taille = std::ftell(fichier);
    std::fclose(fichier);

    return taille;
}

struct EssaiFormat
{
    const char* nom;
    const char* chemin;
};

int main()
{
    // 1. Charger l'image originale.
    NkImage originale;

    if (!originale.Load("murs/photo.jpg"))
    {
        std::printf(
            "ERREUR : impossible de charger murs/photo.jpg\n"
        );
        return 1;
    }

    std::printf(
        "Image originale : %d x %d pixels\n",
        originale.Width(),
        originale.Height()
    );

    // 2. Définir les formats à tester.
    const EssaiFormat essais[] =
    {
        {"PNG", "resultat.png"},
        {"JPEG", "resultat.jpg"},
        {"BMP", "resultat.bmp"},
        {"TGA", "resultat.tga"},
        {"QOI", "resultat.qoi"},
        {"PPM", "resultat.ppm"},
        {"GIF", "resultat.gif"},
        {"HDR", "resultat.hdr"},
        {"EXR", "resultat.exr"}
    };

    const int nombreEssais =
        static_cast<int>(sizeof(essais) / sizeof(essais[0]));

    // 3. Créer le fichier qui recevra les résultats.
    FILE* rapport = std::fopen("formats.txt", "w");

    if (rapport == nullptr)
    {
        std::printf("ERREUR : impossible de creer formats.txt\n");
        return 1;
    }

    // 4. Enregistrer, mesurer puis recharger chaque format.
    for (int i = 0; i < nombreEssais; ++i)
    {
        const char* nom = essais[i].nom;
        const char* chemin = essais[i].chemin;

        // Save choisit le format en fonction de l'extension.
        bool sauvegarde = originale.Save(chemin);

        if (!sauvegarde)
        {
            std::fprintf(
                rapport,
                "%s : 0 octets, illisible\n",
                nom
            );

            std::printf(
                "%s : echec de sauvegarde\n",
                nom
            );

            continue;
        }

        // Mesurer la taille du fichier réellement écrit.
        long taille = tailleFichier(chemin);

        // Recharger le fichier pour vérifier qu'il est décodable.
        NkImage rechargee;
        bool lecture = rechargee.Load(chemin);

        if (!lecture || !rechargee.IsValid() || taille < 0)
        {
            std::fprintf(
                rapport,
                "%s : %ld octets, illisible\n",
                nom,
                taille < 0 ? 0L : taille
            );

            std::printf(
                "%s : fichier cree mais rechargement impossible\n",
                nom
            );

            continue;
        }

        // Écrire les mesures obtenues, sans les inventer.
        std::fprintf(
            rapport,
            "%s : %ld octets, %d x %d\n",
            nom,
            taille,
            rechargee.Width(),
            rechargee.Height()
        );

        std::printf(
            "%s : %ld octets, %d x %d\n",
            nom,
            taille,
            rechargee.Width(),
            rechargee.Height()
        );
    }

    std::fclose(rapport);

    std::printf("\nRapport ecrit dans formats.txt\n");

    return 0;
}
