#include <string>

/* Fonction qui permet de v�rifier si un
 * chemin donn� est valide (= s'il existe) */
bool isDir(const std::string);

/* Fonction qui permet de v�rifier si un dossier
 * existe en fonction du chemin donn� */
bool isValidPath(const std::string);

/* Fonction qui permet de v�rifier si un
 * fichier existe et qu'il est readable */
bool isFile(const std::string);