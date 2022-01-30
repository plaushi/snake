#pragma once


struct BoardParameter
{
public:
  BoardParameter(int width, int height, float gridResolution, bool debugInfo) :
    width(width),
    height(height),
    gridResolution(gridResolution),
    debugInfo(debugInfo)
  {
  };

  int width,
    height;
  float gridResolution;

  bool debugInfo;

};