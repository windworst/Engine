#pragma once
#ifndef BALL
#define BALL
#include "engine/Atom.h"

/**
 * 球的运动计算
 */
class Ball: public Engine::Atom {
  private:
    number mR; //半径
    Engine::Rect mRect; //圆所在的矩形
  public:
    Ball(number r = 10) {
      this->r(r);
    }

    void r(number r) {
      mR = r;
    }

    number r() const {
      return mR;
    }
    const Engine::Rect& rect() {
      number R = mR+mR;
      mRect.width(R);
      mRect.height(R);
      mRect.position().set(position());
      mRect.position().translate(-mR, -mR);
      return mRect;
    }

    Engine::Vector collision(const Engine::Rect& rect) {
      if(!mRect.collision(rect)) return Engine::Vector();
      Engine::Vector vector = rect.toNearPoint(position());
      if(vector.x() * vector.x() + vector.y() * vector.y() > r()*r()) {
        vector.set(0,0);
      }
      return vector;
    }

    void reflection(const Engine::Vector& vector) {
      if(vector.isZero()) return;
      v().reflectionThis(vector);
    }
};
#endif
