#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include"graphemat.h"
#include "liste.h"
#include <time.h>

boolean grapheDetruit = vrai;
static int noeudsVisite=0;

static booleen check=faux;
static NomSom* chemin = (NomSom*) malloc((sizeof(NomSom))*100);
static int* cout = (int*)malloc(sizeof(int)*100) ;
static booleen trouveS = faux;



// razMarque met par defaut tous les champs marque a faux ( S non visité )  :
//=> Elle remet à 0 tableau de marquage 
static void razMarque (GrapheMat* graphe)
{
    for (int i=0; i<graphe->n; i++)
        graphe->marque [i] = faux;
}
// Allocation dynamique & initialisation d'un struct de type GrapheMat :
GrapheMat* creerGrapheMat (int nMax, int value)
{
    // allocation dynamique : 
    GrapheMat* graphe  = (GrapheMat*) malloc (sizeof (GrapheMat));
    graphe->n       = 0;
    graphe->nMax    = nMax;
    graphe->value   = value; // value : vrai si le graphe est value
    graphe->nomS    = (NomSom*)  malloc (sizeof(NomSom)  *nMax);
    graphe->marque  = (boolean*) malloc (sizeof(boolean) *nMax);
    graphe->element = (int*)     malloc (sizeof(int)*nMax*nMax);
    graphe->valeur  = (int*)     malloc (sizeof(int)*nMax*nMax);
    // initialisation par defaut : 
    for (int i=0; i<nMax; i++)
    {
        for (int j=0; j<nMax; j++)
        {
            graphe->element [i*nMax+j] = faux;
            graphe->valeur  [i*nMax+j] = INFINI;
        }
    }
    razMarque (graphe);
    grapheDetruit = faux;
    return graphe;
}
// Desallocation d'un graphe : 
void detruireGraphe (GrapheMat* graphe)
{
    free (graphe->nomS);
    free (graphe->marque);
    free (graphe->element);
    free (graphe->valeur);
    free (graphe);
    grapheDetruit = vrai;
}
// rang() => det le rang dans le tab nomS du nom : 
static int rang (GrapheMat* graphe, NomSom nom)
{
    int      i      = 0;
    boolean  trouve = faux;
    while ( (i<graphe->n) && !trouve)
    {
        trouve = strcmp (graphe->nomS [i], nom) == 0;
        if (!trouve)
            i++;
    }
    return trouve ? i : -1;
}
// Insertion d'1 sommet dans un graphe : 
void ajouterUnSommet (GrapheMat* graphe, NomSom nom)
{
    if (rang (graphe, nom) == -1)
    {
        if (graphe->n < graphe->nMax)
        {
            strcpy (graphe->nomS [graphe->n++], nom);
        }
        else
        {
            printf ("\nNombre de sommets > %d\n", graphe->nMax);
        }
    }
    else
    {
        printf ("\n%s deja defini\n", nom);
    }
}
// Ajt d'1 arc a graphe , arc entre somD(depart) et somA(arrive) :
void ajouterUnArc (GrapheMat* graphe, NomSom somD, NomSom somA, int cout)
{
    int nMax = graphe->nMax;
    int rd = rang (graphe, somD);
    int rg = rang (graphe, somA);
    graphe->element [rd*nMax+rg] = vrai;
    graphe->valeur  [rd*nMax+rg] = cout;
    // NB : rd*nMax+rg => permet de se positionner dans la matrice  : 
}
// Ecrire Graphe  :
void ecrireGraphe (GrapheMat* graphe)
{
    if (grapheDetruit == vrai)
    {
        printf ("Graphe a detruit ou non cree\n");
    }
    else
    {
        int nMax = graphe->nMax;
        for (int i=0; i<graphe->n; i++)
            printf ("%s ", graphe->nomS[i]);
        printf (";\n");
        for (int i=0; i<graphe->n; i++)
        {
            printf ("\n%s : ", graphe->nomS[i]);
            for (int j=0; j<graphe->n; j++)
            {
                if (graphe->element [i*nMax+j] == vrai)
                {
                    printf ("%s ", graphe->nomS[j]) ;
                    if (graphe->value)
                    {
                        printf (" (%3d) ", graphe->valeur [i*nMax+j] );
                    }
                }
            }
            printf (";");
        }
    }
}
// ------ Les parcours  : ----------

