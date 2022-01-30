// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "engine/Board.h"
#include "engine/GameOver.h"
#include "GameObjects/Snake.h"
#include "engine/Control.h"
#include "Windows.h"
#include "GameObjects/Apple.h"
#include "engine/ScoreScreen.h"
#include <fstream>

#define FRAME_RATE 200

int main()
{
  uint32_t highscore = 0;
  std::ifstream highscoreFile("highscore.bin", std::ios::in | std::ios::binary);
  if (highscoreFile.is_open())
  {
    highscoreFile.read((char*)&highscore, sizeof(highscore));
    highscoreFile.close();
  }

  std::cout << highscore << std::endl;

  double frameTime = 1000. / static_cast<double>(FRAME_RATE);
  std::string windowName = "Snake";
  cv::namedWindow(windowName);

  unsigned int deaths = 0;

  //todo load resources in own class
  cv::Mat appleImg;// = cv::imread("images/apple.png", 1);
  //cv::resize(appleImg, appleImg, cv::Size(30, 30));


  //Parameter
  BoardParameter boardParameter(600, 600, 30.f, false),
    scoreScreenParameter(600, 30, 30.f, false);

  //Game Board
  std::shared_ptr<Board> board = std::make_shared<Board>(boardParameter);
  std::shared_ptr<GameOver> gameOverScreen = std::make_shared<GameOver>(boardParameter);
  std::shared_ptr<ScoreScreen> scoreScreen = std::make_shared<ScoreScreen>(scoreScreenParameter);

  std::shared_ptr<Control> control = std::make_shared<Control>(FRAME_RATE);

  //Game Objects;
  std::shared_ptr<Snake> snake = std::make_shared<Snake>();
  std::shared_ptr<Apple> apple = std::make_shared<Apple>(appleImg, *snake, *board);

  std::vector<IBoard*> otherBoards;
  otherBoards.emplace_back(static_cast<IBoard*>(scoreScreen.get()));

  bool isGameOver = false;
  bool repaint = true;
  while (true)
  {
    double start = cv::getTickCount();

    if (!isGameOver)
    {
      if (repaint)
      {
        board->process(*snake, apple);
        scoreScreen->process(*snake, highscore);
        board->flush(windowName, otherBoards);
      }
      
      isGameOver = control->process(*snake, apple, *board, repaint);
      if (isGameOver)
      {
        uint32_t currentScore = snake->getSnakeSize() - 1;
        if (currentScore > highscore)
        {
          highscore = currentScore;
          std::ofstream file("highscore.bin", std::ios::binary);
          file.write(reinterpret_cast<const char *>(&currentScore), sizeof(currentScore));
          file.close();
        }
      }
    }
    else
    {
      scoreScreen->process(*snake, highscore);
      gameOverScreen->flush(windowName, otherBoards);

      int key = cv::waitKeyEx(1000.0 / static_cast<double>(FRAME_RATE));

      if (key > -1)
      {

        isGameOver = false;
        board = std::make_shared<Board>(boardParameter);
        control = std::make_shared<Control>(FRAME_RATE);
        snake->init();
        apple = std::make_shared<Apple>(appleImg, *snake, *board);
      }
    }

    double end = cv::getTickCount();
    double usedTime = frameTime - ((end - start) / cv::getTickFrequency());

    if (usedTime > 0)
    {
      Sleep(usedTime);
    }
  }

  return 0;
}

