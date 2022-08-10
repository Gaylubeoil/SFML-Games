#include "Platform/Platform.hpp"
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;
const int WINDOW_WIDTH = 455;
const int WINDOW_HEIGHT = 455;

const int size = 56;
Vector2f offset(28, 28);

const int WIDTH = 8;
const int HEIGHT = 8;

sf::Sprite figures[32];
std::string position = "";

const int board[8][8] = {
	-1, -2, -3, -4, -5, -3, -2, -1, -6, -6, -6, -6, -6, -6, -6, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 1, 2, 3, 4, 5, 3, 2, 1
};

std::string toChessNote(Vector2f p);

Vector2f toCoord(char a, char b);

void move(std::string str);

void load_position();

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "De la Luben Chess");

	sf::Texture pisces_texture, board_texture;

	pisces_texture.loadFromFile("assets/figures.png");
	board_texture.loadFromFile("assets/board0.png");

	sf::Sprite board_sprite(board_texture);

	for (int i = 0; i < 32; ++i)
	{
		figures[i].setTexture(pisces_texture);
	}

	load_position();

	bool is_move = false;
	float dx = 0, dy = 0;
	Vector2f old_pos, new_pos;
	std::string current_figure;
	std::string str;
	int n = 0;

	while (window.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			///Takebacks with Backspace///
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::BackSpace)
				{
					position.erase(position.length() - 6, 5);
					load_position();
					//TODO
					//FIX FIRST MOVE EXCEPTION
				}
			}

			//// Drag and Drop ////
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					for (int i = 0; i < 32; ++i)
					{
						if (figures[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							is_move = true;
							n = i;
							dx = pos.x - figures[i].getPosition().x;
							dy = pos.y - figures[i].getPosition().y;
							old_pos = figures[i].getPosition();
						}
					}
			}
			if (event.type == sf::Event::MouseButtonReleased)
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					is_move = false;
					Vector2f p = figures[n].getPosition() + Vector2f(size / 2, size / 2);
					new_pos = Vector2f(size * int(p.x / size), size * int(p.y / size));
					str = toChessNote(old_pos) + toChessNote(new_pos);
					move(str);
					position += str + " ";
					std::cout << str << std::endl;
					figures[n].setPosition(new_pos);
				}
		}
		//Computer move


		if (is_move)
		{
			figures[n].setPosition(pos.x - dx, pos.y - dy);
		}
		/// draw ///
		window.clear();
		window.draw(board_sprite);
		for (size_t i = 0; i < 32; i++)
		{
			window.draw(figures[i]);
		}

		window.display();
	}

	return 0;
}

void load_position()
{
	int k = 0;
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			int n = board[i][j];
			if (!n)
				continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			figures[k].setTextureRect(IntRect(size * x, size * y, size, size));
			figures[k++].setPosition(size * j, size * i);
		}
	}
	for (size_t i = 0; i < position.length(); i += 5)
	{
		move(position.substr(i, 4));
	}
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return Vector2f(x * size, y * size);
}
void move(std::string str)
{
	Vector2f old_pos = toCoord(str[0], str[1]);
	Vector2f new_pos = toCoord(str[2], str[3]);

	for (int i = 0; i < 32; i++)
		if (figures[i].getPosition() == new_pos)
			figures[i].setPosition(-100, -100);

	for (int i = 0; i < 32; i++)
		if (figures[i].getPosition() == old_pos)
			figures[i].setPosition(new_pos);

	//castling       //if the king didn't move
	if (str == "e1g1")
		if ((int)position.find("e1") == -1)
			move("h1f1");
	if (str == "e8g8")
		if ((int)position.find("e8") == -1)
			move("h8f8");
	if (str == "e1c1")
		if ((int)position.find("e1") == -1)
			move("a1d1");
	if (str == "e8c8")
		if ((int)position.find("e8") == -1)
			move("a8d8");
}

std::string toChessNote(Vector2f p)
{
	std::string s = "";
	s += char(p.x / size + 97);
	s += char(7 - p.y / size + 49);
	return s;
}