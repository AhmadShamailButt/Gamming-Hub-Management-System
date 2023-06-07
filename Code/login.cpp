#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<Windows.h>
#include "textbox.h"
#include"Managementsystem.h"
#include<iostream>
#include<conio.h>
#include<time.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include<iostream>
#include <chrono>sfml
#include <random>
#include "Cell.h"
#include "DrawText.h"
#include "Field.h"
#include "GetCell.h"
#include "Global.h"
#include <chrono>
#include<string>
using namespace std;
using namespace sf;
int stringToInt(const string& str) {
	int result = 0;
	int sign = 1; // positive by default
	for (char c : str) {
		if (c == '-') {
			sign = -1;
		}
		else if (c >= '0' && c <= '9') {
			result = result * 10 + (c - '0');
		}
		else {
			// error handling - handle invalid input as necessary
			throw std::invalid_argument("Invalid input");
		}
	}
	return result * sign;
}
class Paddles
{
public:
	RectangleShape shape;
	Vector2f velocity{ 0,5 };

	Paddles(float x, float y)
	{
		shape.setPosition(x, y);
		shape.setSize({ 20.f, 100.f });
		shape.setFillColor(Color::White);
		shape.setOrigin(shape.getSize() / 2.f);
	}
	float getX()
	{
		return shape.getPosition().x;
	}
	float getY()
	{
		return shape.getPosition().y;
	}
	float getLeft()
	{
		return getX() - shape.getSize().x / 2.f;
	}
	float getRight()
	{
		return getX() + shape.getSize().x / 2.f;
	}
	float getTop()
	{
		return getY() - shape.getSize().y / 2.f;
	}
	float getBottom()
	{
		return getY() + shape.getSize().y / 2.f;
	}
	void upDate()
	{
		shape.move(velocity);

		if (getTop() < 0)
		{
			shape.setPosition(getX(), shape.getSize().y / 2.f);
		}
		else if (getBottom() > 800)
		{
			shape.setPosition(getX(), 800 - shape.getSize().y / 2.f);
		}
	}
};
class Ball
{
public:
	CircleShape shape;
	Vector2f velocity{ 10.f,4.f };
	Vector2f velocity1{ 15.f,4.f };
	Vector2f velocity2{ 19.f,4.f };

