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

//Function for sorting items according to in_box
bool sort_in_box_or_not(Item litem, Item ritem)
{
    return litem.in_box <= ritem.in_box;
}

std::vector<Box> voisin(std::vector<Item> items,std::vector<Box> boxes,int m,int c)
{
    //choose an item not already placed
    //put it in a box randomly chosen (uniform probability distribution)
    //if box overflow, choose random item in this box and put it out
    //until no overflow
    //return new box set

    //find last unplaced item
    int i=0;
    while(items[i].in_box==0)
        i++;

    //choice of random item
    int r=rand() %i; 

    //choice of random box
    int s=rand() %m; 

    //item placement
    if(items[r].v_item+boxes[s].occupied<=c)
    {
        items[r].in_box=1;
        boxes[s].things.push_back(items[r]);
        boxes[s].occupied+=items[r].v_item;
    }
    else
    {
        items[r].in_box=1;
        boxes[s].things.push_back(items[r]);
        boxes[s].occupied+=items[r].v_item;
        //Removal of random element in the box
        int t=rand() %boxes[s].things.size();
        int index=boxes[s].things.at(t).place_in_list;
        //Erasure from the box
        boxes[s].things.erase(boxes[s].things.begin()+t);
        boxes[s].occupied-=items[index].v_item;
        //Marked as not placed in items list
        items[index].in_box=0;
    }
    return boxes;
}

int volume(std::vector<Box> boxes,int m)
{
    int s=0;
    for(int i=0;i<m;i++)
    {
        s+=boxes[i].occupied;
    }
    return s;
}


std::vector<Box> recuit_simule(std::vector<Item> items,int m,int n,int c, int k_max, double T, double P, double alpha){
    //Creation of a set of empty boxes
    std::vector<Box> S;
    Box b;
    b.occupied=0;
    S.assign(m,b);

    //Other declarations/initializations
    std::vector<Box> S_meilleur=S;
    double theta = T;
    std::vector<Box> S_prime;
    int delta;

    for(int k=1;k<=k_max;k++)
    {
        for(int j=1;j<=P;j++)
        {
            S_prime=voisin(items,S,m,c);
            delta=volume(S_prime,m)-volume(S,m);
            if(critere_metropolis(delta,theta))
            {
                S=S_prime;
                if(volume(S,m)>volume(S_meilleur,m))
                    S_meilleur=S;
            }
        }
        theta=theta*alpha;
    }
    return S_meilleur;
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
                    //int arr[n];
                    std::vector<Item> items;
                    for(vector<Item>::size_type i=0;i<n;i++)
                    {
                        //myfile >> arr[i];
                        myfile >> items[i].v_item;
                        items[i].in_box=0;
                        items[i].place_in_list=i;
                    }

                    //sort items
                    sort(items.begin(),items.end(),sort_in_box_or_not);

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
    }
    return 0;
}

/*
 * Pour la performance : moyenne des capacités résiduelles (somme de ce qui reste dans chaque boite)
 * sur plusieurs exemplaires de meme taille
 */
