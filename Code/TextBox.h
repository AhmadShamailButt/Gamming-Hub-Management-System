#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
class TextBox1
{
public:
	TextBox1(sf::Vector2f size, sf::Font& font)
	{
		m_box.setSize(size);
		m_box.setFillColor(sf::Color::White);
		m_box.setOutlineThickness(2.f);
		m_box.setOutlineColor(sf::Color::Black);

		m_text.setFont(font);
		m_text.setCharacterSize(30);
		m_text.setFillColor(sf::Color::Black);

		m_cursor.setSize(sf::Vector2f(2.f, 20.f));
		m_cursor.setFillColor(sf::Color::Black);
		m_cursor.setPosition(5.f, 5.f);
	}

	void setPosition(sf::Vector2f position)
	{
		m_box.setPosition(position);
		m_text.setPosition(position.x + 5.f, position.y + 5.f);
	}

	void handleEvent(sf::Event event)
	{
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b') {
				// backspace
				if (!m_input.empty()) {
					m_input.pop_back();
					m_text.setString(m_input);
				}
			}
			else if (event.text.unicode < 128) {
				// regular character
				m_input += static_cast<char>(event.text.unicode);
				m_text.setString(m_input);
			}
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_box, states);
		target.draw(m_text, states);
		if (m_showCursor) {
			target.draw(m_cursor, states);
		}
	}

	const std::vector<std::string>& getValues() 
	{
		m_values.clear();
		m_values.push_back(m_input);
		return m_values;
	}
	bool empty() {
      if (m_values.empty())
			return 0;
		return 1;
	}
private:
	sf::RectangleShape m_box;
	sf::Text m_text;
	std::string m_input;
	std::vector<std::string> m_values;
	bool m_showCursor = true;
	sf::RectangleShape m_cursor;
};
class Textbox {
public:
	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;

		// Check if the textbox is selected upon creation and display it accordingly:
		if (isSelected)
			textbox.setString("_");
		else
			textbox.setString("");
	}

	// Make sure font is passed by reference:
	void setFont(sf::Font& fonts) {
		textbox.setFont(fonts);
	}

	void setPosition(sf::Vector2f point) {
		textbox.setPosition(point);
	}

	// Set char limits:
	void setLimit(bool ToF) {
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim - 1;
	}

	// Change selected state:
	void setSelected(bool sel) {
		isSelected = sel;

		// If not selected, remove the '_' at the end:
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(textbox);
	}

	// Function for event loop:
	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;

			// Only allow normal inputs:
			if (charTyped < 128) {
				if (hasLimit) {
					// If there's a limit, don't go over it:
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					// But allow for char deletions:
					else if (text.str().length() > limit&& charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				// If no limit exists, just run the function:
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
private:
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	// Delete the last character of the text:
	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_");
	}

	// Get user input:
	void inputLogic(int charTyped) {
		// If the key pressed isn't delete, or the two selection keys, then append the text with the char:
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			text << static_cast<char>(charTyped);
		}
		// If the key is delete, then delete the char:
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		// Set the textbox text:
		textbox.setString(text.str() + "_");
	}
};
