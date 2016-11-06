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
      Engine::Vector vector;
      Engine::Point nearPoint = rect.nearPoint(position());
      number dx = nearPoint.x() - position().x(),
             dy = nearPoint.y() - position().y();
      //已经碰撞了!
      if(mR * mR >= dx*dx + dy*dy) {
        //从碰撞点指向圆心的向量
        vector.set(dx, dy);
      }
      return vector;
    }
};
#endif
