#include "game.h"

int numGame = 0;

float distance(float x0, float y0, float x1, float y1){
    return sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
}

void setView(float x, float y) {
    if (x < WIDTH_WINDOW / 2) x = WIDTH_WINDOW / 2;
    if (y < HEIGHT_WINDOW / 2) y = HEIGHT_WINDOW / 2;
    if (y > HEIGHT_WINDOW / 2) y = HEIGHT_WINDOW / 2;
    view.setCenter(x, y);
}

void showMenu(RenderWindow& window){
    Image back_image; back_image.loadFromFile("graphic/i.jpeg");
    Texture back_t; back_t.loadFromImage(back_image);
    Sprite back_s; back_s.setTexture(back_t);

    Image about_image; about_image.loadFromFile("graphic/about.jpg");
    Texture about_t; about_t.loadFromImage(about_image);
    Sprite about_s; about_s.setTexture(about_t);
    about_s.setScale(0.48, 0.52);

    Font font;
    font.loadFromFile("graphic/font.otf");
    Text menu0("Start", font, 70);
    Text menu1("About game", font, 70);
    Text menu2("Quit", font, 70);
    menu0.setColor(Color::White);
    menu1.setColor(Color::White);
    menu2.setColor(Color::White);
    menu0.setPosition(view.getCenter().x - 150, view.getCenter().y - 120);
    menu1.setPosition(view.getCenter().x - 150, view.getCenter().y - 60);
    menu2.setPosition(view.getCenter().x - 150, view.getCenter().y);
    bool isMenu = true;
    int menuNum = 0;
    while (isMenu) {
        window.draw(back_s);
        window.draw(menu0);
        window.draw(menu1);
        window.draw(menu2);
        window.display();

        Event event;
        if (window.pollEvent(event)) {
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Down)) {
                menuNum += 1;
                if (menuNum > 2) {menuNum = 0;}
            }
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Up)) {
                menuNum -= 1;
                if (menuNum < 0) {menuNum = 2;}
            }
        }

        if (menuNum == 0) {
            menu0.setColor(Color::Red);
            menu1.setColor(Color::White);
            menu2.setColor(Color::White);
        }
        if (menuNum == 1) {
            menu1.setColor(Color::Red);
            menu0.setColor(Color::White);
            menu2.setColor(Color::White);
        }
        if (menuNum == 2)  {
            menu2.setColor(Color::Red);
            menu1.setColor(Color::White);
            menu0.setColor(Color::White);
        }

        if (menuNum == 0 && Keyboard::isKeyPressed(Keyboard::Return)) {
            isMenu = false;
        }
        if (menuNum == 1 && Keyboard::isKeyPressed(Keyboard::Return)) {
            while (!Keyboard::isKeyPressed(Keyboard::Escape)){
                window.draw(about_s);
                window.display();
            };
        }
        if (menuNum == 2 && Keyboard::isKeyPressed(Keyboard::Return)) {
            window.close();
            isMenu = false;
        }
    }
}

void showResults(RenderWindow& window, int finalScore) {
    Font font;
    font.loadFromFile("graphic/font.otf");
    Text text1("You lose!", font,40);
    Text text2("", font, 30);
    Text text3("Press Enter to restart", font, 30);
    Text text4("Goodbye!", font, 50);
    text1.setColor(Color::White);
    text2.setColor(Color(10,170, 170));
    text3.setColor(Color::White);
    text4.setColor(Color(10,170, 170));
    ostringstream endScore;
    endScore << finalScore;
    text1.setPosition(view.getCenter().x - 105, view.getCenter().y - 60);
    text2.setString("Your score: " + endScore.str());
    text2.setPosition(view.getCenter().x - 110, view.getCenter().y - 10);
    text3.setPosition(view.getCenter().x - 145, view.getCenter().y + 40);
    text4.setPosition(view.getCenter().x - 105, view.getCenter().y - 60);
    window.clear(Color(0, 0, 0));
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);

    if(Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::N)) {
        window.close();
    }
    if(Keyboard::isKeyPressed(Keyboard::Return) || Keyboard::isKeyPressed(Keyboard::Y)) {
        window.close();
        gameStart();
    }
}

