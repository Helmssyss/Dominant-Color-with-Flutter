#ifndef DOMINANT_COLOR_H
#define DOMINANT_COLOR_H
#include <cstdint>
#include <unordered_map>

class DominantColor{
    public:
        uint32_t CalculateDominantColor(const uint8_t* pixels, const int& width,const int& height);
    private:
        void ThreadWorker(const uint8_t* pixels, int start, int end, std::unordered_map<uint32_t,int>& localHisto);
};
#endif