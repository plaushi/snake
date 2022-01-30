#include "Snake.h"
#include "../engine/Board.h"

void Snake::draw(Board & board)
{
  cv::Point3i head(snakeTail.front());
  cv::Point head2D(head.x, head.y);

  if (snakeTail.size() == 1)
  {
    board.drawCircle(head2D, color);
    return;
  }

  board.drawHead(head2D, static_cast<common::Direction>(head.z),color);

  int lastDir = head.z;
  for (unsigned int i = 1; i < snakeTail.size()-1; ++i)
  {
    board.drawCube(cv::Point(snakeTail[i].x, snakeTail[i].y), color);
    lastDir = snakeTail[i].z;
  }

  cv::Point3i tail(snakeTail.back());
  cv::Point tail2D(tail.x, tail.y);
  board.drawHead(tail2D, getReverseDir(static_cast<common::Direction>(tail.z  == lastDir ? tail.z : lastDir)), color);
}


void Snake::getSnake(std::vector<cv::Point> &snake)
{
  snake.clear();
  for (const auto &part : snakeTail)
  {
    snake.emplace_back(cv::Point(part.x, part.y));
  }
}

void Snake::addNextMove(const common::Direction &dir, cv::Point3i &current)
{
  switch (dir)
  {
  case common::Direction::up:
    current += cv::Point3i(0, -1, 0);

    break;
  case common::Direction::left:
    current += cv::Point3i(-1, 0, 0);

    break;
  case common::Direction::down:
    current += cv::Point3i(0, 1, 0);

    break;
  case common::Direction::right:
    current += cv::Point3i(1, 0, 0);

    break;
  default:
    break;
  }
}

void Snake::moveSnake(common::Direction dir, bool eaten)
{
  cv::Point3i current = snakeTail.front();
  current.z = static_cast<int>(dir);

  if (!eaten)
  {
    snakeTail.pop_back();
  }
  addNextMove(dir, current);

  snakeTail.push_front(current);
}

bool Snake::ownBiting()
{
  cv::Point3i current3D = snakeTail.front();
  cv::Point current(current3D.x, current3D.y);

  for (unsigned int i = 1; i < snakeTail.size(); ++i)
  {
    if (cv::Point(snakeTail[i].x, snakeTail[i].y) == current)
    {
      return true;
    }
  }

  return false;
}