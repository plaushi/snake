#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include "BoardParameter.h"
#include "IBoard.h"

class Snake;
class Apple;

class Board : public IBoard
{
public:

  Board(const BoardParameter &param);

  void drawGrid();

  bool invalidPos(cv::Point &pos);


  void process(Snake &snake, std::shared_ptr<Apple> &apple);

  void toggleGrid();


  void getFreeFields(const std::vector<cv::Point> &snakeObj, std::vector<cv::Point> &freeFields)
  {
    freeFields.clear();
    for (int x = 0; x < maxNumCells.x; ++x)
    {
      for (int y = 0; y < maxNumCells.y; ++y)
      {
        bool free(true);
        for (auto &part : snakeObj)
        {
          if (part.x == x && part.y == y)
          {
            free = false;
            break;
          }
        }
        if (free)
        {
          freeFields.emplace_back(cv::Point(x, y));
        }
      }
    }
  }
};
