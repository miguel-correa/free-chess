#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <experimental/filesystem>
#include "GameState.h"


std::map<std::string, sf::Texture> PIECES;

// Loads the pieces textures in a very stupid way
void LoadTextures()
{
    std::experimental::filesystem::path path, aux;
    path = aux = std::experimental::filesystem::current_path().parent_path().concat("/data");

    PIECES["br"].loadFromFile(path.concat("/br.png"));
    path = aux;
    PIECES["bn"].loadFromFile(path.concat("/bn.png"));
    path = aux;
    PIECES["bb"].loadFromFile(path.concat("/bb.png"));
    path = aux;
    PIECES["bq"].loadFromFile(path.concat("/bq.png"));
    path = aux;
    PIECES["bk"].loadFromFile(path.concat("/bk.png"));
    path = aux;
    PIECES["bp"].loadFromFile(path.concat("/bp.png"));
    path = aux;
    PIECES["wr"].loadFromFile(path.concat("/wr.png"));
    path = aux;
    PIECES["wn"].loadFromFile(path.concat("/wn.png"));
    path = aux;
    PIECES["wb"].loadFromFile(path.concat("/wb.png"));
    path = aux;
    PIECES["wq"].loadFromFile(path.concat("/wq.png"));
    path = aux;
    PIECES["wk"].loadFromFile(path.concat("/wk.png"));
    path = aux;
    PIECES["wp"].loadFromFile(path.concat("/wp.png"));
}

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

// Creates a sprite for a piece found on the board
sf::Sprite NewSprite(std::string piece_name)
{
    sf::Sprite piece;

    if(!PIECES[piece_name].isSmooth())
        PIECES[piece_name].setSmooth(true);
    piece.setTexture(PIECES[piece_name]);
    piece.setScale(75 / piece.getLocalBounds().height, 75 / piece.getLocalBounds().width);

    return piece;
}

// Draws the pieces on the chess board
// BUG: Files and ranks are reversed
void DrawPieces(sf::RenderWindow &window, std::vector<std::vector<std::string>> board)
{
    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            if(board[rank][file] != "-")
            {
                sf::Sprite piece = NewSprite(board[rank][file]);
                piece.setPosition(file * 75, rank * 75);
                window.draw(piece);
            }
        }
    }
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
    LoadTextures();
    GameState game_state;
    std::vector<std::vector<std::string>> curr_state = game_state.GetGameState();
    sf::Sprite sprite;
    sprite = NewSprite("wk");
    sf::RenderWindow window(sf::VideoMode(600, 600), "Chess", sf::Style::Close);

    std::vector<std::vector<sf::RectangleShape>> squares;
    sf::RectangleShape selected_square;
    while (window.isOpen())
    {
        sf::Event event{};
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
//        window.draw(sprite);
        DrawPieces(window, curr_state);

        window.display();
    }
}