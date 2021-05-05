#include <SFML/Graphics.hpp>
#include <libgallows/menu.h>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1200, 1000), "The gallows");

	MainMenu(window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}
