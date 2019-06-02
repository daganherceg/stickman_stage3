#include "stage3dialog.h"
#include "collision.h"
#include "debugrenderer.h"

#include <iostream>

Stage3Dialog::Stage3Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout) :
    Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), constantVelocity(2), currentLevel(1), maxLevel(2), levelComplete(false), playerVelocity(4), obstacleVelocity(3), savedScore(0)
{
}

void Stage3Dialog::released(QKeyEvent &event) {
    // TODO clean this up. This functionality dosnt all need be here
    if (event.key() == Qt::Key_Right || event.key() == Qt::Key_Left) {
        background.setVelocity(0);
        for (auto const& obs : obstacles) {
            if (currentLevel == 1) {
                obs->setVelocity(0);
            } else {
                obs->setVelocity(obstacleVelocity);
            }
        }
    }
}

void Stage3Dialog::input(QKeyEvent &event) {
    handleMovement(event);
    stickman->handleInput(event);
}

void Stage3Dialog::handleMovement(QKeyEvent &event) {
    // Move @ player velocity + obstacle velocity
    if (event.key() == Qt::Key_Right) {
        moveRight();
    } else if (event.key() == Qt::Key_Left) {
        moveLeft();
    }

    int x = stickman->getCoordinate().getXCoordinate();

    // Pushed to left side of the screen
    if (x <= 0) {
        leftBoundaryCollision();
    }

    // Reached end of screen
    if (x >= game.width()) {
        rightBoundaryCollision();
    }

    if (currentLevel >= maxLevel && levelComplete) {
        win();
    } else if (levelComplete) {
        nextLevel();
    }
}

void Stage3Dialog::update() {
    stickman->update(obstacles);
    if (!stickman->isColliding()) {
        // Reduce distance to next obstacle
        distanceToSpawn -= constantVelocity;
        background.update();
        if (counter % 20 == 0) score.increment();
        speedUp(unsigned(counter));
    }
    if (nextObstacle + 1 < int(obstacleLayout.size())) {
        spawnObstacles(unsigned(counter));
    }

    int levelSize = int(obstacleLayout.size())/maxLevel;
    if (nextObstacle + 1 >= currentLevel*levelSize && int(obstacles.size()) == 0) {
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

            // Add score when jumping over obstacles
            if (o->height() <= 0) reward(std::move(o));
        }
    }
    if (deleteObstacle) {
        obstacles.erase(obstacles.begin());
    }
}

void Stage3Dialog::spawnObstacles(unsigned int /*counter*/) {
    // Check if it's time to spawn an obstacle
    if (obstacleLayout.size() == 0 || distanceToSpawn > 0) return;

    auto &e = obstacleLayout[unsigned(nextObstacle)];

    // Check for collisions between next obstacle and current obstacles
    bool isOverlapping = false;
    for (auto &o : obstacles) {
        if (Collision::overlaps(*e.first, *o)) {
            isOverlapping = true;
            break;
        }
    }

    // Only spawn the obstacle if it isn't colliding with anything
    if (!isOverlapping) {
        if (currentLevel == 1) {
            auto obs = factory->getEntity("cactus");
            obs->getCoordinate().setXCoordinate(e.first->getCoordinate().getXCoordinate());
            obs->setVelocity(0);
            addObstacle(std::move(obs));
        }else {
            auto obs = e.first->clone();
            obs->setVelocity(background.getVelocity());
            addObstacle(std::move(obs));
        }

        // Set next obstacle in sequence
        distanceToSpawn = e.second;
        nextObstacle = (nextObstacle + 1) % int(obstacleLayout.size());
    }
}

void Stage3Dialog::moveRight() {
    background.setVelocity(playerVelocity);
    for (auto const& obs : obstacles) {
        if (currentLevel == 1) {
            obs->setVelocity(background.getVelocity());
        } else {
            obs->setVelocity(obstacleVelocity+playerVelocity);
        }

    }
    Stage2Dialog::distanceToSpawn = Stage2Dialog::distanceToSpawn -= 1;
}

void Stage3Dialog::moveLeft() {
    background.setVelocity(-playerVelocity);
    for (auto const& obs : obstacles) {
        if (currentLevel == 1) {
            obs->setVelocity(background.getVelocity());
        } else {
            obs->setVelocity(-playerVelocity+obstacleVelocity);
        }
    }
}

void Stage3Dialog::rightBoundaryCollision() {
    levelComplete = true;
}

void Stage3Dialog::leftBoundaryCollision() {
    std::cout << "Oh no! You've been pushed back to the last level..." << std::endl;
    if (stickman->getNumLives() < 1) {
        lose();
    } else {
        stickman->setNumLives(stickman->getNumLives() - 1);
        std::cout << "Lost a life. Total Lives: " << stickman->getNumLives() << std::endl;
        resetLevel();
    }
}

void Stage3Dialog::nextLevel() {
    // Save score incase level is to be revisited
    savedScore = score.getScore();
    std::cout << "Starting Level" << currentLevel + 1 << std::endl;
    nextObstacle = 0;
    levelComplete = false;

    int i = 0;
    while (i < currentLevel * 1000) {
        score.increment();
        i++;
    }
    currentLevel++;
}

void Stage3Dialog::resetLevel() {
    std::cout << "\nRestarting Level " << currentLevel << std::endl;
    nextObstacle = (currentLevel-1) * int(obstacleLayout.size())/maxLevel;

    // revert score back to what it was at the beginning of level
    score.setScore(savedScore);

    // delete all obstacles
    removeObstacles();
    stickman->getCoordinate().setXCoordinate(400);
}

void Stage3Dialog::removeObstacles() {
    for (auto &obs : obstacles) {
        obs->setVelocity(1000);
        update();
    }
}

void Stage3Dialog::speedUp(unsigned int counter) {

}

void Stage3Dialog::win() {
    std::cout << "WINNER!! Total score is " << score.getScore() << std::endl;
    QCoreApplication::quit();
}

void Stage3Dialog::lose() {
    std::cout << "LOST" << std::endl;
    QCoreApplication::quit();
}

void Stage3Dialog::reward(std::unique_ptr<Entity> obstacle) {

        // Toggle mode
        std::vector<std::string> modes = {"tiny","normal","large","giant"};

        std::vector<std::string>::iterator mode_it = std::find(modes.begin(), modes.end(), stickman->getMode());
        int mode = int(std::distance(modes.begin(),mode_it));

        // Change size

        if (stickman->getMode() != "giant") stickman->setMode(modes[(mode + 1) % 4 ]);

        int i = 0;
        while (i < 100) {
            score.increment();
            i++;
        }
}
