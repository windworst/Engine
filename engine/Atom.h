#pragma once
#ifndef ENGINE_ATOM
#define ENGINE_ATOM
#include "Rect.h"
#include "Vector.h"
/**
 *  物体的运动计算
 */
namespace Engine {
  class Atom {
    private:
      Point mPosition;   //坐标
      Vector mV; //速度
      Vector mA; //加速度向量
      number mF; //摩擦力系数
    public:
      Atom(const Point& point = Point()):mPosition(point) {}
      virtual ~Atom(){}
      Point& position() {
        return mPosition;
      }
      const Point& position() const {
        return mPosition;
      }
      Vector& v() {
        return mV;
      }
      const Vector& v() const {
        return mV;
      }
      Vector& a() {
        return mA;
      }
      const Vector& a() const {
        return mA;
      }
      number f() {
        return mF;
      }
      void f(number inF) {
        mF = inF;
      }
      //极短时间内的变化
      void run(number dt) {
        //速度: 被加速度影响
        mV.translate(mA.x() * dt, mA.y() * dt);
        //摩擦力: 速度向量取单位向量取反然后乘上摩擦力系数
        Vector f = Vector(mV).unit_vector().reverse() *= mF;
        //摩擦力不可能让速度反向
        number fx = f.x() * dt, fy = f.y() * dt;
        ABS(mV.x()) < ABS(fx) ? fx = -mV.x() : 0;
        ABS(mV.y()) < ABS(fy) ? fy = -mV.y() : 0;
        mV.translate(fx, fy);
        if(IS_ZERO(mV.x())) mV.x(0);
        if(IS_ZERO(mV.y())) mV.y(0);
        //位移: 速度乘上时间
        mPosition.translate(mV.x() * dt, mV.y() * dt);
      }
      //物体所占矩形的大小
      virtual const Rect& rect() = 0;
  };
};
#endif
