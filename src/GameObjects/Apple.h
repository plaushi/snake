#pragma once

#include <vector>
#include <opencv2/opencv.hpp>


class Board;
class Snake;

class Apple
{
public:

  Apple(const cv::Mat &img, Snake &snake, Board &board);

  void init(Snake & snake, Board & board);

  void draw(Board &board);



  bool isValid()
  {
    return valid;
  }

  bool allowEating(const cv::Point &pos)
  {
    return currentPos == pos;
  }

private:

  bool spawnRandom(Snake &snake, Board &board);
  bool valid = false;
  cv::Point currentPos;

  cv::Mat img;

};


