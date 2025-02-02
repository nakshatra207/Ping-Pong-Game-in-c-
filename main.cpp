#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_SPEED = 0.2f;
const float BALL_SPEED = 0.15f;

int main() {
    // Create the game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong Game");

    // Create paddles
    sf::RectangleShape leftPaddle(sf::Vector2f(20, 100));
    leftPaddle.setPosition(50, WINDOW_HEIGHT / 2 - 50);
    leftPaddle.setFillColor(sf::Color::White);

    sf::RectangleShape rightPaddle(sf::Vector2f(20, 100));
    rightPaddle.setPosition(WINDOW_WIDTH - 70, WINDOW_HEIGHT / 2 - 50);
    rightPaddle.setFillColor(sf::Color::White);

    // Create ball
    sf::CircleShape ball(10);
    ball.setPosition(WINDOW_WIDTH / 2 - 10, WINDOW_HEIGHT / 2 - 10);
    ball.setFillColor(sf::Color::White);

    // Ball direction
    float ballDX = BALL_SPEED;
    float ballDY = BALL_SPEED;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0) {
            leftPaddle.move(0, -PADDLE_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + leftPaddle.getSize().y < WINDOW_HEIGHT) {
            leftPaddle.move(0, PADDLE_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0) {
            rightPaddle.move(0, -PADDLE_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + rightPaddle.getSize().y < WINDOW_HEIGHT) {
            rightPaddle.move(0, PADDLE_SPEED);
        }

        // Move ball
        ball.move(ballDX, ballDY);

        // Ball collision with top and bottom walls
        if (ball.getPosition().y <= 0 || ball.getPosition().y + 20 >= WINDOW_HEIGHT) {
            ballDY = -ballDY;
        }

        // Ball collision with paddles
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballDX = -ballDX;
        }

        // Ball out of bounds (left or right)
        if (ball.getPosition().x <= 0 || ball.getPosition().x + 20 >= WINDOW_WIDTH) {
            ball.setPosition(WINDOW_WIDTH / 2 - 10, WINDOW_HEIGHT / 2 - 10);
        }

        // Clear the window
        window.clear();

        // Draw paddles and ball
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);

        // Display the window
        window.display();
    }

    return 0;
}
