#pragma once
#ifndef ENGINE_RECT
#define ENGINE_RECT
#include "Line.h"

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
      Point nearPoint(const Point& point) const {
        Point tPoint(point);
        tPoint.translate(-mPosition.y(), -mPosition.y());
        //判断点是否在矩形内部
        if(
            0 <= tPoint.x() && tPoint.x() <= mWidth
            &&
            0 <= tPoint.y() && tPoint.y() <= mHeight
          ) {
          return point;
        }
        Point pList[] = {Point(0, 0), Point(mWidth, 0), Point(0,mHeight), Point(mWidth,mHeight) }; //四个点
        int l[4][2] = {{0, 1}, {1, 3}, {2, 3}, {0, 2}};//四条边
        number distance = -1;
        Point result, head, tail;
        int i;
        for(i = 0; i < 4; ++i) {
          Point p = Line::nearPoint(pList[l[i][0]], pList[l[i][1]], point);
          number dx = p.x() - point.x(), dy = p.y() - point.y();
          number d = dx * dx + dy * dy;
          if(distance < 0 || d < distance) {
            distance = d;
            result = p;
          }
          if( IS_ZERO(distance) ) {
            break;
          }
        }
        result.translate(mPosition.x(), mPosition.y());
        return result;
      }
  };
};
#endif
