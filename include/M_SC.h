#ifndef M_SC_H
#define M_SC_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include <Animation.h>


using namespace sf;
class M_SC
{
    public:
        void textscore(RenderWindow &window, Font &font);

        unsigned long SCORE=0;



    protected:

    private:
};

#endif // M_SC_H
