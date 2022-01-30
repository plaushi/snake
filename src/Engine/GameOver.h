#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdlib>
#include "BoardParameter.h"
#include "IBoard.h"


class GameOver : public IBoard
{
public:

  GameOver(const BoardParameter &param) :
    IBoard(param, cv::Scalar(102, 0, 102))
  {
    std::string text = "GAME OVER",
      text2 = "Press Any Key";
    int fontFace = cv::FONT_HERSHEY_PLAIN;
    double fontScale = 2;
    int thickness = 3;

    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
    cv::Size textSize2 = cv::getTextSize(text2, fontFace, fontScale, thickness, &baseline);

    // center the text
    cv::Point textOrg((board.cols - textSize.width) / 2,
      (board.rows + textSize.height) / 2 - textSize2.height / 2);

    cv::putText(board, text, textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness, 8);



    // center the text
    cv::Point textOrg2((board.cols - textSize2.width) / 2,
      (board.rows + textSize.height) / 2 - textSize2.height / 2 + textSize2.height + 20);

    cv::putText(board, text2, textOrg2, fontFace, fontScale, cv::Scalar::all(255), thickness, 8);
  }

};
