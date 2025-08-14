#include "StickerSheet.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using namespace cs225;

// Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
StickerSheet::StickerSheet(const Image & picture, unsigned max){
    base_pic = picture;
    max_ = max;
    // Create vector that stores "max" uninitiallized image 
    layers_.resize(max, nullptr);
    x_val.resize(max, 0.0);
    y_val.resize(max, 0.0);

}

// The copy constructor makes this StickerSheet an independent copy of the source. 
StickerSheet::StickerSheet (const StickerSheet & other){
    //this->~StickerSheet();
    clear();
    copy(other);
}

void StickerSheet::copy(const StickerSheet & other){
    base_pic = other.base_pic;
    max_ = other.max_;
    for (unsigned i = 0; i < max_; i++){
        layers_.push_back(((other.layers_).at(i)));
        x_val.push_back(other.x_val.at(i));
        y_val.push_back(other.y_val.at(i));
    }

}

// Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
int StickerSheet::addSticker(Image & sticker, int x, int y){
    // If not full
    unsigned int min_ = 0;
    for (unsigned int i = 0; i < max_ ; i++){
        if(layers_.at(i) != nullptr){
            min_ = min_ + 1;
        }
    }

    if(min_ < max_){
        layers_.at(min_) = &sticker;
        x_val.at(min_) = x;
        y_val.at(min_) = y;
        // Update latest min_
        min_ = min_ + 1;
    }else if(min_ == max_){
        layers_.push_back(&sticker);
        // Update latest min_ and max_
        x_val.push_back(x);
        y_val.push_back(y);
        min_ = min_ + 1;
        max_ = max_ + 1;
    }
    return min_ - 1;

}

// Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
void StickerSheet::changeMaxStickers(unsigned max){
    if(max < max_){
        for (unsigned i = 0; i < (max_ - max); i++){
            layers_.pop_back();
            x_val.pop_back();
            y_val.pop_back();

        }

    }else{
        for (unsigned j = 0; j < max - max_; j++){
            layers_.push_back(nullptr);
            x_val.push_back(0);
            y_val.push_back(0);
        }
    }
    max_ = max;

    // layers_.resize(max);
    // max_ = max;
}

// Returns a pointer to the sticker at the specified index, not a copy of it. 
Image* StickerSheet::getSticker(unsigned index){
    // If invalid
    if((index >= max_) || (index < 0)){
        return NULL;
    }else{
        return (layers_.at(index));
    }
}

// Returns the total number of layers available on the Stickersheet. 
int StickerSheet::layers()const{
    return max_;
}

// Destructor
StickerSheet::~StickerSheet(){
    this->layers_.clear();
    this->x_val.clear();
    this->y_val.clear();
}

void StickerSheet::clear(){
    this->layers_.clear();
    this->x_val.clear();
    this->y_val.clear();
}

// The assignment operator for the StickerSheet class. 
const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
    //this->~StickerSheet();
    if(this != &other){
        clear();
        copy(other);
    }
    return *this;
}

// Removes the sticker at the given zero-based layer index. 
void StickerSheet::removeSticker(unsigned index){
    if((index >= 0) && (index < max_)){
        layers_.erase(layers_.begin() + index);
        x_val.erase(x_val.begin() + index);
        y_val.erase(y_val.begin() + index);
        max_ = max_ - 1;
    }
}

