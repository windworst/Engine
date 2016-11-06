#pragma once
#ifndef BALL
#define BALL
#include "engine/Atom.h"

/**
 * ����˶�����
 */
class Ball: public Engine::Atom {
  private:
    number mR; //�뾶
    Engine::Rect mRect; //Բ���ڵľ���
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
      //�Ѿ���ײ��!
      if(mR * mR >= dx*dx + dy*dy) {
        //����ײ��ָ��Բ�ĵ�����
        vector.set(dx, dy);
      }
      return vector;
    }
};
#endif