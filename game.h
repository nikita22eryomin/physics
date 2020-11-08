#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class Input;
class Graphics;
class Fly;
class Registration;


enum Command
{
    IDEAL_PRECISION = 1101,
    REAL_PRECISION,
    LOW_REG_FREQ = 1121,
    MED_REG_FREQ,
    HIGH_REG_FREQ,
    EXPORT_ON_OFF = 1131,
    DATA_COLLECTION_STANDARD = 1141,
    DATA_COLLECTION_ADVANCED,
    BIG_BEN_BUT = 1201,
    TOWN_HOUSE,
    MOON = 1221,
    EARTH,
    MARS,
    JUPITER,
    START = 1400,
    PAUSE,
    CLEAR
};

enum stateID
{
    INITIAL_STATE,
    PLAYS_STATE,
    PAUSED_STATE,
    FINISHED_STATE
};



class Game
{
public:
    Game();
    virtual ~Game();
    LRESULT messageHandler(HWND, UINT, WPARAM, LPARAM);

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void createMenu() = 0;
    virtual void setDefaultState() = 0;
    virtual void start() = 0;
    virtual void pause() = 0;


    virtual void renderGame();
    virtual void run();

    Graphics* getGraphics()
    {
        return graphics;
    }
    Input* getInput()
    {
        return input;
    }
    void setHWND(HWND hW)
    {
        hwnd = hW;
    }
protected:



    HWND hwnd;
    long long int timeStart;
    long long int timeEnd;
    long long int timerFreq;
    float frameTime;
    float fps;
    int sleepTime;//ms
    static Input* input;
    static Graphics* graphics;
    static Registration* registration;
    //bool paused;
    bool initialized;
    bool registrationEnabled;
    bool registrationAdvanced;
    //bool plays;
    HDC hdc;
    PAINTSTRUCT ps;

    const float MIN_FRAME_TIME = 0.02;
};

class State
{
public:
State();
State(Fly*, int);
virtual int getStateID();
virtual void update() = 0;

protected:
Fly* fly;
int id;
};

class InitialState: public State
{
    public:
InitialState(Fly*, int);
void update();
};

class PlaysState: public State
{
public:
PlaysState(Fly*, int);
void update();
};

class PausedState: public State
{
public:
PausedState(Fly*, int);
void update();
};

class FinishedState: public State
{
public:
FinishedState(Fly*, int);
void update();
};

class Fly: public Game
{
public:
Fly();
void setState(State*);
void start();
void pause();
void step();
void frozenStep();
void update();
void render();
void setDefaultState();
void createMenu()
{
            HMENU MainMenu = CreateMenu();
            HMENU hPopupMenuGames = CreatePopupMenu();
            HMENU hPopupMenuMetering = CreatePopupMenu();
            HMENU hPopupMenuConditions = CreatePopupMenu();
            //третий уровень:
            HMENU hPopupMenuPrecision = CreatePopupMenu();
            HMENU hPopupMenuFrequency = CreatePopupMenu();
            HMENU hPopupMenuGravity = CreatePopupMenu();
            HMENU hPopupMenuDataExport = CreatePopupMenu();
            HMENU hPopupMenuDataCollection = CreatePopupMenu();

            AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenuGames, "Выбор игры");
            {
                AppendMenu(hPopupMenuGames, MF_STRING, 1000, "Падение");
                AppendMenu(hPopupMenuGames, MF_STRING, 1001, "Другая 1");
                AppendMenu(hPopupMenuGames, MF_STRING, 1002, "Другая 2");
                AppendMenu(hPopupMenuGames, MF_STRING, 1003, "...");
            }

            AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenuMetering, "Система измерений");
            {
                AppendMenu(hPopupMenuMetering, MF_STRING | MF_POPUP, (UINT)hPopupMenuPrecision, "Точность регистрации");
                {
                    AppendMenu(hPopupMenuPrecision, MF_STRING, 1101, "Идеальная");
                    AppendMenu(hPopupMenuPrecision, MF_STRING, 1102, "Реальная");
                }
                AppendMenu(hPopupMenuMetering, MF_STRING | MF_POPUP, (UINT)hPopupMenuFrequency, "Частота регистрации");
                {
                    AppendMenu(hPopupMenuFrequency, MF_STRING, 1121, "Низкая");
                    AppendMenu(hPopupMenuFrequency, MF_STRING, 1122, "Средняя");
                    AppendMenu(hPopupMenuFrequency, MF_STRING, 1123, "Высокая");
                }

                AppendMenu(hPopupMenuMetering, MF_STRING | MF_POPUP, (UINT)hPopupMenuDataCollection, "Набор параметров");
                {
                    AppendMenu(hPopupMenuDataCollection, MF_STRING, 1141, "Стандартный");
                    AppendMenu(hPopupMenuDataCollection, MF_STRING, 1142, "Расширенный");
                }
                AppendMenu(hPopupMenuMetering, MF_STRING, 1131, "Экспорт данных в CSV");

            }

            AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenuConditions, "Условия эксперимента");
            {
                AppendMenu(hPopupMenuConditions, MF_STRING | MF_POPUP, (UINT)hPopupMenuGravity, "Гравитация");
                {
                    AppendMenu(hPopupMenuGravity, MF_STRING, 1221, "Луна");
                    AppendMenu(hPopupMenuGravity, MF_STRING, 1222, "Земля");
                    AppendMenu(hPopupMenuGravity, MF_STRING, 1223, "Марс");
                    AppendMenu(hPopupMenuGravity, MF_STRING, 1224, "Юпитер");
                }
                AppendMenu(hPopupMenuConditions, MF_STRING, 1201, "Биг Бэн, 96 метров");
                AppendMenu(hPopupMenuConditions, MF_STRING, 1202, "Домик, 9,6 метра");
            }
/*
            AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenuControl, "Управление");
            {
                AppendMenu(hPopupMenuControl, MF_STRING, 1400, "Старт");
                AppendMenu(hPopupMenuControl, MF_STRING, 1401, "Пауза");
                AppendMenu(hPopupMenuControl, MF_STRING, 1402, "Сброс");
            }
*/
            AppendMenu(MainMenu, MF_STRING | MF_POPUP, 1400, "Старт");
            AppendMenu(MainMenu, MF_STRING | MF_POPUP, 1401, "Пауза");
            AppendMenu(MainMenu, MF_STRING | MF_POPUP, 1402, "Сброс");



            AppendMenu(MainMenu, MF_STRING | MF_POPUP, 1500, "О программе");



            SetMenu(hwnd, MainMenu);
}

protected:
    double height;
    double dist;
    double speed;
    double acceleration;
    double* currentValues;

    double currentTime;

    State* state;

};





#endif // GAME_H_INCLUDED