// Renders the whole StickerSheet on one Image and returns that Image. 
Image StickerSheet:: render()const{

    unsigned int final_width;
    unsigned int final_height;
    Image final;
    unsigned int img_width = base_pic.width();
    unsigned int img_height = base_pic.height();

    int a = 0; // stores negative x
    int b = 0; // stores positive x
    int c = 0; // stores negative y
    int d = 0; // stores positive y

    for(unsigned i = 0; i < max_; i++){
        if(layers_.at(i) != nullptr){
            unsigned int sticker_width = (layers_.at(i))->width();
            unsigned int sticker_height = (layers_.at(i))->height();
            if(x_val.at(i) < 0){
                if(x_val.at(i) < a){
                    a = x_val.at(i);
                }
            }
            //if(x_val.at(i) > 0){
                if(((x_val.at(i) + sticker_width) > img_width)){
                    if((x_val.at(i) + sticker_width - img_width) > b){
                        b = x_val.at(i) + sticker_width - img_width;
                    }
                }
            //}
            if(y_val.at(i) < 0){
                if(y_val.at(i) < c){
                    c = y_val.at(i);
                }
            }
            //if(y_val.at(i) > 0){
                if((y_val.at(i) + sticker_height) > img_height){
                    if((y_val.at(i) + sticker_height - img_height) > d){
                        d = y_val.at(i) + sticker_height - img_height;
                    }
                }
            //}

        }
    }
    final_width = img_width + b - a;
    final_height = img_height + d - c;
    final.resize(final_width, final_height);

    // int a = 0;
    // int b = 0;
    // int c = 0;
    // int d = 0;

    // sort(x.begin(), x.end());
    // sort(y.begin(), y.end());

    // if(x.at(0) < 0){
    //     a = x.at(0);
    // }
    // if(x.back() > (int)img_width){
    //     b = x.back() - (int)img_width;
    // }
    // final_width = img_width + b - a;

    // if(y.at(0) < 0){
    //     c = y.at(0);
    // }
    // if(y.back() > (int)img_height){
    //     d = y.back() - (int)img_height;
    // }
    // final_height = img_height + d - c;
    // final.resize(final_width, final_height);

    for(unsigned int e = 0; e < img_width; e++){
        for(unsigned int f = 0; f < img_height; f++){
            HSLAPixel & semi_pixel = final.getPixel(e - a, f - c );
            semi_pixel = base_pic.getPixel(e, f);
        }
    }

    for (unsigned j = 0; j < max_; j++){
        if(layers_.at(j) != nullptr){
            for(unsigned int m = 0; m < (layers_.at(j))->width(); m++){
                for(unsigned int n = 0; n < (layers_.at(j))->height(); n++){
                    HSLAPixel & final_pixel = final.getPixel(m - a + x_val.at(j), n - c + y_val.at(j));
                    if(((layers_.at(j))->getPixel(m, n)).a != 0){
                        final_pixel = ((layers_.at(j))->getPixel(m, n));
                    }
                }
            }
        }
    }
    return final;


    // unsigned int final_width;
    // unsigned int final_height;
    // Image final(base_pic);
    
    // for(unsigned i = 0; i < max_; i++){
    //     if(layers_.at(i) != nullptr){
    //         unsigned int img_width = final.width();
    //         unsigned int img_height = final.height();
    //         unsigned int sticker_width = (layers_.at(i))->width();
    //         unsigned int sticker_height = (layers_.at(i))->height();
    //         // Outside bound
    //         if((x_val.at(i) > 0) && ((x_val.at(i) + sticker_width) > img_width)){
    //             final_width = x_val.at(i) + sticker_width;
    //         // Inside bound
    //         }else if((x_val.at(i) > 0) && ((x_val.at(i) + sticker_width) <= img_width)){
    //             final_width = img_width;
    //         // Negative x value
    //         }else if(x_val.at(i) <= 0){
    //             final_width = abs((int)x_val.at(i)) + img_width;
    //         }
    //         // Outside bound
    //         if((y_val.at(i) > 0) && ((y_val.at(i) + sticker_height) > img_height)){
    //             final_height = y_val.at(i) + sticker_height;
    //         // Inside bound
    //         }else if((y_val.at(i) > 0) && ((y_val.at(i) + sticker_height) <= img_height)){
    //             final_height = img_height;
    //         // Negative y value
    //         }else if(y_val.at(i) <= 0){
    //             final_height = abs((int)y_val.at(i)) + img_height;
    //         }
            
    //         final.resize(final_width, final_height);

    //         // Traverse the sticker and assign value
    //         for(unsigned int m = 0; m < sticker_width; m++){
    //             for(unsigned int n = 0; n < sticker_height; n++){
    //                 HSLAPixel & final_pixel = final.getPixel(m + x_val.at(i), n + y_val.at(i));
    //                 if(((layers_.at(i))->getPixel(m, n)).a != 0){
    //                     final_pixel = ((layers_.at(i))->getPixel(m, n));
    //                 }
    //             }
    //         }
    //     }
    // }
    // return final;

}

// Adds a sticker to the StickerSheet at layer layer, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){
    if((layer >= max_) || (layer < 0)){
        return -1;
    }else{
        layers_.at(layer) = &sticker;
        x_val.at(layer) = x;
        y_val.at(layer) = y;
        return layer;
    }

}

// Changes the x and y coordinates of the Image in the specified layer. 
bool StickerSheet::translate(unsigned index, int x, int y){
    if((index >= max_) || (index < 0)){
        return false;
    }
    if(layers_.at(index) != nullptr){
        x_val.at(index) = x;
        y_val.at(index) = y;
        return true;
    }else{
        return false;
    }
}
