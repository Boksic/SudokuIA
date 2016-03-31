#include <stdlib.h>
#include <stdio.h>
//#include <stdbool.h>

#define TAILLE 9

int main(void)
{
	int grille[TAILLE][TAILLE] =
	{
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0}
	};

	printf("Grille avant l'IA :\n");
	afficheGrille(grille);

	grilleEstValide();

	printf("\nGrille après l'IA :\n)";
	afficheGrille(grille);
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet d'afficher la grille de Sudoku  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
void afficheGrille(int grille[TAILLE][TAILLE])
{
	int ligne;
	int colonne;

	for(ligne=0 ; ligne<9 ; ligne++)
	{
		for (colonne=0 ; colonne<9; colonne++)
		{
			printf(((colonne+1)%3) ? "%d " : "%d|", grille[ligne][colonne]);
		}
		printf("\n");
	}
	printf("\n");
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet de verifier si un nombre est déjà sur la même ligne */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void absentDeLigne(int numero, int grille[TAILLE][TAILLE], int ligne)
{
	int colonne;

	for(colonne=0 ; colonne<TAILLE ; colonne++)
	{
		if(grille[ligne][colonne] == numero)
		{
			return false;
		}
	}
	return true;
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet de verifier si un nombre est déjà sur la même colonne */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void absentDeColonne(int numero, int grille[TAILLE][TAILLE], int colonne)
{
	int ligne;

		for(ligne=0 ; ligne<TAILLE ; ligne++)
		{
			if(grille[ligne][colonne] == numero)
			{
				return false;
			}
		}
		return true;
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet de verifier si un nombre est déjà sur le même bloc  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void absentDebloc(int numero, int grille[TAILLE][TAILLE], int ligne, int colonne)
{
	int ligne1 = (ligne/3)*3;
	int colonne1 = (colonne/3)*3;

	for(ligne=ligne1 ; ligne<ligne1+3 ; ligne++)
	{
		for(colonne=colonne1 ; colonne<colonne1+3 ; colonne++)
		{
			if(grille[ligne][colonne] == numero)
			{
				return false;
			}
		}
	}
	return true;
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet de verifier si une grille est valide  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void grilleEstValide(int grille[TAILLE][TAILLE], LIST* position)
{
	//On recupere les coordonnées de la case
	int ligne = position->ligne;
	int colonne = position->colonne;
	int numero;

	//Si la fonction parcourt toute la grille sans trouver d'erreur alors la grille est valide
	if(position == NULL)
	{
		return true;
	}

	//Pour toutes les valeurs possibles (de 1 à TAILLE inclu)
	for(numero=1 ; numero<=TAILLE ; numero++)
	{
		//Si "numero" est ni dans la ligne, ni dans la colonne, ni dans le bloc...
		if(absentDeLigne(numero, grille, ligne) && absentDeColonne(numero, grille, colonne) && absentDeBloc(numero, grille,ligne, colonne))
		{
			//On met a jour la case avec la valeur de "numero"
			grille[ligne][colonne] = numero;

			//On appelle grilleEstValide recursivement et return true si c'est bon
			if(grilleEstValide(grille, position->next))
			{
				return true;
			}
		}
	}

	//Aucun true n'est sortie de la boucle, cela veut dire qu'on a pas de solution...
	grille[ligne][colonne] = 0;

	return false;
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet de retourner le nombre de valeur possible pour une case */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int nbPossibilite(int grille[TAILLE][TAILLE], ligne, colonne)
{
	int nombrePossibilite = 0;
	int numero;

	for(numero=1 ; numero<=TAILLE ; numero++)
	{
		//Si "numero" est ni dans la ligne, ni dans la colonne, ni dans le bloc...
		if(absentDeLigne(numero, grille, ligne) && absentDeColonne(numero, grille, colonne) && absentDeBloc(numero, grille,ligne, colonne))
		{
			//On incremente "nombrePossibilite"
			nobrePossibilite++;
		}
		return nombrePossibilite;
	}
}

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 /* Fonction qui permet de retourner le nombre de valeur possible pour une case */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool resolution(int grille[TAILLE][TAILLE])
{
	int ligne;
	int colonne;

	//Creer et remplit la liste avec les cases vides
	LIST* positions = NULL;

	for(ligne=0 ; ligne<9 ; ligne++)
	{
		for(colonne=0 ; colonne<9 ; colonne++)
		{
			if(grille[ligne][colonne] == 0)
			{
				liste_cons(&positions, ligne, colonne, nbPossibilite(grille, ligne, colonne));
			}
		}
	}

	//Trie la liste par ordre croissant
	positions = list_sort (positions);

	bool resultat = estValide (grille, positions);

	//Supprime la liste
	liste_delete (&positions);

	return resultat;
}

