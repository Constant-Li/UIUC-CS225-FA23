/**
 * @file sketching.cpp
 * Implementation for sketching.h
 */

#include "sketching.h"
#include <algorithm>
#include <cmath>

std::vector<uint64_t> kminhash(std::vector<int> inList, unsigned k, hashFunction h){
    std::vector<uint64_t> temp;

    // push all non-duplicate hash value into temp
    for(int i = 0; i < (int)inList.size(); i++){
        uint64_t hashval = h(inList[i]);
        if(has(hashval, temp) == false){
            temp.push_back(hashval);
        }
    }
    
    // sort, if less than k, push MAX
    std::sort(temp.begin(), temp.end());
    while(temp.size() < k){
        temp.push_back(GLOBAL_MAX_INT);
    }
    // only keep the k element
    temp.resize(k);

    return temp;
}

bool has(int val, std::vector<uint64_t> list){
    for(int i = 0; i < (int)list.size(); i++){
        if(val == (int)list[i]){
            return true;
        }
    }
    return false;
}

bool has_int(int val, std::vector<int> list){
    for(int i = 0; i < (int)list.size(); i++){
        if(val == (int)list[i]){
            return true;
        }
    }
    return false;
}

std::vector<uint64_t> khash_minhash(std::vector<int> inList, std::vector<hashFunction> hv){
    std::vector<uint64_t> out;
    // loop through every hv
    for(int i = 0; i < (int)hv.size(); i++){
        std::vector<uint64_t> temp;
        // loop through entire inList
        for(int j = 0; j < (int)inList.size(); j++){
             uint64_t hashval = hv[i](inList[j]);
             temp.push_back(hashval);
        }
        // sort each individual hash and store the smallest
        std::sort(temp.begin(), temp.end());
        out.push_back(temp[0]);
    }
    
    return out;
}

std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h){
    // find the number of partitions
    int partitions = pow(2, part_bits);

    // initialize all with MAX
    std::vector<uint64_t> out(partitions, GLOBAL_MAX_INT);

    for (int i = 0; i < (int)inList.size(); i++){
        uint64_t hashval = h(inList[i]);

        // find the bucket
        int index = hashval >> (64 - part_bits);

        if (hashval < out[index]){
            out[index] = hashval;
        }
    }

    return out;
}

float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2){
    double intersection = 0;
    double total = 0;
    // find intersection && # of mh1
    for(int i = 0; i < (int)mh1.size(); i++){
        if((mh1[i] != GLOBAL_MAX_INT) && (has(mh1[i], mh2))){
            intersection = intersection + 1;
        }
        if(mh1[i] != GLOBAL_MAX_INT){
            total = total + 1;
        }
    }

    // find # of mh2
    for(int j = 0; j < (int)mh2.size(); j++){
        if(mh2[j] != GLOBAL_MAX_INT){
            total = total + 1;
        }
    }
    
    double uni = total - intersection;
    return intersection / uni;
}


int minhash_cardinality(std::vector<uint64_t> mh, unsigned k){
    double temp = (double)k * (double)GLOBAL_MAX_INT / (double)mh[k - 1];
    return (int)temp;
}

void remove_duplicate(std::vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end(); it++){
        // only check the element after it
        auto it2 = it + 1;
        while(it2 != vec.end()){
            // if the same then delete it and check everything after
            if(*it == *it2){
                it2 = vec.erase(it2);
            // if no, then check everything after
            }else{
                it2 = it2 + 1;
            }
        }   
    }
}

float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2){
    double intersection = 0;
    // remove duplicates
    remove_duplicate(raw1);
    remove_duplicate(raw2);

    // find intersection
    for(int i = 0; i < (int)raw1.size(); i++){
        if(has_int(raw1[i], raw2)){
            intersection = intersection + 1;
        }
    }

    double total = raw1.size() + raw2.size();
    double uni = total - intersection;
    return intersection / uni;
}


int exact_cardinality(std::vector<int> raw){
    remove_duplicate(raw);
    return raw.size();
}


MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h){
    numtiles_ = (int)numTiles;
    int tilewidth = std::ceil((double)input.width() / (double)numtiles_);
    int tileheight = std::ceil((double)input.height() / (double)numtiles_);

    // loops through tiles
    for(int y = 0; y < (int)numTiles; y++){
        for(int x = 0; x < (int)numTiles; x++){
            // get the pixels in that specific rigion
            std::vector<int> temp = pixel_helper(input, x, y, tilewidth, tileheight);
            // store the hashed vector in sketches for one tile
            sketches.push_back(kminhash(temp, k, h));
        }
    }
}

std::vector<int> MM::pixel_helper(const cs225::PNG& input, int xtile, int ytile, int tw, int th){
    std::vector<int> pixels;

    int startx = xtile * tw;
    int starty = ytile * th;
    // handling the edge case
    int endx = std::min(startx + tw, (int)input.width());
    int endy = std::min(starty + th, (int)input.height());

    for(int i = startx; i < endx; i++){
        for(int j = starty; j < endy; j++){
            int a = (input.getPixel(i, j).l * 255);
            pixels.push_back(a);
        }
    }
    return pixels;
}

std::vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const{
    int idx = width + height * numtiles_;
    return sketches[idx];
}


int MM::countMatchTiles(const MM & other, float threshold) const{
    int count = 0;
    for(int i = 0; i < (int)(this->sketches.size()); i++){
        if(minhash_jaccard(this->sketches[i], other.sketches[i]) >= threshold){
            count = count + 1;
        }
    }
    return count;
}

std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold){
    std::vector<MM> mm;

    // convert all images to mm and store it
    for (int a = 0; a < (int)flist.size(); a++) {
        cs225::PNG image;
        image.readFromFile(flist[a]);
        mm.push_back(MM(image, numTiles, k, h));
    }

    std::vector<std::tuple<int, int, int>> edgelist;
    // compare all of them and store it, avoid compare to itself
    for (int i = 0; i < (int)mm.size(); i++) {
        for (int j = i + 1; j < (int)mm.size(); j++) {
            int count = mm[i].countMatchTiles(mm[j], threshold);
            std::tuple<int, int, int> temp(i, j, count);
            edgelist.push_back(temp);
        }
    }

    return edgelist;
}