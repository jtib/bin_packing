#include <iostream>
#include <array>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

/*
 * c : capacite des boites
 * m : nombre de boites
 */
template<std::size_t size>
void f(int c, int m, std::array<int, size> arr)
{
    if( c > 0) {
        for(int i=0; i<=m; i++) {
            arr[size - 1 - c] = m - i;
            f(c-1, i, arr);
        }
    } else {
        arr[size - 1] = m;
        for(auto e : arr)
            std::cout << e << " ";
        std::cout << std::endl;
    }
}

template<std::size_t c>
void fd(int m)
{
    std::array<int, c+1> arr;
    f(c, m, arr);
}

int 
    
}

int boite_dynamique(int m, int c, int n, int vi[]){
    //Creation du tableau T
    //Probleme : tableau a deux dimensions (a priori) mais la deuxieme dimension n'est
    //pas referencee directement par un indice mais par la combinaison des differentes boites
    //=> au lieu de mettre "colonne j", on sera a la "colonne (a,b,c,etc.)"
    //avec a+b+c+...=m (le nombre de boites)a
    //possibilites : trouver un moyen d'indexer l'array comme ça
    //autre possibilite : calculer l'indice a partir du (m+1)-uplet avec une autre fonction
    //Solution : dictionnaire fait a la generation des tuples
    //on peut d'ailleurs ne maintenir que deux lignes du tableau, on gagne en espace
    //"Remplissage" du "tableau" T
    //Initialisation des valeurs frontiere
    
}

int main()
{
    // 5 boites de capacite 3
    fd<3>(5);

    return 0;
}