// parcours en profondeur  : 
static void profondeur(GrapheMat* graphe,int numSommet)
{
	int i,nMax=graphe->nMax;
	
	graphe->marque[numSommet]=vrai;
	
	printf("%s\n",graphe->nomS[numSommet]);
	
	for(i=0;i<graphe->n;i++)
	{
		if((graphe->element[numSommet*nMax+i]==vrai) && !graphe->marque[i])
		profondeur(graphe,i);
	}
		
}

void parcoursProfond(GrapheMat* graphe)
{
	int i;
	razMarque(graphe);
	
	for(i=0;i<graphe->n;i++)
	{
		if(!graphe->marque[i])
		profondeur(graphe,i);
	}	
}
// Parcours en largeur  : 
static void largeur (GrapheMat* graphe, int numSommet)
{
    int nMax = graphe->nMax;
    if(graphe->marque [numSommet]!=vrai)
    {
        graphe->marque [numSommet] = vrai;
        printf ("%s\n", graphe->nomS [numSommet]);
    }
    int tab[10];
    for(int i=0; i<10; i++)
    {
        tab[i]=-1;
    }
    //int j=0;
    for (int i=0,j=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            tab[j]=i;
            j++;
        }
    }
    for(int i=0; tab[i]!=-1; i++)
    {
        printf("%s\n",graphe->nomS[tab[i]]);
        graphe->marque [tab[i]] = vrai;
    }
    if(tab[0]!=-1)
        largeur(graphe,tab[0]);
    for(int i=0; i<10; i++)
    {
        tab[i]=-1;
    }
}

void parcoursLargeur(GrapheMat* graphe)
{
    razMarque (graphe);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i])
        {
            //printf("i>> %d",i);
            largeur (graphe, i);
        }
    }
}

// Algorithme de Floyd  : 
static void initFloyd(GrapheMat* graphe, Matrice* a, Matrice* p){
    int nMax = graphe->nMax; 

    Matrice ta = (int*) malloc (sizeof(int)*nMax*nMax);
    Matrice tp = (int*) malloc (sizeof(int)*nMax*nMax);

    for(int i = 0; i<graphe->n; i++){
        for(int j = 0; j<graphe->n; j++){
            ta [i*nMax+j] = graphe->valeur [i*nMax+j]; 
            tp [i*nMax+j] = i; 
        }
    }
    *a = ta; 
    *p = tp; 

}

static void ecrireEtape (Matrice a, Matrice p, int k, int ns, int nMax){
    printf("Passage par le sommet numéro %d\n", k); 

    for(int i=0; i<ns; i++){
        for(int j=0; j<ns; j++){
            if(a [i*nMax+j]==INFINI){
                printf(" %3s", "*"); 
            } else {
                printf(" %3d", a[i*nMax+j]); 
            }
        }
        printf("%6s", " "); 
        for (int j=0; j<ns; j++){
            printf("%3d", p [i*nMax+j]); 
        }
        printf("\n"); 
    }
    printf("\n"); 
}

void floyd ( GrapheMat* graphe){
    Matrice a, p; 
    int n = graphe->n; 
    int nMax = graphe->nMax; 
    initFloyd (graphe, &a, &p); 
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if ((a [i*nMax+k] != INFINI) && (a [k*nMax+j] != INFINI) && 
                    (a [i*nMax+k] + a [k*nMax+j] < a [i*nMax+j])){
                        a [i*nMax+j] = a [i*nMax+k] + a [k*nMax+j]; 
                        p [i*nMax+j] = p [k*nMax+j]; 
                    }
            }
        }
        ecrireEtape( a, p, k, n, nMax); 
    }
}

