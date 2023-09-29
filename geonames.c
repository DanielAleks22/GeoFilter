/**
* geonames.c
*
* Description: Un programme qui tire de l'information d'une base de donnnees
* connu sous le nom GeoNames, qui ensuite permet a l'utilisateur de trier en ordre
* croissant un nombre de pays que lui meme donne en argument.
* 
* Auteur: Aleksandrov Daniel (ALED22119901)
* Date: 09/10/2022
* Version: 1.0
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USAGE "\
Usage: %s <NUMBER OF CITIES>\n\
\n\
Display a table of the n most populous cities on stdout. The number of cities must not exceed 5000.\n\
\n\
If no argument is provided, the program prints this help and exit.\n\
\n\
Program parameters :\n\
  NUMBER of cities         Number de cities to print (1..500)\n\
  "

#define FORMAT_TITRE    "%4s   %-20.20s   %-20.20s   %s\n"
#define FORMAT_COLONNES "%4d   %-20.20s   %-20.20s   %10ld\n"
#define TAILLE_BUFFER 5000
#define LONG_NOM_PAYS 50
#define LONG_NOM_VILLE 100
#define LONG_CODE_PAYS 3
#define MIN_ARG 1
#define MAX_ARG 5000

struct Pays {
    char nom[LONG_NOM_PAYS]; // Le nom du pays
    char code[LONG_CODE_PAYS]; // Le code de deux lettres identifiant le pays
};
const struct Pays PAYS_BIDON = {"??", "??"};

struct Ville {
    char nom[LONG_NOM_VILLE];    // Le nom ASCII de la ville
    long population;  // La population
    struct Pays pays; // Le pays dans laquelle la ville existe
};
const struct Ville VILLE_BIDON = {"??", -1, {"??", "??"}};

/**
 * -----------------------
 * Codes d'erreur
 * -----------------------
 */

enum error {
    OK                      = 0,
    ERREUR_NB_ARGS          = 1,
    ERREUR_NB_VILLES        = 2,
    ERREUR_ARGS_TYPE	    = 3,
    ERREUR_LECTURE			= 4,
    ERREUR_FERMETURE		= 5
};

/*
* Decoupe un buffer recu en argument, extrait les champs necessair 
* pour la creation de la struct "Ville"
*
* @param buffer		Pointeur vers le buffer a decouper
* @return			Une struct de type Ville
*/
struct Ville extrait_champ_buff_ville(char *buffer);

/*
* Decoupe un buffer recu en argument, extrait les champs necessair 
* pour la creation de la struct "Pays"
*
* @param buffer		Pointeur vers le buffer a decouper
* @return			Une struct de type Pays
*/
struct Pays extrait_champ_buff_pays(char *buffer);

/**
* Valide le string recu par la redirection d'un fichier a partir du stdin
*
* @param argv		Le string a valider
* @param taille		La taille du string recu en parametre
* @return			Le nombre de ville extrai du string s'il passe toutes les validations
*/
int valide_stdin(char *argv, int taille);

/**
* Compare la population entre deux structures
*
* @param ville1		La premiere ville
* @param ville2		La premiere ville
* return			La population qui est plus grande
*/
int compare_pop(const void *ville1, const void *ville2);

/**
* Compare des codes de pays jusqu'a temps que deux code identiques sont trouver,
* a ce moment un pointeur vers le nom du pays en question sera retourner
*
* @param code_pays			Un pointeur vers le string du code pays
* @param Pays tab_pays		Un pointeur vers un tab de type Pays qui contient les info
* @param nb_ele_tab			Le nombre d'elements dans le tableau
* @return		Un pointeur vers le debut de la chaine de char qui definit le pays 
*/
char* remplace_code_nom(char *code_pays, struct Pays *tab_pays, int nb_ele_tab);

struct Ville extrait_champ_buff_ville(char *buffer){
	struct Ville ville_courante;
	int pop_courante;
	char sous_string[strlen(buffer)];
	int index_debut_str = 0;
	int index_fin_str = 0;
	int index_fin_delim = 0;
	int compteur_tab = 0;	
    	
   	for(long unsigned int i = 0; i < strlen(buffer); i++)
   	{
   		if(buffer[i] == '\t')
   		{
   			compteur_tab++;
   			index_fin_delim = i;
   			index_fin_str = index_fin_delim - 1;
   			strncpy(sous_string, buffer + index_debut_str, (index_fin_str - index_debut_str) + 1);
   			index_debut_str = index_fin_delim + 1;
   			
   			if(compteur_tab == 3)
   			{			
   				strcpy(ville_courante.nom, sous_string);
   				
   			} else if (compteur_tab == 9)
   			{
   				strcpy(ville_courante.pays.code, sous_string);
   				
   			} else if (compteur_tab == 15)
   			{
   				pop_courante = atoi(sous_string);
   				ville_courante.population = pop_courante;
   			}
   			//Reintialise le sous_string
   			memset(sous_string, '\0', sizeof sous_string);
   				
   		}
   	}
	
