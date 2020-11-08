#ifndef REGISTRATION_H_INCLUDED
#define REGISTRATION_H_INCLUDED

enum FrequencyMode
{
    MAX_FREQ,
    MED_FREQ,
    MIN_FREQ
};

class Registration
{
public:
    Registration();
    void start(const char* tableHeadString);
    void stop();
    void nextString(const double* valuesArr, int numOfVal);
    void setPreciselyMode(bool mode);
    void setFreqMode(unsigned int mode);
protected:
double lastRegistrationTime;
unsigned int frequencyMode;
bool preciselyMode;
double randGenerate(double maximum);
int fileNumber;
std::ofstream fout;
};




#endif // REGISTRATION_H_INCLUDED
