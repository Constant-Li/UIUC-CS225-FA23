/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
#include<iostream>
using namespace std;

class StickerSheet{
    public:
        // Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
        StickerSheet(const Image & picture, unsigned max);

        // The copy constructor makes this StickerSheet an independent copy of the source. 
        StickerSheet (const StickerSheet & other);

        // Copy constructor
        void copy(const StickerSheet & other);

        // Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
        int addSticker(Image & sticker, int x, int y);

        // Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
        void changeMaxStickers(unsigned max);

        // Returns a pointer to the sticker at the specified index, not a copy of it. 
        Image * getSticker(unsigned index);

        // Returns the total number of layers available on the Stickersheet. 
        int layers()const;

        // Deconstructor
        ~StickerSheet();

        // clear
        void clear();

        // The assignment operator for the StickerSheet class. 
        const StickerSheet & operator=(const StickerSheet & other);

        // Removes the sticker at the given zero-based layer index. 
        void removeSticker(unsigned index);

        // Renders the whole StickerSheet on one Image and returns that Image. 
        Image render ()const;

        // Adds a sticker to the StickerSheet at layer layer, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
        int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y);

        // Changes the x and y coordinates of the Image in the specified layer. 
        bool translate(unsigned index, int x, int y);

    private:

        // Stores the basic picture
        Image base_pic;

        // Maximum layers
        unsigned max_;

        // X coordinates
        vector<double> x_val;

        // Y coordinates
        vector<double> y_val;
        
        // StickerSheet
        vector<Image*> layers_;
};