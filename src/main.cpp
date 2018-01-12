#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

// include of game rules etc.
#include "tictactoe.h"

// include of minimax AI
#include "minimax.h"


int main()
{
    // rand needed to background
    srand(time(NULL));

    // file var
    std::fstream config;
    // config open and create
    config.open("config.ini", std::ios::in | std::ios::out);
    if(config.good()==false){
        std::cout << "Config saved to config.ini in program directory! \n";
        std::ofstream tmp("config.ini");
        tmp << 1 << std::endl;
        tmp << 1 << std::endl;
        tmp << 3 << std::endl;
        tmp << 3 << std::endl;
        tmp.close();
        config.open("config.ini", std::ios::in | std::ios::out);
    }

    // set loaded config
    std::string tmp = {1, 1};
    int opponents[2];
    int field = 3, terms = 3;

    sf::Clock clock; // handle game time

    int crazytick = 1;
    int turn = 1;
    int whowin = 0;
    int** state;
    int actualState;

    int randomPosx = rand()%16;
    int randomPosy = rand()%4;

    config >> opponents[0];
    config >> opponents[1];
    config >> field;
    config >> terms;

    // object of game class
    ticTacToe game(field, terms);
    if(opponents[0]==1 && opponents[1]==1)
        game.setPlayers('p','p');
    if(opponents[0]==2 && opponents[1]==1)
        game.setPlayers('m','p');
    if(opponents[0]==1 && opponents[1]==2)
        game.setPlayers('p','m');
    if(opponents[0]==2 && opponents[1]==2)
        game.setPlayers('m','m');
    // close file
    config.close();

    // creates window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tic Tac Toe by. MichalF V1");

    // defining txt objects (just txt)
    sf::Texture txtTile, txtOtile, txtXtile, txtStartoff, txtStarton, txtSign, txtCreated, txtSettingsoff, txtSettingson, txtExitoff, txtExiton, txtTileoff, txtTilebig, txtXtilebig, txtOtilebig, txtBackground, txtTic, txtTac, txtToe;
    // defining txt objects for settings
    sf::Texture txtVs, txtPlayer, txtMinmax, txtSizeoffield, txtTermsofwin, txt3x3, txt4x4, txt5x5, txt6x6, txt3inline, txt4inline, txt5inline, txt6inline, txtSave, txtBack;
    // defining txt for result
    sf::Texture txtXwin, txtOwin, txtDraw;

    // loading textures from files
    txtTile.loadFromFile("textures/tile.png");
    txtTilebig.loadFromFile("textures/tilebig.png");
    txtTileoff.loadFromFile("textures/tileoff.png");
    txtOtilebig.loadFromFile("textures/otilebig.png");
    txtXtilebig.loadFromFile("textures/xtilebig.png");
    txtOtile.loadFromFile("textures/otile.png");
    txtXtile.loadFromFile("textures/xtile.png");

    txtStartoff.loadFromFile("textures/startoff.png");
    txtStarton.loadFromFile("textures/starton.png");
    txtSettingsoff.loadFromFile("textures/settingsoff.png");
    txtSettingson.loadFromFile("textures/settingson.png");
    txtExitoff.loadFromFile("textures/exitoff.png");
    txtExiton.loadFromFile("textures/exiton.png");

    txtBackground.loadFromFile("textures/background.png");
    txtTic.loadFromFile("textures/tic.png");
    txtTac.loadFromFile("textures/tac.png");
    txtToe.loadFromFile("textures/toe.png");
    txtSign.loadFromFile("textures/sign.png");
    txtCreated.loadFromFile("textures/created.png");

    // more textures.. for settings
    txtVs.loadFromFile("textures/vs.png");
    txtPlayer.loadFromFile("textures/player.png");
    txtMinmax.loadFromFile("textures/minmax.png");
    txtSizeoffield.loadFromFile("textures/sizeoffield.png");
    txtTermsofwin.loadFromFile("textures/termsofwin.png");
    txtSave.loadFromFile("textures/save.png");
    txtBack.loadFromFile("textures/back.png");

    txt3x3.loadFromFile("textures/3x3.png");
    txt4x4.loadFromFile("textures/4x4.png");
    txt5x5.loadFromFile("textures/5x5.png");
    txt6x6.loadFromFile("textures/6x6.png");

    txt3inline.loadFromFile("textures/3inline.png");
    txt4inline.loadFromFile("textures/4inline.png");
    txt5inline.loadFromFile("textures/5inline.png");
    txt6inline.loadFromFile("textures/6inline.png");

    // textures of result
    txtXwin.loadFromFile("textures/xwin.png");
    txtOwin.loadFromFile("textures/owin.png");
    txtDraw.loadFromFile("textures/draw.png");

    // tail object, can be empty, X or O
    sf::Sprite objTile(txtTile);
    sf::Sprite objTilebig(txtTilebig);
    sf::Sprite objTileoff(txtTileoff);

    // only for main menu, on game scene objTile change its texture
    sf::Sprite objOtile(txtOtile);
    sf::Sprite objXtile(txtXtile);
    sf::Sprite objOtilebig(txtOtilebig);
    sf::Sprite objXtilebig(txtXtilebig);
    sf::Sprite objBackground(txtBackground);
    sf::Sprite objTictactoe(txtTic);

    // objects which can change texture
    sf::Sprite objStart(txtStartoff);
    sf::Sprite objSettings(txtSettingsoff);
    sf::Sprite objExit(txtExitoff);

    // author objects
    sf::Sprite objSign(txtSign);
    sf::Sprite objCreated(txtCreated);

    // settings objects
    sf::Sprite objVs(txtVs);
    sf::Sprite objFirstplayer(txtPlayer);
    sf::Sprite objSecondplayer(txtPlayer);
    sf::Sprite objSizeoffield(txtSizeoffield);
    sf::Sprite objTermsofwin(txtTermsofwin);
    sf::Sprite objSave(txtSave);
    sf::Sprite objBack(txtBack);
    sf::Sprite objField(txt3x3);
    sf::Sprite objInline(txt3inline);

    // result objects
    sf::Sprite objXwin(txtXwin);
    sf::Sprite objOwin(txtOwin);
    sf::Sprite objDraw(txtDraw);


    // ######## options for switch function
    
    char scene; // m, p, s..
    scene = 'm';


    // ######## things for main menu

    int** mainMenu = new int*[20];
    for(int i=0; i<10; i++){
        mainMenu[i] = new int[20];
    }

    int* tilePosition = new int[20];
    for(int i=0; i<20; i++){
        tilePosition[i]=i*50;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch(scene){
            //
// CASE OF MAIN MENU ######################################################
            //
            case 'm':
            {
                window.clear();

                // white tiles loop
                for(int i=0; i<20; i++){
                    for(int j=0; j<20; j++){
                        objTile.setPosition(tilePosition[j], tilePosition[i]);
                        window.draw(objTile);
                    }
                }
                // background
                window.draw(objBackground);

                sf::Time elapsed = clock.getElapsedTime();
                if(elapsed.asSeconds()>0.8f){
                    randomPosx = rand()%16;
                    randomPosy = rand()%4;
                    crazytick++;
                    elapsed = clock.restart();
                }
                if(crazytick==1){
                    objTictactoe.setTexture(txtTic);
                    objTictactoe.setPosition(tilePosition[randomPosx], tilePosition[randomPosy]);
                }
                if(crazytick==2){
                    objTictactoe.setTexture(txtTac);
                    objTictactoe.setPosition(tilePosition[randomPosx], tilePosition[randomPosy]);
                }
                if(crazytick==3){
                    objTictactoe.setTexture(txtToe);
                    objTictactoe.setPosition(tilePosition[randomPosx], tilePosition[randomPosy]);
                }
                window.draw(objTictactoe);
                if(crazytick==4) crazytick=1;

                // signature
                objCreated.setPosition(tilePosition[0], tilePosition[10]);
                window.draw(objCreated);

                // loading choosable options

                // start
                objStart.setPosition(tilePosition[8], tilePosition[12]);
                window.draw(objStart);
                // for this ^
                    objStart.setTexture(txtStartoff);
                if(objStart.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        scene = 'p';
                        sf::sleep(sf::milliseconds(300));
                    }
                    objStart.setTexture(txtStarton);
                }

                // settings
                objSettings.setPosition(tilePosition[8], tilePosition[14]);
                window.draw(objSettings);
                // for this ^
                    objSettings.setTexture(txtSettingsoff);
                if(objSettings.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        scene = 's';
                    }
                    objSettings.setTexture(txtSettingson);
                }

                // quit
                objExit.setPosition(tilePosition[8], tilePosition[16]);
                window.draw(objExit);
                // for this ^
                    objExit.setTexture(txtExitoff);
                if(objExit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        scene = 'e';
                    }
                    objExit.setTexture(txtExiton);
                }

                

                window.display(); 
            }
            break;
            //
