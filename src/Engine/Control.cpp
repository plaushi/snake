#include "Control.h"
#define NOMINMAX
#include <windows.h>


bool Control::process(Snake & snake, std::shared_ptr<Apple>& apple, Board & board, bool & repaint)
{
  bool eaten(false);
  if (snake.getSnakeSize() % 10 == 0)
  {
    if (!changeSpeed)
    {
      changeSpeed = true;
      speedFactor = std::max(0.f, speedFactor - 0.005f);
    }
  }
  else
  {
    changeSpeed = false;
  }

  unsigned int speed = std::max(1u, static_cast<unsigned int>(frameRate * speedFactor));

  if (frameCounter % speed == 0)
  {
    repaint = true;
    if (snake.ownBiting())
    {
      snake.increaseDeaths();
      return true;
    }

    cv::Point nextPos = snake.getNextHead(movingDir);
    if (board.invalidPos(nextPos))
    {
      snake.increaseDeaths();
      return true;
    }

    if (apple && apple->allowEating(nextPos))
    {
      PlaySound("sounds/eat.wav", NULL, SND_FILENAME | SND_ASYNC);
      apple->init(snake, board);
      eaten = true;
    }
    snake.moveSnake(movingDir, eaten);
  }
  else
  {
    repaint = false;
  }

  if (!eaten)
  {
    checkKeyInput(snake, board);
  }

  ++frameCounter;

  return false;
}
