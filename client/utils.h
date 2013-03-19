#include <string>

/* Fonction qui permet de vérifier si un
 * chemin donné est valide (= s'il existe) */
bool isDir(const std::string);

/* Fonction qui permet de vérifier si un dossier
 * existe en fonction du chemin donné */
bool isValidPath(const std::string);

/* Fonction qui permet de vérifier si un
 * fichier existe et qu'il est readable */
bool isFile(const std::string);