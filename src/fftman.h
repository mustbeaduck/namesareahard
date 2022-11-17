#ifndef FFTMAN_H
#define FFTMAN_H

#include "QByteArray"

#include "fftw3.h"

class FFTMan
{
    fftw_plan plan;

    fftw_complex * in;
    fftw_complex * out;
    float  * hammingwnd;

    size_t buffsize;
    float hertzperbin;
    int frequencylimit;

    void calcHammingWindow();
    int findMainFrequency();

    FFTMan();

 public:

    static FFTMan * makeNew(size_t buffsize, size_t framerate);
    int parseFrequency(QByteArray bytearray);

    ~FFTMan();
};

#endif // FFTMAN_H