void gameStart() {
    RenderWindow window(VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Quantum race");
    window.setVerticalSyncEnabled(true);
    view.reset(FloatRect(0, 0, WIDTH_WINDOW, HEIGHT_WINDOW));

    if(numGame == 0){
        showMenu(window);
        numGame += 1;
    }
    spaceCraft ship;
    coord cc = ship.getPosition();

    Image ship_image; ship_image.loadFromFile("graphic/rocket2.png");
    Texture ship_t; ship_t.loadFromImage(ship_image);
    Sprite ship_s; ship_s.setTexture(ship_t);
    ship_s.setScale(0.10, 0.10);
    ship_s.setOrigin(400, 400);
    ship_s.setPosition(cc.x, cc.y);

    CircleShape spaceArea(ship.radius);
    spaceArea.setFillColor(Color(40, 0, 40, 140));
    spaceArea.setOutlineThickness(5);
    spaceArea.setOutlineColor(Color(160, 0, 175));
    spaceArea.setOrigin(ship.radius, ship.radius);
    spaceArea.setPosition(cc.x, cc.y);

    srand(time(0));
    int stepCreateFig = 1;
    int stepCreateTablets = 1;
    float x, y;
    int typeFig, typeTabl;
    float realCenterX, realCenterY;
    const int numberFigure = 6;
    const int numberTablets = 4;

    AbstractFigure creator;
    Shape** arrShape = new Shape*[numberFigure];
    float arrRadius[numberFigure];
    bool isDestroy[numberFigure];
    for(int i = 0; i < numberFigure; i++) {
        x = 700 + 200 * i + rand() % 100;
        y = rand() % 500;
        typeFig = 1 + rand() % 5;
        arrShape[i] = creator.getFigure(typeFig, x, y);
        arrRadius[i] = creator.getRadius();
        isDestroy[i] = false;
    }

    CircleShape** arrTablets = new CircleShape*[numberTablets];
    bool isEaten[numberTablets];
    int typeT[numberTablets];
    for(int i = 0; i < numberTablets; i++) {
        x = 700 + 400 * i + rand() % 100;
        y = rand() % 500;
        typeTabl = 1 + rand() % 4;
        arrTablets[i] = creator.getBonus(typeTabl, x, y);
        isEaten[i] = false;
        typeT[i] = typeTabl;
    };

    Image map_image; map_image.loadFromFile("graphic/space.jpg");
    Texture map_t; map_t.loadFromImage(map_image);
    Sprite map_s1; map_s1.setTexture(map_t);
    map_s1.setScale(1.1, 1.4);
    Sprite map_s2; map_s2.setTexture(map_t);
    map_s2.setScale(1.1, 1.4);
    map_s1.setPosition(0, 0);
    map_s2.setPosition(SIZE, 0);
    int background_1 = 0;
    int background_2 = SIZE;

    Font font;
    font.loadFromFile("graphic/font.otf");
    Text text("", font, 30);
    text.setColor(Color::Red);
    text.setStyle(Text::Bold);

    Text text2("You lose!", font, 40);
    Text text3("", font, 30);
    text2.setColor(Color::White);
    text3.setColor(Color(10, 170, 170));

    coord c, d;
    int v, ccc = 1;
    int iter = 0;

    Image vel_image; vel_image.loadFromFile("graphic/1.png");
    Texture vel_t; vel_t.loadFromImage(vel_image);
    Sprite vel_s; vel_s.setTexture(vel_t);
    vel_s.setScale(0.0245, 0.0245);
    vel_s.setOrigin(40, 40);

    Image dis_image; dis_image.loadFromFile("graphic/2.png");
    Texture dis_t; dis_t.loadFromImage(dis_image);
    Sprite dis_s; dis_s.setTexture(dis_t);
    dis_s.setScale(0.3, 0.3);
    dis_s.setOrigin(40, 40);


    Image life_image; life_image.loadFromFile("graphic/3.png");
    Texture life_t; life_t.loadFromImage(life_image);
    Sprite life_s; life_s.setTexture(life_t);
    life_s.setScale(0.04, 0.04);
    life_s.setOrigin(40, 40);

    Image fuel_image; fuel_image.loadFromFile("graphic/4.png");
    Texture fuel_t; fuel_t.loadFromImage(fuel_image);
    Sprite fuel_s; fuel_s.setTexture(fuel_t);
    fuel_s.setScale(0.078, 0.078);
    fuel_s.setOrigin(41, 41);

    RectangleShape timeBar(Vector2f(20, 20));
    timeBar.setSize(Vector2f(30, 600));
    timeBar.setFillColor(Color(150, 50, 250));

    string num;
    float xx;
    float yy;
    int playerScore = 0;
    int finalScore = 0;

    while (window.isOpen()) {
        num = "";
        srand( time( NULL ) * ( rand() % 100 ) * ( rand() % 100 ) );

        Event event;
        while (window.pollEvent(event)) {
            if ((event.type == Event::Closed) ||
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }

        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Left) {
                ship.flight(75);
                ship_s.rotate(-5);
            }
            if (event.key.code == Keyboard::Right) {
                ship.flight(77);
                ship_s.rotate(5);
            }
            if (event.key.code == Keyboard::Up) {
                ship.flight(73);
            }
            if (event.key.code == Keyboard::Down) {
                ship.flight(80);
            }
        };

        c = ship.getPosition();
        d = ship.getDirection();
        v = ship.getVelocity();

        xx = c.x + d.x/sqrt(d.x*d.x+d.y*d.y)*v;
        yy = c.y + d.y/sqrt(d.x*d.x+d.y*d.y)*v;

        if (yy < 0) {
            yy = 0;
        }
        if (yy > MAX_Y) {
            yy = MAX_Y;
        }
        if (xx < WIDTH_WINDOW / 2){
            xx = WIDTH_WINDOW / 2;
        }

        ship.setPosition(xx,yy);
        setView(xx,yy);
        ship_s.setPosition(xx,yy);

        spaceArea.setRadius(ship.radius);
        spaceArea.setOrigin(ship.radius,ship.radius);
        spaceArea.setPosition(ship.getPosition().x,ship.getPosition().y);

        timeBar.setPosition(ship.getPosition().x - 400,0);
        timeBar.setScale(1, 1 - static_cast<float> (ccc) / 400);

        if (ccc == 400) {
            ship.teleportation();
            while (ccc < 450) {
                ship_s.setScale(static_cast<float> (0.1 * (450 - ccc) / 50),
                                static_cast<float> (0.1 * (450 - ccc) / 50));

                window.clear(Color(40,0,40));
                window.draw(map_s1);
                window.draw(map_s2);
                window.setView(view);
                for(int i = 0; i < 6; i++) {
                    if(!isDestroy[i]) {
                        window.draw(*(arrShape[i]));
                    };
                }
                for(int i = 0; i < numberTablets; i++) {
                    if(!isEaten[i]) {
                        switch (typeT[i]) {
                            case 1: {
                                life_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                   (*(arrTablets[i])).getPosition().y);
                                window.draw(life_s);
                                break;
                            };
                            case 2: {
                                vel_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                  (*(arrTablets[i])).getPosition().y);
                                window.draw(vel_s);
                                break;
                            };
                            case 3: {
                                dis_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                  (*(arrTablets[i])).getPosition().y);
                                window.draw(dis_s);
                                break;
                            };
                            case 4: {
                                fuel_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                   (*(arrTablets[i])).getPosition().y);
                                window.draw(fuel_s);
                                break;
                            };
                        };
                    }
                }

                window.draw(spaceArea);
                window.draw(timeBar);
                window.draw(ship_s);
                window.draw(text);
                window.display();

                usleep(1000);
                ccc++;
            };

            xx = ship.getPosition().x;
            yy = ship.getPosition().y;
            timeBar.setPosition(ship.getPosition().x - 400,0);
            timeBar.setScale(1, 1 - static_cast<float> (ccc) / 400);
            ship_s.setPosition(xx,yy);

            while (ccc < 500) {
                ship_s.setScale(static_cast<float> (0.1 * (ccc - 450) / 50),
                                static_cast<float> (0.1 * (ccc - 450)/ 50));

                window.clear(Color(40, 0, 40));
                window.draw(map_s1);
                window.draw(map_s2);
                for(int i = 0; i < 6; i++) {
                    if(!isDestroy[i]) {
                        window.draw(*(arrShape[i]));
                    };
                }
                for(int i = 0; i < numberTablets; i++) {
                    if(!isEaten[i]) {
                        switch (typeT[i]) {
                            case 1: {
                                life_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                   (*(arrTablets[i])).getPosition().y);
                                window.draw(life_s);
                                break;
                            };
                            case 2: {
                                vel_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                  (*(arrTablets[i])).getPosition().y);
                                window.draw(vel_s);
                                break;
                            };
                            case 3: {
                                dis_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                  (*(arrTablets[i])).getPosition().y);
                                window.draw(dis_s);
                                break;
                            };
                            case 4: {
                                fuel_s.setPosition((*(arrTablets[i])).getPosition().x,
                                                   (*(arrTablets[i])).getPosition().y);
                                window.draw(fuel_s);
                                break;
                            };
                        };
                    }
                }
                window.draw(timeBar);
                window.draw(ship_s);
                window.draw(text);
                window.display();

                usleep(1000);
                ccc++;
            };
            spaceArea.setOrigin(ship.radius, ship.radius);
            ccc = 0;
        };

        ccc++;
        usleep(5500);

        if(view.getCenter().x >(1300 + 200 * stepCreateFig)) {
            delete arrShape[0];
            for(int i = 0; i < numberFigure-1; i ++) {
                arrShape[i] = arrShape[i + 1];
                arrRadius[i] = arrRadius[i + 1];
                isDestroy[i] = isDestroy[i + 1];
            }
            typeFig = 1 + rand() % 5;
            x = 1700 + 200 * stepCreateFig + rand() % 100;
            y = rand() % 500;
            arrShape[5] = creator.getFigure(typeFig, x, y);
            arrRadius[5] = creator.getRadius();
            isDestroy[5] = false;
            stepCreateFig++;
        }

        if(view.getCenter().x >(1300 + 400*stepCreateTablets)) {
            delete arrTablets[0];
            for(int i = 0; i < numberTablets-1; i ++){
                arrTablets[i] = arrTablets[i + 1];
                isEaten[i] = isEaten[i + 1];
                typeT[i] = typeT[i + 1];
            }
            typeTabl = 1 + rand() % 4;
            x = 1900 + 400 * stepCreateTablets + rand() % 100;
            y = rand() % 500;
            arrTablets[3] = creator.getBonus(typeTabl, x, y);
            isEaten[3] = false;
            typeT[3] = typeTabl;
            stepCreateTablets++;
        }

        if (iter > 10) {
            num = '0' + iter / 10;
            num += ('0'+(iter % 10));
        } else {
            num = '0' + iter;
        };
        if(ccc % 4 == 0) {
            iter++;
        }
        if (iter == 10) {
            iter = 0;
        }

        window.draw(map_s1);
        window.draw(map_s2);
        window.setView(view);

        if( xx > max(background_1,background_2) + SIZE / 2 ) {
            if( background_1 < background_2 ) {
                background_1 += SIZE + SIZE / 2;
                map_s1.setPosition(background_1, 0);
            } else {
                background_2 += SIZE + SIZE / 2;
                map_s2.setPosition(background_2, 0);
            };
        };

        for(int i =0; i < 6; i ++) {
            if(!isDestroy[i]) {
                window.draw(*(arrShape[i]));
            };
        }

        for(int i =0; i < numberTablets; i++) {
            if(!isEaten[i]){
                switch (typeT[i]) {
                    case 1: {
                        life_s.setPosition((*(arrTablets[i])).getPosition().x,
                                           (*(arrTablets[i])).getPosition().y);
                        window.draw(life_s);
                        break;
                    };
                    case 2: {
                        vel_s.setPosition((*(arrTablets[i])).getPosition().x,
                                          (*(arrTablets[i])).getPosition().y);
                        window.draw(vel_s);
                        break;
                    };
                    case 3: {
                        dis_s.setPosition((*(arrTablets[i])).getPosition().x,
                                          (*(arrTablets[i])).getPosition().y);
                        window.draw(dis_s);
                        break;
                    };
                    case 4: {
                        fuel_s.setPosition((*(arrTablets[i])).getPosition().x,
                                           (*(arrTablets[i])).getPosition().y);
                        window.draw(fuel_s);
                        break;
                    };
                };
            }
        }


        for(int i =0; i < numberFigure; i++) {
            realCenterX = arrShape[i]->getPosition().x ;
            realCenterY = arrShape[i]->getPosition().y ;
            if( distance(realCenterX, realCenterY, ship.getPosition().x, ship.getPosition().y)
                < (40.0 + arrRadius[i]) && !isDestroy[i] ) {
                isDestroy[i] = true;
                ship.getInTouch();
            }
        }

        for(int i =0; i < numberTablets; i++) {
            realCenterX = arrTablets[i]->getPosition().x ;
            realCenterY = arrTablets[i]->getPosition().y ;
            if((distance(realCenterX, realCenterY, ship.getPosition().x, ship.getPosition().y)
                < (40.0 + 20.0)) && !isEaten[i]) {
                isEaten[i] = true;
                ship.getBonus(typeT[i]);
            }
        }

        window.draw(spaceArea);
        window.draw(ship_s);
        window.draw(timeBar);

        playerScore = (static_cast<int> (ship.getPosition().x) - 400) / 100;
        ostringstream gameTimeString, playerLife, playerFuel, playerVel;
        gameTimeString << playerScore, playerLife << ship.lives,
                playerFuel << ship.fuel, playerVel << ship.velocity;
        text.setString("Score: " + gameTimeString.str() + "\nLife: " + playerLife.str()
                       + "\nVel: " + playerVel.str() + "\nFuel: " + playerFuel.str() );
        text.setPosition(view.getCenter().x - 390, view.getCenter().y - 295);
        window.draw(text);

        if(ship.lives <= 0) {
            ship.velocity = 0;
            ccc = 0;
            finalScore = (static_cast<int> (ship.getPosition().x) - 400) / 100;
            showResults(window, finalScore);
        }

        window.display();
    }
    for(int i =0; i < numberFigure; i ++) {
        delete arrShape[i];
    }
    for(int i =0; i < numberTablets; i ++) {
        delete arrTablets[i];
    }
    delete [] arrShape;
    delete [] arrTablets;
};

int main() {
    gameStart();
    return 0;
}
