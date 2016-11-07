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
      mCollisionVector.set(0,0); //�����ײ�ٶ�������
      mMatrix.calcRectCover(ball.rect(), *this); //��ʼ������
      if(!mCollisionVector.isZero()) {
        ball.v().reflectionThis(mCollisionVector); //������ײ���ٶ�
        mCollisionVector.set(0,0);
      }
      mBall = NULL;
      mCallback = NULL;
    }
  protected:
    void cover(int xIndex, int yIndex, const Engine::Rect& rect) {
      //�������Ϸ�
      if(NULL == mBall) {
        return;
      }
      //����
      if(0>xIndex || xIndex >= mXcount ||
          0>yIndex || yIndex >= mYcount) {
        return;
      }
      bool& avaliable = mBlockAvaliableList[xIndex + yIndex * mXcount];
      if(!avaliable) {
        return;
      }
      //�ж���ײ����
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
