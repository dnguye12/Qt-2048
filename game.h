#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef vector<vector<int> > Plateau;

Plateau plateauVide(); /*implantée par Gloire LINVANI
/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial(); /*implantée par Gloire LINVANI
/** génè aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre(); /*implantée par Gloire LINVANI
/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau); /*implantée par Huy NGUYEN
/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau); /*implantée par Huy NGUYEN
/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau); /*implantée par Huy NGUYEN
/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau); /*implantée par Huy NGUYEN
/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le deplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 **/
Plateau deplacement(Plateau plateau, int direction);




#endif // GAME_H
