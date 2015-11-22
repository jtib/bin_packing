#include <iostream>
#include <array>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>


//get indexes on previous buffer 
struct Repartition {
    int capa;
    int m;
    int *Data;
    //----

    Repartition(int c,int m_rep) {
        capa=c;
        m=m_rep;
        Data=(int*) calloc(capa+1, sizeof(int));;
        Data[0] = m; };
        //-
        const int& operator[] (int i) const {return Data[i];};
        /* */ int& operator[] (int i) /* */ {return Data[i];};
        //-
        Repartition& operator--(){
            Repartition& r = *this;
            int cnt = r.Data[capa];
            if (cnt==m){
                printf("Should not happen!\n");
                return r;
            }
            int* pIt = &r.Data[capa];
            bool b(true);
            while (b){
                --pIt;
                if ((*pIt)!=0){
                    --(*pIt);
                    *(++pIt) = cnt+1;
                    b=false;
                }
                cnt+=*pIt;
            }
            while (++pIt<&r.Data[capa+1])
                *pIt = 0;
            return r;
        };
        void renew(){
            memset(Data, 0, (capa+1)*sizeof(int));
            Data[0] = m;
        }
        void print(){
            for (int i=0; i<capa+1; ++i)
                std::cout << Data[i] << " ";
            std::cout << std::endl;
        }
};

// c parmi (m+c) = [(m+1)*..*(m+c)]/(c!)
int weakCompo(const int c, const int m){
    if (c<0) {return 0;}
    if (c>m) {return weakCompo(m, c);}
    int num(1), den(1);
    for (int i=0; i++<c;)
    {
        num*=m+i;
        den*=i;
    }
    return num/den;
};

// (c-1 parmi m+c-1) - (c-1 parmi w-1+c-1)
//template<std::size_t capa, std::size_t m>
int lastIndexForWeight(int w,int capa,int m){
    int wcp = weakCompo(capa, m);
    int wcm = weakCompo(w-1, m);
    return (wcp - wcm);
};

// To calculate where to go next
//template<std::size_t capa, std::size_t m>
int prevBufferIndex(const Repartition& currentRepart, int k, int vi, int capa, int m){
    Repartition tempRepart = *new Repartition(capa,m);
    memcpy(tempRepart.Data, currentRepart.Data, tempRepart.capa*sizeof(int));
    if (tempRepart[capa-k]>0){
        --tempRepart[capa-k];
        ++tempRepart[capa-(k-vi)];
        int acc(0), cnt(m);
        for(int i=0; i<capa; ++i)
        {
            int endj(tempRepart[i]);
            for (int j=0; j<endj ; ++j){
                acc += weakCompo(capa-i-1, cnt-j);
            }
            cnt -= endj;
        }
        return weakCompo(capa, m) - acc -1;
    }
    return -1;
};

bool descending(int i, int j){return i>j;}

