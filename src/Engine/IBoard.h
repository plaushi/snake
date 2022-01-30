#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include "BoardParameter.h"
#include "../Engine/Direction.h"


class IBoard
{
public:

  IBoard(const BoardParameter &param, cv::Scalar &color) :
    boardColor(color),
    param(param),
    board(param.height, param.width, CV_8UC3, boardColor),
    maxNumCells(param.width / param.gridResolution, param.height / param.gridResolution)
  {

  }

  void drawCube(const cv::Point & pos, cv::Scalar &color)
  {
    cv::Point tl(pos * param.gridResolution),
      br(tl + cv::Point(param.gridResolution, param.gridResolution));

    cv::Rect cube(tl, br), boardRect(0, 0, board.cols - 1, board.rows - 1);
    cube &= boardRect;

    cv::rectangle(board, cube, color, -1);
  }

  void drawCircle(const cv::Point & pos, cv::Scalar &color)
  {
    cv::Point center(pos * param.gridResolution);
    center += cv::Point(param.gridResolution * 0.5, param.gridResolution * 0.5);

    cv::circle(board, center, param.gridResolution * 0.5, color, -1);
  }

  void drawImage(const cv::Mat &img, const cv::Point & pos)
  {
    cv::Point tl(pos * param.gridResolution);

    for (int y = 0; y < img.rows; ++y)
    {
      for (int x = 0; x < img.cols; ++x)
      {
        auto other = img.at<cv::Vec3b>(y, x);
        if (other[0] != 255 || other[1] != 255 || other[2] != 255)
        {
          board.at<cv::Vec3b>(tl.y + y, tl.x + x) = other;
        }
      }
    }
  }

  void drawHead(const cv::Point & pos, common::Direction dir, cv::Scalar &color)
  {
    int halfCubeLength = static_cast<int>(param.gridResolution * 0.5);

    cv::Point center(pos * param.gridResolution);
    center += cv::Point(halfCubeLength, halfCubeLength);

    cv::circle(board, center, halfCubeLength, color, -1);

    cv::Point tl, br;

    switch (dir)
    {
    case common::Direction::up:
      tl = center + cv::Point(-halfCubeLength, 0);
      br = center + cv::Point(halfCubeLength, halfCubeLength);
      break;

    case common::Direction::left:
      tl = center + cv::Point(0, -halfCubeLength);
      br = center + cv::Point(halfCubeLength, halfCubeLength);
      break;

    case common::Direction::down:
      tl = center + cv::Point(-halfCubeLength, -halfCubeLength);
      br = center + cv::Point(halfCubeLength, 0);

      break;
    case common::Direction::right:
      tl = center + cv::Point(-halfCubeLength, -halfCubeLength);
      br = center + cv::Point(0, halfCubeLength);

      break;
    default:
      break;
    }

    cv::Rect cube(tl, br), boardRect(0, 0, board.cols - 1, board.rows - 1);
    cube &= boardRect;

    cv::rectangle(board, cube, color, -1);
  }

  void vConcat(cv::Mat &img)
  {
    cv::vconcat(board, img, img);
  }


  void flush(std::string &name)
  {
    imshow(name, board);
  }

  void flush(std::string &name, std::vector<IBoard*> &otherBoards)
  {
    cv::Mat out = board.clone();
    for (auto &other : otherBoards)
    {
      other->vConcat(out);
    }

    imshow(name, out);
  }


protected:

  const cv::Scalar boardColor;
  BoardParameter param;
  cv::Mat board;
  cv::Point maxNumCells;
};