//---- Explorations : --------
/* Explorations Non informées : */
//exLargeur dabord  : 
static int exLargeur(GrapheMat* graphe, Liste* li, int numS, char but[] ){
    int nMax = graphe->nMax;
    NomSom* extraite = NULL;//Nd avec etat = pb.ei, c = 0 
    insererEnFinDeListe (li,graphe->nomS[numS]);
    graphe->marque[numS]=true;
    while (!listeVide (li) )
    {
        extraite = (NomSom*) extraireEnTeteDeListe (li);
        noeudsVisite++;
        if(strcmp(*extraite,but)==0)
        {
            printf("->%s (Noeud but) ",but);
            return 1;
        }
        numS = rang (graphe,*extraite);
        printf("->%s",*extraite);

        for (int i=0; i<graphe->nMax; i++)
        {
            if ( (graphe->element [numS*nMax+i] == vrai)
                    && !graphe->marque [i] )
            {
                insererEnFinDeListe(li,graphe->nomS[i]);
                graphe->marque[i] = vrai;
            }
        }
    }
    if(numS == graphe->n)
    {
        printf("\nNoeud but %s INTROUVABLE. ",but);
        return 0;
    }
}
void parcoursLargeurEx(GrapheMat* graphe)
{
    razMarque(graphe);
    Liste* li = creerListe();
    char str[25];
    printf("Veuillez saisir le sommet But :  \n");
    printf("-->  ");
    scanf("%s", str);
    printf("Chemin du parcours  :   ");
    int trouve=0;
    for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i])
        {
            trouve=exLargeur(graphe,li,i,str);
        }
        if(trouve==1)
            break;
    }
    printf("\nLe nombre de Noeuds visites : %d",noeudsVisite);
    noeudsVisite=0;
}
/// ExCout UN : 
static void coutUniforme (GrapheMat* graphe, Liste* li, int numSommet, int but)
{
    for(int j=0; j<100; j++)
    {
        strcpy (*(chemin+j),"");
    }
    strcpy (*(chemin+numSommet),graphe->nomS[numSommet]);
    int nMax = graphe->nMax;
    Element* extraite=NULL;
    insererEnFinDeListe (li,graphe->nomS[numSommet],cout+numSommet);
    graphe->marque [numSommet]=vrai;
    while (!listeVide (li)  )
    {
        extraite = (Element*) extraireEnTeteDeListe(li);
        noeudsVisite++;
        numSommet = rang (graphe,(char*)extraite);
        if(numSommet==but)
        {
            trouveS=vrai;
            return;
        }
        for (int i=0; i<graphe->n; i++)
        {
            if ( (graphe->element [numSommet*nMax+i] == vrai) && !graphe->marque [i] )
            {
                strcat (*(chemin+i),*(chemin+numSommet));
                strcat (*(chemin+i),"->");
                strcat (*(chemin+i),graphe->nomS[i]);
                *(cout+i)=graphe->valeur[numSommet*nMax+i]+*(cout+numSommet );

                insererEnOrdre(li,graphe->nomS[i],cout+i);
                graphe->marque[i] = vrai;

            }
            else 
            {
                booleen trouvee = chercherUnObjetBis(li,graphe->nomS[i]);
                if((graphe->element [numSommet*nMax+i] == vrai)&& trouvee &&*(cout+i)>graphe->valeur[numSommet*nMax+i]+*(cout+numSommet ))
                {
                    *(cout+i)=graphe->valeur[numSommet*nMax+i]+*(cout+numSommet ); 
                    strcpy (*(chemin+i),""); 
                    strcat (*(chemin+i),*(chemin+numSommet));
                    strcat (*(chemin+i),"->");
                    strcat (*(chemin+i),graphe->nomS[i]);
                }
            }
        }
    }
}
void parcoursCoutUniforme(GrapheMat* graphe)
{
    int but;
    printf("Entrez le numero du sommet but : ");
    scanf("%d", &but);
    Liste* li=creerListe(1);
    razMarque (graphe);
    for(int j=0; j<graphe->n; j++)
    {
        *(cout+j)=0;
    }
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i])
        {
            *(cout+i)=0;
            coutUniforme (graphe, li,i,but);
        }
        break;
    }
    if(trouveS)
    {
        printf("\n\n Le chemin trouve vers le noeud   %s   :",graphe->nomS[but]);
        printf("%s\n",*(chemin+but));
        printf("Le cout de ce chemin :  %d ",*(cout+but));
        trouveS=faux;
    }
    else
    {
        printf("\nNoeud INTROUVABLE");
    }
    printf("\nNoeuds visites : %d",noeudsVisite);
    noeudsVisite=0;
}
// ex profondeur d'abord : 
static void profondeurDabord (GrapheMat* graphe, int numSommet,char but[])
{
    int nMax = graphe->nMax;

    graphe->marque [numSommet] = vrai;
    if(strcmp(graphe->nomS[numSommet],but)==0)
    {
        check=vrai;
        printf("->%s (Noeud but) ",but);
        return ;
    }
    printf ("%s\n", graphe->nomS [numSommet]);

    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            if (check!=vrai)
                profondeurDabord (graphe, i,but);
        }
    }
}


