#pragma once
#ifndef CONTAINER
#define CONTAINER
#include "engine/Atom.h"

class Container {
  private:
    Engine::Rect mRect;
  public:
    Container(number width = 1000, number height = 1000):mRect(width, height) {}
    Engine::Rect& rect() {
      return mRect;
    }
    //Լ������������
    bool constraint(Engine::Atom& atom) {
      Engine::Rect child = atom.rect();
      //�������,Լ��ʧ��
      if(child.width() > mRect.width() || child.height() > mRect.height()) {
        return false;
      }
      //���κ������ıڵľ���
      number yt = child.top() - mRect.top(),
             yb = mRect.bottom() - child.bottom(),
             xl = child.left() - mRect.left(),
             xr = mRect.right() - child.right();
      //���ݾ������һ����������, ���������������ڲ�
      //���Ҹ�����ײ���, �����ٶ�����
      Engine::Vector adjust, xAxis(1,0), yAxis(0,1);
      //ײ��
      if(yt < 0) {
        adjust.y(-yt);
        atom.v().reflectionThis(yAxis);
      } else if(yb < 0) { //ײ��
        adjust.y(yb);
        atom.v().reflectionThis(yAxis);
      }
      //ײ��
      if(xl < 0) {
        adjust.x(-xl);
        atom.v().reflectionThis(xAxis);
      } else if(xr < 0) { //ײ��
        adjust.x(xr);
        atom.v().reflectionThis(xAxis);
      }
      adjust.move(atom.position());
      return true;
    }
};
#endif
