#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdlib>
#include "BoardParameter.h"
#include "IBoard.h"
#include "../GameObjects/Snake.h"


class ScoreScreen : public IBoard
{
public:

  ScoreScreen(const BoardParameter &param) :
    IBoard(param, cv::Scalar(102, 0, 102))
  {

  }

  void process(Snake &snake, uint32_t highscore)
  {
    board.setTo(cv::Scalar(102, 0, 102));

    std::string text = "Score: ";

    unsigned int score = snake.getSnakeSize() - 1;
 
    text += std::to_string(score);

    int fontFace = cv::FONT_HERSHEY_PLAIN;
    double fontScale = 1;
    int thickness = 2;

    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);

    cv::Point textOrg(0, (board.rows + textSize.height) / 2);

    cv::putText(board, text, textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness, 8);

    std::string death = "Deaths: ";
    death += std::to_string(snake.getDeaths());

    cv::Size textSize2 = cv::getTextSize(death, fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg2(board.cols - textSize2.width, (board.rows + textSize2.height) / 2);

    cv::putText(board, death, textOrg2, fontFace, fontScale, cv::Scalar::all(255), thickness, 8);

    std::string hscore = "Highscore: ";
    hscore += std::to_string(highscore);

    cv::Size textSize3 = cv::getTextSize(hscore, fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg3((board.cols - textSize3.width) / 2, (board.rows + textSize3.height) / 2);

    cv::putText(board, hscore, textOrg3, fontFace, fontScale, cv::Scalar::all(255), thickness, 8);
  }


};
