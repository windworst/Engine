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
    //约束容器内物体
    bool constraint(Engine::Atom& atom) {
      Engine::Rect child = atom.rect();
      //物体过大,约束失败
      if(child.width() > mRect.width() || child.height() > mRect.height()) {
        return false;
      }
      //矩形和容器四壁的距离
      number yt = child.top() - mRect.top(),
             yb = mRect.bottom() - child.bottom(),
             xl = child.left() - mRect.left(),
             xr = mRect.right() - child.right();
      //根据距离产生一个调整向量, 将矩形拉回容器内部
      //并且根据碰撞情况, 调整速度向量
      Engine::Vector adjust, xAxis(1,0), yAxis(0,1);
      //撞顶
      if(yt < 0) {
        adjust.y(-yt);
        atom.v().reflectionThis(yAxis);
      } else if(yb < 0) { //撞底
        adjust.y(yb);
        atom.v().reflectionThis(yAxis);
      }
      //撞左
      if(xl < 0) {
        adjust.x(-xl);
        atom.v().reflectionThis(xAxis);
      } else if(xr < 0) { //撞右
        adjust.x(xr);
        atom.v().reflectionThis(xAxis);
      }
      adjust.move(atom.position());
      return true;
    }
};
#endif
