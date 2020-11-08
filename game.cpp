#include "headers.h"



Game::Game()
{
    initialized = true;
    registrationEnabled = false;
    registrationAdvanced = false;
    timeStart = clock();
    frameTime = 0;
    timeEnd = clock();
    sleepTime = 0;
}

Game::~Game()
{
    delete input;
}

Input* Game::input = new Input;
Graphics* Game::graphics = new Graphics;
Registration* Game::registration = new Registration;

void Game:: renderGame()
{
    InvalidateRect(hwnd,NULL,FALSE);
}

void Game::run()
{
    //timing:
    //now timeStart == timeEnd (time of start of last iteration - run call)
    timeEnd = clock();
    //std::cout<<"timeEnd "<<timeEnd<<std::endl;
   // std::cout<<"timeStart "<<timeStart<<std::endl;
    frameTime = double(timeEnd - timeStart) / (double)CLOCKS_PER_SEC;
    /////////
    timeStart = timeEnd;
        sleepTime += (MIN_FRAME_TIME - frameTime)*1000;
       // std::cout<<"frameTime = "<<frameTime<<std::endl;
       // std::cout<<"sleepTime = "<<sleepTime<<std::endl;
       // std::cout<<"clock_1 = "<<clock()<<std::endl;
            if(sleepTime>0)
        Sleep(sleepTime); // Release CPU for sleepTime
            //std::cout<<"clock_2 = "<<clock()<<std::endl;
    if (frameTime>0.0)
    {
        fps = fps*0.99f + 0.01f/frameTime;
    }


    //input->readControllers();

    update();
        //std::cout<<"after update()"<<fps<<std::endl;
    renderGame();
        //std::cout<<"after renderGame()"<<fps<<std::endl;

    input->clearButtonsPressed();

}

LRESULT Game:: messageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    if(initialized)
    {
        switch(message)
          {
            case WM_COMMAND:
                switch (LOWORD(wParam)) {
                case START:
                    //this->start();
                    input->pressButton(START_INP);
                    break;
                case PAUSE:
                    //this->pause();
                    input->pressButton(PAUSE_INP);
                    break;
                case CLEAR:
                    //this->setDefaultState();
                    input->pressButton(RESET_INP);
                    break;

                case 1201:
                    input->pressButton(BIG_BEN_INP);
                    break;
                case 1202:
                    input->pressButton(LITTLE_HOUSE_INP);
                    break;
                case MOON:
                    input->pressButton(MOON_INP);
                    break;
                case EARTH:
                    input->pressButton(EARTH_INP);
                    break;
                case MARS:
                    input->pressButton(MARS_INP);
                    break;
                case JUPITER:
                    input->pressButton(JUPITER_INP);
                    break;

                case IDEAL_PRECISION:
                    input->pressButton(PRECISION_IDEAL_INP);
                    break;
                case REAL_PRECISION:
                    input->pressButton(PRECISION_REAL_INP);
                    break;
                case LOW_REG_FREQ:
                    input->pressButton(FREQ_LOW_INP);
                    break;
                case MED_REG_FREQ:
                    input->pressButton(FREQ_MED_INP);
                    break;
                case HIGH_REG_FREQ:
                    input->pressButton(FREQ_HIGH_INP);
                    break;
                case EXPORT_ON_OFF:
                    input->pressButton(EXPORT_ON_INP);
                    break;
                case DATA_COLLECTION_STANDARD:
                    input->pressButton(STANDARD_DATALIST_INP);
                    break;
                case DATA_COLLECTION_ADVANCED:
                    input->pressButton(ADVANCED_DATALIST_INP);
                    break;

                }
                break;
            case WM_LBUTTONDOWN:
                input->leftButtonDown(lParam);
                break;
            case WM_PAINT:
                render();
                break;
            case WM_SIZE:
                std::cout<<"width = "<<LOWORD(lParam)<<std::endl;
                std::cout<<"height = "<<HIWORD(lParam)<<std::endl;
                input->setButtonsLocation(LOWORD(lParam), HIWORD(lParam));
                InvalidateRect(hwnd,NULL,TRUE);
                break;
            case WM_DESTROY:
                PostQuitMessage (0);
                break;
            default:
                return DefWindowProc(hwnd, message, wParam, lParam);
          }
    }

      return 0;
}
State::State(){}

State::State(Fly* f, int stateId)
{
    fly = f;
    id = stateId;
}
int State::getStateID()
{
    return id;
}

InitialState::InitialState(Fly* f, int stateId):State(f, stateId){}
PlaysState::PlaysState(Fly* f, int stateId):State(f, stateId){}
PausedState::PausedState(Fly* f, int stateId):State(f, stateId){}
FinishedState::FinishedState(Fly* f, int stateId):State(f, stateId){}

void InitialState::update()
{
 //добавить работу с временем
}

void PausedState::update()
{
 fly->frozenStep();
}

void PlaysState::update()
{
fly->step();
}

void FinishedState::update()
{

}

Fly::Fly()
{
    acceleration = 1.62;//g Луны
    dist = 0.0;
    speed = 0.0;
    height = 96.0;
    state = new InitialState(this, INITIAL_STATE);
    currentTime = 0;
    currentValues = new double[20];//20 - число регистрируемых с запасом
}

void Fly::render()
{
 graphics->draw(hwnd, ps, hdc, dist, currentTime, speed);
}