void parcoursProfondeurDabord(GrapheMat* graphe)
{
    razMarque (graphe);
    char str[20];
    printf("Entrez le sommet but :  ");
    scanf("%s", str);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i])
        {
            profondeurDabord (graphe, i,str);
            if(check== vrai)
            {
                break;
            }
        }
    }
    if(check!=vrai)
    {
        printf("\nNoeuds INTROUVABLE");
    }

    check=faux;
}
// ProfondeurLimite : 
static booleen trouve=false;
static void profondeurLimite (GrapheMat* graphe,int k, char but[], int limite)
{
    if(!trouveS)
    {
        noeudsVisite++;
        int nMax = graphe->nMax;
        if(strcmp(graphe->nomS[k],but) == 0)
        {
            printf("%s  ",graphe->nomS[k]);
            trouveS = vrai;
            return;
        }
        else if(limite <= 0)
        {
            printf("%s  ",graphe->nomS[k]);
            graphe->marque[k] = vrai;
            return;
        }
        else
        {
            if(limite>0)
            {
                printf("%s  ",graphe->nomS[k]);
                graphe->marque[k] = vrai;
                for(int i = 0; i < graphe->n; i++)
                {
                    if ( (graphe->element [k*nMax+i] == vrai) && !graphe->marque [i] && !trouveS )
                    {
                        profondeurLimite (graphe,i, but,limite-1);
                    }
                }
            }
        }
    }
}
void parcoursProfendeurLimite(GrapheMat* graphe)
{
    razMarque(graphe);
    Liste* li = creerListe();
    char str[20];
    printf("Entrer le sommet but :  ");
    scanf("%s", str);
    int limite;
    printf("Entrer la limite :   ");
    scanf("%d",&limite);
    for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i])
            profondeurLimite(graphe,i,str,limite);

        break;
    }
    if (trouveS==faux)   printf("\nLe Noeud est INTROUVABLE\n");
    else    printf("\nLe nombre de Noeuds visites : %d",noeudsVisite);
    noeudsVisite=0;
    trouveS=faux;
}
// exIteratif : 
static void profondeurIterative (GrapheMat* graphe, int numSommet,int numNiveau,char but[])
{
    if(!trouveS)
    {
        noeudsVisite++;
        if(strcmp(graphe->nomS[numSommet],but)==0)
        {
            printf("->%s (Noeud but) ",but);
            trouveS=true;
        }
        else if(numNiveau==0)
        {
            printf ("->%s", graphe->nomS [numSommet]);
            graphe->marque [numSommet] = vrai;
        }
        else
        {
            if (numNiveau>0)
            {
                int nMax = graphe->nMax;
                graphe->marque [numSommet] = vrai;
                printf ("->%s", graphe->nomS [numSommet]);
                for (int i=0; i<graphe->n; i++)
                {
                    if ( (graphe->element [numSommet*nMax+i] == vrai)
                            && !graphe->marque [i] )
                    {
                        profondeurIterative(graphe, i, numNiveau-1,but);
                    }
                }
            }
        }
    }
}

void parcoursProfondeurIterative(GrapheMat* graphe)
{
    char str[20];
    int niveau,numNiveau=0;
    printf("Entrez le sommet but : ");
    scanf("%s", str);
    printf("Entrez la limite du recherche : ");
    scanf("%d", &niveau);
    razMarque (graphe);
    printf("Chemin du parcous en profendeur iteratif :  \n");
    for ( numNiveau=0; numNiveau<=niveau; numNiveau++)
    {
        if (trouveS)
            break;
        printf("limite %d : ",numNiveau);
        razMarque (graphe);
        for (int i=0; i<graphe->n; i++)
        {
            if(!graphe->marque[i])
                profondeurIterative(graphe,i,numNiveau,str);
            break;
        }
        printf("\n");
    }
    if(!trouveS)
    {
        trouveS=false;
        printf("\nLe noeud %s est INTROUVABLE",str);
    }
    else
    {
        printf("\n\t===== le noeud est trouve dans le parcours de limite %d =====\n\n",numNiveau-1);
    }
    printf("\nNoeuds visites : %d",noeudsVisite);
    noeudsVisite=0;
    trouveS=false;
}

