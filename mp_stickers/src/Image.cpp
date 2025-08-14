# include "Image.h"
# include "cs225/HSLAPixel.h"
# include <iostream>
# include <cmath>
using namespace cs225;
using namespace std;

Image::Image(){
    width_ = 0;
    height_ = 0;
}

// Creates an Image of the specified dimensions. 
Image::Image(unsigned int width, unsigned int height){
    width_ = width;
    height_ = height;
}


// Darken an Image by decreasing the luminance of every pixel by 0.1. 
void Image::darken(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            double & cur_pixel_l = (this->getPixel(i, j)).l;
            cur_pixel_l = cur_pixel_l - 0.1;
            if(cur_pixel_l < 0){
                cur_pixel_l = 0;
            }else if(cur_pixel_l > 1){
                cur_pixel_l = 1;
            }
        }
    }
}

// Darkens an Image by decreasing the luminance of every pixel by amount. 
void Image::darken(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            double & cur_pixel_l = (this->getPixel(i, j)).l;
            cur_pixel_l = cur_pixel_l - amount;
            if(cur_pixel_l < 0){
                cur_pixel_l = 0;
            }else if(cur_pixel_l > 1){
                cur_pixel_l = 1;
            }
        }
    }
}    

// Desaturates an Image by decreasing the saturation of every pixel by 0.1. 
void Image::desaturate(){
    std::cout<<"haha";
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            double & cur_pixel_s = (this->getPixel(i, j)).s;
            cur_pixel_s = cur_pixel_s - 0.1;
            if(cur_pixel_s < 0){
                cur_pixel_s = 0;
            }else if(cur_pixel_s > 1){
                cur_pixel_s = 1;
            }
        }
    }    
}

// Desaturates an Image by decreasing the saturation of every pixel by amount. 
void Image::desaturate(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            double & cur_pixel_s = (this->getPixel(i, j)).s;
            cur_pixel_s = cur_pixel_s - amount;
            if(cur_pixel_s < 0){
                cur_pixel_s = 0;
            }else if(cur_pixel_s > 1){
                cur_pixel_s = 1;
            }
        }
    } 

}

// Turns the image grayscale. 
void Image::grayscale(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            (this->getPixel(i, j)).s = 0;
        }
    } 
}

// Illinify the image
void Image::illinify(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            double & cur_pixel_h = (this->getPixel(i, j)).h;
            double diff_orange = abs(cur_pixel_h - 11);
            double diff_blue = abs(cur_pixel_h - 216);
            // If value exceeds 180, correct the distance
            if(diff_orange > 180){
                diff_orange = 360 - diff_orange;
            }
            if(diff_blue > 180){
                diff_blue = 360 - diff_blue;
            }

            if(diff_orange < diff_blue){
                cur_pixel_h = 11;
            }else{
                cur_pixel_h = 216;
            }
        }
    } 
}

//Lighten an Image by increasing the luminance of every pixel by 0.1. 
void Image::lighten(){
    darken(-0.1);
}

// Lighten an Image by increasing the luminance of every pixel by amount.
void Image::lighten(double amount){
    darken(-amount);
}

//  Rotates the color wheel by degrees. 
void Image::rotateColor(double degrees){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            double & cur_pixel_h = (this->getPixel(i, j)).h;
            cur_pixel_h = cur_pixel_h + degrees;
            if(cur_pixel_h < 0){
                cur_pixel_h = cur_pixel_h + 360;
            }else if(cur_pixel_h > 360){
                cur_pixel_h = cur_pixel_h - 360;
            }
        }
    } 
}

// Saturates an Image by increasing the saturation of every pixel by 0.1. 
void Image::saturate(){
     desaturate(-0.1);
}

// Saturates an Image by increasing the saturation of every pixel by amount. 
void Image::saturate(double amount){
    desaturate(-amount);
}

// Scale the Image by a given factor. 
void Image::scale(double factor){
    // Create new image with expected size
    Image new_image = *this;
    new_image.resize(this->width() * factor, this->height() * factor);

    // Filling each pixel
    if(factor > 1){
        for (unsigned int i = 0; i < this->width() * factor; i++){
            for (unsigned int j = 0; j < this->height() * factor; j++){
                HSLAPixel & new_pixel = new_image.getPixel(i, j);
                new_pixel = this->getPixel(i/factor, j/factor);           
                }
        }
    }else if(factor <= 1){
        for (unsigned int i = 0; i < this->width(); i++){
            for (unsigned int j = 0; j < this->height(); j++){
                HSLAPixel & new_pixel = new_image.getPixel(i*factor, j*factor);
                new_pixel = this->getPixel(i, j);           
                }
        }

    }
    
    // Resizing current and set current to new
    this->resize(this->width() * factor, this->height() * factor);
    *this = new_image;
    }

// Scales the image to fit within the size (w x h). 
void Image::scale(unsigned w, unsigned h){
    double width_ratio =  (double) w / (double) this->width();
    double height_ratio = (double) h / (double) this->height();

    if (height_ratio != width_ratio){
        if(height_ratio < width_ratio){
            scale(height_ratio);
        }else{
            scale(width_ratio);
        }
    }else{
        scale(height_ratio);
    }
}