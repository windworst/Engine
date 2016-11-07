#pragma once
#ifndef BLOCK
#define BLOCK

#include "engine/Matrix.h"
#include "engine/Vector.h"
#include "Ball.h"

class Block;
class BlockKnockCallback {
  friend class Block;
  protected:
    virtual void onKnock(int xIndex, int yIndex, int xCount, int yCount) = 0;
};

class Block: public Engine::MatrixRectCoverCallback {
  private:
    Engine::Matrix mMatrix;
    int mXcount, mYcount;
    bool* mBlockAvaliableList;
    Ball* mBall;
    BlockKnockCallback* mCallback;
    Engine::Vector mCollisionVector;
  public:
    Block(number width, number height, int xCount, int yCount):
      mXcount(xCount),mYcount(yCount),
      mMatrix(width,height) {
        int i, length = mXcount * mYcount;
        mBlockAvaliableList = new bool[length];
        for(i=0; i<length; ++i) {
          mBlockAvaliableList[i] = true;
        }
      }
    virtual ~Block() {
      delete[] mBlockAvaliableList;
    }
    void run(Ball& ball, BlockKnockCallback* callback = NULL) {
      mBall = &ball;
      mCallback = callback;
      mCollisionVector.set(0,0); //清空碰撞速度向量和
      mMatrix.calcRectCover(ball.rect(), *this); //开始遍历块
      if(!mCollisionVector.isZero()) {
        ball.v().reflectionThis(mCollisionVector); //计算碰撞后速度
        mCollisionVector.set(0,0);
      }
      mBall = NULL;
      mCallback = NULL;
    }
  protected:
    void cover(int xIndex, int yIndex, const Engine::Rect& rect) {
      //参数不合法
      if(NULL == mBall) {
        return;
      }
      //界外
      if(0>xIndex || xIndex >= mXcount ||
          0>yIndex || yIndex >= mYcount) {
        return;
      }
      bool& avaliable = mBlockAvaliableList[xIndex + yIndex * mXcount];
      if(!avaliable) {
        return;
      }
      //判断碰撞向量
      Engine::Vector vector = mBall->collision(rect);
      if( !vector.isZero() ) {
        avaliable = false;
        /*mCollisionVector += vector;*/
        if(NULL!= mCallback) {
          mCallback->onKnock(xIndex, yIndex, mXcount, mYcount);
        }
      }
    }
};
#endif
