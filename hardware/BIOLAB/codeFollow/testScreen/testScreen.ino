#include <SPI.h>
#include <TFT.h>

#define SCLK 4
#define MOSI 5
#define CS   6
#define DC   7
#define RESET 8

TFT myScreen = TFT(CS, DC, MOSI, SCLK, RESET);