void Fly::update()
{
if(input->isButtonPressed(START_INP))
    this->start();
if(input->isButtonPressed(PAUSE_INP))
    this->pause();
if(input->isButtonPressed(RESET_INP))
    this->setDefaultState();
if(input->isButtonPressed(BIG_BEN_INP))
{
   graphics->setBigBen();
    height = 96.0;
    setDefaultState();
}
if(input->isButtonPressed(LITTLE_HOUSE_INP))
{
   graphics->setHouse();
    height = 9.6;
    setDefaultState();
}
if(input->isButtonPressed(PRECISION_IDEAL_INP))
{
registration->setPreciselyMode(true);
MessageBox(hwnd, TEXT("Значения параметров регистрируются без погрешности."), TEXT("Установлен режим идеального оборудования"), 0);
}
if(input->isButtonPressed(PRECISION_REAL_INP))
{
registration->setPreciselyMode(false);
MessageBox(hwnd, TEXT("Регистрируемые значения имеют погрешность."), TEXT("Установлен режим реального оборудования"), 0);
}

if(input->isButtonPressed(FREQ_LOW_INP))
{
registration->setFreqMode(MIN_FREQ);
MessageBox(hwnd, TEXT("Данные регистрируются с частотой 1 Гц."), TEXT("Минимальная частота регистрации"), 0);
}
if(input->isButtonPressed(FREQ_MED_INP))
{
registration->setFreqMode(MED_FREQ);
MessageBox(hwnd, TEXT("Данные регистрируются с частотой 2 Гц."), TEXT("Средняя частота регистрации"), 0);
}
if(input->isButtonPressed(FREQ_HIGH_INP))
{
registration->setFreqMode(MAX_FREQ);
MessageBox(hwnd, TEXT("Регистрация производится при каждом шаге вычислений."), TEXT("Максимальная частота регистрации"), 0);
}
if(input->isButtonPressed(MOON_INP))
{
     this->acceleration = 1.62;
     graphics->setGravity("Юпитер");
}
if(input->isButtonPressed(EARTH_INP))
{
     this->acceleration = 9.8;
     graphics->setGravity("Земля");
}
if(input->isButtonPressed(MARS_INP))
{
     this->acceleration = 3.86;
     graphics->setGravity("Марс");
}
if(input->isButtonPressed(JUPITER_INP))
{
     this->acceleration = 23.95;
     graphics->setGravity("Юпитер");
}
if(input->isButtonPressed(EXPORT_ON_INP))
{
     this->registrationEnabled = !registrationEnabled;
     if(registrationEnabled)
     MessageBox(hwnd, TEXT("Результаты экспериментов будут доступны в файлах .csv."), TEXT("Экспорт данных включен"), 0);
     else
     MessageBox(hwnd, TEXT("Запись данных в файлы не производится."), TEXT("Экспорт данных отключен"), 0);
}
if(input->isButtonPressed(STANDARD_DATALIST_INP))
{
     this->registrationAdvanced = false;
     MessageBox(hwnd, TEXT("В файлах записей экспериментов регистрируются значения только основных величин."), TEXT("Установлен стандартный набор величин"), 0);
}
if(input->isButtonPressed(ADVANCED_DATALIST_INP))
{
     this->registrationAdvanced = true;
     MessageBox(hwnd, TEXT("В файлах записей экспериментов регистрируются расчетные значения дополнительных величин."), TEXT("Установлен расширенный набор величин"), 0);
}



state->update();
}

void Fly::step()
{
    currentTime+=frameTime;
    speed+=acceleration*frameTime;
    dist+=speed*frameTime;
    if (dist>height)
    {
    delete state;
    state = new FinishedState(this, FINISHED_STATE);
    graphics->setVisible(false);
    if (registrationEnabled)
    registration->stop();
    }
    if (registrationEnabled)
    {
        if(registrationAdvanced)
        {
        currentValues[0] = currentTime;
        currentValues[1] = height - dist;
        currentValues[2] = dist; //путь
        currentValues[3] = speed; //мгновенная скорость
        currentValues[4] = dist/currentTime;  //средняя скорость
        currentValues[5] = 0.1*speed*speed;//кинетическая энергия для массы 200 г
        currentValues[6] = 0.2*acceleration*(height - dist);//потенциальная энергия для массы 200 г

        registration->nextString(currentValues, 7);
        }
        else
        {
        currentValues[0] = currentTime;
        currentValues[1] = height - dist;
        currentValues[2] = speed;
        registration->nextString(currentValues, 3);
        }

    }

}

void Fly::frozenStep()
{
    //currentTime+=frameTime;
    //fout<< currentTime << "\t"<<height - dist << "\t"<< speed <<"\n";
}


void Fly::setDefaultState()
{
    if (state->getStateID() != INITIAL_STATE)
    {
    MessageBox(hwnd, TEXT("Система будет приведена в состояние готовности с начальными условиями эксперимента."), TEXT("Сброс значений параметров"), 0);
    graphics->setVisible(true);
    setState(new InitialState(this, INITIAL_STATE));
    dist = 0.0;
    speed = 0.0;
    currentTime = 0.0;
    }
}

void Fly::start()
{
if(state->getStateID() == INITIAL_STATE || state->getStateID() == PAUSED_STATE)
{
setState(new PlaysState(this, PLAYS_STATE));
if (registrationEnabled)
registration->start(registrationAdvanced?"Time \t Height \t Distance \t V \t Average V \t W kinetic \t W potential":"Time \t Height \t Speed");
}

else if (state->getStateID() == FINISHED_STATE)
MessageBox(hwnd, TEXT("Система не приведена в состояние готовности."), TEXT("Недопустимая команда"), 0);
}

void Fly::pause()
{
setState(new PausedState(this, PAUSED_STATE));
}
void Fly::setState(State* s)
{
    delete state;
    state = s;
}
