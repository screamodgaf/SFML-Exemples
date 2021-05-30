#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
void events();

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

//sf::Vector2f normalize(sf::Vector2f& oldVector)
//{
//    auto length = std::sqrt(oldVector.x * oldVector.x + oldVector.y * oldVector.y);
//    sf::Vector2f newVector = {oldVector.x/length, oldVector.y/length};
//    if(length!=0)
//        return newVector;
//    else return oldVector;
//}

//sf::Vector2f multiply(sf::Vector2f& oldVector, float scalar)
//{
//    sf::Vector2f newVector = { oldVector.x * scalar, oldVector.y * scalar };
//    return newVector;
//}




class Mover: public sf::CircleShape
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float r;
    sf::Vector2i newPos;

public:
    Mover() {
        position = {200.f, 200.f};
        velocity = {0.f, 0.f};
        acceleration = {0.f, 0.f};
        this->setPosition(position);
        r = 20.f;
        this->setRadius(r);
        this->setOrigin(r,r); //set circle origin to its centre
    }

    void applyForce(sf::Vector2f force)
    {
        acceleration += force;
    }

    void update()
    {
        std::cout << "velocity.y: " << velocity.y << " velocity.x: " << velocity.x  << "\n";
        velocity += acceleration;
        position += velocity;

//        if(std::fabs(velocity.x * velocity.x + velocity.y * velocity.y) < 0.01f)
//        {
//            velocity.x = 0.f;
//            velocity.y = 0.f;
//        }

        std::cout << "position + r: " << position.x + r << " velocity: " <<  velocity.x  << "\n";

        edges();
        this->setPosition(position);
        acceleration = {0.f,0.f};
    }

    void draw()
    {
        window.draw(*this);
    }

    void edges()
    {
        //we're applying force each frame, so the movement sould be ad infinitum

        if(position.y + r > 600){  //if it was >= in each of the conditions, the ball would stop moving eventually - decreasing velocity
            velocity.y *= -1;
            position.y = 600 - r;
        }
        else if(position.y - r < 0){ //no need to use <= cause "position.y = 0 + r;" would cause that setting it to equal position.y = 0 + r
            velocity.y *= -1;
            position.y = 0 + r;
        }

        if(position.x + r > 800){
            velocity.x *= -1;
            position.x = 800 - r;
        }
        else if(position.x - r < 0){
            velocity.x *= -1;
            position.x = 0 + r;
        }
    }
};

int main()
{
    window.setFramerateLimit(30);
    Mover mover;

    while (window.isOpen())
    {
        events();

        sf::Vector2f gravity ={0.f,1.f};
        mover.applyForce(gravity);

        sf::Vector2f wind ={2.f,0.f};
        mover.applyForce(wind);

        mover.update();


        window.clear();
        mover.draw();
        window.display();
    }
    return 0;
}


void events()
{
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
    }
}