// CASE OF SETTINGS ######################################################
            //
            case 's':
            {
                window.clear();
                // white tiles loop
                for(int i=0; i<20; i++){
                    for(int j=0; j<20; j++){
                        objTile.setPosition(tilePosition[j], tilePosition[i]);
                        window.draw(objTile);
                    }
                }

                // loading choosable options

                // vs tile
                objVs.setPosition(tilePosition[8], tilePosition[3]);
                window.draw(objVs);

                // first player
                objFirstplayer.setPosition(tilePosition[1], tilePosition[2]);
                objFirstplayer.setRotation(0);
                // for this ^
                if(opponents[0] == 1){
                    objFirstplayer.setTexture(txtPlayer);
                }else{
                    objFirstplayer.setTexture(txtMinmax);
                }
                if(objFirstplayer.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        if(opponents[0]==1) opponents[0]=2;
                        else opponents[0]=1;
                        sf::sleep(sf::milliseconds(50));
                    }
                    objFirstplayer.setRotation(5);
                }
                window.draw(objFirstplayer);

                // second player
                objSecondplayer.setPosition(tilePosition[11], tilePosition[4]);
                objSecondplayer.setRotation(0);
                // for this ^
                if(opponents[1] == 1){
                    objSecondplayer.setTexture(txtPlayer);
                }else{
                    objSecondplayer.setTexture(txtMinmax);
                }
                if(objSecondplayer.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        if(opponents[1]==1) {opponents[1]=2;
                        sf::sleep(sf::milliseconds(50));}
                        else {opponents[1]=1;
                        sf::sleep(sf::milliseconds(50));}
                    }
                    objSecondplayer.setRotation(5);
                }
                window.draw(objSecondplayer);

                // field size text
                objSizeoffield.setPosition(tilePosition[1], tilePosition[6]);
                window.draw(objSizeoffield);

                // field size
                objField.setPosition(tilePosition[8], tilePosition[7]);
                objField.setRotation(0);
                // for this ^
                if(field == 3){
                    objField.setTexture(txt3x3);
                }else if(field == 4){
                    objField.setTexture(txt4x4);
                }else if(field == 5){
                    objField.setTexture(txt5x5);
                }else{
                    objField.setTexture(txt6x6);
                }
                if(objField.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        if(field==3) {field=4;
                        sf::sleep(sf::milliseconds(300));}
                        else if(field==4) {field=5;
                        sf::sleep(sf::milliseconds(300));}
                        else if(field==5) {field=6;
                        sf::sleep(sf::milliseconds(300));}
                        else if(field==6) {field=3;
                        sf::sleep(sf::milliseconds(300));}
                    }
                    objField.setRotation(5);
                }
                window.draw(objField);

                // terms text
                objTermsofwin.setPosition(tilePosition[1], tilePosition[9]);
                window.draw(objTermsofwin);

                // terms
                objInline.setPosition(tilePosition[8], tilePosition[10]);
                objInline.setRotation(0);
                // for this ^
                // if terms > field...
                if(terms>field) terms=field;

                if(terms == 3){
                    objInline.setTexture(txt3inline);
                }else if(terms == 4){
                    objInline.setTexture(txt4inline);
                }else if(terms == 5){
                    objInline.setTexture(txt5inline);
                }else if(terms == 6){
                    objInline.setTexture(txt6inline);
                }
                if(objInline.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        if(terms==3 && field>3) {terms=4;
                        sf::sleep(sf::milliseconds(300));}

                        else if(terms==4 && field>4) {terms=5;
                        sf::sleep(sf::milliseconds(300));}
                        else if(terms==4 && field<=4) {terms=3;
                        sf::sleep(sf::milliseconds(300));}

                        else if(terms==5 && field>5) {terms=6;
                        sf::sleep(sf::milliseconds(300));}
                        else if(terms==5 && field<=5) {terms=3;
                        sf::sleep(sf::milliseconds(300));}


                        else if(terms==6) {terms=3;
                        sf::sleep(sf::milliseconds(300));}


                    }
                    objInline.setRotation(5);
                }
                window.draw(objInline);

                // back
                objBack.setPosition(tilePosition[8], tilePosition[16]);
                objBack.setRotation(0);
                // for this ^
                if(objBack.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        scene = 'm';
                        sf::sleep(sf::milliseconds(300));
                    }
                    objBack.setRotation(5);
                }
                window.draw(objBack);

                // save
                objSave.setPosition(tilePosition[1], tilePosition[16]);
                objSave.setRotation(0);
                // for this ^
                if(objSave.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        config.open("config.ini", std::ios::out | std::ios::trunc);
                        config << opponents[0] << std::endl;
                        config << opponents[1] << std::endl;
                        config << field << std::endl;
                        config << terms << std::endl;
                        config.close();


                        if(opponents[0]==1 && opponents[1]==1)
                            game.setPlayers('p','p');
                        if(opponents[0]==2 && opponents[1]==1)
                            game.setPlayers('m','p');
                        if(opponents[0]==1 && opponents[1]==2)
                            game.setPlayers('p','m');
                        if(opponents[0]==2 && opponents[1]==2)
                            game.setPlayers('m','m');
                        game.reinit(field, terms);
                        sf::sleep(sf::milliseconds(300));
                    }
                    objSave.setRotation(5);
                }
                window.draw(objSave);

                // quit
                objExit.setPosition(tilePosition[15], tilePosition[18]);
                window.draw(objExit);
                // for this ^
                    objExit.setTexture(txtExitoff);
                if(objExit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        scene = 'e';
                    }
                    objExit.setTexture(txtExiton);
                }
                window.display(); 

            }
            break;
            //
