#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include "Animation.h"
#include "M_SC.h"


using namespace sf;

const int Height = 22;
const int Width = 15;



int field[Height][Width] = {0};

struct Point
{int x,y;} active[4], b[4];

int figures[8][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O

};

bool check()
{
   for (int i=0;i<4;i++)
	  if (active[i].x<0 || active[i].x>=Width || active[i].y>=Height) return 0;
      else if (field[active[i].y][active[i].x]) return 0;

   return 1;
};

int fail = 0;

//score//


int main()
{

    bool MusicSound = true;
    srand(time(0));

	RenderWindow window(VideoMode(640, 960), "Tetris!");

	RectangleShape player(Vector2f(80.0f, 85.0f));
	player.setPosition(545.0f, 4.0f);
	Texture playerTexture;
	playerTexture.loadFromFile("images/miku.png");
	player.setTexture(&playerTexture);

	Animation animation(&playerTexture, Vector2u(3,4), 0.3f);



	RectangleShape player2(Vector2f(80.0f, 85.0f));
	player2.setPosition(20.0f, 0.0f);
	Texture playerTexture2;
	playerTexture2.loadFromFile("images/miku.png");
	player2.setTexture(&playerTexture2);

	Animation animation2(&playerTexture2, Vector2u(3,4), 0.3f);

    Texture tiles;
    Texture fon;
    Texture fr;

	tiles.loadFromFile("images/tiles22.png");
	fon.loadFromFile("images/hatsune-miku-4k-fx-1280x2120.jpg");
	fr.loadFromFile("images/fonff.png");

    fon.setSmooth(true);

	Sprite s(tiles);
	Sprite background(fon);
	Sprite frame(fr);

    background.setScale(window.getView().getSize().x/background.getGlobalBounds().width, window.getView().getSize().y/background.getGlobalBounds().height);
    //audio load//

	Music audio;
	audio.openFromFile("audio.wav");
	audio.setLoop(true);
	audio.setVolume(60);
	audio.play();

	Music lose;
	lose.openFromFile("lose.wav");
    lose.setVolume(60);

    Music ohno;
    ohno.openFromFile("ohno.wav");
    ohno.setVolume(60);


    int dx=0; bool rotate=0; int colorNum=1;
	float timer=0,delay=0.3;

	float deltaTime = 0.0f;


	Clock clock;
    Clock clockAn;

    Font font;
    font.loadFromFile("images/COMICATE.TTF");

    M_SC score;

    while (window.isOpen())
    {
        deltaTime = clockAn.restart().asSeconds();
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

    //keybindings//

	if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;


	if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
        audio.stop();
        ohno.play();


        std::cout<<"You quit the game "<<std::endl;
        std::cout<<"See you next time!"<<std::endl;
         system("pause");
        break;
    }

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
	//move//
	for (int i=0;i<4;i++)  { b[i]=active[i]; active[i].x+=dx; }
    if (!check()) for (int i=0;i<4;i++) active[i]=b[i];

    //rotate//
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

	//TICK//
	if (timer>delay)
	  {
	    for (int i=0;i<4;i++) { b[i]=active[i]; active[i].y+=1; }

		if (!check())
		{
		 for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;
         fail++;


         //quit the game when tiles have no more room to spawn//
         if(fail>1){
            window.close();
            audio.stop();
            lose.play();
            std::cout<<"Final score: "<<score.SCORE<<std::endl;
            system("pause");
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

	//check lines//
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
		    score.SCORE+=100;
		   std::cout << "SCORE: " <<score.SCORE<<std::endl;
		}

		if (count<Width)
    {
        k--;
	}
	}

    dx=0; rotate=0; delay=0.3;

   //draw//
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
    animation.Update(3, deltaTime);
    player.setTextureRect(animation.uvRect);

    animation2.Update(2, deltaTime);
    player2.setTextureRect(animation2.uvRect);


	window.draw(frame);
	window.draw(player);
	window.draw(player2);
	score.textscore(window,font);
	window.display();

	}
    return 0;
}
