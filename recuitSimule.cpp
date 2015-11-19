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

using namespace std;
using namespace std::chrono;

//Struct for an item and whether or not it has been placed
struct Item
{
    int v_item;
    int in_box;
    int place_in_list;
};

//Struct for a box
struct Box
{
    std::vector<Item> things;
    int occupied;
};

bool critere_metropolis(int delta, double theta){
    bool b;
    if(delta>=0)
        return true; 
    else if(exp(delta/theta)>=rand())
        return true;
    return false;
}

*int[] voisin(Item[] items,Box[] boxes,int m,int c)
{
    //choose an item not already placed
    //put it in a box randomly chosen (uniform probability distribution)
    //if box overflow, choose random item in this box and put it out
    //until no overflow
    //return new box set

    //find last unplaced item
    //items is sorted before this
    int i=0;
    while(items[i].placed==0)
        i++;

    //choice of random item
    int r=rand() %i; 

    //choice of random box
    int s=rand() %m; 

    //item placement
    if(items[r].vi+boxes[s].occupied<=c)
    {
        items[r].placed=1;
        boxes[s].things.push_back(items[r]);
        boxes[s].occupied+=items[r].vi;
    }
    else
    {
        items[r].placed=1;
        boxes[s].things.push_back(items[r]);
        boxes[s].occupied+=items[r].vi;
        //Removal of random element in the box
        int t=rand() %boxes[s].things.size();
        int index=boxes[s].things.at(t).place_in_list;
        //Erasure from the box
        boxes[s].things.erase(boxes[s].things.begin()+t);
        boxes[s].occupied-=items[index].vi;
        //Marked as not placed in items list
        items[index].in_box=0;
    }

}

*int[] recuit_simule(int[] I,int m, n, c, k_max, double T, P, alpha){
    int[m]
}

int main(int argc, char *argv[]){ 
    int n;
    int m;
    int c;
    //Lecture du fichier et enregistrement des volumes dans un array arr
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-f") {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv! 
                ifstream myfile(argv[i+1]);
                if(myfile)
                {
                    //Recuperation de n, m et c
                    myfile >> n;
                    myfile >> m;
                    myfile >> c;
                    int items[n][2];
                    for(int i=0;i<n;i++)
                    {
                        myfile >> items[i][0];
                        items[i][1]=0;
                    }
                }
                else
                {
                    cout << "Erreur d'ouverture du fichier" << endl;
                }
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "l'option -f nécessite le nom du fichier en argument" << std::endl;
            }
            return 1;
        } 
        //La taille de l'array est n

        int boites[m];
    }
    return 0;

}

/*
 * Pour la performance : moyenne des capacités résiduelles (somme de ce qui reste dans chaque boite)
 * sur plusieurs exemplaires de meme taille
 */
