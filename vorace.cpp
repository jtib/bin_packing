#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <array>

using namespace std;
using namespace std::chrono;

//Placement d'un item dans une boite
//vi est le volume de l'item a placer
//c est la capacite d'une boite
//boites est le tableau du remplissage actuel des boites
void placement_unitaire(int vi, int c, int boites[], int m){ 
    int min_actuel = c;
    int indice = 0;
    for(int i=0; i<m; i++){
        if(boites[i]+vi <= min_actuel){
            indice=i;
            min_actuel=boites[i]+vi;
        }
   }
}

bool decroissant(int i, int j){return i>j;}

int main(int argc, char *argv[]){
    //int arr[];
    int n;
    int m;
    int c;
    //Lecture du fichier et enregistrement des volumes dans un array arr
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-f") {
           if (i + 1 < argc) { //S'assurer qu'on n'est pas a la fin de argv
			   // TODO: comprendre comment lire ce fichier et achever les lignes qui suivent...
               ifstream myfile;
               myfile.open(argv[i++]);
               int ints[3];
               // Je ne sais plus ce que je voulais faire ><
               std::string input;
               std::getline(myfile, input);
               std::istringstream(input) >> ints[0] >> ints[1] >> ints[2];
               n = ints[0];
               i++;
           } else { // Si pas de fichier destination indique apres -f
			   std::cerr << "l'option -f nécessite le nom du fichier en argument" << std::endl;
           }
		return 1;
	    }
    }
    //La taille de l'array est n
    sort(arr,arr+n,decroissant);
    int boites[m];
    for(int j=1;j<m;j++)
        boites[j]=0;

    for(int k=1;k<n;k++){
        placement_unitaire(arr[k],c,boites,m);
    }
return 0;
}
