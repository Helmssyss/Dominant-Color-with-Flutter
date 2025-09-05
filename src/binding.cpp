#include <cstdlib>
#include "binding.h"
#include "dominant_color.h"

uint32_t GetDominantColor(const uint8_t* pixels,const int width,const int height){
    DominantColor* dominantColor = new DominantColor;
    if(dominantColor != nullptr){
        const uint32_t colorCode = dominantColor->CalculateDominantColor(pixels,width,height);
        delete dominantColor;
        return colorCode;
    }
    return -1;
}