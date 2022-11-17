#ifndef FREQUENCYINPUT_H
#define FREQUENCYINPUT_H

#include "QObject"
#include "QBuffer"
#include "QAudioInput"

#include "fftman.h"
#include "tuner.h"

class FrequencyInput : public QObject
{

    Q_OBJECT

    QBuffer buffer;
    QAudioInput * audio;
    QAudioFormat format;

    FFTMan * fftman;

    Tuner * tuner;

 private slots:

    void processAudio();

 public:

    FrequencyInput(Tuner * tuner);
    ~FrequencyInput();
};

#endif // FREQUENCYINPUT_H
