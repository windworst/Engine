#pragma once
#ifndef ENGINE_MATRIX
#define ENGINE_MATRIX

#include "Rect.h"

namespace Engine {
  class Matrix;
  class MatrixRectCoverCallback {
      friend class Matrix;
    protected:
      /**
       *  回调
       *  x序号, y序号, 覆盖到的rect
       */
      virtual void cover(int xIndex, int yIndex, const Rect& rect) = 0;
  };
  class Matrix {
    private:
      Rect mRect;
      int index(number distance, number gridLength) {
        if(0 == gridLength || 0 == distance) {
          return 0;
        }
        return (int) ( distance / gridLength ) + ( distance < 0 ? -1 : 0 );
      }
    public:
      Matrix(number rectWidth = 10, number rectHeight = 10): mRect(rectWidth, rectHeight) {}
      void set(number rectWidth, number rectHeight) {
        mRect.set(rectWidth, rectHeight);
      }
      void calcRectCover(const Rect& rect, MatrixRectCoverCallback& callback) {
        number x1 = index(rect.left(), mRect.width()), x2 = index(rect.right(), mRect.width()),
              y1 = index(rect.top(), mRect.height()), y2 = index(rect.bottom(), mRect.height());
        int i,j;
        for(i = x1; i <= x2; ++i) {
          for(j = y1; j <= y2; ++j) {
            mRect.position().set( i * mRect.width(), j * mRect.height() );
            callback.cover(i, j, mRect);
          }
        }
      }
  };
};
#endif
