#pragma once
/*

  Tile.h
  2-24-2013

  -Jon Rumion (Yamamushi@gmail.com)


  This is going to be the source of a lot of headaches.

 */

#include "../serialization/Boost_Serialization.h"

#include <string>

class Tile {

private:

  friend class boost::serialization::access;
  template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
  {
    ar & posX;
    ar & posY;
    ar & symbol;
  }

  int posX, posY;
  std::wstring symbol;

  
public:

  Tile(){};
Tile(int PosX, int PosY, std::wstring Symbol=L"\u2550") : posX(PosX), posY(PosY), symbol(Symbol){};

  int getX(){return posX;};
  int getY(){return posY;};
  void setX(int x){posX = x;};
  void setY(int y){posY = y;};
  void setSymbol(std::wstring sym){symbol = sym;};
  
  virtual ~Tile(){};

};