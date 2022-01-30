#include "Apple.h"
#include "Snake.h"
#include "../Engine/Board.h"
#include <stdlib.h>


Apple::Apple(const cv::Mat &img, Snake &snake, Board &board) :
  img(img)
{
  init(snake, board);
}

void Apple::init(Snake &snake, Board &board)
{
  valid = spawnRandom(snake, board);
}


bool Apple::spawnRandom(Snake &snake, Board &board)
{
  std::vector<cv::Point> snakeObj, freeFields;
  snake.getSnake(snakeObj);

  board.getFreeFields(snakeObj, freeFields);

  if (freeFields.empty())
  {
    return false;
  }

  currentPos = freeFields[rand() % freeFields.size()];
  return true;
}

void Apple::draw(Board &board)
{
  if (!valid)
  {
    return;
  }


  board.drawCircle(currentPos, cv::Scalar(0, 0, 0));
//  board.drawCube(currentPos, cv::Scalar(0, 0, 0));
  //board.drawImage(img, currentPos);
}
