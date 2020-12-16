#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Platform.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemyfly.h"
#include "bulletEnemy.h"
#include "Boss.h"
#include "Item.h"
#include "bossState2.h"
#include "RestartMenu.h"
#include "BossState3.h"
#include <vector>
int page_number;

void updateAndSaveScore(std::string playerName, int KILL);


int main()
{

    int KILL = 0;
    bool isTypeName = false;
    bool isGameStarted = false;
    bool toggleLeaderboard = false;
    std::string playerName = "";

    sf::RenderWindow window(sf::VideoMode(1520, 720), "63010930_Stage1", sf::Style::Close);
    Menu menu(window.getSize().x, window.getSize().y);
    sf::Texture texture;
    if (!texture.loadFromFile("background/background main.png"));
    {
        //handle error
    }
    sf::Sprite background;
    background.setTexture(texture);

    
    // init player text
    


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!isTypeName) {
                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            isTypeName = true;
                            // fix later
                            break;
                        case 1:
                            toggleLeaderboard = !toggleLeaderboard;
                            //page_number = 1;
                            //window.close();
                            break;
                        case 2:

                            page_number = -2;
                            window.close();
                            break;
                        }
                    }
                }
            }
            if (event.type == sf::Event::TextEntered && isTypeName && event.text.unicode < 128) {
                std::cout << playerName << std::endl;
                switch (event.key.code) {
                case 32:
                    break;
                case 8:
                    if (playerName.size() == 0) {
                        break;
                    }
                    playerName.pop_back();
                    menu.playerText.setString(playerName);
                    break;
                case 13:
                     page_number = 0;
                     isTypeName = false;
                     std::cout << "Play button has been pressed" << std::endl;
                     window.close();
                default:
                    if (playerName.size() >= 15) break;
                    playerName += event.text.unicode;
                    // play sound
                    menu.playerText.setString(playerName);
                }
            }
            if (toggleLeaderboard) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Key::Escape))) {
                    toggleLeaderboard = false;
                }
            }
        }

     
        window.clear();
        window.draw(background);
        menu.draw(window);
        if (isTypeName) {
            window.draw(menu.textBox);
            window.draw(menu.enter);
            //window.draw(menu.textCursor);
            menu.updateName();
            window.draw(menu.playerText);
        }
        else if (toggleLeaderboard) {
            menu.leaderboard->render(&window);
        }
        window.display();
    }




    while (true)
    {
        if (page_number == 0)
        {
            sf::RectangleShape platform1;
            platform1.setSize(sf::Vector2f(400.0f, 50.0f));
            sf::Texture platform1Texture;
            platform1Texture.loadFromFile("platform.PNG");
            platform1.setTexture(&platform1Texture);
            platform1.setPosition(300.0f, 275.0f);




            sf::RectangleShape platform6;
            platform6.setSize(sf::Vector2f(300.0f, 50.0f));
            sf::Texture platform6Texture;
            platform6Texture.loadFromFile("platform.PNG");
            platform6.setTexture(&platform1Texture);
            platform6.setPosition(8500.0f, 275.0f);



            std::vector<Platform*> platforms;
            std::vector<Platform*> platforms1;

            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(2200.0f, 50.0f), sf::Vector2f(900.0f, 580.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(180.0f, 3.0f), sf::Vector2f(2650.0f, 520.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(180.0f, 3.0f), sf::Vector2f(3420.0f, 520.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(500.0f, 3.0f), sf::Vector2f(3060.0f, 400.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(400.0f, 3.0f), sf::Vector2f(3730.0f, 390.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(500.0f, 3.0f), sf::Vector2f(4300.0f, 390.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(180.0f, 3.0f), sf::Vector2f(4660.0f, 520.0f)));
           


            //ground&ceiling
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(40000.0f, 100.0f), sf::Vector2f(500.0f, -80.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(40000.0f, 200.0f), sf::Vector2f(500.0f, 780.0f)));




            /* sf::RenderWindow window;*/
            sf::Vector2i screenDimensions(1520,720);
            window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "63010930_GUNSLUG", sf::Style::Close);





            sf::Music music;
            music.openFromFile("sound/metalslug1.wav");
            music.setVolume(25.0);
            music.play();

            sf::SoundBuffer soundulti, soundJump, soundAttack, soundItem, soundOk;
            soundulti.loadFromFile("UltimateSound.wav");
            soundJump.loadFromFile("JumpSOUND.wav");
            soundAttack.loadFromFile("attack.ogg");
            soundItem.loadFromFile("sound/coin.wav");
            soundOk.loadFromFile("sound/ok.wav");

            sf::Sound sUlti, sJump, sAtk, sItem, sHit, sOk;
            sItem.setBuffer(soundItem);
            sUlti.setBuffer(soundulti);
            sJump.setBuffer(soundJump);
            sAtk.setBuffer(soundAttack);
            sOk.setBuffer(soundOk);
            sItem.setVolume(15.0);
            sUlti.setVolume(15.0);
            sJump.setVolume(15.0);
            sAtk.setVolume(15.0);
            sOk.setVolume(15.0);


            sf::Texture bTexture;
            sf::Sprite bImage;

            bTexture.loadFromFile("background/background1.png");
            bImage.setTexture(bTexture);
            bImage.setScale(3.0f, (float)screenDimensions.y / bTexture.getSize().y);

            sf::View view;
            view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
            view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

            sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);

            /*sf::CircleShape life1;
            life1.setRadius(20.0f);
            sf::Texture Life1Texture;
            Life1Texture.loadFromFile("life.png");
            life1.setTexture(&Life1Texture);
            life1.setPosition(850, 10);


            sf::CircleShape life2;
            life2.setRadius(20.0f);
            sf::Texture Life2Texture;
            Life2Texture.loadFromFile("life.png");
            life2.setTexture(&Life2Texture);
            life2.setPosition(800, 10);

            sf::CircleShape life3;
            life3.setRadius(20.0f);
            sf::Texture Life3Texture;
            Life3Texture.loadFromFile("life.png");
            life3.setTexture(&Life3Texture);
            life3.setPosition(750, 10);*/


            //ultimate
            int ultivalue[10] = {};
            sf::Clock clockUlti;
            sf::CircleShape ultimate[10];
            sf::Texture ultimateTexture;
            ultimateTexture.loadFromFile("ultimate.png");
            for (int k = 0; k <= 9; k++)
            {
                ultimate[k].setRadius(80.0f);
                ultimate[k].setTexture(&ultimateTexture);
                ultimate[k].setPosition(10000000.0f, 100000000000.0f);
            }
            int indexUlti = 0;


            //bulletTexture
            sf::Clock clockShoot;

            sf::Texture bulletTexture;
            bulletTexture.loadFromFile("bulletred.png");



            window.setFramerateLimit(60);

            //player
            sf::Texture playerTexture;
            playerTexture.loadFromFile("Player/playersheet.png");
            Player* player;
            player = new Player(&playerTexture, sf::Vector2u(8, 5), 0.09f, 500.0f, 300.0f);
            player->setPosition(500, 450);
            float deltaTime = 0.0f;
            sf::Clock clock;
            bool isBonus = false;
            bool endstate = false;

            //enemy
            std::vector<Enemy*> enemy;
            int posx[100];
            for (int i = 0; i <= 20; i++)
            {


                posx[i] = rand() % 15000;
            }



            sf::Texture enemyTexture;
            enemyTexture.loadFromFile("enemy/enemy-soider.png");
            for (int i = 0; i <= 14; i++)
                enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(12, 2), 0.12f, 200.0f, sf::Vector2f(posx[i], 480.0f), sf::Vector2f(1.0f, 1.0f)));
            float dt = 0.0f;
            sf::Clock clock1;

            //boss
            std::vector<Boss*> boss;
            sf::Texture bossTexture;
            bossTexture.loadFromFile("boss/boss1.png");
            boss.push_back(new Boss(&bossTexture, sf::Vector2u(5, 2), 0.2f, 100.0f, sf::Vector2f(5500, 620.0f)));


            //enemyfly
            std::vector<Enemyfly*> enemyfly;
            int posix[100];
            for (int i = 0; i <= 15; i++)
            {


                posix[i] = rand() % 15000;

            }




            sf::Texture enemyflyTexture;
            enemyflyTexture.loadFromFile("enemy/ufo.png");
            for (int i = 0; i <= 14; i++)
                enemyfly.push_back(new Enemyfly(&enemyflyTexture, sf::Vector2u(8, 2), 0.3f, 350.0f, sf::Vector2f(posix[i], .0f)));
            float dti = 0.0f;
            sf::Clock clock2;

            //bullet 
            std::vector<bulletEnemy*> bulletPlayer;


            int cdUltiValue = 1;
            sf::Clock clockCdUltiValue;
            sf::RectangleShape cdUltimate(sf::Vector2f(400.0f, 50.0f));;
            sf::Texture cdUltiTexture;
            cdUltiTexture.loadFromFile("CDULTIMATE.PNG");
            cdUltimate.setTexture(&cdUltiTexture);
            cdUltimate.setPosition(0, 600);

            //bulletEnemy
            sf::Texture bulletEnemyTexture;
            bulletEnemyTexture.loadFromFile("bulletenemy1.png");


            //Item 
            std::vector<item*> Items;
            sf::Texture itemTexture;
            sf::Texture itemBossTexture;
            sf::Texture itemEnemyFlyTexture;
            sf::Texture itemEnemyFly2Texture;
            itemTexture.loadFromFile("item/chicken.png");
            itemEnemyFlyTexture.loadFromFile("item/coin.png");
            itemEnemyFly2Texture.loadFromFile("item/firstaid.png");
            itemBossTexture.loadFromFile("item/chest.png");
            sf::Clock bonusTime;





            //Hptext

            sf::Font SLUG;
            SLUG.loadFromFile("font/metalslug.ttf");


            sf::Text lblHPnum;
            lblHPnum.setCharacterSize(40);
            lblHPnum.setPosition({ 10 ,10 });
            lblHPnum.setFont(SLUG);
            lblHPnum.setString("HP");
            lblHPnum.setFillColor(sf::Color::Red);
            lblHPnum.setOutlineColor(sf::Color::Yellow);
            lblHPnum.setOutlineThickness(3);



            sf::Text lblHP;
            lblHP.setCharacterSize(40);
            lblHP.setPosition({ 70 ,10 });
            lblHP.setFont(SLUG);
            lblHP.setString(std::to_string(player->getHP()));
            lblHP.setFillColor(sf::Color::Red);
            lblHP.setOutlineColor(sf::Color::Yellow);
            lblHP.setOutlineThickness(3);


            //killtext
            sf::Text lblKillnum;
            lblKillnum.setCharacterSize(40);
            lblKillnum.setPosition({ 750 ,60 });
            lblKillnum.setFont(SLUG);
            lblKillnum.setString("Score");
            lblKillnum.setFillColor(sf::Color::Cyan);
            lblKillnum.setOutlineColor(sf::Color::White);
            lblKillnum.setOutlineThickness(3);


            sf::Text lblKill;
            lblKill.setCharacterSize(40);
            lblKill.setPosition({ 870 ,60 });
            lblKill.setFont(SLUG);
            lblKill.setString(std::to_string(KILL));
            lblKill.setFillColor(sf::Color::Cyan);
            lblKill.setOutlineColor(sf::Color::White);
            lblKill.setOutlineThickness(3);


            int  hpEnemy = 2;
            //const float gravitySpeed = 10;*/
            while (window.isOpen())
            {
                lblHP.setString(std::to_string((player->getHP())));
                lblKill.setString(std::to_string(KILL));

                int randomTime, r;
                srand(time(0));
                r = rand() % 3;

                randomTime = rand() % 2;

                deltaTime = clock.restart().asSeconds();
                if (deltaTime > 1.f / 40.f)
                    deltaTime = 1.f / 40.f;
                dt = clock1.restart().asSeconds();
                if (dt > 1.f / 40.f)
                    dt = 1.f / 40.f;
                dti = clock2.restart().asSeconds();
                if (dti > 1.f / 40.f)
                    dti = 1.f / 40.f;
                /*if (deltaTime > 1.0f / 20.0f)
                    deltaTime = 1.0f / 20.0f;*/

                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Escape))) {
                        page_number = -1;
                        window.close();
                    }
                    if (evnt.type == sf::Event::Closed) {
                        page_number = -1;
                        window.close();
                    }
                }
                //sf::Time cdEnemySpawn = cdEnemy.getElapsedTime();*/

                sf::Time cdShoot = clockShoot.getElapsedTime();
                sf::Time cdUlti = clockUlti.getElapsedTime();
                sf::Time cdCdUltiValue = clockCdUltiValue.getElapsedTime();
                const float movespeed = 8;




                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && indexUlti < 10 && ultivalue[indexUlti] == 0 && cdUltiValue == 1)
                {

                    ultimate[indexUlti].setPosition(player->getPosition().x + 40, player->getPosition().y - 80);
                    ultivalue[indexUlti] = 1;
                    cdUltiValue = 0;
                    sUlti.play();

                    indexUlti++;
                    if (indexUlti >= 10)
                        indexUlti = 0;
                }
                if (cdCdUltiValue.asSeconds() >= 10.0 && cdUltiValue == 0)
                {
                    clockCdUltiValue.restart();
                    cdUltiValue = 1;
                }


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && cdShoot.asSeconds() >= 0.2)
                {
                    clockShoot.restart();
                    sAtk.play();
                    if (player->getFaceRight() == true)
                        bulletPlayer.push_back(new bulletEnemy(&bulletTexture, 20.f, player->getPosition().x, player->getPosition().y, 2.0f, 0.0f, sf::Vector2f(4.5f, 1.0f)));
                    if (player->getFaceRight() == false)
                        bulletPlayer.push_back(new bulletEnemy(&bulletTexture, 20.f, player->getPosition().x, player->getPosition().y, -2.0f, 0.0f, sf::Vector2f(4.5f, 1.0f)));
                }




                //screenscroll
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 300;

                }
                else
                {
                    position.x = screenDimensions.x / 2;
                }
                if (position.x + 455 > 16208)
                {
                    position.x = 15753;
                }

                //bullet&Ultimate

                for (int l = 0; l <= 9; l++)
                {
                    ultimate[l].move(20.0f, 0.0f);
                    if (ultivalue[l] == 1)
                    {

                        ultivalue[l] = 0;
                    }
                }



                //Player

                if (player->getPosition().x < 40)
                {
                    player->setPosition(40, player->getPosition().y);
                }
                if (player->getPosition().x > 16104)
                {
                    player->setPosition(16104, player->getPosition().y);
                }
                for (auto* i : enemy)
                {
                    if (player->GetGlobalBounds().intersects(i->GetGlobalBounds()))
                    {
                        player->decreaseHP(1);
                    }
                }
                if (player->getHP() < 0)
                {
                    updateAndSaveScore(playerName, KILL);
                    player->setHP(0);
                    window.close();
                    KILL = 0;
                    page_number = 3;
                    break;



                }



                //Collision
                int temp = 0;

                for (auto* bullet : bulletPlayer)
                {
                    bullet->Update();
                    if (bullet->getPosition().x > player->getPosition().x + 620)
                    {

                        delete bulletPlayer.at(temp);
                        bulletPlayer.erase(bulletPlayer.begin() + temp);
                        --temp;
                    }
                    /*for (auto* i : enemy)
                    {
                        if (bullet->GetGlobalBounds().intersects(i->GetGlobalBounds()))
                        {
                                delete bulletPlayer.at(temp);
                        bulletPlayer.erase(bulletPlayer.begin() + temp);
                            --temp;
                        }
                    }*/

                    ++temp;
                }

                sf::Vector2f direction = sf::Vector2f(0, 0);
                for (auto* i : platforms)
                {
                    if (i->GetCollider().CheckCollision(player->GetCollider(), direction, 1.0f))
                    {
                        player->onCollision(direction);
                    }

                }
                sf::Vector2f direction1 = sf::Vector2f(0, 0);
                for (auto* j : platforms1)
                {
                    if (j->GetCollider().CheckCollision(player->GetCollider(), direction1, 1.0f))
                    {
                        player->onCollision(direction1);
                    }

                }
                player->Update(deltaTime);




                //enemy
                int counter = 0;
                int counter1 = 0;
                sf::Vector2f direction4 = sf::Vector2f(0, 0);
                for (auto* k : enemy)
                {
                    for (auto* i : platforms)
                    {
                        if (i->GetCollider().CheckCollision(k->GetCollider(), direction4, 1.0f))
                        {
                            k->onCollision(direction4);
                        }

                    }
                    sf::Vector2f direction5 = sf::Vector2f(0, 0);
                    for (auto* j : platforms1)
                    {
                        if (j->GetCollider().CheckCollision(k->GetCollider(), direction5, 1.0f))
                        {
                            k->onCollision(direction5);
                        }

                    }
                }
                for (auto* i : enemy)
                {
                    for (auto* bullet : bulletPlayer)
                    {
                        if (i->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {
                            i->setHP(1, isBonus);
                            bullet->setPosition(-50.f, -50.f);



                        }
                        /*++counter1;*/
                    }



                }

                for (auto* i : enemy)
                {

                    i->Update(dt, player, &bulletEnemyTexture);

                    if (i->getHP() <= 0)
                    {
                        if (r == 1)
                        {
                            Items.push_back(new item(&itemTexture, i->getPosition().x, i->getPosition().y + 15, sf::Vector2u(5, 1), 0.3f, "NORMAL", sf::Vector2f(75.f, 75.f)));
                            delete enemy.at(counter);
                        }

                        enemy.erase(enemy.begin() + counter);
                        counter--;
                        KILL += 100;
                    }
                    counter++;
                }




                //boss
                int counter4 = 0;
                int itemCounter = 0;
                for (auto* j : boss)
                {
                    for (auto* bullet : bulletPlayer)
                    {

                        if (j->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {
                            j->setHP(1);
                            bullet->setPosition(-50.f, -50.f);




                        }


                    }

                }
                for (auto* i : boss)
                {

                    i->Update(dt, player);

                    if (i->getHP() <= 0)
                    {
                        Items.push_back(new item(&itemBossTexture, i->getPosition().x, i->getPosition().y + 10, sf::Vector2u(6, 1), 0.09f, "BOSS", sf::Vector2f(80.f, 80.f)));
                        delete boss.at(counter4);
                        boss.erase(boss.begin() + counter4);
                        counter4--;
                        KILL += 300;
                    }
                    counter4++;
                }
                //enemyfly
                int counter2 = 0;
                int counter3 = 0;

                for (auto* k : enemyfly)
                {
                    for (auto* bullet : bulletPlayer)
                    {

                        if (k->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {

                            bullet->setPosition(-50.f, -50.f);
                            if (randomTime == 0)
                            {
                                Items.push_back(new item(&itemEnemyFlyTexture, k->getPosition().x, k->getPosition().y + 10, sf::Vector2u(9, 1), 0.09f, "EnemyFly", sf::Vector2f(50.f, 50.f)));
                            }
                            if (randomTime == 1)
                            {
                                Items.push_back(new item(&itemEnemyFly2Texture, k->getPosition().x, k->getPosition().y + 10, sf::Vector2u(17, 1), 0.09f, "EnemyFly2", sf::Vector2f(75.f, 75.f)));
                                delete enemyfly.at(counter3);

                            }
                            enemyfly.erase(enemyfly.begin() + counter3);
                            counter3--;
                            KILL += 100;
                        }


                    }

                    if (k->getPosition().y < 100)
                    {

                        k->setPosition(k->getPosition().x, 100);

                    }
                    if (k->getPosition().y > 375)
                    {

                        k->setPosition(k->getPosition().x, 375);
                    }

                    counter3++;
                }



                for (auto* k : enemyfly)
                {
                    k->Update(dti);

                }

                for (auto* item : Items)
                {
                    item->Update(deltaTime);
                    if (player->GetGlobalBounds().intersects(item->GetGlobalBounds()))
                    {
                        if (item->getType() == "NORMAL")
                        {
                            sOk.play();
                            KILL += 50;
                            player->decreaseHP(-5);
                            isBonus = true;
                            bonusTime.restart();
                        }
                        if (item->getType() == "EnemyFly")
                        {
                            KILL += 85;
                            sItem.play();
                        }
                        if (item->getType() == "EnemyFly2")
                        {
                            sItem.play();
                            player->decreaseHP(-10);
                        }
                        if (item->getType() == "BOSS")
                        {
                            sItem.play();
                            endstate = true;


                        }

                        delete Items.at(itemCounter);
                        Items.erase(Items.begin() + itemCounter);
                        itemCounter--;


                    }
                    itemCounter++;
                }

                if (endstate == true)
                {
                    page_number = 1;
                    window.close();
                    break;
                }






                if (player->getPosition().x > window.getSize().x / 2.f - 300 && player->getPosition().x < 5500 - window.getSize().x / 2.f)
                    view.setCenter(player->getPosition().x + 300, window.getSize().y / 2.f);


                //life move
                /*if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 695;
                    //life1.setPosition(position.x, 10);
                    life1.setPosition(view.getCenter().x - 300 + 695, 10);
                }

                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 645;
                    //life2.setPosition(position.x, 10);
                    life2.setPosition(view.getCenter().x - 300 + 645, 10);
                }

                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 595;
                    //life3.setPosition(position.x, 10);
                    life3.setPosition(view.getCenter().x - 300 + 595, 10);
                }*/

                //Hp move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 90;
                    //lblHP.setPosition(position.x, 10);
                    lblHP.setPosition(view.getCenter().x - 500 - 90, 10);
                }
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 150;
                    //lblHPnum.setPosition(position.x, 10);
                    lblHPnum.setPosition(view.getCenter().x - 500 - 150, 10);
                }
                //Kill Move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 695;
                    //lblKill.setPosition(position.x, 60);
                    lblKill.setPosition(view.getCenter().x - 100 + 695, 10);
                }
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 605;
                    //lblKillnum.setPosition(position.x, 60);
                    lblKillnum.setPosition(view.getCenter().x - 100 + 575, 10);
                }
                //cdUlti move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 150;
                    cdUltimate.setPosition(position.x, 600);
                }

                //Item timer update
                if (bonusTime.getElapsedTime().asSeconds() >= 5.f)
                {
                    isBonus = false;
                }

                window.clear();

                window.setView(view);



                for (auto* j : platforms1)
                {
                    j->Draw(window);
                }
                window.draw(bImage);


                /* if (cdUltiValue == 1)
                {
                    window.draw(cdUltimate);
                }*/


                /*for (auto* i : platforms)
                {
                    i->Draw(window);
                }*/
               /* window.draw(life1);
                window.draw(life2);
                window.draw(life3);*/
                window.draw(lblHPnum);
                window.draw(lblHP);
                window.draw(lblKill);
                window.draw(lblKillnum);
                for (auto* i : boss)
                    i->Draw(window);


                player->Draw(window);
                for (auto* item : Items)
                    item->Render(window);

                for (auto* bullet : bulletPlayer)
                    bullet->Render(window);
                for (int k = 0; k <= 9; k++)
                {
                    window.draw(ultimate[k]);
                }
                for (auto* i : enemy)
                {
                    i->Draw(window);
                }

                for (auto* k : enemyfly)
                {
                    k->Draw(window);
                }

             
                window.setView(window.getDefaultView());
                window.display();

            }

        }
        if (page_number == 1)
        {
            sf::RectangleShape platform1;
            platform1.setSize(sf::Vector2f(400.0f, 50.0f));
            sf::Texture platform1Texture;
            platform1Texture.loadFromFile("platform.PNG");
            platform1.setTexture(&platform1Texture);
            platform1.setPosition(300.0f, 275.0f);




            sf::RectangleShape platform6;
            platform6.setSize(sf::Vector2f(300.0f, 50.0f));
            sf::Texture platform6Texture;
            platform6Texture.loadFromFile("platform.PNG");
            platform6.setTexture(&platform1Texture);
            platform6.setPosition(8500.0f, 275.0f);



            std::vector<Platform*> platforms;
            std::vector<Platform*> platforms1;

            /*platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(500.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(2000.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(2950.0f, 200.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(5050.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(6850.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(8650.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(10050.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(12550.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(13850.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(15550.0f, 300.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(300.0f, 50.0f), sf::Vector2f(16650.0f, 300.0f)));*/


            //ground&ceiling
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(40000.0f, 3.0f), sf::Vector2f(500.0f, 645.0f)));
           // platforms1.push_back(new Platform(nullptr, sf::Vector2f(40000.0f, 39 * 3.0f), sf::Vector2f(258 * 3.0f, 195 * 3.0f)));
            /*platforms1.push_back(new Platform(nullptr, sf::Vector2f(65 * 3.0f, 39 * 3.0f), sf::Vector2f(455.5 * 3.0f, 162 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(128 * 3.0f, 39 * 3.0f), sf::Vector2f(552 * 3.0f, 128 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(129 * 3.0f, 39 * 3.0f), sf::Vector2f(680.5 * 3.0f, 94.5 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(97 * 3.0f, 39 * 3.0f), sf::Vector2f(792.8 * 3.0f, 60 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(194 * 3.0f, 39 * 3.0f), sf::Vector2f(935.5 * 3.0f, 92 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(97 * 3.0f, 39 * 3.0f), sf::Vector2f(1079.5 * 3.0f, 60 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(129 * 3.0f, 39 * 3.0f), sf::Vector2f(1191.5 * 3.0f, 94.5 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(128 * 3.0f, 39 * 3.0f), sf::Vector2f(1320 * 3.0f, 128 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(65 * 3.0f, 39 * 3.0f), sf::Vector2f(1414 * 3.0f, 162 * 3.0f)));

            platforms1.push_back(new Platform(nullptr, sf::Vector2f(65 * 3.0f, 39 * 3.0f), sf::Vector2f(2328 * 3.0f, 162 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(128 * 3.0f, 39 * 3.0f), sf::Vector2f(2423.5 * 3.0f, 128 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(129 * 3.0f, 39 * 3.0f), sf::Vector2f(2551.5 * 3.0f, 94.5 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(97 * 3.0f, 39 * 3.0f), sf::Vector2f(2664 * 3.0f, 60 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(194 * 3.0f, 39 * 3.0f), sf::Vector2f(2807.5 * 3.0f, 92 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(97 * 3.0f, 39 * 3.0f), sf::Vector2f(2952 * 3.0f, 60 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(129 * 3.0f, 39 * 3.0f), sf::Vector2f(3064 * 3.0f, 94.5 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(128 * 3.0f, 39 * 3.0f), sf::Vector2f(3192 * 3.0f, 128 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(65 * 3.0f, 39 * 3.0f), sf::Vector2f(3287 * 3.0f, 162 * 3.0f)));

            platforms1.push_back(new Platform(nullptr, sf::Vector2f(65 * 3.0f, 39 * 3.0f), sf::Vector2f(4199.5 * 3.0f, 162 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(128 * 3.0f, 39 * 3.0f), sf::Vector2f(4295.5 * 3.0f, 128 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(129 * 3.0f, 39 * 3.0f), sf::Vector2f(4424 * 3.0f, 94.5 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(97 * 3.0f, 39 * 3.0f), sf::Vector2f(4535.5 * 3.0f, 60 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(194 * 3.0f, 39 * 3.0f), sf::Vector2f(4679.5 * 3.0f, 92 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(97 * 3.0f, 39 * 3.0f), sf::Vector2f(4823.5 * 3.0f, 60 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(129 * 3.0f, 39 * 3.0f), sf::Vector2f(4935.5 * 3.0f, 94.5 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(128 * 3.0f, 39 * 3.0f), sf::Vector2f(5063.5 * 3.0f, 128 * 3.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(65 * 3.0f, 39 * 3.0f), sf::Vector2f(5159.5 * 3.0f, 162 * 3.0f)));
            */




            sf::Vector2i screenDimensions(1520, 720);
            sf::RenderWindow window;
            window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "63010930_Stage2", sf::Style::Close);





            sf::Music music;
            music.openFromFile("sound/metalslug2.wav");
            music.setVolume(25.0);
            music.play();

            sf::SoundBuffer soundulti, soundJump, soundAttack, soundItem, soundOk, soundCoin ;
            soundulti.loadFromFile("UltimateSound.wav");
            soundJump.loadFromFile("JumpSOUND.wav");
            soundAttack.loadFromFile("attack.ogg");
            soundItem.loadFromFile("sound/heavy machine gun.wav");
            soundOk.loadFromFile("sound/ok.wav");
            soundCoin.loadFromFile("sound/coin.wav");

            

            sf::Sound sUlti, sJump, sAtk, sItem, sHit, sOk ,sCoin ;
            sItem.setBuffer(soundItem);
            sUlti.setBuffer(soundulti);
            sJump.setBuffer(soundJump);
            sAtk.setBuffer(soundAttack);
            sOk.setBuffer(soundOk);
            sCoin.setBuffer(soundCoin);
            sCoin.setVolume(15.0);
            sItem.setVolume(15.0);
            sUlti.setVolume(15.0);
            sJump.setVolume(15.0);
            sAtk.setVolume(15.0);
            sOk.setVolume(15.0);



            sf::Texture bTexture;
            sf::Sprite bImage;

            bTexture.loadFromFile("background/background2.png");
            bImage.setTexture(bTexture);
            bImage.setScale(3.0f, (float)screenDimensions.y / bTexture.getSize().y);

            sf::View view;
            view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
            view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

            sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);

            /*sf::CircleShape life1;
            life1.setRadius(20.0f);
            sf::Texture Life1Texture;
            Life1Texture.loadFromFile("life.png");
            life1.setTexture(&Life1Texture);
            life1.setPosition(850, 10);


            sf::CircleShape life2;
            life2.setRadius(20.0f);
            sf::Texture Life2Texture;
            Life2Texture.loadFromFile("life.png");
            life2.setTexture(&Life2Texture);
            life2.setPosition(800, 10);

            sf::CircleShape life3;
            life3.setRadius(20.0f);
            sf::Texture Life3Texture;
            Life3Texture.loadFromFile("life.png");
            life3.setTexture(&Life3Texture);
            life3.setPosition(750, 10);*/


            //ultimate
            /*int ultivalue[10] = {};
            sf::Clock clockUlti;
            sf::CircleShape ultimate[10];
            sf::Texture ultimateTexture;
            ultimateTexture.loadFromFile("ultimate.png");
            for (int k = 0; k <= 9; k++)
            {
                ultimate[k].setRadius(80.0f);
                ultimate[k].setTexture(&ultimateTexture);
                ultimate[k].setPosition(10000000.0f, 100000000000.0f);
            }
            int indexUlti = 0;
            */

            //bulletTexture
            sf::Clock clockShoot;

            sf::Texture bulletTexture;
            bulletTexture.loadFromFile("bulletblue.png");



            window.setFramerateLimit(60);

            //player
            sf::Texture playerTexture;
            playerTexture.loadFromFile("Player/playersheet.png");
            Player* player;
            player = new Player(&playerTexture, sf::Vector2u(8, 5), 0.09f, 500.0f, 300.0f);
            player->setPosition(500, 0);
            float deltaTime = 0.0f;
            sf::Clock clock;
            bool isBonus = false;

            //enemy
            std::vector<Enemy*> enemy;




            sf::Texture enemyTexture;
            enemyTexture.loadFromFile("enemy/enemy2.png");

            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(670.0f, 496.0f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(1521.0f, 295.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(2733.f, 187.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(3863.f, 295.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(4875.f, 496.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(5375.f, 496.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(6700.f, 496.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(7346.f, 295.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(8470.f, 187.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(9864.f, 397.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(12000.f, 496.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(10500.f, 496.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(11319.f, 496.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(12957.f, 295.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(13880.f, 187.f), sf::Vector2f(1.0f, 1.0f)));
            enemy.push_back(new Enemy(&enemyTexture, sf::Vector2u(10, 2), 0.1f, 100.0f, sf::Vector2f(15073.f, 295.f), sf::Vector2f(1.0f, 1.0f)));
            float dt = 0.0f;
            sf::Clock clock1;

            //boss
            std::vector<bossState2*> boss;
            sf::Texture bossTexture;
            bossTexture.loadFromFile("boss/boss2.png");
            boss.push_back(new bossState2(&bossTexture, sf::Vector2u(7, 1), 1.0f, 100.0f, sf::Vector2f(6760, 350.0f)));


            //enemyfly
            std::vector<Enemyfly*> enemyfly;
            int posix[100];
            for (int i = 0; i <= 14; i++)
            {


                posix[i] = rand() % 15000;

            }




            sf::Texture enemyflyTexture;
            enemyflyTexture.loadFromFile("enemy/ufo2.png");
            for (int i = 0; i <= 14; i++)
                enemyfly.push_back(new Enemyfly(&enemyflyTexture, sf::Vector2u(6, 2), 0.3f, 200.0f, sf::Vector2f(posix[i], 175.0f)));
            float dti = 0.0f;
            sf::Clock clock2;

            //bullet 
            std::vector<bulletEnemy*> bulletPlayer;


            int cdUltiValue = 1;
            sf::Clock clockCdUltiValue;
            sf::RectangleShape cdUltimate(sf::Vector2f(400.0f, 50.0f));;
            sf::Texture cdUltiTexture;
            cdUltiTexture.loadFromFile("CDULTIMATE.PNG");
            cdUltimate.setTexture(&cdUltiTexture);
            cdUltimate.setPosition(0, 600);

            //bulletEnemy
            sf::Texture bulletEnemyTexture;
            bulletEnemyTexture.loadFromFile("bulletenemy2.png");


            //Item 
            std::vector<item*> Items;
            sf::Texture itemTexture;
            sf::Texture itemBossTexture;
            sf::Texture itemEnemyFlyTexture;
            sf::Texture itemEnemyFly2Texture;

            itemEnemyFlyTexture.loadFromFile("item/heavymachine.png");
            itemEnemyFly2Texture.loadFromFile("item/firstaid.png");
            itemTexture.loadFromFile("item/chicken.png");
            itemBossTexture.loadFromFile("item/chest.png");
            sf::Clock bonusTime;





            //Hptext

            sf::Font SLUG;
            SLUG.loadFromFile("font/metalslug.ttf");

            sf::Text lblHPnum;
            lblHPnum.setCharacterSize(40);
            lblHPnum.setPosition({ 10 ,10 });
            lblHPnum.setFont(SLUG);
            lblHPnum.setString("HP");
            lblHPnum.setFillColor(sf::Color::Red);
            lblHPnum.setOutlineColor(sf::Color::Yellow);
            lblHPnum.setOutlineThickness(3);



            sf::Text lblHP;
            lblHP.setCharacterSize(40);
            lblHP.setPosition({ 70 ,10 });
            lblHP.setFont(SLUG);
            lblHP.setString(std::to_string(player->getHP()));
            lblHP.setFillColor(sf::Color::Red);
            lblHP.setOutlineColor(sf::Color::Yellow);
            lblHP.setOutlineThickness(3);

            //killtext
            sf::Text lblKillnum;
            lblKillnum.setCharacterSize(40);
            lblKillnum.setPosition({ 750 ,60 });
            lblKillnum.setFont(SLUG);
            lblKillnum.setString("Score");
            lblKillnum.setFillColor(sf::Color::Cyan);
            lblKillnum.setOutlineColor(sf::Color::White);
            lblKillnum.setOutlineThickness(3);


            sf::Text lblKill;
            lblKill.setCharacterSize(40);
            lblKill.setPosition({ 870 ,60 });
            lblKill.setFont(SLUG);
            lblKill.setString(std::to_string(KILL));
            lblKill.setFillColor(sf::Color::Cyan);
            lblKill.setOutlineColor(sf::Color::White);
            lblKill.setOutlineThickness(3);

            bool endstate2 = false;
            int  hpEnemy = 20;
            //const float gravitySpeed = 10;*/
            while (window.isOpen())
            {
                lblHP.setString(std::to_string((player->getHP())));
                lblKill.setString(std::to_string(KILL));

                int randomTime, r;
                srand(time(0));
                r = rand() % 3;
                randomTime = rand() % 2;

                deltaTime = clock.restart().asSeconds();
                if (deltaTime > 1.f / 40.f)
                    deltaTime = 1.f / 40.f;
                dt = clock1.restart().asSeconds();
                if (dt > 1.f / 40.f)
                    dt = 1.f / 40.f;
                dti = clock2.restart().asSeconds();
                if (dti > 1.f / 40.f)
                    dti = 1.f / 40.f;
                /*if (deltaTime > 1.0f / 20.0f)
                    deltaTime = 1.0f / 20.0f;*/

                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed)
                        window.close();
                }
                //sf::Time cdEnemySpawn = cdEnemy.getElapsedTime();*/

                sf::Time cdShoot = clockShoot.getElapsedTime();
               // sf::Time cdUlti = clockUlti.getElapsedTime();
                sf::Time cdCdUltiValue = clockCdUltiValue.getElapsedTime();
                const float movespeed = 8;




               /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && indexUlti < 10 && ultivalue[indexUlti] == 0 && cdUltiValue == 1)
                {

                    ultimate[indexUlti].setPosition(player->getPosition().x + 40, player->getPosition().y - 80);
                    ultivalue[indexUlti] = 1;
                    cdUltiValue = 0;
                    sUlti.play();

                    indexUlti++;
                    if (indexUlti >= 10)
                        indexUlti = 0;
                }
                if (cdCdUltiValue.asSeconds() >= 10.0 && cdUltiValue == 0)
                {
                    clockCdUltiValue.restart();
                    cdUltiValue = 1;
                }*/


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && cdShoot.asSeconds() >= 0.2)
                {
                    clockShoot.restart();
                    sAtk.play();
                    if (player->getFaceRight() == true)
                        bulletPlayer.push_back(new bulletEnemy(&bulletTexture, 20.f, player->getPosition().x, player->getPosition().y, 2.0f, 0.0f, sf::Vector2f(4.5f, 1.0f)));
                    if (player->getFaceRight() == false)
                        bulletPlayer.push_back(new bulletEnemy(&bulletTexture, 20.f, player->getPosition().x, player->getPosition().y, -2.0f, 0.0f, sf::Vector2f(4.5f, 1.0f)));
                }




                //screenscroll
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 300;

                }
                else
                {
                    position.x = screenDimensions.x / 2;
                }
                if (position.x + 455 > 16208)
                {
                    position.x = 15753;
                }

                //bullet&Ultimate

               /* for (int l = 0; l <= 9; l++)
                {
                    ultimate[l].move(20.0f, 0.0f);
                    if (ultivalue[l] == 1)
                    {

                        ultivalue[l] = 0;
                    }
                }*/



                //Player

                if (player->getPosition().x < 40)
                {
                    player->setPosition(40, player->getPosition().y);
                }
                if (player->getPosition().x > 16104)
                {
                    player->setPosition(16104, player->getPosition().y);
                }
                for (auto* i : enemy)
                {
                    if (player->GetGlobalBounds().intersects(i->GetGlobalBounds()))
                    {
                        player->decreaseHP(1);
                    }
                }
                if (player->getHP() < 0)
                {
                    updateAndSaveScore(playerName, KILL);
                    player->setHP(0);
                    KILL = 0;

                    window.close();
                    page_number = 3;
                    break;


                }



                //Collision
                int temp = 0;

                for (auto* bullet : bulletPlayer)
                {
                    bullet->Update();
                    if (bullet->getPosition().x > player->getPosition().x + 620)
                    {

                        delete bulletPlayer.at(temp);
                        bulletPlayer.erase(bulletPlayer.begin() + temp);
                        --temp;
                    }
                    /*for (auto* i : enemy)
                    {
                        if (bullet->GetGlobalBounds().intersects(i->GetGlobalBounds()))
                        {
                                delete bulletPlayer.at(temp);
                        bulletPlayer.erase(bulletPlayer.begin() + temp);
                            --temp;
                        }
                    }*/

                    ++temp;
                }

                sf::Vector2f direction = sf::Vector2f(0, 0);
                for (auto* i : platforms)
                {
                    if (i->GetCollider().CheckCollision(player->GetCollider(), direction, 1.0f))
                    {
                        player->onCollision(direction);
                    }

                }
                sf::Vector2f direction1 = sf::Vector2f(0, 0);
                for (auto* j : platforms1)
                {
                    if (j->GetCollider().CheckCollision(player->GetCollider(), direction1, 1.0f))
                    {
                        player->onCollision(direction1);
                    }

                }
                player->Update(deltaTime);
                //enemyfly

                sf::Vector2f direction6 = sf::Vector2f(0, 0);
                for (auto* k : enemyfly)
                {
                    for (auto* i : platforms)
                    {
                        if (i->GetCollider().CheckCollision(k->GetCollider(), direction6, 1.0f))
                        {
                            k->onCollision(direction6);
                        }

                    }
                    sf::Vector2f direction7 = sf::Vector2f(0, 0);
                    for (auto* j : platforms1)
                    {
                        if (j->GetCollider().CheckCollision(k->GetCollider(), direction7, 1.0f))
                        {
                            k->onCollision(direction7);
                        }

                    }
                }
                int counter2 = 0;
                int counter8 = 0;

                for (auto* k : enemyfly)
                {
                    for (auto* bullet : bulletPlayer)
                    {

                        if (k->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {

                            bullet->setPosition(-50.f, -50.f);

                            if (randomTime == 0)
                            {
                                Items.push_back(new item(&itemEnemyFlyTexture, k->getPosition().x, k->getPosition().y + 10, sf::Vector2u(4, 1), 0.3f, "EnemyFly", sf::Vector2f(50.f, 50.f)));
                            }
                            if (randomTime == 1)
                            {
                                Items.push_back(new item(&itemEnemyFly2Texture, k->getPosition().x, k->getPosition().y + 10, sf::Vector2u(17, 1), 0.3f, "EnemyFly2", sf::Vector2f(75.f, 75.f)));
                                /*delete enemyfly.at(counter8);*/

                            }
                            k->setPosition(-50.f, -50.f);
                            /*enemyfly.erase(enemyfly.begin() + counter8);
                            counter8--;*/
                            KILL += 100;
                        }


                    }

                    if (k->getPosition().y < 100)
                    {

                        k->setPosition(k->getPosition().x, 100);

                    }
                    if (k->getPosition().y > 375)
                    {

                        k->setPosition(k->getPosition().x, 375);
                    }

                    /* counter8++;*/
                }



                for (auto* k : enemyfly)
                {
                    k->Update(dti);

                }




                //enemy
                sf::Vector2f direction2 = sf::Vector2f(0, 0);
                for (auto* k : enemy)
                {
                    for (auto* i : platforms)
                    {
                        if (i->GetCollider().CheckCollision(k->GetCollider(), direction2, 1.0f))
                        {
                            k->onCollision(direction2);
                        }

                    }
                    sf::Vector2f direction3 = sf::Vector2f(0, 0);
                    for (auto* j : platforms1)
                    {
                        if (j->GetCollider().CheckCollision(k->GetCollider(), direction3, 1.0f))
                        {
                            k->onCollision(direction3);
                        }

                    }
                }

                int counter = 0;
                int counter1 = 0;
                for (auto* i : enemy)
                {
                    for (auto* bullet : bulletPlayer)
                    {
                        if (i->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {
                            i->setHP(1, isBonus);
                            bullet->setPosition(-50.f, -50.f);



                        }
                        /*++counter1;*/
                    }



                }

                for (auto* i : enemy)
                {

                    i->Update(dt, player, &bulletEnemyTexture);

                    if (i->getHP() <= 0)
                    {
                        if (r == 1)
                        {
                            Items.push_back(new item(&itemTexture, i->getPosition().x, i->getPosition().y + 10, sf::Vector2u(5, 1), 0.3f, "NORMAL", sf::Vector2f(75.f, 75.f)));
                            delete enemy.at(counter);
                        }

                        enemy.erase(enemy.begin() + counter);
                        counter--;
                        KILL += 100;
                    }
                    counter++;
                }




                //boss
                int counter4 = 0;
                int itemCounter = 0;
                for (auto* j : boss)
                {
                    for (auto* bullet : bulletPlayer)
                    {

                        if (j->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {
                            j->setHP(1);
                            bullet->setPosition(-50.f, -50.f);




                        }


                    }

                }
                for (auto* i : boss)
                {

                    i->Update(dt, player);

                    if (i->getHP() <= 0)
                    {
                        Items.push_back(new item(&itemBossTexture, i->getPosition().x, i->getPosition().y + 10, sf::Vector2u(6, 1), 0.3f, "BOSS", sf::Vector2f(80.f, 80.f)));
                        delete boss.at(counter4);
                        boss.erase(boss.begin() + counter4);
                        counter4--;
                        KILL+=300;
                    }
                    counter4++;
                }


                for (auto* item : Items)
                {
                    item->Update(deltaTime);
                    if (player->GetGlobalBounds().intersects(item->GetGlobalBounds()))
                    {
                        if (item->getType() == "NORMAL")
                        {
                            sOk.play();
                            isBonus = true;
                            KILL += 50;
                            bonusTime.restart();
                        }
                        if (item->getType() == "EnemyFly")
                        {
                            sItem.play();
                            KILL += 85;
                        }
                        if (item->getType() == "EnemyFly2")
                        {
                            sCoin.play();
                            player->decreaseHP(-10);
                        }
                        else if (item->getType() == "BOSS")
                        {
                            endstate2 = true;
                        }
                        delete Items.at(itemCounter);
                        Items.erase(Items.begin() + itemCounter);
                        itemCounter--;
                    }
                    itemCounter++;
                }
                if (endstate2 == true)
                {
                    page_number = 2;
                    window.close();
                    break;
                }





                if (player->getPosition().x > window.getSize().x / 2.f - 300 && player->getPosition().x < 6600 - window.getSize().x / 2.f)
                    view.setCenter(player->getPosition().x + 300, window.getSize().y / 2.f);


                //life move
               /* if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 695;
                    //life1.setPosition(position.x, 10);
                   // life1.setPosition(view.getCenter().x - 300 + 695, 10);
                }

                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 645;
                    //life2.setPosition(position.x, 10);
                    //life2.setPosition(view.getCenter().x - 300 + 645, 10);
                }

                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 595;
                    //life3.setPosition(position.x, 10);
                   // life3.setPosition(view.getCenter().x - 300 + 595, 10);
                }*/

                //Hp move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 90;
                    //lblHP.setPosition(position.x, 10);
                    lblHP.setPosition(view.getCenter().x - 500 - 90, 10);
                }
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 150;
                    //lblHPnum.setPosition(position.x, 10);
                    lblHPnum.setPosition(view.getCenter().x - 500 - 150, 10);
                }
                //Kill Move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 695;
                    //lblKill.setPosition(position.x, 60);
                    lblKill.setPosition(view.getCenter().x - 100 + 695, 10);
                }
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 605;
                    //lblKillnum.setPosition(position.x, 60);
                    lblKillnum.setPosition(view.getCenter().x - 100 + 575, 10);
                }
                //cdUlti move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 150;
                    cdUltimate.setPosition(position.x, 600);
                }

                //Item timer update
                if (bonusTime.getElapsedTime().asSeconds() >= 5.f)
                {
                    isBonus = false;
                }

                window.clear();

                window.setView(view);



                window.draw(bImage);

                /*for (auto* j : platforms1)
                {
                    j->Draw(window);
                }*/
                


                /* if (cdUltiValue == 1)
                {
                    window.draw(cdUltimate);
                }*/


                for (auto* i : platforms)
                {
                    i->Draw(window);
                }
                /*window.draw(life1);
                window.draw(life2);
                window.draw(life3);*/
                window.draw(lblHPnum);
                window.draw(lblHP);
                window.draw(lblKill);
                window.draw(lblKillnum);
                for (auto* i : boss)
                    i->Draw(window);


                player->Draw(window);
                for (auto* item : Items)
                    item->Render(window);

                for (auto* bullet : bulletPlayer)
                    bullet->Render(window);
                /*for (int k = 0; k <= 9; k++)
                {
                    window.draw(ultimate[k]);
                }*/
                for (auto* i : enemy)
                {
                    i->Draw(window);
                }

                for (auto* k : enemyfly)
                {
                    k->Draw(window);
                }

                window.setView(window.getDefaultView());
                window.display();

            }

        }
        if (page_number == 2)
        {
            sf::RectangleShape platform1;
            platform1.setSize(sf::Vector2f(400.0f, 50.0f));
            sf::Texture platform1Texture;
            platform1Texture.loadFromFile("platform.PNG");
            platform1.setTexture(&platform1Texture);
            platform1.setPosition(300.0f, 275.0f);




            sf::RectangleShape platform6;
            platform6.setSize(sf::Vector2f(300.0f, 50.0f));
            sf::Texture platform6Texture;
            platform6Texture.loadFromFile("Player/platforBoss.png");
            platform6.setTexture(&platform1Texture);
            platform6.setPosition(8500.0f, 275.0f);



            std::vector<Platform*> platforms;
            std::vector<Platform*> platforms1;

            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(330.0f, 3.0f), sf::Vector2f(270.0f, 370.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(640.0f, 3.0f), sf::Vector2f(1050.0f, 420.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(430.0f, 3.0f), sf::Vector2f(2100.0f, 410.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(140.0f, 3.0f), sf::Vector2f(2800.0f, 470.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(140.0f, 3.0f), sf::Vector2f(3220.0f, 470.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(360.0f, 3.0f), sf::Vector2f(4675.0f, 370.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(640.0f, 3.0f), sf::Vector2f(5490.0f, 420.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(390.0f, 3.0f), sf::Vector2f(6561.0f, 420.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(140.0f, 3.0f), sf::Vector2f(7230.0f, 470.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(140.0f, 3.0f), sf::Vector2f(7655.0f, 470.0f)));
            platforms.push_back(new Platform(&platform6Texture, sf::Vector2f(80.0f, 3300.0f), sf::Vector2f(3715.0f, 470.0f)));
          










            //ground&ceiling
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(80000.0f, 100.0f), sf::Vector2f(500.0f, -80.0f)));
            platforms1.push_back(new Platform(nullptr, sf::Vector2f(80000.0f, 10.0f), sf::Vector2f(258 * 3.0f, 650.0f)));
   






            sf::Vector2i screenDimensions(1520, 720);
            sf::RenderWindow window;
            window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "63010930_Stage3", sf::Style::Close);





            sf::Music music;
            music.openFromFile("sound/metalslug3.wav");
            music.setVolume(25.0);
            music.play();

            sf::SoundBuffer soundulti, soundJump, soundAttack;
            soundulti.loadFromFile("UltimateSound.wav");
            soundJump.loadFromFile("JumpSOUND.wav");
            soundAttack.loadFromFile("attack.ogg");
            sf::Sound sUlti, sJump, sAtk;
            sUlti.setBuffer(soundulti);
            sJump.setBuffer(soundJump);
            sAtk.setBuffer(soundAttack);
            sUlti.setVolume(15.0);
            sJump.setVolume(15.0);
            sAtk.setVolume(15.0);


            sf::Texture bTexture;
            sf::Sprite bImage;

            bTexture.loadFromFile("background/background3.png");
            bImage.setTexture(bTexture);
            bImage.setScale(3.5f, (float)screenDimensions.y / bTexture.getSize().y);

            sf::View view;
            view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
            view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

            sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);

            /*sf::CircleShape life1;
            life1.setRadius(20.0f);
            sf::Texture Life1Texture;
            Life1Texture.loadFromFile("life.png");
            life1.setTexture(&Life1Texture);
            life1.setPosition(850, 10);


            sf::CircleShape life2;
            life2.setRadius(20.0f);
            sf::Texture Life2Texture;
            Life2Texture.loadFromFile("life.png");
            life2.setTexture(&Life2Texture);
            life2.setPosition(800, 10);

            sf::CircleShape life3;
            life3.setRadius(20.0f);
            sf::Texture Life3Texture;
            Life3Texture.loadFromFile("life.png");
            life3.setTexture(&Life3Texture);
            life3.setPosition(750, 10);*/


            //ultimate
            /*int ultivalue[10] = {};
            sf::Clock clockUlti;
            sf::CircleShape ultimate[10];
            sf::Texture ultimateTexture;
            ultimateTexture.loadFromFile("ultimate.png");
            for (int k = 0; k <= 9; k++)
            {
                ultimate[k].setRadius(80.0f);
                ultimate[k].setTexture(&ultimateTexture);
                ultimate[k].setPosition(10000000.0f, 100000000000.0f);
            }
            int indexUlti = 0;*/


            //bulletTexture
            sf::Clock clockShoot;

            sf::Texture bulletTexture;
            bulletTexture.loadFromFile("bullet3.png");



            window.setFramerateLimit(60);

            //player
            sf::Texture playerTexture;
            playerTexture.loadFromFile("Player/playersheet.png");
            Player* player;
            player = new Player(&playerTexture, sf::Vector2u(8, 5), 0.09f, 600.0f, 300.0f);
            player->setPosition(10, 150);
            float deltaTime = 0.0f;
            sf::Clock clock;
            bool isBonus = false;

          
         


            //boss
            std::vector<BossState3*> boss;
            sf::Texture bossTexture;
            bossTexture.loadFromFile("boss/copter.png");
            boss.push_back(new BossState3(&bossTexture, sf::Vector2u(7, 3), 0.2f, 300.0f, sf::Vector2f(1200, 300.0f)));




            //bullet 
            std::vector<bulletEnemy*> bulletPlayer;

            //bulletEnemy
            sf::Texture bulletEnemyTexture;
            bulletEnemyTexture.loadFromFile("bulletenemy2.png");







            //Item 
            std::vector<item*> Items;
            sf::Texture itemTexture;
            sf::Texture itemBossTexture;
            sf::Texture itemEnemyFlyTexture;
            sf::Texture itemEnemyFly2Texture;

            itemEnemyFlyTexture.loadFromFile("item/heavymachine.png");
            itemEnemyFly2Texture.loadFromFile("item/coin.png");
            itemTexture.loadFromFile("item/chicken.png");
            itemBossTexture.loadFromFile("item/chest.png");
            sf::Clock bonusTime;





            //Hptext

            sf::Font SLUG;
            SLUG.loadFromFile("font/metalslug.ttf");


            sf::Text lblHPnum;
            lblHPnum.setCharacterSize(40);
            lblHPnum.setPosition({ 10 ,10 });
            lblHPnum.setFont(SLUG);
            lblHPnum.setString("HP");
            lblHPnum.setFillColor(sf::Color::Red);
            lblHPnum.setOutlineColor(sf::Color::Yellow);
            lblHPnum.setOutlineThickness(3);;

            sf::Text lblHP;
            lblHP.setCharacterSize(40);
            lblHP.setPosition({ 70 ,10 });
            lblHP.setFont(SLUG);
            lblHP.setString(std::to_string(player->getHP()));
            lblHP.setFillColor(sf::Color::Red);
            lblHP.setOutlineColor(sf::Color::Yellow);
            lblHP.setOutlineThickness(3);


            //killtext
            sf::Text lblKillnum;
            lblKillnum.setCharacterSize(40);
            lblKillnum.setPosition({ 750 ,60 });
            lblKillnum.setFont(SLUG);
            lblKillnum.setString("Score");
            lblKillnum.setFillColor(sf::Color::Cyan);
            lblKillnum.setOutlineColor(sf::Color::White);
            lblKillnum.setOutlineThickness(3);


            sf::Text lblKill;
            lblKill.setCharacterSize(40);
            lblKill.setPosition({ 870 ,60 });
            lblKill.setFont(SLUG);
            lblKill.setString(std::to_string(KILL));
            lblKill.setFillColor(sf::Color::Cyan);
            lblKill.setOutlineColor(sf::Color::White);
            lblKill.setOutlineThickness(3);

            int hpenemy = 2;



            //const float gravitySpeed = 10;*/
            while (window.isOpen())
            {
                lblHP.setString(std::to_string((player->getHP())));
                lblKill.setString(std::to_string(KILL));

                int randomTime, r;
                srand(time(0));
                r = rand() % 3;
                randomTime = rand() % 2;

                deltaTime = clock.restart().asSeconds();
                if (deltaTime > 1.f / 40.f)
                    deltaTime = 1.f / 40.f;

                /*if (deltaTime > 1.0f / 20.0f)
                    deltaTime = 1.0f / 20.0f;*/

                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed)
                        window.close();
                }
                //sf::Time cdEnemySpawn = cdEnemy.getElapsedTime();*/

                sf::Time cdShoot = clockShoot.getElapsedTime();
               // sf::Time cdUlti = clockUlti.getElapsedTime();

                const float movespeed = 8;




                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && cdShoot.asSeconds() >= 0.2)
                {
                    clockShoot.restart();
                    sAtk.play();
                    if (player->getFaceRight() == true)
                        bulletPlayer.push_back(new bulletEnemy(&bulletTexture, 20.f, player->getPosition().x, player->getPosition().y, 1.0f, 0.0f, sf::Vector2f(1.f, 1.0f)));
                    if (player->getFaceRight() == false)
                        bulletPlayer.push_back(new bulletEnemy(&bulletTexture, 20.f, player->getPosition().x, player->getPosition().y, -1.0f, 0.0f, sf::Vector2f(1.f, 1.0f)));
                }




                //screenscroll
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 300;

                }
                else
                {
                    position.x = screenDimensions.x / 2;
                }
                if (position.x + 455 > 16208)
                {
                    position.x = 15753;
                }

                //bullet&Ultimate





                //Player

                if (player->getPosition().x < 40)
                {
                    player->setPosition(40, player->getPosition().y);
                }
                if (player->getPosition().x > 16104)
                {
                    player->setPosition(16104, player->getPosition().y);
                }
                for (auto* i : boss)
                {
                    if (player->GetGlobalBounds().intersects(i->GetGlobalBounds()))
                    {
                        player->decreaseHP(1);
                    }
                }

               if (player->getHP() < 0)
                {
                    // end game over fail

                    updateAndSaveScore(playerName, KILL);

                    player->setHP(0);
                    KILL = 0;

                    window.close();
                    page_number = 3;
                    break;


                }



                //Collision
                int temp = 0;

                for (auto* bullet : bulletPlayer)
                {
                    bullet->Update();
                    if (bullet->getPosition().x > player->getPosition().x + 620)
                    {

                        delete bulletPlayer.at(temp);
                        bulletPlayer.erase(bulletPlayer.begin() + temp);
                        --temp;
                    }


                    ++temp;
                }

                sf::Vector2f direction = sf::Vector2f(0, 0);
                for (auto* i : platforms)
                {
                    if (i->GetCollider().CheckCollision(player->GetCollider(), direction, 1.0f))
                    {
                        player->onCollision(direction);
                    }

                }
                sf::Vector2f direction1 = sf::Vector2f(0, 0);
                for (auto* j : platforms1)
                {
                    if (j->GetCollider().CheckCollision(player->GetCollider(), direction1, 1.0f))
                    {
                        player->onCollision(direction1);
                    }

                }
                player->Update(deltaTime);


                //boss
                sf::Vector2f direction11 = sf::Vector2f(0, 0);
                for (auto* k : boss)
                {


                    for (auto* j : platforms1)
                    {
                        if (j->GetCollider().CheckCollision(k->GetCollider(), direction11, 1.0f))
                        {
                            k->onCollision(direction11);
                        }

                    }
                }
                int counter4 = 0;
                int itemCounter = 0;
                for (auto* j : boss)
                {
                    for (auto* bullet : bulletPlayer)
                    {

                        if (j->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
                        {
                            j->setHP(1);
                            bullet->setPosition(-50.f, -50.f);




                        }


                    }

                }
                for (auto* i : boss)
                {

                    i->Update(deltaTime, player);

                    if (i->getHP() <= 0)
                    {
                        Items.push_back(new item(&itemBossTexture, i->getPosition().x, i->getPosition().y + 10, sf::Vector2u(6, 1), 0.3f, "BOSS", sf::Vector2f(100.f, 100.f)));
                        delete boss.at(counter4);
                        boss.erase(boss.begin() + counter4);
                        counter4--;
                        KILL+=500;
                    }
                    counter4++;
                }



                for (auto* item : Items)
                {
                    item->Update(deltaTime);
                    if (player->GetGlobalBounds().intersects(item->GetGlobalBounds()))
                    {
                        if (item->getType() == "BOSS")
                        {

                        }
                        delete Items.at(itemCounter);
                        Items.erase(Items.begin() + itemCounter);
                        itemCounter--;
                    }
                    itemCounter++;
                }





                if (player->getPosition().x > window.getSize().x / 2.f - 300 && player->getPosition().x < 3400 - window.getSize().x / 2.f)
                    view.setCenter(player->getPosition().x + 300, window.getSize().y / 2.f);


                /*//life move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 695;
                    //life1.setPosition(position.x, 10);
                  //  life1.setPosition(view.getCenter().x - 300 + 695, 10);
                }

                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 645;
                    //life2.setPosition(position.x, 10);
                   // life2.setPosition(view.getCenter().x - 300 + 645, 10);
                }

                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 595;
                    //life3.setPosition(position.x, 10);
                   // life3.setPosition(view.getCenter().x - 300 + 595, 10);
                }*/

                //Hp move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 90;
                    //lblHP.setPosition(position.x, 10);
                    lblHP.setPosition(view.getCenter().x - 500 - 90, 10);
                }
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x - 150;
                    //lblHPnum.setPosition(position.x, 10);
                    lblHPnum.setPosition(view.getCenter().x - 500 - 150, 10);
                }
                //Kill Move
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 695;
                    //lblKill.setPosition(position.x, 60);
                    lblKill.setPosition(view.getCenter().x - 100 + 695, 10);
                }
                if (player->getPosition().x + 300 > screenDimensions.x / 2)
                {
                    position.x = player->getPosition().x + 605;
                    //lblKillnum.setPosition(position.x, 60);
                    lblKillnum.setPosition(view.getCenter().x - 100 + 575, 10);
                }


                //Item timer update
                if (bonusTime.getElapsedTime().asSeconds() >= 5.f)
                {
                    isBonus = false;
                }

                window.clear();

                window.setView(view);

                for (auto* j : platforms1)
                {
                    j->Draw(window);
                }

                window.draw(bImage);




                /* if (cdUltiValue == 1)
                {
                    window.draw(cdUltimate);
                }*/


                /*for (auto* i : platforms)
                {
                    i->Draw(window);
                }*/
               /* window.draw(life1);
                window.draw(life2);
                window.draw(life3);*/
                window.draw(lblHPnum);
                window.draw(lblHP);
                window.draw(lblKill);
                window.draw(lblKillnum);
                for (auto* i : boss)
                    i->Draw(window);


                player->Draw(window);
                for (auto* item : Items)
                    item->Render(window);

                for (auto* bullet : bulletPlayer)
                    bullet->Render(window);
               /* for (int k = 0; k <= 9; k++)
                {
                    window.draw(ultimate[k]);
                }*/




                window.setView(window.getDefaultView());
                window.display();

            }

        }
        else if (page_number == 3)
        {
            sf::RenderWindow window(sf::VideoMode(1520, 720), "63010930_END", sf::Style::Close);
            RestartMenu RestartMenu(window.getSize().x, window.getSize().y);
            sf::Texture texture;
            if (!texture.loadFromFile("background/background main.png"));
            {
                //handle error
            }
            sf::Sprite background;
            background.setTexture(texture);
            bool close = false;


            sf::Font SLUG;
            SLUG.loadFromFile("font/metalslug.ttf");

            




            while (window.isOpen())
            {

                sf::Event event;
                while (window.pollEvent(event))
                {
                    switch (event.type)
                    {
                    case sf::Event::KeyReleased:
                        switch (event.key.code)
                        {
                        case sf::Keyboard::Up:
                            RestartMenu.MoveUp();
                            break;
                        case sf::Keyboard::Down:
                            RestartMenu.MoveDown();
                            break;
                        case sf::Keyboard::Return:
                            switch (RestartMenu.GetPressedItem())
                            {
                            case 0:

                                page_number = 0;
                                window.close();

                                break;


                            case 1:

                                window.close();
                                return 0;
                                break;

                            }
                        }
                    }
                }
                if (page_number == 0)
                {
                    window.close();

                    break;
                }
                /* if (page_number  == 5)
                 {
                     window.close();

                     break;
                 }*/

                window.clear();
                window.draw(background);
                RestartMenu.draw(window);
                window.display();
            }


        }
       
    }


    
    return 0;
}

