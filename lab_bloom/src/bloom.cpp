/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"

BF::BF(uint64_t size, std::vector<hashFunction> hashList){

    // Your code here 
    for(int i = 0; i < (int)size; i++){
        bv.push_back(false);
    }
    for(int j = 0; j < (int)hashList.size(); j++){
        hv.push_back(hashList[j]);
    }
}

BF::BF(const BF& other){
    // Your code here 
    bv = other.bv;
    hv = other.hv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){
    // Your code here 
    for(int i = 0; i < (int)hv.size(); i++){
        int hashval = hv[i](key) % (bv.size());
        if(bv[hashval] == false){
            bv[hashval] = true;
        }
    }

}

bool BF::contains(const int& key) const{
    // Your code here 
    for(int i = 0; i < (int)hv.size(); i++){
        int hashval = hv[i](key) % (bv.size());
        if(bv[hashval] == false){
            return false;
        }
    }
    return true;
}

void BF::bit_union(const BF& other){
    // Your code here
    for(int i = 0; i < (int)bv.size(); i++){
        bool temp = bv[i];
        bv[i] = (temp | other.bv[i]);
    } 
}

void BF::intersect(const BF& other){
    // Your code here 
    for(int i = 0; i < (int)bv.size(); i++){
        bool temp = bv[i];
        bv[i] = (temp & other.bv[i]);
    } 
}

bool present(std::vector<int> list, unsigned num){
    for(int i = 0; i < (int)list.size(); i++){
        if(list[i] == (int)num){
            return true;
        }
    }
    return false;
}

bool hasinbloom(std::vector<bool> bloom, std::vector<hashFunction> hashList, unsigned num){
    // Your code here 
    for(int i = 0; i < (int)hashList.size(); i++){
        int hashval = hashList[i](num) % (bloom.size());
        if(bloom[hashval] == false){
            return false;
        }
    }
    return true;
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here
    std::vector<bool> bloom(size, false);
    for(int i = 0; i < (int)hashList.size(); i++){
        for(int j = 0; j < (int)inList.size(); j++){
            int hashval = hashList[i](inList[j]) % size;
            if(bloom[hashval] == false){
                bloom[hashval] = true;
            }
        }

    }

    double falsepositive = 0;
    double truenegative = 0;
    for(int a = 0; a < (int)max; a++){
        if((present(inList, a) == false) && (hasinbloom(bloom, hashList, a) == false)){
            truenegative = truenegative + 1;
        }
        if((present(inList, a) == false) && (hasinbloom(bloom, hashList, a) == true)){
            falsepositive = falsepositive + 1;
        }
    }

    return (falsepositive/(falsepositive + truenegative));

}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    int remainder = index % 8;
    int idx = ((index - remainder) / 8);

    return getBitFromByte(bv[idx], remainder);
}

bool getBitFromByte(char in, int index){
    // Your code here
    std::uint8_t temp = in >> (7 - index);
    temp = temp << 7;
    std::uint8_t temp2{ 0b10000000 };
    return temp == temp2;
}



