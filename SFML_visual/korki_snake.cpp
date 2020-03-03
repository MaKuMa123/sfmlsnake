#include <SFML/Graphics.hpp>
#include <iostream>
#include "plansza.h"
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <chrono>

using namespace std;
sf::RectangleShape segment, sciana, jablko;
sf::Texture segmentT, scianaT, jablkoT;
sf::Text message;
sf::Text print(string msg)
{
	message.setString(msg);
	message.setFillColor(sf::Color::Magenta);
	message.setCharacterSize(60);
	message.setPosition(0, 0);
	return message;
	
}
void zwracaMape(int** mapa, sf::RenderWindow* window)
{
	

	for (int i = 0; i < 20; i++)
	{
		
		for (int j = 0; j<20; j++)
		{
			
			if (mapa[i][j] == plansza::PUSTE)
			{
				
			}
			else if (mapa[i][j] == plansza::WONSZ)
			{
				segment.setPosition(i*30, j*30);
				window->draw(segment);
			}
			else if (mapa[i][j] == plansza::JEDZENIE)
			{
				jablko.setPosition(i * 30, j * 30);
				window->draw(jablko);
			}
			else if (mapa[i][j] == plansza::SCIANA)
			{
				sciana.setPosition(i * 30, j * 30);
				window->draw(sciana);
			}
			
		}
		cout << endl;
	}
	
}
void Load()
{
	if (!segmentT.loadFromFile("img/segment.png"))
	{
		cerr << "Nie można zaladowac grafiki" << endl;
	}
	if (!scianaT.loadFromFile("img/Sciana.png"))
	{
		cerr << "Nie można zaladowac grafiki" << endl;
	}
	if (!jablkoT.loadFromFile("img/Jabłkoo.png"))
	{
		cerr << "Nie można zaladowac grafiki" << endl;
	}
	segment.setSize(sf::Vector2f(30, 30));
	sciana.setSize(sf::Vector2f(30, 30));
	jablko.setSize(sf::Vector2f(30, 30));
	segment.setTexture(&segmentT);
	sciana.setTexture(&scianaT);
	jablko.setTexture(&jablkoT);

}
int Kierunek()
{
	int k=0;
	if (GetAsyncKeyState('D'))
	{
		k = wonsz::PRAWO;
	}
	else if (GetAsyncKeyState('S'))
	{
		k = wonsz::DOL;
	}
	else if (GetAsyncKeyState('A'))
	{
		k = wonsz::LEWO;
	}
	else if (GetAsyncKeyState('W'))
	{
		k = wonsz::GORA;
	}
	return k;
}


int main()
{
	Load();
	
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	

	while (window.isOpen())
	{
		auto start = chrono::system_clock::now();
		auto aktualne = chrono::system_clock::now();

		float interval = 0.3;
		plansza gra = plansza(20, 20);
		gra.start();
		while (!gra.czyKoniec())
		{
			aktualne = chrono::system_clock::now();
			chrono::duration<float> tajm = aktualne - start;
			float tajmUplynol = tajm.count();
			if (tajmUplynol > interval)
			{
				start = chrono::system_clock::now();
				gra.update();
				
				window.clear();
				zwracaMape(gra.getmapa(), &window);
				window.display();
			}
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
					gra.setkierunek(wonsz::DOL);
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
					gra.setkierunek(wonsz::PRAWO);
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
					gra.setkierunek(wonsz::GORA);
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
					gra.setkierunek(wonsz::LEWO);
			}

			

		}
		
         cout << "TWOJ WYNIK TO: " << gra.getpunkty() << " PUNKTY!";
		 cout << "Czy chcesz zagrac jeszcze raz? " << endl <<"0. Tak"<<endl<<"1. Nie"<<endl;
		 int decyzja;
		 cin >> decyzja;
		 if (decyzja == 0)
		 {

		 }
		 else if (decyzja == 1)
		 {
			 window.close();
		 }
		 else
		 {
			 window.close();
		 }
		
		
		
	}
	
	
	
	return 0;
}
