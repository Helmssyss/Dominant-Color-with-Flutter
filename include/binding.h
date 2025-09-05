#pragma once

#ifndef BINDING_H
#define BINDING_H

#include <cstdint>

#define BIND extern "C" __attribute__((visibility("default"))) __attribute__((used))

BIND uint32_t GetDominantColor(const uint8_t* pixels,const int width,const int height);
#endif