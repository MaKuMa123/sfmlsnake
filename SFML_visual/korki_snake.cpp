#include <iostream>
#include "plansza.h"
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <chrono>
#include <SFML/Graphics.hpp>
using namespace std;
sf::RectangleShape segment, sciana, jablko;
sf::Texture segmentT, scianaT, jablkoT;
void zwracaMape(int** mapa, sf::RenderWindow* window)
{
	system("cls");

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
	if (!segmentT.loadFromFile("img/Segment.png"))
	{
		cerr << "Nie można zaladowac grafiki" << endl;
	}
	if (!scianaT.loadFromFile("img/Scianat.png"))
	{
		cerr << "Nie można zaladowac grafiki" << endl;
	}
	if (!jablkoT.loadFromFile("img/Jabłkoo.png"))
	{
		cerr << "Nie można zaladowac grafiki" << endl;
	}
	segment.setSize(sf::Vector2f(50, 50));
	sciana.setSize(sf::Vector2f(50, 50));
	jablko.setSize(sf::Vector2f(50, 50));
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
				zwracaMape(gra.getmapa(),&window);
				window.clear();

				window.display();
			}
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			gra.setkierunek(Kierunek());

		}
		cout << "TWOJ WYNIK TO: " << gra.getpunkty() << " PUNKTY!";
		

		
	}
	
	
	
	return 0;
}

