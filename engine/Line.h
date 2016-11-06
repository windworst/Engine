#pragma once
#ifndef ENGINE_LINE
#define ENGINE_LINE
#include "Point.h"

namespace Engine {
  class Line {
    public:
      //得到线段上与给定点最近的点
      static Point nearPoint(const Point& head, const Point& tail, const Point& point) {
        number dx = tail.x() - head.x(), dy = tail.y() - head.y();
        //向量点乘
        number dot_product = (point.x() - head.x()) *  dx + (point.y() - head.y()) * dy;
        //若投影在head之前
        if(dot_product <= 0) {
          return head;
        }
        //若投影在tail之后
        number length_2 = dx*dx + dy*dy;
        if(dot_product >= length_2) {
          return tail;
        }
        //投影点在线段上, r为head到投影点长度占线段总长比例
        number scale = dot_product / length_2;
        return Point(head.x() +  dx * scale, head.y() +  dy * scale);
      };
  };
};
#endif