	Ball(float x, float y)
	{
		shape.setPosition(x, y);
		shape.setRadius(10.f);
		shape.setFillColor(Color::Yellow);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		shape.setOutlineThickness(2);
		shape.setOutlineColor(Color::Black);
	}
	float getX()
	{
		return shape.getPosition().x;
	}
	float getY()
	{
		return shape.getPosition().y;
	}
	float getLeft()
	{
		return getX() - shape.getRadius();
	}
	float getRight()
	{
		return getX() + shape.getRadius();
	}
	float getTop()
	{
		return getY() - shape.getRadius();
	}
	float getBottom()
	{
		return getY() + shape.getRadius();
	}
	void upDate()
	{
		shape.move(velocity);

		if (getLeft() < 0)
		{
			velocity.x = abs(velocity.x);
		}
		else if (getRight() > 1400)
		{
			velocity.x = -abs(velocity.x);
		}
		if (getTop() < 0)
		{
			velocity.y = abs(velocity.y);
		}
		else if (getBottom() > 800)
		{
			velocity.y = -abs(velocity.y);
		}
	}
	void upDate1()
	{
		shape.move(velocity1);

		if (getLeft() < 0)
		{
			velocity1.x = abs(velocity1.x);
		}
		else if (getRight() > 1400)
		{
			velocity1.x = -abs(velocity1.x);
		}
		if (getTop() < 0)
		{
			velocity1.y = abs(velocity1.y);
		}
		else if (getBottom() > 800)
		{
			velocity1.y = -abs(velocity1.y);
		}
	}
	void upDate2()
	{
		shape.move(velocity2);

		if (getLeft() < 0)
		{
			velocity2.x = abs(velocity2.x);
		}
		else if (getRight() > 1400)
		{
			velocity2.x = -abs(velocity2.x);
		}
		if (getTop() < 0)
		{
			velocity2.y = abs(velocity2.y);
		}
		else if (getBottom() > 800)
		{
			velocity2.y = -abs(velocity2.y);
		}
	}
};
string concatenate(string n)
{
	string l = "Player1 Score : ";
	n = l + n;
	return n;
}
string concatenate1(string m)
{
	string l = "Player2 Score : ";
	m = l + m;
	return m;
}
int game3(RenderWindow &window)
{
	window.clear();
	window.setSize(sf::Vector2u(1400, 800));
	window.setView(sf::View(sf::FloatRect(0, 0, 1400, 800)));


	int max;
	int i = 0, time = 0;
	int j = 0;
	int duration = 150;

	// Get the current clock time
	clock_t start = clock();

	// Convert the duration to clock ticks
	clock_t durationTicks = duration * CLOCKS_PER_SEC;
	string n = "0", m = "0";
	window.setFramerateLimit(60);

	//  Load Font
	Font font;
	font.loadFromFile("arial.ttf");

	//  Pictures
	Texture backpic;
	backpic.loadFromFile("circle.jpg");
	Sprite sprite1(backpic);
	sprite1.setScale(Vector2f(.8, .7));
	float scaleX = static_cast<float>(window.getSize().x) / backpic.getSize().x;
	float	scaleY = static_cast<float>(window.getSize().y) / backpic.getSize().y;
	sprite1.setScale(scaleX, scaleY);

	// Centre line
	RectangleShape line(Vector2f(800, .5));
	line.setFillColor(Color::White);
	line.setPosition(Vector2f(window.getSize().x / 2, 0));
	line.rotate(90);


	// Paddle objects
	Paddles player1(12, 350);
	Paddles player2(1388, 350);

	// Circle object
	Ball ball(window.getSize().x / 2, window.getSize().y / 2);

	// Score 
	Text score1;
	score1.setPosition(350, 10);
	score1.setFont(font);
	score1.setString("0");
	score1.setCharacterSize(60);
	score1.setFillColor(Color::Red);
	score1.setOutlineThickness(2);
	score1.setOutlineColor(Color::Black);

	Text score2;
	score2.setPosition(1050, 10);
	score2.setFont(font);
	score2.setString("0");
	score2.setCharacterSize(60);
	score2.setFillColor(Color::Blue);
	score2.setOutlineThickness(2);
	score2.setOutlineColor(Color::Black);


	Text score5;
	score5.setPosition(730, 700);
	score5.setFont(font);
	score5.setString("0");
	score5.setCharacterSize(60);
	score5.setFillColor(Color::Red);
	score5.setOutlineThickness(2);
	score5.setOutlineColor(Color::Black);


	Text score6;
	score6.setPosition(550, 700);
	score6.setFont(font);
	score6.setString("Time :");
	score6.setCharacterSize(60);
	score6.setFillColor(Color::Blue);
	score6.setOutlineThickness(2);
	score6.setOutlineColor(Color::Black);


	while (window.isOpen())
	{
		clock_t current = clock();

		// Calculate the elapsed time in clock ticks
		clock_t elapsedTicks = current - start;

		// Calculate the elapsed time in seconds
		double elapsedSeconds = static_cast<double>(elapsedTicks) / CLOCKS_PER_SEC;
		time = round(elapsedSeconds);

		string k = to_string(time);
		// Check if the timer has expired
		if (elapsedTicks >= durationTicks) {
			std::cout << "Timer expired!" << std::endl;
			break;
		}



		Event event;
		while (window.pollEvent(event))
		{
			//  Closing Conditions
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		if (time > 40 && time <= 100)
		{
			// Update Paddle 1
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player1.velocity.y = -16.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player1.velocity.y = 16.0f;
			}
			else
			{
				player1.velocity.y = 0.f;
			}
			// Update Paddle 2
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				player2.velocity.y = -16.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				player2.velocity.y = 16.0f;
			}
			else
			{
				player2.velocity.y = 0.f;
			}
		}
		else if (time > 100)
		{
			// Update Paddle 1
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player1.velocity.y = -18.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player1.velocity.y = 18.0f;
			}
			else
			{
				player1.velocity.y = 0.f;
			}
			// Update Paddle 2
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				player2.velocity.y = -18.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				player2.velocity.y = 18.0f;
			}
			else
			{
				player2.velocity.y = 0.f;
			}
		}
		else
		{
			// Update Paddle 1
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player1.velocity.y = -14.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player1.velocity.y = 14.0f;
			}
			else
			{
				player1.velocity.y = 0.f;
			}
			// Update Paddle 2
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				player2.velocity.y = -14.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				player2.velocity.y = 14.0f;
			}
			else
			{
				player2.velocity.y = 0.f;
			}
		}

		if (time > 40 && time <= 100)
		{

			if (ball.shape.getGlobalBounds().intersects(player1.shape.getGlobalBounds()))
			{
				ball.velocity1.x = abs(ball.velocity1.x);
			}
			else if (ball.shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds()))
			{
				ball.velocity1.x = -abs(ball.velocity1.x);
			}
		}
		else if (time > 100)
		{
			if (ball.shape.getGlobalBounds().intersects(player1.shape.getGlobalBounds()))
			{
				ball.velocity2.x = abs(ball.velocity2.x);
			}
			else if (ball.shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds()))
			{
				ball.velocity2.x = -abs(ball.velocity2.x);
			}
		}
		else
		{
			if (ball.shape.getGlobalBounds().intersects(player1.shape.getGlobalBounds()))
			{
				ball.velocity.x = abs(ball.velocity.x);
			}
			else if (ball.shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds()))
			{
				ball.velocity.x = -abs(ball.velocity.x);
			}
		}

		if (ball.getRight() > 1400)
		{
			i++;
			n = to_string(i);
			score1.setString(n);
			sleep(seconds(1));
			ball.shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		}
		if (ball.getLeft() < 0)
		{
			j++;
			m = to_string(j);
			score2.setString(m);
			sleep(seconds(1));
			ball.shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		}

		player1.upDate();
		player2.upDate();
		if (time > 40 && time <= 100)
		{
			ball.upDate1();
		}
		else if (time > 100)
		{
			ball.upDate2();
		}
		else
		{
			ball.upDate();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			return 0;
		}
		window.draw(sprite1);
		window.draw(score1);
		window.draw(score2);
		window.draw(score5);
		window.draw(score6);

		window.draw(player1.shape);
		window.draw(player2.shape);
		window.draw(line);
		score5.setString(k);

		window.draw(ball.shape);

		window.display();


	}
	if (i > j)
	{
		max = i;
	}
	else if (i < j)
	{
		max = i;
	}
	else
	{
		max = j;
	}
	int rec = 0;
	ifstream input("record.txt");


	Text score7;
	score7.setPosition(300, 600);
	score7.setFont(font);
	score7.setCharacterSize(60);
	score7.setFillColor(Color::Black);
	score7.setOutlineThickness(2);
	score7.setOutlineColor(Color::White);
	if (input.is_open())
	{

		input >> rec;
	}
	if (rec < max)
	{
		ofstream out("record.txt");
		if (out.is_open())
		{
			out << max;
		}
		score7.setString("Congratulations! New Record Score");
	}


	Font font1;
	font1.loadFromFile("arial.ttf");

	Texture backpic1;
	backpic1.loadFromFile("dadu1.jpeg");
	Sprite sprite2(backpic1);
	sprite2.setScale(Vector2f(.8, .7));
	float scaleX1 = static_cast<float>(window.getSize().x) / backpic1.getSize().x;
	float	scaleY1 = static_cast<float>(window.getSize().y) / backpic1.getSize().y;
	sprite2.setScale(scaleX1, scaleY1);

	n = concatenate(n);
	m = concatenate1(m);


	Text score3;
	score3.setPosition(400, 8);
	score3.setFont(font);
	score3.setString("----RESULTS----");
	score3.setCharacterSize(60);
	score3.setFillColor(Color::Black);
	score3.setOutlineThickness(2);
	score3.setOutlineColor(Color::White);


	score1.setPosition(120, 120);
	score1.setFont(font);
	score1.setString(n);
	score1.setCharacterSize(47);
	score1.setFillColor(Color::Red);
	score1.setOutlineThickness(2);
	score1.setOutlineColor(Color::Black);
	score2.setPosition(120, 200);
	score2.setFont(font);
	score2.setString(m);
	score2.setCharacterSize(47);
	score2.setFillColor(Color::Blue);
	score2.setOutlineThickness(2);
	score2.setOutlineColor(Color::Black);

	string l;

	if (i > j)
	{
		l = "Player1 Won!!";
	}
	else if (i < j)
	{
		l = "Player2 Won!!";
	}
	else
	{
		l = "Match Tied";
	}
	Text score4;
	score4.setPosition(500, 500);
	score4.setFont(font);
	score4.setString(l);
	score4.setCharacterSize(60);
	score4.setFillColor(Color::White);
	score4.setOutlineThickness(4);
	score4.setOutlineColor(Color::Black);

	while (window.isOpen())
	{
		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::Closed)
			{
				window.close();
			}
		}

		window.draw(sprite2);
		window.draw(score3);
		window.draw(score1);
		window.draw(score2);
		window.draw(score4);
		if (max > rec)
		{
			window.draw(score7);
		}
		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			return 0;
		}
	}
}
template <typename T>
const T& clamp(const T& value, const T& minValue, const T& maxValue) {
	if (value < minValue) {
		return minValue;
	}
	else if (value > maxValue) {
		return maxValue;
	}
	else {
		return value;
	}
}
string getScore() {
	ifstream r1("HS.txt");
	string s;
	r1 >> s;
	return s;
}
void setScore(string s) {
	ofstream r1("HS.txt");
	r1 << s;
}
int game1(RenderWindow& window)
{
	sf::Time d = sf::seconds(2.0f);
	sf::Clock dc;
	sf::Texture menu;
	menu.loadFromFile("MineMenu1.png");
	sf::Sprite spriteMenu(menu);
	//Used to make the game framerate-independent
	unsigned lag = 0;

	//Alexander has 4 states:
	//0) Idle
	//1) When you're about to open a cell
	//2) When the game is over and you've lost
	//3) When the game is over and you've won
	unsigned char Alexander_state = 0;

	//Similar to lag, used to make the game framerate-independent
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	//SFML thing. Stores events, I think
	sf::Event event;

	//SFML window
	//sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMNS * SCREEN_RESIZE, SCREEN_RESIZE * (FONT_HEIGHT + CELL_SIZE * COLUMNS)), "Minesweeper", sf::Style::Close);
	//sf::RenderWindow window(sf::VideoMode(643, 705), "Minesweeper", sf::Style::Close);

	//Here we're resizing the window
	//window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, FONT_HEIGHT + CELL_SIZE * ROWS)));
	//Alexander's sprite.
	sf::Sprite Alexander;

	//Alexander's texture.
	sf::Texture Alexander_texture;	
	//We get the texture from an image
	Alexander_texture.loadFromFile("Alexander.png");

	//We're putting Alexander in the bottom right corner
	Alexander.setPosition(static_cast<float>(CELL_SIZE * COLUMNS - Alexander_texture.getSize().y), CELL_SIZE * ROWS);
	Alexander.setTexture(Alexander_texture);

	//Field object called "field" (I'm so good at naming stuff!)
	Field field;

	//Get the current time and store it in a variable
	previous_time = std::chrono::steady_clock::now();
	sf::Clock clock;
	int scene = 0;
	/*while (window.isOpen()) {
		if (scene == 0) {
			window.setSize(sf::Vector2u(650, 730));

			window.draw(spriteMenu);

		}
		else {
			window.setSize(sf::Vector2u(650, 730));
			window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, FONT_HEIGHT + CELL_SIZE * ROWS)));
			field.draw(window);
		}
		window.display();
		Sleep(10000);
		if (scene == 0) {
			scene = 1;
		}
		else {
			scene = 0;
		}
	}*/
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		//error handling
	}
	sf::Text score;
	score.setFont(font);
	string s = getScore();
	score.setString(s);
	score.setCharacterSize(26); // Set the character size
	score.setFillColor(sf::Color::Black); // Set the fill color
	score.setOutlineColor(sf::Color::Black); // Set the outline color
	score.setOutlineThickness(0.75); // Set the outline thickness
	//window.setSize(sf::Vector2u(651, 731));
	int ht = 0;
	Time t;
	window.setPosition(sf::Vector2i(350, 10));
	while (1 == window.isOpen())
	{
		while (scene == 0) {
			score.setString(s);
			window.clear();
			window.setSize(sf::Vector2u(651, 731));
			window.setView(sf::View(sf::FloatRect(0.f, 0.f, 651.f, 731.f)));
			while (1 == window.pollEvent(event) && scene == 0) {
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Mouse::Left) {
						int x = sf::Mouse::getPosition(window).x;
						int y = sf::Mouse::getPosition(window).y;
						if (x > 222 && x < 430 && y>275 && y < 330) {
							scene = 1;
							window.setSize(sf::Vector2u(650, 730));
							window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, FONT_HEIGHT + CELL_SIZE * ROWS)));
							window.clear();
							break;
						}
						if (x > 222 && x < 430 && y>478 && y < 530) {
							scene = 2;
							//window.setSize(sf::Vector2u(1600, 1000));
							//window.setView(sf::View(sf::FloatRect(0, 0, 1600, 1000)));

							window.setPosition(sf::Vector2i(0, 0));
							//window.clear();
							return 0;
						}
					}
				}
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				score.setPosition(465, 385);
				window.draw(spriteMenu);
				window.draw(score);
				window.display();
			}
		}
		sf::Event::Closed;
		t = sf::Time::Zero;
		clock.restart();
		while (scene == 1) {
			t = clock.getElapsedTime(); // Get the elapsed time
			int seconds = t.asSeconds();
			//static int t = 0;
			//Here we're calculating the lag
			unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

			lag += delta_time;

			previous_time += std::chrono::microseconds(delta_time);

			//While the lag exceeds the maximum allowed frame duration
			while (FRAME_DURATION <= lag)
			{
				//We get the coordinates of the cell under the cursor
				////unsigned char mouse_cell_x = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).x / static_cast<float>(CELL_SIZE * SCREEN_RESIZE))), 0, COLUMNS - 1);
				////unsigned char mouse_cell_y = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).y / static_cast<float>(CELL_SIZE * SCREEN_RESIZE))), 0, ROWS - 1);
				unsigned char mouse_cell_x = clamp(static_cast<unsigned char>(floor(sf::Mouse::getPosition(window).x / static_cast<float>(CELL_SIZE * SCREEN_RESIZE))), static_cast<unsigned char>(0), static_cast<unsigned char>(COLUMNS - 1));
				unsigned char mouse_cell_y = clamp(static_cast<unsigned char>(floor(sf::Mouse::getPosition(window).y / static_cast<float>(CELL_SIZE * SCREEN_RESIZE))), static_cast<unsigned char>(0), static_cast<unsigned char>(ROWS - 1));

				//We use one of the basic arithmetic operations to perform this complex calculation
				lag -= FRAME_DURATION;

				while (1 == window.pollEvent(event))
				{
					switch (event.type)
					{
						//If the user clicked the close window button
					case sf::Event::Closed:
					{
						//We close the window
						window.close();

						break;
					}
					case sf::Event::KeyReleased:
					{
						switch (event.key.code)
						{
						case sf::Keyboard::Enter:
						{
							//We restart the game if the Enter key was release
							field.restart();
							scene = 0;
							break;
						}
						}

						break;
					}
					case sf::Event::MouseButtonReleased:
					{
						switch (event.mouseButton.button)
						{
							//If the LMB is released
						case sf::Mouse::Left:
						{
							//We open the cell under the cursor
							field.open_cell(mouse_cell_x, mouse_cell_y);

							break;
						}
						//If the RMB is released
						case sf::Mouse::Right:
						{
							//We flag the cell under the cursor
							field.flag_cell(mouse_cell_x, mouse_cell_y);
						}

						}
					}
					}
				}
				//Here we're deciding the state of Alexander's face
				//If any cell is currently pressed
				if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Left) || 1 == sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					//Alexander opens his mouth
					Alexander_state = 1;

					//We also change the mouse state of the cell
					field.set_mouse_state(2, mouse_cell_x, mouse_cell_y);
				}
				//Otherwise
				else
				{
					//Alexander closes his mouth
					Alexander_state = 0;

					field.set_mouse_state(1, mouse_cell_x, mouse_cell_y);
				}

				//If the game is lost
				if (-1 == field.get_game_over())
				{
					//Alexander is disappointed (How could you!)
					Alexander_state = 2;
				}
				//If the game is won
				else if (1 == field.get_game_over())
				{
					//Alexander is proud! (Yeah)
					Alexander_state = 3;
				}

				//Let's draw everything!
				if (FRAME_DURATION > lag)
				{
					//First we clear the window
					window.clear();

					//Then we draw the game field
					field.draw(window);

					//Here we show the text informing the player that he lost or won the game
					if (1 == field.effect_over() && dc.getElapsedTime() >= d)
					{
						ht = seconds;
						if (1 == field.get_game_over())
						{
							draw_text(1, static_cast<unsigned short>(round(0.5f * (CELL_SIZE * COLUMNS - 8 * FONT_WIDTH))), static_cast<unsigned short>(round(0.5f * (CELL_SIZE * ROWS - FONT_HEIGHT))), "VICTORY!", window);
							if (ht < std::stoi(s)) {
								s = std::to_string(ht);
								setScore(s);
							}

						}
						else
						{
							draw_text(1, static_cast<unsigned short>(round(0.5f * (CELL_SIZE * COLUMNS - 4 * FONT_WIDTH))), static_cast<unsigned short>(round(0.5f * (CELL_SIZE * ROWS - 2 * FONT_HEIGHT))), "GAME\nOVER", window);
							//	scene = 0;


						}
					}

					//How many mines are left?
					draw_text(0, 0, CELL_SIZE * ROWS, "Mines:" + std::to_string(MINES - field.get_flags()), window);
					draw_text(0, 65, CELL_SIZE * ROWS, "|Time:" + std::to_string(seconds), window);
					//Sleep(1000);
					//We choose Alexander's face from a texture based on Alexander_state
					Alexander.setTextureRect(sf::IntRect(Alexander_state * Alexander_texture.getSize().y, 0, Alexander_texture.getSize().y, Alexander_texture.getSize().y));

					//We're drawing Alexander on the top of everything because he DESERVES to be at the top!
					window.draw(Alexander);
					//	window.draw(t);
					window.display();
					/*if (scene == 0) {
						window.clear();
						field.restart();
						break;
					}*/
				}
			}
		}
	}
}
int scene = -1, i = 1;
scn2 scene2;
scn3 scene3;
scn4 scene4;
Players  player;
scn9 scene10;
bool first = true;
bool check(string a, string b)
{
	// Open the input files
	ifstream fin("PlayerloginEmail.txt");
	ifstream fn("PlayerloginPassword.txt");

	// Declare variables to hold the email and password
	string email, password;

	// Read a line from each input file
	while (getline(fin, email) && getline(fn, password)) {
		// Check if the lengths of the email and password match the input values
		if (email.length() != a.length() || password.length() != b.length()) {
			continue; // If they don't match, skip to the next line
		}

		// Check if the email matches the input value
		bool match = true;
		for (int i = 0; i < email.length(); i++) {
			if (email[i] != a[i]) {
				match = false;
				break;
			}
		}

		// If the email matches, check if the password matches
		if (match) {
			for (int i = 0; i < password.length(); i++) {
				if (password[i] != b[i]) {
					match = false;
					break;
				}
			}
		}

		// If both the email and password match, return true
		if (match) {
			return true;
		}
	}

	// If no match was found, return false
	return false;
}
bool check1(string a, string b)
{
	ifstream fin("AdminloginEmail.txt");
	ifstream fn("AdminloginPassword.txt");


	string email, password;

	while (getline(fin, email) && getline(fn, password)) {
		if (email.length() != a.length() || password.length() != b.length()) {
			continue; 
		}
bool match = true;
		for (int i = 0; i < email.length(); i++) {
			if (email[i] != a[i]) {
				match = false;
				break;
			}
		}

		// If the email matches, check if the password matches
		if (match) {
			for (int i = 0; i < password.length(); i++) {
				if (password[i] != b[i]) {
					match = false;
					break;
				}
			}
		}

		// If both the email and password match, return true
		if (match) {
			return true;
		}
	}

	// If no match was found, return false
	return false;
}
void login()
{
	RenderWindow window(VideoMode(1600, 950), "Gaming Hub", Style::Titlebar | Style::Close | Style::Resize);
	
	Texture backgroundTexture,loginok, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, error, acct_created, acct_exist, game_start;;
	Texture backgroundTexture1,game_select, start, cash_deposit,admin_details,game2;

	bool flag3;
	Clock clock;
	Time t;
	t = Time::Zero;
	
	game2.loadFromFile("game2start.png");
	Sprite game(game2);
	float scale1 = static_cast<float>(window.getSize().x) / game2.getSize().x;
	float scale2 = static_cast<float>(window.getSize().y) /game2.getSize().y;
	game.setScale(scale1, scale2);


	admin_details.loadFromFile("adminDetails.png");
	cash_deposit.loadFromFile("cash.png");
	game_select.loadFromFile("gameselect.png");
	loginok.loadFromFile("login_success.png");
	game_start.loadFromFile("game_begin.png");
	acct_exist.loadFromFile("account_exists.png");
	acct_created.loadFromFile("account_created.png");
	error.loadFromFile("error.png");
	t11.loadFromFile("100.jpg");
	t10.loadFromFile("1.jpg");
	start.loadFromFile("gamer.jpg");
	backgroundTexture1.loadFromFile("10.jpg");
	backgroundTexture.loadFromFile("Background.jpeg");
	t1.loadFromFile("Login.png");
	t2.loadFromFile("Register.png");
	t3.loadFromFile("Email.png");
	t4.loadFromFile("Password.png");
	t5.loadFromFile("Submit.png");
	t6.loadFromFile("Back.png");
	t7.loadFromFile("ConfirmEmail.png");
	t8.loadFromFile("ConfirmPassword.png");


	Sprite background(backgroundTexture), Error(error), a_created(acct_created), a_exist(acct_exist),a_details(admin_details);
	Sprite login(t1), g_start(game_start),loginOK(loginok), ConfirmPassword(t8), login1(t10);
	Sprite registerr(t2),g_select(game_select), Back(t6), ConfirmEmail(t7), start1(start), register1(t11);
	Sprite Email(t3),cash(cash_deposit), Password(t4), Submit(t5), background1(backgroundTexture1);
	bool s = 0;

	// Calculate scale factors to fit sprite to window
	float scaleX = static_cast<float>(window.getSize().x) / t10.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / t10.getSize().y;
	login1.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / start.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / start.getSize().y;
	start1.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	background.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / backgroundTexture1.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / backgroundTexture1.getSize().y;
	background1.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / t11.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / t11.getSize().y;
	register1.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / error.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / error.getSize().y;
	Error.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / acct_created.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / acct_created.getSize().y;
	a_created.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / acct_exist.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / acct_exist.getSize().y;
	a_exist.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / game_start.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / game_start.getSize().y;
	g_start.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / loginok.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / loginok.getSize().y;
    loginOK.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / cash_deposit.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / cash_deposit.getSize().y;
	cash.setScale(scaleX, scaleY);
	scaleX = static_cast<float>(window.getSize().x) / admin_details.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / admin_details.getSize().y;
	a_details.setScale(scaleX, scaleY);


	Font arial;
	arial.loadFromFile("Arial.ttf");

	RectangleShape textBox_Loginemail(Vector2f(690.f, 44.f));
	textBox_Loginemail.setPosition(405.f, 253.f);
	textBox_Loginemail.setFillColor(Color::White);
	textBox_Loginemail.setOutlineThickness(2.f);
	textBox_Loginemail.setOutlineColor(Color::Black);

	RectangleShape textBox_Loginpassword(Vector2f(631.f, 44.f));
	textBox_Loginpassword.setPosition(464.f, 378.f);
	textBox_Loginpassword.setFillColor(Color::White);
	textBox_Loginpassword.setOutlineThickness(2.f);
	textBox_Loginpassword.setOutlineColor(Color::Black);

	RectangleShape textBox_RegisterEmail(Vector2f(779.f, 44.f));
	textBox_RegisterEmail.setPosition(325.f, 207.f);
	textBox_RegisterEmail.setFillColor(Color::White);
	textBox_RegisterEmail.setOutlineThickness(2.f);
	textBox_RegisterEmail.setOutlineColor(Color::Black);

	RectangleShape textBox_RegisterComfirmEmail(Vector2f(655.f, 44.f));
	textBox_RegisterComfirmEmail.setPosition(453.f, 298.f);
	textBox_RegisterComfirmEmail.setFillColor(Color::White);
	textBox_RegisterComfirmEmail.setOutlineThickness(2.f);
	textBox_RegisterComfirmEmail.setOutlineColor(Color::Black);

	RectangleShape textBox_Registerpassword(Vector2f(722.f, 44.f));
	textBox_Registerpassword.setPosition(384.f, 389.f);
	textBox_Registerpassword.setFillColor(Color::White);
	textBox_Registerpassword.setOutlineThickness(2.f);
	textBox_Registerpassword.setOutlineColor(Color::Black);

	RectangleShape textBox_RegisterComfirmpassword(Vector2f(625.f, 44.f));
	textBox_RegisterComfirmpassword.setPosition(487.f, 481.f);
	textBox_RegisterComfirmpassword.setFillColor(Color::White);
	textBox_RegisterComfirmpassword.setOutlineThickness(2.f);
	textBox_RegisterComfirmpassword.setOutlineColor(Color::Black);


	Textbox textLoginEmail(30, Color::Black, false);
	textLoginEmail.setFont(arial);
	Textbox textLoginPassword(30, Color::Black, false);
	textLoginPassword.setFont(arial);
	Textbox textRegisterEmail(30, Color::Black, false);
	textRegisterEmail.setFont(arial);
	Textbox textRegisterConfirmEmail(30, Color::Black, false);
	textRegisterConfirmEmail.setFont(arial);
	Textbox textRegisterPassword(30, Color::Black, false);
	textRegisterPassword.setFont(arial);
	Textbox textRegisterConfirmPassword(30, Color::Black, false);
	textRegisterConfirmPassword.setFont(arial);
	Textbox textLoginEmail1(30, Color::Black, false);
	textLoginEmail.setFont(arial);
	Textbox textLoginPassword1(30, Color::Black, false);
	textLoginPassword.setFont(arial);
	Textbox cash1(50, Color::Black, false);
	cash1.setFont(arial);


	int seconds = 0;
	Text timeText(to_string(seconds), arial, 50);
	timeText.setFillColor(Color::Blue);
	timeText.setPosition(68, 60);
	timeText.setStyle(Text::Bold);
	RectangleShape textBox3(Vector2f(400.f, 70.f));
	textBox3.setPosition(60.f, 60.f);
	textBox3.setFillColor(Color::White);
	textBox3.setOutlineThickness(2.f);
	textBox3.setOutlineColor(Color::Black);

	Text password(" ", arial, 30);
	password.setFillColor(Color::Black);
	password.setStyle(Text::Bold);

	Text text(" ", arial, 50);
	text.setFillColor(Color::Black);
	text.setPosition(735, 275);
	text.setStyle(Text::Bold);
	Text text1(" ", arial, 50);
	text1.setFillColor(Color::Black);
	text1.setPosition(736, 428);
	text1.setStyle(Text::Bold);
	Text text2(" ", arial, 50);
	text2.setFillColor(Color::Black);
	text2.setPosition(702, 580);
	text2.setStyle(Text::Bold);
	Text text3(" ", arial, 50);
	text3.setFillColor(Color::Black);
	text3.setPosition(738, 733);
	text3.setStyle(Text::Bold);

	Textbox textLoginEmail10(30, Color::Black, false);
	textLoginEmail10.setFont(arial);
	Textbox textLoginPassword10(30, Color::Black, false);
	textLoginPassword10.setFont(arial);


	while (window.isOpen())
	{

		Event e;
		int temp = 0;
		while (window.pollEvent(e))
		{

			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					int x = Mouse::getPosition(window).x;
					int y = Mouse::getPosition(window).y;
					if (scene == -1)
					{
						if (x >= 0 && x <= 1600 && y >= 0 && y <= 960)
						{
							scene = 0;
							goto start;
						}
					}
					if (scene == 0)
					{
						if (x >= 460 && x <= 1170 && y >= 400 && y <= 520)
						{
							scene = 10;
						}
						if (x >= 460 && x <= 1170 && y >= 630 && y <= 750)
						{
							// Player
							scene = 1;
						}
						if (scene != 0)
							goto player;
					}

					if (scene == 1)
					{
						if (x >= 555 && x <= 1045 && y >= 255 && y <= 415)
						{
							
							// LOGIN
							scene = 2;
						}
						if (x >= 555 && x <= 1045 && y >= 530 && y <= 790)
						{
							
							// REGISTER
							scene = 3;
						}
						if (x >= 715 && x <= 829 && y >= 775 && y <= 825)
						{//back
							scene = 0;
						}

					}
					if (scene == 2)
					{
						// back
						if (x >= 705 && x <= 829 && y >= 670 && y <= 740)
						{
							scene = 0;
						}
						if (x >= 245 && x <= 395 && y >= 250 && y <= 300)
						{
							// click on email
							scene2.email = true;
							textLoginEmail.setSelected(true);
						}
						if (x >= 245 && x <= 454 && y >= 345 && y <= 425)
						{
						
							//click on password
							scene2.password = true;
							textLoginPassword.setSelected(true);
						}
						// submit
						if (x >= 625 && x <= 940 && y >= 555 && y <= 630)
						{
							bool valid = false;

							string e, p;
							e = textLoginEmail.getText();
							p = textLoginPassword.getText();
							if (e.empty() == false && p.empty() == false)
							{
								
									if (check(e, p))
									{
								      	valid = true;
										
									}
								
							}
							if (valid)
							{
								scene = 4;
								flag3 = 0;
								goto succeed;
							}
							else
							{
								temp = 2;
								scene = 5;
							}
						}
					}
					if (scene == 3)
					{
						// back
						if (x >= 693 && x <= 827 && y >= 780 && y <= 830)
						{
							scene = 1;
						}
						// email
						if (x >= 165 && x <= 310 && y >= 204 && y <= 254)
						{
							scene3.email = true;
							textRegisterEmail.setSelected(true);
						}
						// confirm email
						if (x >= 165 && x <= 443 && y >= 296 && y <= 346)
						{
							scene3.confirmEmail = true;
							textRegisterConfirmEmail.setSelected(true);
						}
						// password
						if (x >= 165 && x <= 374 && y >= 388 && y <= 438)
						{
							scene3.password = true;
							textRegisterPassword.setSelected(true);
						}
						// confirm password
						if (x >= 165 && x <= 500 && y >= 480 && y <= 530)
						{
							scene3.confirmPassword = true;
							textRegisterConfirmPassword.setSelected(true);
						}
						//submit
						if (x >= 613 && x <= 928 && y >= 645 && y <= 720)
						{
							string e, ce, p, cp;
							e = textRegisterEmail.getText();
							ce = textRegisterConfirmEmail.getText();
							p = textRegisterPassword.getText();
							cp = textRegisterConfirmPassword.getText();
							if (e.empty() == false && ce.empty() == false && p.empty() == false && cp.empty() == false)
							{
								if (e == ce && p == cp)
								{
									if (!check(e, p)) {
										ofstream fout("PlayerloginEmail.txt", ios::app);
										fout << endl << e;
										fout.close();
										ofstream fw("PlayerloginPassword.txt", ios::app);
										fw << endl << p;
										fw.close();
										ifstream f1("peopleRegister.txt");
										int num;
										f1 >> num;
										num++;
										f1.close();
										ofstream f2("peopleRegister.txt");
										f2 << num;
										f2.close();
										scene = 8; goto a_acct;
									}
									else
										scene = 9;
								}

							}

						}
					}//loginok
					if (scene == 4) {
						if (x >= 640 && x <= 920 && y >= 720 && y <= 840)
						{
						
							if (flag3) {
								scene = 15; goto a100;
							}
							else
							{
								scene = 14;
								x = 0, y = 0; goto g_start;
							}

						}


					}//error
					if (scene == 5)
					{
						if (x >= 530 && x <= 810 && y >= 690 && y <= 795)
						{
							
							scene = 2;
						}


					}
					//error
					if (scene == 6) {
						if (x >= 530 && x <= 810 && y >= 690 && y <= 795)
						{
							scene = 10;
						}



					}//account created
					if (scene == 8) {
						if (x >= 740 && x <= 1030 && y >= 735 && y <= 830)
						{
						
							scene = 1;
							x = 0, y = 0;
						}

					}
					//account exists
					if (scene == 9)
					{
						if (x >= 630 && x <= 900 && y >= 670 && y <= 800)
						{

							scene = 3;
							x = 0; y = 0;
							goto a;
						}
					}	if (scene == 15) {
							if (Keyboard::isKeyPressed(Keyboard::Enter))
							{
								scene = 1;
							}
						}

					//game start
					if (scene == 12)
					{
						clock.restart();
						if (x >= 0 && x <= 1600 && y >= 0 && y <= 960)
						{
							scene = 11; goto g_select1;
						}
					}
					//cash
					if (scene == 14) {

						if (x >= 260 && x <= 950 && y >= 400 && y <= 540)
						{
							scene4.cash = true;
							cash1.setSelected(true);
						}
						if (x >= 550 && x <= 900 && y >= 600 && y <= 700)
						{
							string e = cash1.getText();
							if (e.empty() == false)
							{
								scene = 12;

								int num2 = stringToInt((cash1.getText())) * 500;
								ifstream f10("earning.txt");
								int temp;
								f10 >> temp;
								num2 += temp;
								f10.close();
								ofstream f1("earning.txt");
								
								f1 << num2;
								f1.close();

							}
						}
						}
						if (x >= 550 && x <= 900 && y >= 745 && y <= 845)
						{
								scene = 2;
						

					}
					//gameselect
					bool flag = 0;
					if (scene == 11) {
						t = clock.getElapsedTime();

						int t1 = t.asSeconds();
						if (t1 > stringToInt((cash1.getText())) * 60) {
							scene = 14;
						}
						if (x >= 570 && x <= 1180 && y >= 345 && y <= 465)
						{
							scene = 13; flag = 1;
						}
						if (x >= 570 && x <= 1180 && y >= 615 && y <= 730)
						{
							scene = 17;
						}
						if (x >= 700 && x <= 940 && y >= 830 && y <= 900)
						{
							scene = 14;

						}
						

					}//game1
					if (scene == 13 && flag) {
						game1(window);

						window.setSize(sf::Vector2u(1600, 1000));
						window.setView(sf::View(sf::FloatRect(0, 0, 1600, 950)));
						window.setPosition(sf::Vector2i(112, 20));
						scene = 11;

					}//game2
					if (scene == 17) {

						if (x >= 965 && x <= 1350 && y >= 255 && y <= 360)
						{
							game3(window);
							window.setSize(sf::Vector2u(1600, 1000));
							window.setView(sf::View(sf::FloatRect(0, 0, 1600, 950)));
							window.setPosition(sf::Vector2i(112, 20));

						}
						if (x >= 1140 && x <= 1340 && y >= 760 && y <= 860)
						{
							scene = 11; goto g_select1;
						}

					}



					if (scene == 10)
					{
						// back
						if (x >= 715 && x <= 829 && y >= 680 && y <= 730)
						{
							scene = 0;
						}
						if (x >= 245 && x <= 395 && y >= 250 && y <= 300)
						{
							// click on email
							scene10.email = true;
							textLoginEmail10.setSelected(true);
						}
						if (x >= 245 && x <= 454 && y >= 375 && y <= 425)
						{
							//click on password
							scene10.password = true;
							textLoginPassword10.setSelected(true);
						}
						// submit
						if (x >= 625 && x <= 940 && y >= 555 && y <= 630)
						{

							bool valid = false;
							string e, p;
							e = textLoginEmail10.getText();
							p = textLoginPassword10.getText();
							if (e.empty() == false && p.empty() == false)
							{
								
									if (check1(e, p))
									{
										valid = true;
									
									}
								
							}
							if (valid)
							{
								scene = 4;
								flag3 = 1;
								goto succeed;
							}
							else
							{
								temp = 2;
								scene = 6;
								goto error1;
							}

						}
					}


				}
			}
			if (e.type == Event::TextEntered)
			{
				if (scene == 10)
				{
					if (scene10.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginEmail10.setSelected(false);
							scene10.email = false;
						}
						else
						{
							textLoginEmail10.typedOn(e);
						}
					}
					else if (scene10.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginPassword10.setSelected(false);
							scene10.password = false;
						}
						else
						{
							textLoginPassword10.typedOn(e);
						}
					}
				}
				if (scene == 2)
				{
					if (scene2.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginEmail.setSelected(false);
							scene2.email = false;
						}
						else
						{
							textLoginEmail.typedOn(e);
						}
					}
					else if (scene2.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginPassword.setSelected(false);
							scene2.password = false;
						}
						else
						{
							textLoginPassword.typedOn(e);
						}
					}
				}
				if (scene == 14)
				{
					if (scene4.cash == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							cash1.setSelected(false);
							scene4.cash = false;
						}
						else
						{
							cash1.typedOn(e);
						}
					}
				}

				if (scene == 3)
				{
					if (scene3.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterEmail.setSelected(false);
							scene3.email = false;
						}
						else
						{
							textRegisterEmail.typedOn(e);
						}
					}
					else if (scene3.confirmEmail == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterConfirmEmail.setSelected(false);
							scene3.confirmEmail = false;
						}
						else
						{
							textRegisterConfirmEmail.typedOn(e);
						}
					}
					else if (scene3.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterPassword.setSelected(false);
							scene3.password = false;
						}
						else
						{
							textRegisterPassword.typedOn(e);
						}
					}
					else if (scene3.confirmPassword == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterConfirmPassword.setSelected(false);
							scene3.confirmPassword = false;
						}
						else
						{
							textRegisterConfirmPassword.typedOn(e);
						}
					}
				}
			}
		}
		window.clear(Color(280, 130, 100));
		if (scene == -1)
		{
			window.draw(start1);


		}
		if (scene == 0)
		{
		start:
			window.draw(background1);
		}

		if (scene == 1)
		{
		player:
			window.draw(background);
			login.setPosition(555, 255);
			window.draw(login);
			registerr.setPosition(555, 530);
			window.draw(registerr);
			Back.setPosition(705, 780);
			window.draw(Back);

		}
		if (scene == 2)
		{
			window.draw(login1);
			window.draw(textBox_Loginemail);
			window.draw(textBox_Loginpassword);
			Submit.setPosition(625, 555);
			window.draw(Submit);
			Password.setPosition(245, 375);
			window.draw(Password);
			Email.setPosition(245, 250);
			window.draw(Email);
			Back.setPosition(715, 680);
			window.draw(Back);
			textLoginEmail.setPosition({ 410,256 });
			textLoginEmail.drawTo(window);
			textLoginPassword.setPosition({ 469,379 });
		textLoginPassword.drawTo(window);
		}
		if (scene == 10)
		{
			window.draw(login1);
			window.draw(textBox_Loginemail);
			window.draw(textBox_Loginpassword);
			Submit.setPosition(625, 555);
			window.draw(Submit);
			Password.setPosition(245, 375);
			window.draw(Password);
			Email.setPosition(245, 250);
			window.draw(Email);
			Back.setPosition(715, 680);
			window.draw(Back);
			textLoginEmail10.setPosition({ 410,256 });
			textLoginEmail10.drawTo(window);
			textLoginPassword10.setPosition({ 469,379 });
			textLoginPassword10.drawTo(window);
		}
		a:
		if (scene == 3)
		{
			window.draw(register1);
			window.draw(textBox_RegisterEmail);
			window.draw(textBox_RegisterComfirmEmail);
			window.draw(textBox_RegisterComfirmpassword);
			window.draw(textBox_Registerpassword);
			Submit.setPosition(613, 645);
			window.draw(Submit);
			Back.setPosition(693, 780);
			window.draw(Back);
			Email.setPosition(165, 204);
			window.draw(Email);
			ConfirmEmail.setPosition(165, 296);
			window.draw(ConfirmEmail);
			Password.setPosition(165, 388);
			window.draw(Password);
			ConfirmPassword.setPosition(165, 480);
			window.draw(ConfirmPassword);
			textRegisterEmail.setPosition({ 330, 207 });
			textRegisterEmail.drawTo(window);
			textRegisterConfirmEmail.setPosition({ 458,297 });
			textRegisterConfirmEmail.drawTo(window);
			textRegisterPassword.setPosition({ 389,392 });
			textRegisterPassword.drawTo(window);
			textRegisterConfirmPassword.setPosition({ 494,485 });
			textRegisterConfirmPassword.drawTo(window);

		}
		if (scene == 4)
		{
		succeed:
			window.draw(loginOK);
		}
		if (scene == 5)
		{
		error:
			window.draw(Error);
		
		}

		if (scene == 6)
		{
		error1:
			window.draw(Error);
		}
	a_acct:
		if (scene == 8) {
			window.draw(a_created);
		}
		if (scene == 9) {
			window.draw(a_exist);
		}
	g_start:
		if (scene == 12)
		{
			window.draw(g_start);
		}
	g_select1:
		if (scene == 11)
		{
			t = clock.getElapsedTime(); // Get the elapsed time
			seconds = t.asSeconds();
			timeText.setString("Seconds: "+to_string(seconds));

	window.draw(g_select);
	window.draw(textBox3);
	window.draw(timeText);

		}
		if (scene == 14) {
			window.draw(cash);
			cash1.setPosition({ 1020,430 });
			cash1.drawTo(window);
		}
		if (scene == 17) {
			window.draw(game);
		}
		a100:
		if (scene == 15) {
			window.draw(a_details);
			int num,num1,num2,num3;
			ifstream i("peopleRegister.txt");
			i >> num;
			text.setString(to_string(num));
			window.draw(text);
			ifstream j("login.txt");
			j >> num1;
			text1.setString(to_string(num1));
			window.draw(text1);
			
				ifstream f10("earning.txt");
				f10 >> num2;
				f10.close();

			ifstream l("loss.txt");
			l >> num3;
			text3.setString(to_string(num3));
			window.draw(text3);
			text2.setString(to_string(num2));
			window.draw(text2);

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				scene = 0;
			}

		}
	
		window.display();
	}
}
int main()
{
	login();
	return 0;
}