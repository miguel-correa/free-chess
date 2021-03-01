#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <experimental/filesystem>
#include <iostream>
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

// Creates a sprite for the input piece
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
            if(board[file][rank] != "-")
            {
                sf::Sprite piece = NewSprite(board[file][rank]);
                piece.setPosition(rank * 75, file * 75);
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

// Returns a sprite of the selected piece at the event position
sf::Sprite MovePiece(std::string selected_piece, sf::Event event)
{
    sf::Sprite piece = NewSprite(selected_piece);
    if(event.type == sf::Event::MouseButtonPressed)
        piece.setPosition(event.mouseButton.x - 75/2, event.mouseButton.y - 75/2);
    else
        piece.setPosition(event.mouseMove.x - 75/2, event.mouseMove.y - 75/2);

    return piece;
}

int main()
{
    LoadTextures();
    GameState game_state;
    std::vector<std::vector<std::string>> curr_state;

    sf::RenderWindow window(sf::VideoMode(600, 600), "Chess", sf::Style::Close);

    std::vector<std::vector<sf::RectangleShape>> squares;
    sf::RectangleShape selected_square;

    std::string selected_piece;
    sf::Sprite dragged_piece;

    bool isPressed = false;

    while (window.isOpen())
    {
        curr_state = game_state.GetGameState();
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close window" event
            if (event.type == sf::Event::Closed)
                window.close();

            // When the mouse button is released, updates the new piece position and
            // selects the square
            // TODO: only select the square if it's the same square that the mouse was pressed down
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if (isPressed) {
                    isPressed = false;
                    game_state.ChangeSquare(event.mouseButton.x / 75, event.mouseButton.y / 75, selected_piece);
                }

                selected_square = DrawSelectedSquare(window, event);
            }


            // If the left mouse button is pressed, removes the piece from the square
            // and creates a sprite at the mouse location
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                isPressed = true;
                selected_piece = curr_state[event.mouseButton.y / 75][event.mouseButton.x / 75];
                game_state.ChangeSquare(event.mouseButton.x / 75, event.mouseButton.y / 75, "-");
                dragged_piece = MovePiece(selected_piece, event);
            }

            // If the mouse is moving and the left button is down update the piece position
            // to the mouse location
            if (event.type == sf::Event::MouseMoved && isPressed)
                if(isPressed)
                    dragged_piece = MovePiece(selected_piece, event);
        }

        window.clear(sf::Color::Black);

        // Drawing loop
        DrawBoard(window);
        window.draw(selected_square);
        DrawPieces(window, curr_state);

        // If the left button is still pressed, draw the dragged piece at the mouse location
        if(isPressed)
            window.draw(dragged_piece);

        window.display();
    }
}