#pragma once
#ifndef BOARD
#define BOARD
#include "engine/Atom.h"

class Board: public Engine::Atom {
  private:
    Engine::Rect mRect;
  public:
    Board(const Engine::Rect& rect = Engine::Rect()):mRect(rect) {}
    void set(number width, number height) {
      mRect.set(width, height);
    }
    const Engine::Rect& rect() {
      mRect.position().set(position());
      return mRect;
    }
    void reflection(const Engine::Vector& vector) {
      v().set(0,0);
    }
};
#endif
