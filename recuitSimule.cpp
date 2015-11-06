#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <array>
#include <cmath>


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

*int[] voisin(int[][] S){
    //choose an item not already placed
    //put it in a box randomly chosen (uniform probability distribution)
    //if box overflow, choose random item in this box and put it out
    //until no overflow
    //return new box set
}

int main(int argc, char *argv[]){
    

}

/*
 * Pour la performance : moyenne des capacités résiduelles (somme de ce qui reste dans chaque boite)
 * sur plusieurs exemplaires de meme taille
 */
