#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include <queue>
#include "../Engine/Direction.h"


class Board;

class Snake
{
public:

  Snake()
  {
    init();
  }

  void init()
  {
    snakeTail.clear();
    snakeTail.push_front(cv::Point3i(0, 0, static_cast<int>(common::Direction::down)));
  }

  unsigned int getDeaths()
  {
    return deaths;
  }

  void increaseDeaths()
  {
    ++deaths;
  }

  void draw(Board &board);

  void getSnake(std::vector<cv::Point> &snake); //todo  use std::map for that!!!!

  void addNextMove(const common::Direction & dir, cv::Point3i & current);

  void moveSnake(common::Direction dir, bool eaten);

  unsigned int getSnakeSize()
  {
    return snakeTail.size();
  }

  bool ownBiting();

  cv::Point getCurrentHead()
  {
    return cv::Point(snakeTail.front().x, snakeTail.front().y);
  }

  cv::Point getNextHead(const common::Direction & dir)
  {
    cv::Point3i current = snakeTail.front();
    addNextMove(dir, current);
    return cv::Point(current.x, current.y);
  }

  common::Direction getReverseDir(common::Direction dir)
  {
    switch (dir)
    {
    case common::Direction::up:
      return common::Direction::down;
      break;

    case common::Direction::left:
      return common::Direction::right;
      break;

    case common::Direction::down:
      return  common::Direction::up;
      break;

    case common::Direction::right:
      common::Direction::left;
      break;

    default:
      break;
    }

    return common::Direction::left;
  }

private:

  std::deque<cv::Point3i> snakeTail;
  cv::Scalar color = cv::Scalar(102, 0, 102);
  unsigned int deaths = 0;

};

