#pragma once
#ifndef ENGINE_LINE
#define ENGINE_LINE
#include "Point.h"

namespace Engine {
  class Line {
    public:
      //�õ��߶��������������ĵ�
      static Point nearPoint(const Point& head, const Point& tail, const Point& point) {
        number dx = tail.x() - head.x(), dy = tail.y() - head.y();
        //�������
        number dot_product = (point.x() - head.x()) *  dx + (point.y() - head.y()) * dy;
        //��ͶӰ��head֮ǰ
        if(dot_product <= 0) {
          return head;
        }
        //��ͶӰ��tail֮��
        number length_2 = dx*dx + dy*dy;
        if(dot_product >= length_2) {
          return tail;
        }
        //ͶӰ�����߶���, rΪhead��ͶӰ�㳤��ռ�߶��ܳ�����
        number scale = dot_product / length_2;
        return Point(head.x() +  dx * scale, head.y() +  dy * scale);
      };
  };
};
#endif
