# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include "graphemat.h"
typedef GrapheMat Graphe;
int menu(){
  printf("\n\nLes graphes : \n");
  printf("0 : Arreter le programme : \n");
  printf("\t****************************************\n");
  printf("1 : Creer Graphe : \n");
  printf("2 : Ajouter un sommet :  \n");
  printf("3 : Ajouter un arc :  \n");
  printf("4 : Ecrire Graphe :  \n");
  printf("5 : Detruire graphe :  \n");
  printf("6 : Parcours en profondeur d'un graphe :  \n");
  printf("7 : Parcours en largeur d'un graphe :  \n");

  printf("8 : Floyd :  \n");

  printf("9 : Exploration en Largeur dabord (BFS = Breadth-First Search : ) \n");
  printf("10 : Exploration a cout uniforme :  \n");
  printf("11 : Exploration en profondeur D'abord :  \n");
  printf("12 : Exploration en profondeur limite :  \n");
  printf("13 : Exploration en profondeur Iterative :  \n");

  printf("14 : Exploration A* :  \n");

  printf("15  - Perceptron monocouche : \n");
  printf("16  - Perceptron multicouches : \n");
  printf("veuillez saisir votre choix : \n");
  printf("-->  ");  
  int choix; scanf("%d", &choix); 
  printf("\n"); 
  return choix; 
}
int main(){

int stop = 1;
Graphe* graphe; 
graphe = creerGrapheMat(9,1);
    NomSom a = "S0";
    NomSom b = "S1";
    NomSom c = "S2";
    NomSom d = "S3";
    NomSom e = "S4";
    NomSom f = "S5";
    NomSom g = "S6";
    NomSom h = "S7";
    ajouterUnSommet(graphe,a);
    ajouterUnSommet(graphe,b);
    ajouterUnSommet(graphe,c);
    ajouterUnSommet(graphe,d);
    ajouterUnSommet(graphe,e);
    ajouterUnSommet(graphe,f);
    ajouterUnSommet(graphe,g);
    ajouterUnSommet(graphe,h);
    //ajouterUnArc(graphe,s1,s2,2);
    ajouterUnArc(graphe,a,b,25);
    ajouterUnArc(graphe,a,g,17);
    ajouterUnArc(graphe,b,c,30);
    ajouterUnArc(graphe,b,d,33);
    ajouterUnArc(graphe,b,f,15);
    ajouterUnArc(graphe,c,d,18);
    ajouterUnArc(graphe,d,b,33);
    ajouterUnArc(graphe,e,d,25);
    ajouterUnArc(graphe,e,f,26);
    ajouterUnArc(graphe,e,h,20);
    ajouterUnArc(graphe,f,b,15);
    ajouterUnArc(graphe,f,d,35);
    ajouterUnArc(graphe,g,f,22);

while(stop){
  switch (menu())
  {
    case 0 : 
      stop = 0;  
      break; 
    case 1: // Creation of the graph 
      /* Asking the user to enter the number of vertices and the nature of the graph. */
      printf("veuillez saisir le nombre maximum de sommet de votre graphe : \n");
      printf("-->  "); 
      int ns; scanf("%d", &ns); 
      printf("\nveuillez choisir la nature de votre graphe : \n");
      printf("0 - Graphe non valué : \n"); 
      printf("1 - Graphe valué : \n"); 
      printf("-->  "); 
      int v; scanf("%d",&v ); 
      graphe = creerGrapheMat(ns, v); 
      break;
    case 2 : // Adding vertices 
      printf("Veuillez saisir le nom du sommet à inserer : \n"); 
      printf("-->  "); 
      NomSom s; scanf("%s", s); 
      ajouterUnSommet(graphe, s); 
      break;
    case 3 : 
      printf("veuillez saisir le nom du sommet de depart : \n"); 
      printf("-->  "); 
      NomSom sD; scanf("%s", sD);  
      printf("veuillez saisir le nom du sommet d'arrivé : \n"); 
      printf("-->  "); 
      NomSom sA; scanf("%s", sA);  
      int c;
      if (graphe->value) {
        printf("\nVeuillez saisir le coût entre ces deux sommets : \n"); 
        printf("-->  "); 
        scanf("%d", &c); 
      }
      else {
        c = 0; 
      }
      ajouterUnArc(graphe, sD, sA, c); 
      printf("%d", c); 
      break;
    case 4 : 
      ecrireGraphe(graphe); 
      printf("\n"); 
      break;
    case 5 : 
      detruireGraphe(graphe); 
      printf("graphe detruit !! \n"); 
      break;
    case 6 : 
      parcoursProfond(graphe); 
      break;
    case 7 : 
      parcoursLargeur(graphe); 
      break;
    case 8 : 
      floyd(graphe); 
      break;
    case 9 : 
      parcoursLargeurEx(graphe); 
      break;
    case 10 : 
      parcoursCoutUniforme(graphe); 
      break;
    case 11 : 
      parcoursProfondeurDabord(graphe);
      break;
    case 12 : 
      parcoursProfendeurLimite(graphe); 
      break;
    case 13 : 
      parcoursProfondeurIterative(graphe); 
      break;  
    case 14 : 
      AEtoile(graphe); 
      break;
    case 15 : 
      perceptron();
      break;
    case 16 : 
      perceptronMulticouche();
      break;
  }
}
}