#include <vector>
#include <thread>
#include <cstdint>
#include "dominant_color.h"

uint32_t DominantColor::CalculateDominantColor(const uint8_t* pixels, const int& width, const int& height) {
    int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;

    std::vector<std::thread> threads;
    std::vector<std::unordered_map<uint32_t,int>> histos(numThreads);

    int totalPixels = width * height;
    int chunkSize = totalPixels / numThreads;
    int start = 0;

    for (int t = 0; t < numThreads; t++) {
        int end = (t == numThreads - 1) ? totalPixels : start + chunkSize;
        threads.emplace_back(&DominantColor::ThreadWorker, this, pixels, start * 3, end * 3, std::ref(histos[t]));
        start += chunkSize;
    }

    for (std::thread& th : threads) th.join();

    std::unordered_map<uint32_t,int> combinedHisto;
    for (auto& h : histos) {
        for (auto& kv : h) {
            combinedHisto[kv.first] += kv.second;
        }
    }

    uint32_t dominant = 0;
    int maxCount = -1;
    for (auto& kv : combinedHisto) {
        if (kv.second > maxCount) {
            maxCount = kv.second;
            dominant = kv.first;
        }
    }

    int r = ((dominant >> 16) & 255) * 16 + 8;
    int g = ((dominant >> 8) & 255) * 16 + 8;
    int b = (dominant & 255) * 16 + 8;

    r = (r > 255) ? 255 : r;
    g = (g > 255) ? 255 : g;
    b = (b > 255) ? 255 : b;

    return (r << 16) | (g << 8) | b;
}

void DominantColor::ThreadWorker(const uint8_t* pixels, int start, int end, std::unordered_map<uint32_t, int> &localHisto) {
    for (int i = start; i < end; i += 3) {
        int r = pixels[i] / 16;
        int g = pixels[i+1] / 16;
        int b = pixels[i+2] / 16;
        uint32_t key = (r << 16) | (g << 8) | b;
        localHisto[key]++;
    }

}
