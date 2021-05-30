#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

void events();

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

sf::Vector2f normalize(sf::Vector2f& oldVector)
{
    auto length = std::sqrt(oldVector.x * oldVector.x + oldVector.y * oldVector.y);
    sf::Vector2f newVector = {oldVector.x/length, oldVector.y/length};
    if(length!=0)
        return newVector;
    else return oldVector;
}

sf::Vector2f multiply(sf::Vector2f& oldVector, float scalar)
{
    sf::Vector2f newVector = { oldVector.x * scalar, oldVector.y * scalar };
    return newVector;
}





class Mover: public sf::CircleShape
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    int r;
    float mass;
    sf::Text text;
    sf::Font font; // font must be kept as a field
public:
    Mover() {
        position = {std::rand() %800, 200.f};
        velocity = {0.f, 0.f};
        acceleration = {0.f, 0.f};
        this->setPosition(position);
        r = 30;
        this->setRadius(r);
        this->setOrigin(r,r); //set circle origin to its centre
        mass = 10  + std::rand() % 1000;
        if(mass < 333)  setFillColor(sf::Color::Red);
        else if(mass >= 333 && mass < 666) setFillColor(sf::Color::Magenta);
        else if(mass >= 666 && mass <= 1010) setFillColor(sf::Color::Blue);

        if (!font.loadFromFile("D:/Qt_workspace/SFMLTrain2/arial.ttf")){
            std::cerr << ".Error while loading font" << std::endl;
        }

        text.setString(std::to_string(int(mass)));
        text.setCharacterSize(20);
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::White);
    }

    void applyForce(sf::Vector2f force)
    {
        acceleration += force/mass;
    }

    void update()
    {
        velocity += acceleration;
        position += velocity;
        edges();
        this->setPosition(position);
        acceleration = {0.f,0.f};

        text.setFont(font); //font must be set each time here
        text.setPosition(getPosition().x-r+10, getPosition().y-r+10);
    }

    void draw()
    {

        window.draw(*this);
        window.draw(text);
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

    int getMass(){return mass;}
    sf::Vector2f getVelocity(){return velocity;}
};

void updateMovers(std::vector<Mover>& v_movers)
{
    for (int i = 0; i < v_movers.size(); ++i) {
        sf::Vector2f gravity ={0.f,1.f};
        sf::Vector2f gravityTimesMass = {gravity.x, gravity.y * v_movers[i].getMass()};
        v_movers[i].applyForce(gravityTimesMass);

        sf::Vector2f wind ={5.f,0.f};
        v_movers[i].applyForce(wind);

        sf::Vector2f friction = v_movers[i].getVelocity();
        friction = normalize(friction);
        float frictionCoefficient = -2.1;
        friction = multiply(friction, frictionCoefficient);
        v_movers[i].applyForce(friction);


        v_movers[i].update();
    }
}

int main()
{
    std::srand(std::time(nullptr));

    window.setFramerateLimit(30);

    std::vector<Mover> v_movers;

    for (int i = 0; i < 5; ++i) {
        v_movers.push_back(Mover());
    }

    while (window.isOpen())
    {
        events();
        updateMovers(v_movers);

        window.clear();
        for (int i = 0; i < v_movers.size(); ++i) {
            v_movers[i].draw();
        }

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
