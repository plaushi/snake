#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "../GameObjects/Snake.h"
#include "../GameObjects/Apple.h"
#include "../Engine/Direction.h"
#include "Board.h"

class Control
{
public:
  Control(unsigned int frameRate) :
    frameRate(frameRate),
    speedFactor(0.05f)
  {
  }

  bool process(Snake &snake, std::shared_ptr<Apple> &apple, Board &board, bool &repaint);


private:

  common::Direction movingDir = common::Direction::down;
  unsigned int frameCounter = 0,
    frameRate;

  float speedFactor;

  bool changeSpeed = false;


  void checkKeyInput(Snake &snake, Board &board)
  {
    int key = cv::waitKeyEx(1000.0 / frameRate); //TODO THIS NEEDS TO GO INTO A THREAD!!!!! NEXT THING

    if (key > -1)
    {
      std::cout << key << std::endl;
    }

    switch (key)
    {
    case 2424832: //left
    case 97:
      if (movingDir == common::up || movingDir == common::down)
      {
        movingDir = common::left;
      }
      break;
    case 2490368: //up
    case 119:
      if (movingDir == common::right || movingDir == common::left)
      {
        movingDir = common::up;
      }
      break;
    case 2555904: //right
    case 100:
      if (movingDir == common::up || movingDir == common::down)
      {
        movingDir = common::right;
      }
      break;
    case 2621440: //down
    case 115:
      if (movingDir == common::right || movingDir == common::left)
      {
        movingDir = common::down;
      }
      break;
    case 35:
      board.toggleGrid();
      break;
    default:
      break;
    }
  }

};
