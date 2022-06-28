#include<stdio.h>
#include <limits.h>

typedef int boolean;
#define faux 0
#define vrai 1
typedef char NomSom[20]; // nom d'un sommet 
#define INFINI INT_MAX
typedef int* Matrice;

typedef struct{
	
	int n;				//nombre de sommets
	int nMax;			//nombre max de sommets
	boolean value;		//graphe value ou non
	NomSom* nomS;		//noms des sommets
	Matrice element;	//existence d'1 arc(i,j)
	Matrice valeur;		//cout arc(i,j)
	boolean* marque;	//if sommet visite ou non
		
}GrapheMat;

GrapheMat* creerGrapheMat(int nMax,int value);
void detruireGraphe(GrapheMat* graphe);
void ajouterUnSommet(GrapheMat* graphe,NomSom som);
void ajouterUnArc(GrapheMat* graphe,NomSom somD,NomSom somA, int cout);
void ecrireGraphe(GrapheMat* graphe);

//Parcours : 
void parcoursProfond(GrapheMat* graphe);
void parcoursLargeur(GrapheMat* graphe);

//floyd : 
void floyd(GrapheMat* graphe);

// explorations : 
/* Non Informées : */
void parcoursLargeurEx(GrapheMat* graphe); 
void parcoursCoutUniforme(GrapheMat* graphe); 
void parcoursProfondeurDabord(GrapheMat* graphe); 
void parcoursProfendeurLimite(GrapheMat* graphe); 
void parcoursProfondeurIterative(GrapheMat* graphe);
/* Informée :*/
void AEtoile(GrapheMat* graphe); 

// Reseau de neuronnes : 
/* Monocouche  : */
void perceptron();
/* Multicouche : */
void perceptronMulticouche();