//template<std::size_t capa, std::size_t m>
int boite_dynamique(const int n, int vi[],int capa,int m, bool display){
    //Creation du tableau T
    //Problem : 2-dim array with several numbers for second index
    //Solution : map with first index and second index as key and volume as value

    // Let's sort the weights in descending order
    std::sort(vi,vi+n,descending);

    // Let's Initialize 2 buffers
    const int BufferSize = weakCompo(capa, m);
    int* BufferDataIprev = (int*) calloc(BufferSize, sizeof(int));
    int* BufferDataI = (int*) calloc(BufferSize, sizeof(int));
    int  Trace[BufferSize][n];// = {-1};
    int  iLastIndex(0);

    Repartition currentRepartition(capa,m);


    // Let's Iterate throuht the weights
    for (int iObject=0; iObject<n; ++iObject)
    {
        // Swap iteration Buffer
        {
            int* tb = BufferDataIprev;
            BufferDataIprev = BufferDataI;
            BufferDataI = tb;
        }

        currentRepartition.renew();

        // Get Next weight in line
        int objectWeight = vi[iObject];
        // Calculate LastIndex which matters for this weight
        iLastIndex = lastIndexForWeight(objectWeight,capa,m);

        // Iterate on the different configurations
        for (int iCurrentIndex=0; iCurrentIndex < iLastIndex; ++iCurrentIndex, --currentRepartition)
        {
            int currentMaxWeight = BufferDataIprev[iCurrentIndex];
            // Compose through what is necessary
            for (int k=objectWeight; k<=capa; ++k)
            {
                int iPrev = prevBufferIndex(currentRepartition, k, objectWeight, capa, m);
                if (iPrev>=0)
                {
                    int compWeight = objectWeight + BufferDataIprev[iPrev];
                    if (compWeight > currentMaxWeight){
                        currentMaxWeight = compWeight;
                        //---- Start Trace
                        memcpy(Trace[iCurrentIndex], Trace[iPrev], n*sizeof(int));
                        Trace[iCurrentIndex][iObject] = capa-k;
                        //---- End Trace
                    }
                }
            }
            BufferDataI[iCurrentIndex] = currentMaxWeight;
        }

        // End of Loop, i-1 -> i

    }
    delete BufferDataIprev;

    // --- Analyse du résultat --- 
    //std::cout << "//--- Analyse des résultats ---//" << std::endl;
    //Volume maximal atteignable
    std::cout << n << "," << m << "," << BufferDataI[0] << std::endl;

    if(display)
    {
        // --- Affichage des cases ---
        int Cases[m];
        std::vector<std::vector<int> > casesVec;
        casesVec.resize(m);
        //int* itStart = Cases;
        //int* itEnd   = &Cases[m];
        for (int j=0; j<m; ++j) { Cases[j]=capa; }
        std::cout << std::endl;
        for (int i=0; i<n; ++i)
        {
            for (int j=0; j<m; ++j){
                if (Cases[j]>=vi[i]){
                    casesVec[j].push_back(i);
                    Cases[j] = Trace[0][i];
                    break;
                    //std::cout << "Object " << i << " utilise " << Trace[0][i] << " en plus de son poids (" << vi[i] << ")" << std::endl;
                }
            }
        }

        std::cout << "Case numCase : [ Objet(Volume_Objet), ... ]" << std::endl;
        for (int j=0; j<m; ++j){
            std::cout << "Case " << j << " : [ ";
            for (int i=0; i<casesVec[j].size(); i++){
                std::cout << casesVec[j][i] << "(" << vi[casesVec[j][i]] << ") ";
            }
            std::cout << "]" << std::endl;
        }
    }

    // Create Table to work with, map is not such a great idea
    // It would take O(n) to search for one element in it
    // So Vectors?
    // Looking to the array generated by fd it does not seem impossible
    // In Fact :
    //    V[i-1](mu_0, ..., mu_(k-1), mu_k - 1, mu_(k+1), ..., mu_c) is needed only for k >= v_i and v_i <= c
    // So for a given v_i nothing less than v_i will be touched
    // 
    // ...
    // Ok let's skip this...
    // V[n](0, 0, ..., m) = max (V[n-1](0, 0, ..., m), c + V[n-1](1, 0, 0, ..., m-1), (c-1)*max(V[n-1](1, 0, ..., 0, m-1), V[n-1](0, 1, 0, ..., 0, m-1)), (c-2)...)
}

int main(int argc,char *argv[])
{
    //constexpr int m;//3;//5;
    //constexpr int c;//4;//3;

    //typedef Repartition<c, m> Rep3;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-f") {
            if (i + 1 < argc) {  
                int n;
                int m;
                int c;
                //File reading, storage in tab
                //informations
                int volumeTotalBoites = 0;
                int volumeTotalItems = 0;
                float tempsCalcul = 0;

                //Reading
                std::ifstream myFile;
                myFile.open(argv[i+1]);
                std::string input;
                std::getline(myFile, input);
                std::istringstream stream(input);
                stream >> n >> m >> c;
                // std::cout << "Les valeurs de n, m et c sont respectivement : " << n << " , " << m << " , " << c << std::endl;
                std::string volume;
                std::getline(myFile, volume);
                std::istringstream streamV(volume);

                int tab[n];
                for(int j=0 ; j < n ; j++){
                    streamV >> tab[j];
                }

                //Calcul du volume total des items
                for(int j=0;j<n;j++)
                    volumeTotalItems += tab[j];

                bool disp = false;
                for(int j=1;j<argc;j++){
                    if(j  < argc && std::string(argv[j]) == "-p"){
                        disp=true;
                    }
                }
                    if(disp)
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        boite_dynamique(n,tab,c,m,true);
                        auto finish = std::chrono::high_resolution_clock::now();
                        //time of execution
                        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
                        std::cout << n << "," << m << ","  << microseconds.count() << std::endl;
                    }
                    else
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        boite_dynamique(n,tab,c,m,false);
                        auto finish = std::chrono::high_resolution_clock::now();
                        //time of execution
                        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
                        std::cout << n << "," << m << ","  << microseconds.count() << std::endl;
                        //std::cout << "Temps de calcul : " << microseconds.count() << " ms" << std::endl;
                    } 
            }
        }
    }
    //std::cout << tab[0] << std::endl;
    return 0;
}