void updateAndSaveScore(std::string playerName, int KILL)
{

    typedef struct NameWithScore {
        std::string name;
        int score;
    } NameWithScore;

    auto compareScores = [](NameWithScore p_1, NameWithScore p_2) {
        return p_1.score > p_2.score;
    };

    std::vector<NameWithScore> namesWithScore;

    NameWithScore currentPlayer;
    currentPlayer.name = playerName;
    currentPlayer.score = KILL;

    namesWithScore.push_back(currentPlayer);

    std::ifstream ifs("score/score.txt");

    if (ifs.is_open())
    {
        std::string playerName1 = "";
        std::string playerScore = "";

        while (ifs >> playerName1 >> playerScore)
        {

            std::cout << playerName1 << std::endl << playerScore << std::endl;
            NameWithScore temp;
            temp.name = playerName1;
            temp.score = std::stoi(playerScore);
            namesWithScore.push_back(temp);
        }


    }

    ifs.close();

    std::sort(namesWithScore.begin(), namesWithScore.end(), compareScores);

    while (namesWithScore.size() > 5) {
        namesWithScore.pop_back();
    }

    std::fstream ofs;

    ofs.open("score/score.txt", std::ios::out | std::ios::trunc);

    for (auto nameWithScore : namesWithScore) {
        std::cout << "write "<<nameWithScore.name << std::endl << nameWithScore.score<< std::endl;

        ofs << nameWithScore.name + "\t" + std::to_string(nameWithScore.score) + "\n";
    }

    ofs.close();
}
