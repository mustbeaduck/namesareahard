#include "tuner.h"
#include "frequencies.h"


#include "QDebug"

int Tuner::offset() { return _offset; }
QString Tuner::midnote() { return _midnote; }
int Tuner::frequency() { return _frequency; }
QString Tuner::leftnote() { return _leftnote; }
QString Tuner::rightnote() { return _rightnote; }
bool Tuner::notechanged() { return _notechanged; }


Tuner::Tuner() {}


void Tuner::update(int fq)
{
    _frequency = fq;

    int note = FREQS[fq];

    if ( currentnote != note )
    {
        if ( _notechanged != true ) {
            _notechanged = true;
            emit noteChanged();
        }
        currentnote = note;
    } else {
        if ( _notechanged != false ) {
            _notechanged = false;
            emit noteChanged();
        }
    }

    if ( note == 0 ) {
        _midnote = NOTE_ARR[note];
        _leftnote = NOTE_ARR[note];
        _rightnote = NOTE_ARR[note];
        _offset = 0;
    } else {
        _midnote = NOTE_ARR[note];
        _leftnote = NOTE_ARR[note-1];
        _rightnote = NOTE_ARR[note+1];
        _offset = fq - PERF_HRZ[note];
    }

    emit offsetChanged();
    emit rightnoteChanged();
    emit frequencyChanged();
    emit leftnoteChanged();
    emit midnoteChanged();
}