/* Parcours informé : */
static void A (GrapheMat* graphe, Liste* li, int numSommet, char but[])
{
    int* fn=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0; j<graphe->n; j++)
    {
        *(fn+j)=0;
    }

//valeurs de h
    int* h=(int*)malloc(sizeof(int)*graphe->n);
    *(h)=366;
    *(h+1)=253;
    *(h+2)=329;
    *(h+3)=374;
    *(h+4)=176;
    *(h+5)=380;
    *(h+6)=193;
    *(h+7)=0;
    *(h+8)=160;
    *(h+9)=100;

    for(int j=0; j<100; j++)
    {
        strcpy (*(chemin+j),"");
    }
    strcpy (*(chemin+numSommet),graphe->nomS[numSommet]);
    int nMax = graphe->nMax;
    Element* extraite=NULL;
    *(fn+numSommet)=*(cout+numSommet)+h[numSommet];
    insererEnFinDeListe (li,graphe->nomS[numSommet],fn+numSommet);
    graphe->marque [numSommet]=vrai;
    while (!listeVide (li)  )
    {
        extraite = (Element*) extraireEnTeteDeListe(li);

        noeudsVisite++;
        numSommet = rang (graphe,(char*)extraite);
        printf("(%s,%d)\t", graphe->nomS[numSommet],fn[numSommet]);
        if(strcmp(graphe->nomS[numSommet],but)==0)
        {
            trouveS=vrai;
            return;
        }
        for (int i=0; i<graphe->n; i++)
        {
            if ( (graphe->element [numSommet*nMax+i] == vrai) && !graphe->marque [i] )
            {
                strcat (*(chemin+i),*(chemin+numSommet));
                strcat (*(chemin+i),"->");
                strcat (*(chemin+i),graphe->nomS[i]);
                *(cout+i)=graphe->valeur[numSommet*nMax+i]+*(cout+numSommet );
                *(fn+i)=*(cout+i)+h[i];
                insererEnOrdre(li,graphe->nomS[i],fn+i);
                graphe->marque[i] = vrai;

            }
            else
            {
                booleen trouvee = chercherUnObjetBis(li,graphe->nomS[i]);
                if((graphe->element [numSommet*nMax+i] == vrai)&& trouvee && *(fn+i)>graphe->valeur[numSommet*nMax+i]+*(cout+numSommet)+*(h+i))
                {
                    *(cout+i)=graphe->valeur[numSommet*nMax+i]+*(cout+numSommet ); // on met le nouveau cout
                    *(fn+i)=*(cout+i)+h[i];
                    strcpy (*(chemin+i),""); //on ecrase l'ancien chemin pour mettre le nouveau
                    strcat (*(chemin+i),*(chemin+numSommet));
                    strcat (*(chemin+i),"->");
                    strcat (*(chemin+i),graphe->nomS[i]);
                    booleen flag=extraireUnObjet(li,graphe->nomS[i]);
                    insererEnOrdre(li,graphe->nomS[i],fn+i);
                }
            }
        }
    }
}
void AEtoile (GrapheMat* graphe )
{
    char but[20];
    printf("Veuillez saisir le sommet but : ");
    scanf("%s", but);
    int num=rang(graphe,but);
    Liste* li=creerListe(1);
    razMarque (graphe);
    for(int j=0; j<graphe->n; j++)  {*(cout+j)=0;}
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i])
        {
            *(cout+i)=0;
            A (graphe, li,i,but);
        }
        break;
    }
    if(trouveS)
    {
        printf("\n\n Le chemin trouve vers Noeud   %s   :",graphe->nomS[num]);
        printf("%s\n",*(chemin+num));
        printf("Cout chemin :  %d ",*(cout+num));
        trouveS=faux;
    }
    else  {printf("\n Noeud introuvable !! ");}
    printf("\nNoeuds visites : %d",noeudsVisite);
    noeudsVisite=0;
}

// Reseau de noeuronnes : 
/* Perceptron */

