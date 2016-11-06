#pragma once
#ifndef ENGINE_ATOM
#define ENGINE_ATOM
#include "Rect.h"
#include "Vector.h"
/**
 *  ������˶�����
 */
namespace Engine {
  class Atom {
    private:
      Point mPosition;   //����
      Vector mV; //�ٶ�
      Vector mA; //���ٶ�����
      number mF; //Ħ����ϵ��
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
      //����ʱ���ڵı仯
      void run(number dt) {
        //�ٶ�: �����ٶ�Ӱ��
        mV.translate(mA.x() * dt, mA.y() * dt);
        //Ħ����: �ٶ�����ȡ��λ����ȡ��Ȼ�����Ħ����ϵ��
        Vector f = Vector(mV).unit_vector().reverse() *= mF;
        //Ħ�������������ٶȷ���
        number fx = f.x() * dt, fy = f.y() * dt;
        ABS(mV.x()) < ABS(fx) ? fx = -mV.x() : 0;
        ABS(mV.y()) < ABS(fy) ? fy = -mV.y() : 0;
        mV.translate(fx, fy);
        if(IS_ZERO(mV.x())) mV.x(0);
        if(IS_ZERO(mV.y())) mV.y(0);
        //λ��: �ٶȳ���ʱ��
        mPosition.translate(mV.x() * dt, mV.y() * dt);
      }
      //������ռ���εĴ�С
      virtual const Rect& rect() = 0;
  };
};
#endif
