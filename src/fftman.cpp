#include "fftman.h"

#include "math.h"


#define _2Pi 6.28
#define FQ_LOW_END 40
#define FQ_HIGH_END 1000



#include "QDebug"


FFTMan::FFTMan()
{

}

FFTMan::~FFTMan()
{
    //frees in and out buffers without asking like a chade
    fftw_destroy_plan(plan);
    free(hammingwnd);
}


void FFTMan::calcHammingWindow()
{
    for (size_t i = 0; i <= buffsize - 1; i+=1) {
        hammingwnd[i] = 0.54 - 0.46 * cos(_2Pi * i/buffsize);
    }
}

FFTMan * FFTMan::makeNew(size_t buffsize, size_t samplerate)
{

    if ( buffsize > 0 ) {

        FFTMan * instance = new FFTMan();

        //avoid processing excessive bins
        instance->frequencylimit = samplerate / 2;
        if ( instance->frequencylimit > FQ_HIGH_END ) instance->frequencylimit = FQ_HIGH_END;

        instance->hertzperbin = (float)buffsize / (float)samplerate;

        instance->buffsize = buffsize;
        instance->hammingwnd = (float*) malloc(sizeof(float) * buffsize);

        instance->out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * buffsize);
        instance->in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * buffsize);

        memset(instance->in, 0, sizeof(fftw_complex)*buffsize);

        if ( instance->in and instance->out and instance->hammingwnd ) {

            //instance->plan = fftw_plan_dft_1d(samplerate, TIN, TOUT, FFTW_FORWARD, FFTW_ESTIMATE);
            instance->plan = fftw_plan_dft_1d(samplerate, instance->in, instance->out, FFTW_FORWARD, FFTW_ESTIMATE);

            if ( instance->plan ) {

                instance->calcHammingWindow();
                return instance;
            }
        }

        delete instance;
    }

    return NULL;
}


int FFTMan::findMainFrequency()
{
    //frequency magnitude
    float mag = 0;
    float max_val = 0;

    //index to remember
    int ind = 0;
    for ( int i = FQ_LOW_END; i < frequencylimit; i+=1 ) {

        mag = abs(out[i][0]) + abs(out[i][1]);

        if ( mag > max_val ) {
            max_val = mag;
            ind = i;
        }
    }
    //quiet pointless considering i'll never use
    //ratio other than 1hz per fft bin so i could just return ind
    //yet here we are

    return (float)ind * hertzperbin;
}


int FFTMan::parseFrequency(QByteArray bytearray)
{
    size_t size = bytearray.size() / sizeof(float);
    if ( size > buffsize ) size = buffsize;

    float * data = (float*) bytearray.data();

    //apply hamming window
    for ( size_t i = 0; i < size; i+=1 ) {
        in[i][0] = data[i] * hammingwnd[i];
    }
    fftw_execute(plan);

    int frequency = findMainFrequency();
    return frequency;
}
