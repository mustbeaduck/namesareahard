#ifndef TUNER_H
#define TUNER_H

#include <QObject>

class Tuner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset NOTIFY offsetChanged)
    Q_PROPERTY(int frequency READ frequency NOTIFY frequencyChanged)

    //notes
    //considering exporting qlist just to DRY this mess
    Q_PROPERTY(QString rightnote READ rightnote NOTIFY rightnoteChanged)
    Q_PROPERTY(QString leftnote READ leftnote NOTIFY leftnoteChanged)
    Q_PROPERTY(QString midnote READ midnote NOTIFY midnoteChanged)

    Q_PROPERTY(bool notechanged READ notechanged NOTIFY noteChanged)

 signals:

    void offsetChanged();
    void frequencyChanged();

    void rightnoteChanged();
    void leftnoteChanged();
    void midnoteChanged();
    void noteChanged();

 private:


    QString _rightnote;
    QString _leftnote;
    QString _midnote;

    bool _notechanged;
    int currentnote;
    int _frequency;
    int _offset;

 public:

    static int getOctave(int fq);

    void update(int fq);

    QString rightnote();
    bool notechanged();
    QString leftnote();
    QString midnote();

    int frequency();
    int offset();


    Tuner();
};

#endif // TUNER_H
