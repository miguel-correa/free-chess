#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Draws the chess board on the screen
void DrawBoard(sf::RenderWindow &window)
{
    sf::RectangleShape square(sf::Vector2f(75, 75));

    for (int ranks = 0; ranks < 8; ranks++)
    {
        for (int files = 0; files < 8; files++)
        {
            square.setPosition(sf::Vector2f(75 * ranks, 75 * files));
            if ((ranks + files) % 2 == 0)
                square.setFillColor(sf::Color(222, 227, 230));
            else
                square.setFillColor(sf::Color(140, 162, 173));
            window.draw(square);
        }
    }
}

// Draws the pieces on the chess board
void DrawPieces(sf::RenderWindow &window)
{

}

// This function changes the color of the active square
sf::RectangleShape DrawSelectedSquare(sf::RenderWindow &window, sf::Event event)
{
    int rank = event.mouseButton.x / 75;
    int file = event.mouseButton.y / 75;

    sf::RectangleShape selected_square(sf::Vector2f(75, 75));
    selected_square.setPosition(sf::Vector2f(rank * 75, file * 75));
    selected_square.setFillColor(sf::Color(0, 153, 51, 80));
    
    return selected_square;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Chess");

    std::vector<std::vector<sf::RectangleShape>> squares;
    sf::RectangleShape selected_square;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close window" event
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
                selected_square = DrawSelectedSquare(window, event);
        }

        window.clear(sf::Color::Black);

        // Drawing loop
        DrawBoard(window);
        window.draw(selected_square);
        DrawPieces(window);

        window.display();
    }
}