#pragma once
#ifndef ENGINE_VECTOR
#define ENGINE_VECTOR
#include "Point.h"
#include <math.h>

namespace Engine {
  class Vector{
    private:
      number mX, mY;
    public:
      Vector(number x = 0, number y = 0):mX(x),mY(y){}
      Vector(const Vector& vector) {
        set(vector);
      }
      number length() const {
        return sqrt( x()*x() + y()*y() );
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
      void set(const Vector& vector) {
        mX = vector.x();
        mY = vector.y();
      }
      void set(number x, number y) {
        mX = x;
        mY = y;
      }
      void translate(number x, number y) {
        mX += x;
        mY += y;
      }
      void move(Point& point) {
        point.translate(x(), y());
      }
      //向量反向
      Vector& reverse() {
        mX = -mX;
        mY = -mY;
        return *this;
      }
      //单位向量
      Vector& unit_vector() {
        if(!IS_ZERO(mX) || !IS_ZERO(mY)) {
          number xy2 = sqrt(mX*mX + mY*mY);
          mX /= xy2;
          mY /= xy2;
        }
        return *this;
      }
      bool isZero() {
        return mX == 0 && mY == 0;
      }
      //向量加法
      Vector& operator+=(const Vector& vector) {
        mX += vector.x();
        mY += vector.y();
        return *this;
      }
      const Vector operator+(const Vector& vector) const {
        return Vector(*this) += vector;
      }
      //乘一个系数
      Vector& operator*=(number n) {
        mX *= n;
        mY *= n;
        return *this;
      }
      const Vector operator*(number n) const {
        return Vector(*this) *= n;
      }
      //向量点积
      number dot(const Vector& vector) {
        return x() * vector.x() + y() * vector.y();
      }
      //自己向量在另外的向量上的投影
      Vector projection(const Vector& vector) {
        number dot_product = dot(vector);
        //正交, 投影为零向量
        if(0 == dot_product) {
          return Vector(0, 0);
        }
        number dx = vector.x();
        number dy = vector.y();
        //投影长度占向量的比例
        number scale = dot_product / (dx*dx + dy*dy);
        return Vector(dx * scale, dy * scale);
      }
      //向量被法线反射
      Vector reflection(Vector line) {
        return Vector(*this).reflectionThis(line);
      }
      Vector& reflectionThis(Vector line) {
        Vector p = projection(line).reverse();
        p += p;
        return *this += p;
      }
  };
};
#endif
