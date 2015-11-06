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
/*
int boite_dynamique(int m, int c, int n, int vi[], int *T[]){
    //Remplissage du tableau T
    //Initialisation des valeurs frontiere
    return 0;
}*/

int main()
{
    // 5 boites de capacite 3
    fd<3>(5);

    return 0;
}