	return ville_courante;
}

struct Pays extrait_champ_buff_pays(char *buffer){
	struct Pays pays_courant;
	char str_courant[strlen(buffer)];
	char delim[5] = "\t";
	int compteur = 0;
	
	char *tok = strtok (buffer, delim);
    //Reinitialiser le compteur
    compteur = 0; 	

    if(!(buffer[0] == '#')){

    	while ((tok != NULL)) 
    	{
       		strcpy(str_courant, tok);
        		
       		if(compteur == 0)
       		{
       			strcpy(pays_courant.code, str_courant);	
       		}
       		if(compteur == 3)
       		{
       			if(strlen(str_courant) != 2)
       			{
       				strcpy(pays_courant.nom, str_courant);
       				compteur = 5;
       			}
       		}
       		if(compteur == 4)
       		{
       			strcpy(pays_courant.nom, str_courant);
       		}
        				
			compteur++;
       		//Permet de parcourir les delimiteurs
       		tok = strtok(NULL, delim); 
  
       	}    				
    }
	
	return pays_courant;
}


int valide_stdin(char *argv, int taille_str){
	int nb_ville_arg = 0;
		
	for (int i = 0; i < taille_str; i++)
	{
		if(!((argv[i] >= '0') && (argv[i] <= '9')))
		{
			printf("type argument invalide");
			exit(ERREUR_ARGS_TYPE);
		}	
	}
	
	nb_ville_arg = atoi(argv);
	
	if(nb_ville_arg < MIN_ARG || nb_ville_arg > MAX_ARG)
	{
		printf("nombre de ville invalide");
		exit(ERREUR_NB_VILLES);
	}
	
	return nb_ville_arg;	
}

int compare_pop(const void *ville1, const void *ville2) {

	struct Ville *villeA =  (struct Ville *)ville1;
	struct Ville *villeB =  (struct Ville *)ville2;
	
	return (villeB->population - villeA->population);
}

char* remplace_code_nom(char *code_pays, struct Pays *tab_pays, int nb_ele_tab){

	struct Pays *tab_de_pays = (struct Pays *)tab_pays;
	int valeur_cmp = 1;
	char *retour;
	
	for (int i = 0; i < nb_ele_tab; i++)
	{
		valeur_cmp = strcmp(tab_de_pays[i].code, code_pays);
		
		if (valeur_cmp == 0)
		{
			retour = tab_de_pays[i].nom;
		}
	}
	
	return retour;
}

int main(int argc, char *argv[]) {

	char buffer[TAILLE_BUFFER + 1];	
    int comp_tab_ville = 0;
    int comp_tab_pays = 0;
    struct Ville tab_ville[30000];
    struct Pays tab_pays[300];
    int arg_ville;


  	if(argc != 2)
  	{
  		printf("nombre arguments invalide\n");
  		printf(USAGE,argv[0]);
		exit(ERREUR_NB_ARGS);
  	}
  
  	char str_argv[strlen(argv[1])];
  	strcpy(str_argv, argv[1]);
  	arg_ville = valide_stdin(str_argv, strlen(str_argv));
	 		
	//Lecture fichier cities15000
    FILE *fichier = fopen("cities15000.txt", "r");
    
    if (fichier == NULL) 
    {    	
    	printf("Erreur de lecture\n");
    	exit(ERREUR_LECTURE);
    }
    
   	while ((fgets(buffer, TAILLE_BUFFER, fichier) != NULL))
   	{
   		tab_ville[comp_tab_ville] = extrait_champ_buff_ville(buffer);
    	comp_tab_ville++;
   	}  
   	
   	if (fclose(fichier) == EOF)
    {
        printf ( "Erreur lors de la fermeture du fichier.\n" );
        exit(ERREUR_FERMETURE);
    }
    
    //Lecture fichier countryInfo
    FILE *fichier2 = fopen("countryInfo.txt", "r");
    
    if (fichier2 == NULL) 
    {    	
    	printf("Erreur de lecture\n");
    	exit(ERREUR_LECTURE);
    }
    
   	while ((fgets(buffer, TAILLE_BUFFER, fichier2) != NULL))
   	{  
   		tab_pays[comp_tab_pays] = extrait_champ_buff_pays(buffer);
    	comp_tab_pays++;
    }
    
    if (fclose(fichier) == EOF)
    {
        printf ( "Erreur lors de la fermeture du fichier.\n" );
        exit(ERREUR_FERMETURE);
    }
    
    
    qsort(tab_ville, comp_tab_ville, sizeof(struct Ville), compare_pop);
    
    printf(FORMAT_TITRE,"Rang", "Nom", "Pays", "Population");
    printf(FORMAT_TITRE,"----","---","----","----------");
    for (int i = 0; i < arg_ville; i++)
    {
    	printf(FORMAT_COLONNES,(i+1) ,tab_ville[i].nom, remplace_code_nom(tab_ville[i].pays.code, 
    			tab_pays, comp_tab_pays), tab_ville[i].population);
    }
    
    
    return 0;
}







