#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

class Graphics
{
public:
    enum Pictures
    {
        DEF_PICTURE,
        HOUSE,
        BIG_BEN
    };
    Graphics()
    {
        visible = true;
        buildingX = 519;
        buildingTopY = 31;
        buildingHeightPix = 260;
        buildingHeightMetres = 96.0;
        backgroundFile[0] = "default.bmp";
        backgroundFile[1] = "height_3_floors.bmp";
        backgroundFile[2] = "height_96_m.bmp";
        building = BIG_BEN;
        gravity = "Луна";
 //шрифт:
    font.lfHeight =  16;// Устанавливает высоту шрифта или символа
    font.lfWidth =  0;// Устанавливает среднюю ширину символов в шрифте
    font.lfEscapement = 0;// Устанавливает угол, между вектором наклона и осью X устройства
    font.lfOrientation = 0;// Устанавливает угол, между основной линией каждого символа и осью X устройства
    font.lfWeight = 1000;// Устанавливает толщину шрифта в диапазоне от 0 до 1000
    font.lfItalic = 0;// Устанавливает курсивный шрифт
    font.lfUnderline = 0;// Устанавливает подчеркнутый шрифт
    font.lfStrikeOut = 0;// Устанавливает зачеркнутый шрифт
    font.lfCharSet = RUSSIAN_CHARSET;// Устанавливает набор символов
    font.lfOutPrecision = 0;// Устанавливает точность вывода
    font.lfClipPrecision = 0;// Устанавливает точность отсечения
    font.lfQuality = 0;// Устанавливает качество вывода
    font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта
    strcpy(font.lfFaceName , "VERDANA");//  устанавливает название шрифта

    hfont = ::CreateFontIndirect(&font);
    }

    void setHouse()
    {
        building = HOUSE;
        buildingHeightMetres = 9.6;
    }
        void setBigBen()
    {
        building = BIG_BEN;
        buildingHeightMetres = 96.0;
    }

 void setGravity(const char* planetName)
 {
     delete gravity;
     gravity = planetName;
 }

    void setVisible(bool vis)
    {
        visible = vis;
    }

    void draw(HWND hWnd, PAINTSTRUCT pS, HDC hDc, double distance, double time, double speed)
    {
            hwnd = hWnd;
            ps = pS;
            hdc = hDc;

     hdc = BeginPaint(hwnd, &ps);
        {
            HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, backgroundFile[building], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            BITMAP Bitmap;
            GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
            HDC hCompatibleDC = CreateCompatibleDC(hdc);
            HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);
            RECT Rect;

//цвет шрифта и фона:
    SelectObject(hCompatibleDC,hfont);
    SetTextColor(hCompatibleDC, RGB(255, 240, 240));
    SetBkColor(hCompatibleDC, RGB(0, 0, 0));
//вывод надписей:
//Состояние системы:
    if (!visible)
    {
    SetTextColor(hCompatibleDC, RGB(255, 120, 120));
    TextOut(hCompatibleDC, 425, 480, "Столкновение", lstrlen("Столкновение"));
    SetTextColor(hCompatibleDC, RGB(255, 180, 180));
    }
    else if (time>0.01)
    {
    SetTextColor(hCompatibleDC, RGB(255, 255, 80));
    TextOut(hCompatibleDC, 425, 480, "Полёт", lstrlen("Полёт"));
    SetTextColor(hCompatibleDC, RGB(255, 255, 140));
    }
    else
    {
    SetTextColor(hCompatibleDC, RGB(120, 255, 120));
    TextOut(hCompatibleDC, 425, 480, "Готовность", lstrlen("Готовность"));
    SetTextColor(hCompatibleDC, RGB(200, 255, 200));
    }
    TextOut(hCompatibleDC, 425, 465, "Состояние:", lstrlen("Состояние:"));
//Гравитация:
    TextOut(hCompatibleDC, 425, 420, "Гравитация:", lstrlen("Гравитация:"));
    TextOut(hCompatibleDC, 425, 435, gravity, lstrlen(gravity));
//Время:
    TextOut(hCompatibleDC, 140, 420, "Время:", lstrlen("Время:"));
    char strTime[17];
    itoa ((int)time, strTime, 10);
    TextOut(hCompatibleDC, 140, 435, strTime, lstrlen(strTime));
    TextOut(hCompatibleDC, 160, 435, "с", lstrlen("с"));
//Высота:
    TextOut(hCompatibleDC, 140, 465, "Высота:", lstrlen("Высота:"));
    char strHeight[17];
    itoa ((int)(buildingHeightMetres - distance), strHeight, 10);
    TextOut(hCompatibleDC, 140, 480, strHeight, lstrlen(strHeight));
    TextOut(hCompatibleDC, 160, 480, "м", lstrlen("м"));
//Скорость:
    TextOut(hCompatibleDC, 280, 420, "Скорость:", lstrlen("Скорость:"));
    char strSpeed[17];
    itoa ((int)speed, strSpeed, 10);
    TextOut(hCompatibleDC, 280, 435, strSpeed, lstrlen(strSpeed));
    TextOut(hCompatibleDC, 300, 435, "м/с", lstrlen("м/с"));
//Путь:
    TextOut(hCompatibleDC, 280, 465, "Путь:", lstrlen("Путь:"));
    char strDist[17];
    itoa ((int)distance, strDist, 10);
    TextOut(hCompatibleDC, 280, 480, strDist, lstrlen(strDist));
    TextOut(hCompatibleDC, 300, 480, "м", lstrlen("м"));






        if(visible)
            phone(hCompatibleDC, distance);


            GetClientRect(hwnd, &Rect);
            StretchBlt(hdc, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
                Bitmap.bmHeight, SRCCOPY);


            SelectObject(hCompatibleDC, hOldBitmap);
            DeleteObject(hBitmap);
            DeleteDC(hCompatibleDC);

        }
        EndPaint(hwnd, &ps);
    }
protected:
    bool visible;
    int buildingX;
    int buildingTopY;
    int buildingHeightPix;
    double buildingHeightMetres;
    char* backgroundFile[3];
    int building;
    LOGFONT font;
    HFONT hfont;
    const char* gravity;

    HWND hwnd;
    PAINTSTRUCT ps;
    HDC hdc;
    void phone(HDC hCmpDC, double dist)
    {
        //мерцание:
        bool dark = true;
        static long int timer = 0;
        timer++;
        if(timer%10<5)
            dark = true;
        else
            dark = false;

        //случайные цвета:
        srand(clock());
        int randAddition = rand()%49-24;

        static unsigned int red = 200;
        static unsigned int green = 200;
        if(red+randAddition<255&&red+randAddition>150)
                red+=randAddition;
        if(green-randAddition<255&&green-randAddition>150)
                green-=randAddition;

        double pixPerMetre = buildingHeightPix/buildingHeightMetres;
            HPEN hpen1 = CreatePen(PS_SOLID, 2, RGB(dark?0:red, dark?0:green, 255));
            HBRUSH hbrush = CreateSolidBrush(RGB(red, green, 255));
            SelectObject(hCmpDC,hbrush);
            SelectObject(hCmpDC,hpen1);

            //прямоугольник:


            Rectangle(hCmpDC,buildingX,buildingTopY + dist*pixPerMetre,
                       buildingX + ((building==BIG_BEN)?1:2), buildingTopY + dist*pixPerMetre + 2);

            DeleteObject(hbrush);
            DeleteObject(hpen1);
    }

};

#endif // GRAPHICS_H_INCLUDED
