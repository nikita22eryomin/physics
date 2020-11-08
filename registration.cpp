#include "headers.h"


Registration::Registration()
    {
        fileNumber = 1;
        preciselyMode = false;
        lastRegistrationTime = 0;
    }
void Registration::start(const char* tableHeadString)
{
    lastRegistrationTime = 0;
    char* baseFileName = "results_000.csv";
    char fileName[16];
    strcpy(fileName, baseFileName);

    if (fileNumber<10)
    {
        fileName[10] = fileNumber + '0';
    }
    else if (fileNumber<100)
    {
    fileName[9] = fileNumber/10 + '0';
    fileName[10] = fileNumber%10 + '0';
    }
    else if (fileNumber<1000)
    {
    fileName[8] = fileNumber/100 + '0';
    fileName[9] = fileNumber/10 - (fileNumber/100)*10 + '0';
    fileName[10] = fileNumber%10 + '0';
    }
    fout.open(fileName);
    fout<<tableHeadString<<"\n";
}
void Registration::stop()
{
    fout.close();
    fileNumber++;

}
void Registration::nextString(const double* valuesArr, int numOfVal)
{
double elapsed = valuesArr[0] - lastRegistrationTime;
if (elapsed>=frequencyMode*0.5/*соответствие между ID режима и периодом*/)
{
    for (int i = 0; i < numOfVal; i++)
    {
        fout<<valuesArr[i] + ((i==0||preciselyMode)?0:(0.5 - randGenerate(1)));
        if (i<numOfVal-1)
            fout<<"\t";
        else
            fout<<"\n";
    }
    lastRegistrationTime = valuesArr[0];
}

}

double Registration::randGenerate(double maximum)
{
    static int randomInt = 0;
    srand(clock());
    randomInt += rand();
    int maxInt = int(maximum*20);
    double result = (randomInt%maxInt)/20.0;
    return result;
}

void Registration::setPreciselyMode(bool mode)
{
    preciselyMode = mode;
}

void Registration::setFreqMode(unsigned int mode)
{
    frequencyMode = mode;
}
