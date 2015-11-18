#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

void placement_unitaire(int vi, int c, int boites[], int m,string contenu[]){
    int min_actuel = c;
    bool fill = false;
    for(int i=0; i<m; i++){
        if(boites[i] + vi <= min_actuel && !fill){
            min_actuel=boites[i]+vi;
            boites[i] += vi;
            contenu[i] +=  to_string(vi) + " | ";
            fill = true;
        }
    }
}
bool decroissant(int i, int j){return i>j;}
int main(int argc, char *argv[]){

    //Contenu des boites
    string *contenu;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-f") {
            if (i + 1 < argc) {  
                vector<int> arr;
                int n;
                int m;
                int c;
                //Lecture du fichier et enregistrement des volumes dans un array arr
                //informations
                int volumeTotalBoites = 0;
                int volumeTotalItems = 0;
                float tempsCalcul = 0;

                //Lecture du fichier et enregistrement des volumes dans un array arr
                ifstream myFile;
                myFile.open(argv[i+1]);
                std::string input;
                std::getline(myFile, input);
                std::istringstream stream(input);
                stream >> n >> m >> c;
                cout << "Les valeurs de n, m et c sont respectivement : " << n << " , " << m << " , " << c << endl;
                std::string volume;
                std::getline(myFile, volume);
                std::istringstream streamV(volume);
                int nums[n];

                for(int j=0 ; j < n ; j++){
                    streamV >> nums[j];
                    arr.push_back(nums[j]);
                }

                //Calcul du volume total des items
                for(int j=0;j<n;j++)
                    volumeTotalItems += arr[j];

                //On initiale le nombre de boites en les mettant vide
                int boites[m];
                for(int j=0;j<m;j++)
                    boites[j]=0;

                //Volume totale 
                volumeTotalBoites = c * m;

                contenu = new string[m];

                //On débute la mesure du temps de calcul à partir du tri des volumes des items
                auto start = std::chrono::high_resolution_clock::now();

                //Tri de l'array
                sort(arr.begin(),arr.end(),decroissant);

                for(int k=0;k<n;k++){
                    placement_unitaire(arr[k],c,boites,m,contenu);
                }

                //On arrête la mesure du temps de calcul après la fonction qui place les items dans les boites
                auto finish = std::chrono::high_resolution_clock::now();
                //Calcul du temps d'execution 
                auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

                cout << "Volume totale de boites : " << volumeTotalBoites << endl;
                cout << "Volume total des items : " << volumeTotalItems << endl;
                cout << "Temps de calcul : " << microseconds.count() << " ms" << endl;

                //On regarde si le paramètre -p a été mis
                for(int j=1;j<argc;j++){
                    if(j  < argc && std::string(argv[j]) == "-p"){
                        for(int k=1;k<=m;k++)
                            cout << "Contenu de la boite " << k << " : " << contenu[k-1] << endl;
                    }
                }

                //suppression du tableau dynamique
                delete[] contenu;

            }
            else { //Pas de nom de fichier en argument
                std::cerr << "l'option -f nécessite le nom du fichier en argument" << std::endl;
            }
        }
    }
    return 0;
}
