/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num){

    for(int i = 0; i < num; i++){
        dset.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(dset[elem] < 0){
        return elem;
    }else{
        dset[elem] = find(dset[elem]);
        return dset[elem];
    }
}

void DisjointSets::setunion(int a, int b){
    int roota = find(a);
    int rootb = find(b);
    int newsize = dset[roota] + dset[rootb];

    if(dset[roota] <= dset[rootb]){
        dset[rootb] = roota;
        dset[roota] = newsize;
    }else{
         dset[roota] = rootb;

        dset[rootb] = newsize; 
    }
}

int DisjointSets::size(int elem){
    int size = find(elem);
    return -dset[size];
}