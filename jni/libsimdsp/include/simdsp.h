#ifndef SIMDSP_H
#define SIMDSP_H
#include <iostream>
using namespace std;


void captureBlock(  void (*callback)(short *) );
void playBlock( short* pBuffer);
void enableAudio(int bufSizeInFrames,int sampleRate);
void println(string text);
void println(int number);
void println(short number);
void println(double number);
void println(float number);
void println(const char *format, ...);



#endif /* SIMDSP */
