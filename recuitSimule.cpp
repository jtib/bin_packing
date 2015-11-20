#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <array>
#include <cmath>
#include <fstream>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

bool critere_metropolis(int delta, double theta){
    bool b;
    if(delta>=0)
        return true; 
    else if(exp(delta/theta)>=rand())
        return true;
    return false;
}

std::vector<vector<int> > voisin(std::vector<vector<int> > *boxes,std::vector<int> *placed, std::vector<int> *not_placed, int m,int c)
{
    //choose an item not already placed
    //put it in a box randomly chosen (uniform probability distribution)
    //if box overflow, choose random item in this box and put it out
    //until no overflow
    //return new box set
    int r;
    int s;
    int a;
    int v_to_place;
    int v_to_remove;
    int box_volume;
    std::vector<int>::iterator it;
    int nplcd=(*not_placed).size();
    int plcd=(*placed).size();
    std::vector<vector<int> > myvec(m);
    std::copy((*boxes).begin(),(*boxes).end(),myvec.begin());
    //std::vector<int> *neighbor

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    //choice of random item
    std::uniform_int_distribution<int> distribution_r(0,nplcd-1);
    r=distribution_r(generator);

    //choice of random box
    std::uniform_int_distribution<int> distribution_s(0,m-1);
    s=distribution_s(generator);

    //addition of new volume to selected box
    v_to_place=(*not_placed)[r];
    myvec[s].push_back(v_to_place);
    int size_box=myvec[s].size();

    //mv placed/v_to_place not_placed/
    (*not_placed).erase((*not_placed).begin()+r);
    (*placed).push_back(v_to_place);
    int size_placed=(*placed).size();

    //Box volume > c?
    box_volume=0;
    for(int vol : myvec[s])
        box_volume+=vol;

    //Removal of random item from box
    while(box_volume>c)
    {
        int box_size=myvec[s].size();
        std::uniform_int_distribution<int> distribution_a(0,box_size-1);
        a=distribution_a(generator);

        v_to_remove=myvec[s][a];
        myvec[s].erase(myvec[s].begin()+a);

        it=find((*placed).begin(),(*placed).end(),v_to_remove);
        int index=it-(*placed).begin();
        (*placed).erase((*placed).begin()+index);
        (*not_placed).push_back(v_to_remove);

        //Box volume > c?
        box_volume=0;
        for(int vol : myvec[s])
            box_volume+=vol;
    }

    return myvec;
}

int volume_solution(std::vector<vector<int> > *sol,int m)
{
    int box_volume;
    int volume=0;
    for(int i=0;i<m;i++)
    {
        box_volume=0;
        for(int vol : (*sol)[i])
            box_volume+=vol;
        volume+=box_volume;
    }
    cout << volume << endl;
    return volume;
}

std::vector<vector<int> > recuit_simule(std::vector<int> *items,int m,int n,int c, int k_max, double T, int P, double alpha){
    //Creation of a set of empty boxes
    std::vector<vector<int> > *S = new std::vector<vector<int> >;
    (*S).resize(m);

    //Other declarations/initializations
    std::vector<vector<int> > *S_meilleur=new std::vector<vector<int> >;
    *S_meilleur=*S;
    double theta = T;
    std::vector<vector<int> > *S_prime=new std::vector<vector<int> >;
    int delta;
    std::vector<int> *not_placed=new std::vector<int>;
    *not_placed=*items;
    std::vector<int> *placed=new vector<int>;

    for(int k=1;k<=k_max;k++)
    {
        for(int j=1;j<=P;j++)
        {
            *S_prime=voisin(S,placed,not_placed,m,c);
            cout << "voisin ok" << endl;
            delta=volume_solution(S_prime,m)-volume_solution(S,m);
            cout << delta << endl;
            if(critere_metropolis(delta,theta))
            {
                S=S_prime;
                if(volume_solution(S,m)>volume_solution(S_meilleur,m))
                    S_meilleur=S;
            }
        }
        theta=theta*alpha;
    }
    return *S_meilleur;
}

int main(int argc, char *argv[]){ 
    int n;
    int m;
    int c;
    int volumeTotalBoites;
    int volumeTotalItems;
    int vi;

    //Lecture du fichier et enregistrement des volumes dans un array items
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-f") {
            if (i + 1 < argc) { // Attention a la fin de argv
                ifstream myfile(argv[i+1]);
                if(myfile)
                {
                    //Recuperation de n, m et c
                    myfile >> n;
                    myfile >> m;
                    myfile >> c;
                    std::vector<int> *items=new vector<int>;
                    //(*items).resize(n);

                    //Calcul du volume total des items et ajout dans le vecteur d'items
                    volumeTotalItems=0;
                    for(vector<int>::size_type i=0;i<n;i++)
                    {

                        myfile >> vi;
                        (*items).push_back(vi);
                        volumeTotalItems+=vi;
                    }

                    //Volume total des boîtes
                    volumeTotalBoites=c*m;

                    int k_max=20;
                    double T=40;
                    int P=20;
                    double alpha=0.99;
                    std::vector<vector<int> > *solution;

                    //On debute la mesure du temps de calcul apres la derniere declaration
                    auto start=std::chrono::high_resolution_clock::now();

                    (*solution)=recuit_simule(items,m,n,c,k_max,T,P,alpha);

                    //On arrête la mesure du temps de calcul après la fonction qui place les items dans les boites
                    auto finish = std::chrono::high_resolution_clock::now();
                    //Calcul du temps d'execution 
                    auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

                    cout << "Volume totale de boites : " << volumeTotalBoites << endl;
                    cout << "Volume total des items : " << volumeTotalItems << endl;
                    cout << "Temps de calcul : " << microsec.count() << " ms" << endl;

                    //On regarde si le paramètre -p a été mis
                    for(int j=1;j<argc;j++){
                        if(j  < argc && std::string(argv[j]) == "-p"){
                            for(int k=1;k<=m;k++)
                                cout << "Contenu de la boite " << k << " : " << endl;
                        }
                    }
                }
                else
                {
                    cout << "Erreur d'ouverture du fichier" << endl;
                }
            } else { // Pas de chemin vers un fichier
                std::cerr << "l'option -f nécessite le nom du fichier en argument" << std::endl;
            }
            return 1;
        } 
    }
    return 0;
}

/*
 * Pour la performance : moyenne des capacités résiduelles (somme de ce qui reste dans chaque boite)
 * sur plusieurs exemplaires de meme taille
 */
