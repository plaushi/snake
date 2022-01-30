#include "Board.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/Apple.h"

Board::Board(const BoardParameter & param) : 
  IBoard(param, cv::Scalar(204,0,204))
{
}

void Board::drawGrid()
{
  if (!param.debugInfo)
  {
    return;
  }

  for (int y = param.gridResolution; y <= board.rows - param.gridResolution; y += param.gridResolution)
  {
    cv::line(board, cv::Point(0, y), cv::Point(board.cols - 1, y), cv::Scalar(255, 255, 255), 3);
  }

  for (int x = param.gridResolution; x <= board.cols - param.gridResolution; x += param.gridResolution)
  {
    cv::line(board, cv::Point(x, 0), cv::Point(x, board.rows - 1), cv::Scalar(255, 255, 255), 3);
  }

}

bool Board::invalidPos(cv::Point & pos)
{
  return pos.x >= maxNumCells.x || pos.x < 0 || pos.y >= maxNumCells.y || pos.y < 0;
}

void Board::toggleGrid()
{
  param.debugInfo = !param.debugInfo;
}

void Board::process(Snake & snake, std::shared_ptr<Apple> &apple)
{
  board.setTo(boardColor);
  snake.draw(*this);
  if (apple)
  {
    apple->draw(*this);
  }
  drawGrid();
}
