#include "frequencyinput.h"

#include "math.h"
#include "QDebug"

#define DESIRABLE_SAMPLE_RATE 16000


FrequencyInput::~FrequencyInput()
{
    delete fftman;
    delete audio;
}


void FrequencyInput::processAudio()
{
    tuner->update(fftman->parseFrequency(buffer.data()));
    buffer.buffer().clear();
    buffer.seek(0);
}


FrequencyInput::FrequencyInput(Tuner * tuner)
    : tuner(tuner)
{
    format.setChannelCount(1);
    format.setSampleRate(DESIRABLE_SAMPLE_RATE);
    format.setSampleSize(sizeof(float));
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::Float);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    if (!info.isFormatSupported(format)) {
        qWarning() << "Provided format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);

        if ( format.sampleType() != QAudioFormat::Float ) {
            throw std::runtime_error("what a cruel fucking world we are living in!\n float not suported by audio device");
        }
    }

    fftman = FFTMan::makeNew(format.sampleRate(), format.sampleRate());

    if ( fftman == NULL ) {

        throw std::runtime_error("fft setup failed");
    }

    audio = new QAudioInput(format);
    audio->setNotifyInterval(1000);
    audio->setVolume(1);

    //process event
    connect(audio, &QAudioInput::notify, this, &FrequencyInput::processAudio);


    buffer.open(QBuffer::ReadWrite);
    audio->start(&buffer);
}
