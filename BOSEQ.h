#ifndef _BOSEQ_H_
#define _BOSEQ_H_

template<int N>
class Sequencer
{
  unsigned int mLength;
  unsigned int mIndex;

  int mSequence[N];

  bool mDoRetrig;

public:

  int next()
  {
    int ret = mSequence[mIndex];
    mIndex = (mIndex + 1) % mLength; //cell is done jump forward.
    return ret;
  }

  Sequencer(Connector::Jack& jack) : mLength(0), mDoRetrig(false)
  {

  }

  void setRetrig(bool r)
  {
    mDoRetrig = r;
  }

  void trigged() {
    if(mDoRetrig) mIndex = 0;
  }

  int operator()()
  {
    int val = next();
    trigged();
    return val;
  }

  //replace
  Sequencer& operator=(const Sequencer& s)
  {
    if(this!=s)
    {
      for(int i = 0; i < s.mLength; ++i)
      {
        mSequence[i] = s.mSequence[i];
      }
      mLength = s.mLength;
    }
    return *this;
  }

  //add
  Sequencer& operator+=(const Sequencer& s)
  {
    unsigned int len = s.mLength;
    //To avoid buffer overload.
    if( N < mLength + len)
    {
      len = N - mLength;
    }

    for(int i = mLength, j = 0; j < len ; ++i, ++j)
    {
      mSequence[i] = s.mNotes[j];
    }
    mLength = mLength + len;
    return *this;
  }

  Sequencer& operator+=(int t)
  {
    mSequence[mLength] = t;
    mLength = (mLength + 1) % N;
  }

};

#dendif