// CASE OF PLAY ######################################################
            //
            case 'p':
            {
                window.clear();
                if(whowin==0){
                    // gray tiles loop
                    for(int i=0; i<20; i++){
                        for(int j=0; j<20; j++){
                            objTileoff.setPosition(tilePosition[j], tilePosition[i]);
                            window.draw(objTileoff);
                        }
                    }

                    state = game.getGameState();
                    
                    //
                    if(whowin==0){
                        for(int i=0; i<field; i++){
                            for(int j=0; j<field; j++){
                                if(state[i][j] == 0){
                                    objTilebig.setRotation(0);
                                    objTilebig.setPosition(tilePosition[j*3]+50, tilePosition[i*3]+50);
                                    if(objTilebig.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                                            actualState = game.checkState();
                                            if(turn%2!=0 && opponents[0]==1){
                                                game.player1move(i, j);
                                                actualState = game.checkState();
                                                ++turn;
                                                if(actualState==1){
                                                    whowin = 1;
                                                }
                                                if(actualState==2){
                                                    whowin = 2;
                                                }
                                                if(actualState==-1){
                                                    whowin = -1;
                                                }
                                            }else if(turn%2==0 && opponents[1]==1){
                                                game.player2move(i, j);
                                                actualState = game.checkState();
                                                ++turn;
                                                if(actualState==1){
                                                    whowin = 1;
                                                }
                                                if(actualState==2){
                                                    whowin = 2;
                                                }
                                                if(actualState==-1){
                                                    whowin = -1;
                                                }
                                            }
                                            sf::sleep(sf::milliseconds(300));
                                        }
                                        objTilebig.setRotation(5);
                                    }
                                    window.draw(objTilebig);
                                }
                                if(state[i][j] == 1){
                                    objXtilebig.setPosition(tilePosition[j*3]+50, tilePosition[i*3]+50);
                                    window.draw(objXtilebig);
                                }
                                if(state[i][j] == 2){
                                    objOtilebig.setPosition(tilePosition[j*3]+50, tilePosition[i*3]+50);
                                    window.draw(objOtilebig);
                                }
                            }
                        }
                    }
                    if(whowin==0){
                        if(turn%2!=0 && opponents[0]==2){
                            pcMove AI = findBestMove(game, 1);
                            game.player1move(AI.x, AI.y);
                            actualState = game.checkState();
                            ++turn;
                            if(actualState==1){
                                whowin = 1;
                            }
                            if(actualState==2){
                                whowin = 2;
                            }
                            if(actualState==-1){
                                whowin = -1;
                            }
                        }else if(turn%2==0 && opponents[1]==2){
                            pcMove AI = findBestMove(game, 2);
                            game.player2move(AI.x, AI.y);
                            actualState = game.checkState();
                            ++turn;
                            if(actualState==1){
                                whowin = 1;
                            }
                            if(actualState==2){
                                whowin = 2;
                            }
                            if(actualState==-1){
                                whowin = -1;
                            }
                        }
                    }




                    // back
                    objBack.setPosition(tilePosition[1], tilePosition[19]);
                    objBack.setRotation(0);
                    // for this ^
                    if(objBack.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            scene = 'm';
                            sf::sleep(sf::milliseconds(300));
                        }
                        objBack.setRotation(5);
                    }
                    window.draw(objBack);
                    // quit
                    objExit.setPosition(tilePosition[15], tilePosition[19]);
                    window.draw(objExit);
                    // for this ^
                        objExit.setTexture(txtExitoff);
                    if(objExit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            scene = 'e';
                        }
                        objExit.setTexture(txtExiton);
                    }
                    // terms
                    objInline.setPosition(tilePosition[4], tilePosition[0]);
                    objInline.setRotation(0);
                    // for this ^
                    // if terms > field...
                    if(terms>field) terms=field;

                    if(terms == 3){
                        objInline.setTexture(txt3inline);
                    }else if(terms == 4){
                        objInline.setTexture(txt4inline);
                    }else if(terms == 5){
                        objInline.setTexture(txt5inline);
                    }else if(terms == 6){
                        objInline.setTexture(txt6inline);
                    }
                    window.draw(objInline);
                }

                if(whowin!=0){
                    game.reinit(field, terms);
                    // back
                    objBack.setPosition(tilePosition[5], tilePosition[15]);
                    objBack.setRotation(0);
                    // for this ^
                    if(objBack.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            scene = 'm';
                            whowin = 0;
                            turn = 1;
                            sf::sleep(sf::milliseconds(300));
                        }
                        objBack.setRotation(5);
                    }
                    window.draw(objBack);
                }


                if(whowin==1){
                    window.draw(objXwin);
                }
                if(whowin==2){
                    window.draw(objOwin);
                }
                if(whowin==-1){
                    window.draw(objDraw);
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                    turn = 1;
                    whowin = 0;
                    game.reinit(field, terms);
                }

                
                window.display();
            }
            break;
            //
// CASE OF EXIT ######################################################
            //
            case 'e':
            {
                window.close();
            }
            break;
            default:
            break;
        }        
    }
    return 0;
}