#ifndef MAINZ_H_INCLUDED
#define MAINZ_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include <SFML/System.hpp>


using namespace sf;

const int Height = 22;
const int Width = 15;

unsigned long SCORE=0;

int field[Height][Width] = {0};

struct Point
{int x,y;} active[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};



    std::string IntToStr(int val){
        std::stringstream sssr;
        sssr<<val;
        std::string comunism=sssr.str();
        return comunism;
    }

    bool check()
    {
        for (int i=0;i<4;i++)
            if (active[i].x<0 || active[i].x>=Width || active[i].y>=Height) return 0;
            else if (field[active[i].y][active[i].x]) return 0;

        return 1;
    }


    int fail = 0;

    void textscore(RenderWindow & window, Font& font)
    {
        Text text;
        text.setFont(font);
        text.setFillColor(Color::Magenta);
        text.setString(IntToStr(SCORE));
        text.setCharacterSize(55);
        text.setPosition((window.getView().getSize().x/2)-text.getLocalBounds().width/2,7);
        window.draw(text);
    }

    class game
    {
        public:

        Texture tiles;
        Texture fon;
        Texture fr;


        Sprite s(tiles);
        Sprite background(fon);
        Sprite frame(fr);



        Clock clock;
        Font font;

        bool MusicSound = true;

        RenderWindow window(VideoMode(640, 960), "Tetris!");

        Music audio;

        int dx=0; bool rotate=0; int colorNum=1;
        float timer=0,delay=0.3;

    void dokeyboard(){

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                audio.openFromFile("earrape.wav");
                audio.setLoop(true);
                audio.setVolume(100);
                audio.play();
            }
            if (Keyboard::isKeyPressed(Keyboard::N))
            {
                audio.openFromFile("audio.wav");
                audio.setLoop(true);
                audio.setVolume(60);
                audio.play();
            }

            if (Keyboard::isKeyPressed(Keyboard::N))
            {
                audio.openFromFile("audio.wav");
                audio.setLoop(true);
                audio.setVolume(60);
                audio.play();
            }
            if (Keyboard::isKeyPressed(Keyboard::M))
            {
                MusicSound = !MusicSound;
                if(MusicSound==true)
                {
                    audio.setVolume(100);
                }

                if(MusicSound==false)
                {
                    audio.setVolume(0);
                }

            }
    }
    void doevente(){
        float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

			if (e.type == Event::KeyPressed)
            if (e.key.code==Keyboard::Up) rotate=true;
			  else if (e.key.code==Keyboard::Left) dx=-1;
			  else if (e.key.code==Keyboard::Right) dx=1;


		}
    }


    void movemente(){
        for (int i=0;i<4;i++)  { b[i]=active[i]; active[i].x+=dx; }
        if (!check()) for (int i=0;i<4;i++) active[i]=b[i];

    };

    void rotatate(){
    if (rotate)
	  {
		Point p = active[1]; //centor//
		for (int i=0;i<4;i++)
		  {
			int x = active[i].y-p.y;
			int y = active[i].x-p.x;
			active[i].x = p.x - x;
			active[i].y = p.y + y;
	 	  }
   	    if (!check()) for (int i=0;i<4;i++) active[i]=b[i];
	  }
    }

    void tiktak(){
    	if (timer>delay)
	  {
	    for (int i=0;i<4;i++) { b[i]=active[i]; active[i].y+=1; }

		if (!check())
		{
		 for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;
         fail++;


         //quit the game when tiles have no more room to spawn//
         if(fail>2){

            window.close();
            std::cout<<"Final score: "<<SCORE;
         }

		 colorNum=1+rand()%7;
		 int n=rand()%7;
		 for (int i=0;i<4;i++)
		   {
		    active[i].x = figures[n][i] % 2;
		    active[i].y = figures[n][i] / 2-1;
		   }
		} else fail = 0;

	  	timer=0;
	  }

    }

    void checks(){
        int k=Height-1;
	for (int i=Height-1;i>0;i--)
	{
		int count=0;
		for (int j=0;j<Width;j++)
		{
		    if (field[i][j]) count++;
		    field[k][j]=field[i][j];
		}
		if(count >= Width)
		{
		    SCORE+=100;
		   std::cout << "SCORE: " <<SCORE<<std::endl;
		}

		if (count<Width)
    {
        k--;
	}
	}

    dx=0; rotate=0; delay=0.3;


    }

    void draww(){
    window.clear(Color::White);
    window.draw(background);

	for (int i=0;i<Height;i++)
	 for (int j=0;j<Width;j++)
	   {
         if (field[i][j]==0) continue;
		 s.setTextureRect(IntRect(field[i][j]*36,0,36,36));
		 s.setPosition(j*36,i*36);
		 s.move(57,89); //offset
		 window.draw(s);
	   }

	for (int i=0;i<4;i++)
	  {
		s.setTextureRect(IntRect(colorNum*36,0,36,36));
		s.setPosition(active[i].x*36,active[i].y*36);
		s.move(57,89); //offset
		window.draw(s);
	  }


	window.draw(frame);
	textscore(window,font);
	window.display();


    }


}; //zakanchivaetsa class game




#endif // MAINZ_H_INCLUDED
