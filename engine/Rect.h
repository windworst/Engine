#pragma once
#ifndef ENGINE_RECT
#define ENGINE_RECT
#include "Line.h"
#include "Vector.h"

namespace Engine {
  class Rect {
    private:
      number mWidth, mHeight; //宽高
      Point mPosition; //偏移坐标(左上角)
    public:
      Rect(number width = 0, number height = 0):mWidth(width),mHeight(height) {}
      Point& position() {
        return mPosition;
      }
      const Point& position() const {
        return mPosition;
      }
      number width() const {
        return mWidth;
      }
      number height() const {
        return mHeight;
      }
      void width(number width) {
        mWidth = width;
      }
      void height(number height) {
        mHeight = height;
      }
      void set(number width, number height) {
        mWidth = width;
        mHeight = height;
      }
      number left() const {
        return mPosition.x();
      }
      number top() const {
        return mPosition.y();
      }
      number right() const {
        return mPosition.x() + mWidth;
      }
      number bottom() const {
        return mPosition.y() + mHeight;
      }
      bool collision(const Rect& rect) const {
        return !(top() > rect.bottom() || rect.top() > bottom()
            ||  left() > rect.right() || rect.left() > right());
      }
      Vector toNearPoint(const Point& point) const {
        Vector vector;
        number dx1 = point.x() - left(), dx2 = right() - point.x(),
               dy1 = point.y() - top(), dy2 = bottom() - point.y(),
               dx = 0, dy = 0;
        //点在矩形内部
        if(dx1 > 0 && dx2 > 0 && dy1 > 0 && dy2 > 0) {
          dx = dx1 < dx2 ? dx1 : dx2;
          dy = dy1 < dy2 ? dy1:  dy2;
          dx < dy ? dy = 0 : dx = 0;
        } else {
          dx1 < 0 ? dx = dx1 : 0;
          dx2 < 0 ? dx = dx2 : 0;
          dy1 < 0 ? dy = dy1 : 0;
          dy2 < 0 ? dy = dy2 : 0;
        }
        vector.set(-dx, -dy);
        return vector;
      }
  };
};
#endif
