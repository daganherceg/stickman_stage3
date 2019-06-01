#include "stage3dialog.h"
#include "collision.h"
#include "debugrenderer.h"
//#include "game.h"
//#include "stagefactory.h"

#include <iostream>

Stage3Dialog::Stage3Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout) :
    Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), constantVelocity(2), currentLevel(1), maxLevel(2), levelComplete(false)
{
}

void Stage3Dialog::released(QKeyEvent &event) {
    // TODO clean this up. This functionality dosnt all need be here
    if (event.key() == Qt::Key_Right) {
        background.setVelocity(0);
        for (auto const& obs : obstacles) {
            obs->setVelocity(1);
        }
    } else if (event.key() == Qt::Key_Left) {
        background.setVelocity(0);
        for (auto const& obs : obstacles) {
            obs->setVelocity(1);
        }
    }
}

void Stage3Dialog::input(QKeyEvent &event) {
    handleMovement(event);
    stickman->handleInput(event);
}

void Stage3Dialog::handleMovement(QKeyEvent &event) {
    // TODO handle both held at same time
    if (event.key() == Qt::Key_Right) {
        background.setVelocity(4);
        for (auto const& obs : obstacles) {
            obs->setVelocity(4);
        }
        Stage2Dialog::distanceToSpawn = Stage2Dialog::distanceToSpawn -= 1;
    } else if (event.key() == Qt::Key_Left) {
        background.setVelocity(-4);
        for (auto const& obs : obstacles) {
            obs->setVelocity(0);
        }
    }
    int x = stickman->getCoordinate().getXCoordinate();


    // TODO Move this functionality into the GAME ??
    // getCurrentLevel... al that jazz

    if (x <= 0) {
        counter = 0;
        std::cout << "LOST" << std::endl;
    }
    if (x >= game.width()) {
        levelComplete = true;
    }

    if (currentLevel >= maxLevel && levelComplete) {
        // TODO add winning logic.. Probably use state for this??
        std::cout << "WINNER!!" << std::endl;
    } else if (levelComplete) {
        std::cout << "LEVEL COMPLETE" << std::endl;
        nextObstacle = 0;
        levelComplete = false;

        int i = 0;
        while (i < currentLevel * 1000) {
            score.increment();
            i++;
        }
        currentLevel++;
    }
}

void Stage3Dialog::update() {
    stickman->update(obstacles);
    if (!stickman->isColliding()) {
        // Reduce distance to next obstacle
        distanceToSpawn -= constantVelocity;
        background.update();
        speedUp(unsigned(counter));
    }
    if (nextObstacle + 1 < int(obstacleLayout.size())) {
        Stage2Dialog::spawnObstacles(unsigned(counter));
    }
    if (nextObstacle + 1 == int(obstacleLayout.size()) && int(obstacles.size()) == 0) {
        levelComplete = true;
    }

    for (auto &c : clouds) {
        c->collisionLogic(*stickman);
    }

    for (auto &o : obstacles) {
        o->collisionLogic(*stickman);
    }
}

void Stage3Dialog::render(Renderer &renderer) {
    if (counter == 0) background.setVelocity(0);

    // TODO Overwritten
    renderBackground(renderer, unsigned(counter));
    renderObstacles(renderer, unsigned(counter));

    // Only render on even counters when velocity = 0
    if (background.getVelocity() == 0) {
        if (counter/5 % 2 == 0) {
            stickman->render(renderer, unsigned(counter));
        } else {
            stickman->render(renderer, unsigned(counter*5*2));
        }
    } else {
        stickman->render(renderer, unsigned(counter));
    }

    score.render(renderer);
    counter++;
}

void Stage3Dialog::renderObstacles(Renderer &renderer, unsigned int counter) {
    // TODO Overwritten
    bool deleteObstacle = false;
    for (auto &o: obstacles) {
        o->render(renderer, counter);
        if (o->getCoordinate().getQtRenderingXCoordinate() + o->width() < 0) {

            // Increment score when marked for deletion
            deleteObstacle = true;

            int i = 0;
            while (i < 100) {
                score.increment();
                i++;
            }
        }
    }
    if (deleteObstacle) {
        obstacles.erase(obstacles.begin());
    }
}