float const M=0.1;
float const THETA=0.2;
int const NBRENTREE=4;
int const NBRPOIDS=2;
void modifierPoids(float w[],int d[],int x[],int e[NBRPOIDS][NBRENTREE],int i)
{
    for(int j=0; j<NBRPOIDS; j++)
    {
        w[j]=w[j]+M*((d[i]-x[i])*e[j][i]);

    }
}

int calculerSortie(float w[],int e[NBRPOIDS][NBRENTREE],int i)
{
    float resultat=0;
    int resultatTemporaire;
    for(int j=0; j<NBRPOIDS; j++)
    {
        resultat+=w[j]*e[j][i];
    }
    resultat=resultat-THETA;

    if(resultat>0)
    {
        resultatTemporaire=1;
    }
    else
        resultatTemporaire=0;

    return resultatTemporaire;
}



void perceptron()
{
    float w[NBRPOIDS]= {0.3,-0.1};
    int e[NBRPOIDS][NBRENTREE]= {{0,0,1,1},{0,1,0,1}};
    int d[NBRENTREE]= {0,0,0,1};
    int x[NBRENTREE];
    booleen fini=false;
    int nbrOK=0;
    while(!fini)
    {
        nbrOK=0;
        printf("e1  e2  d      w1          w2     x    w1Final   w2Final   \n");
        for (int i=0; i<NBRENTREE; i++)
        {
            x[i]=calculerSortie(w,e,i);
            printf("%d   %d   %d   %f   %f   %d   ",e[0][i],e[1][i],d[i],w[0],w[1],x[i]);
            if(x[i]!=d[i])
            {
                modifierPoids(w,d,x,e,i);
            }
            else
                nbrOK++;
            printf("%f  %f",w[0],w[1]);
            if(nbrOK==4)
                fini=true;
            printf("\n");
        }
        printf("\n");
        printf("\n");
        printf("\n");
    }
}

// perceptron multicouches : 
float sigmoide(float x)
{
    return 1/(1+exp(-x));
}

void perceptronMulticouche()
{
    float w[7][8]= {{0,0,0,0,0,0,0,0},
        {0,0,0,0.5,-1,0,0,0},
        {0,0,0,1.5,-2,0,0,0},
        {0,0,0,0,0,1,-1,0},
        {0,0,0,0,0,3,-4,0},
        {0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,-3}
    };
    float temp=0.0;
    float alpha=0.1;
    float delta[8]= {0,0,0,0,0,0,0,0};
    float in[8]= {0,0,0,0,0,0,0,0};

    float a[8]= {0,0,0,0,0,0,0,0};
    float x[3]= {0,2,-1};
    printf(" Propagation Avant \n\n");
    do{
        for(int i=0; i<3; i++)
        {
            a[i]=x[i];
        }

        for( int j=3; j<=7; j++)
        {
            for( int i=0; i<7; i++)
            {
                in[j]+=w[i][j]*a[i];
            }
            a[j]=sigmoide(in[j]);
        }
        for(int j=1; j<7+1; j++)
        {
            printf("\ta%d  ====  %f\n",j,a[j]);
        }
        delta[7]=1-a[7];
        printf("\n\n");
        printf(" Retropropagation \n\n");
        printf("\tDelta7  ====  %f\n",delta[7]);
        for(int i=6; i>2; i--)
        {
            for(int j=1; j<8; j++)
            {
                temp+=w[i][j]*delta[j];

            }
            delta[i]=sigmoide(in[i])*(1-sigmoide(in[i]))*temp;
            printf("\tDelta%d  ====  %f\n",i,delta[i]);
            temp=0;
        }
        printf("\n\n");
        for(int i=1; i<7; i++)
        {
            for(int j=1; j<8; j++)
            {
                if(w[i][j]!=0)
                {
                    w[i][j]=w[i][j]+alpha*a[i]*delta[j];
                }
            }
        }
        for(int i=1; i<7; i++)
        {
            for(int j=1; j<8; j++)
            {
                if(w[i][j]!=0)
                {
                    printf("\tW%d%d  ====  %f\n",i,j,w[i][j]);
                }
            }
        }
        printf("\n\n");
        if((delta[7]>0.1))printf("Propagation Avant \n\n");
    }while(delta[7]>0.1);
}



