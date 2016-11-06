#pragma once
#ifndef ENGINE_POINT
#define ENGINE_POINT
#include "defines.h"
#include <math.h>

namespace Engine {
  class Point{
    private:
      number mX, mY;
    public:
      Point(number x = 0, number y = 0):mX(x),mY(y){}
      number distance(const Point& point) const {
        number dx = point.x() - mX;
        number dy = point.y() - mY;
        return sqrt( dx*dx + dy*dy );
      }
      number x() const {
        return mX;
      }
      number y() const {
        return mY;
      }
      void x(number x) {
        mX = x;
      }
      void y(number y) {
        mY = y;
      }
      void set(const Point& point) {
        mX = point.x();
        mY = point.y();
      }
      void set(number x, number y) {
        mX = x;
        mY = y;
      }
      void translate(number x, number y) {
        mX += x;
        mY += y;
      }
  };
};
#endif
