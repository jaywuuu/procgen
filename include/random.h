#ifndef _random_h_
#define _random_h_

#include "noisefunc.h"

class RandomIf {
  public:
    virtual int getRandInt() = 0;
    virtual unsigned getRandUInt() = 0;
    virtual unsigned getRandUIntInRange(unsigned from, unsigned to) = 0;
};

class NoiseFunctionRNG : public RandomIf {
  public:
    NoiseFunctionRNG(unsigned seed = 0, unsigned pos = 0) : m_nf(seed), m_pos(pos) {}

    int getRandInt();
    unsigned getRandUInt();
    unsigned getRandUIntInRange(unsigned from, unsigned to);

    template <class T> T getRand() {
        unsigned ret = m_nf.noise1D(m_pos++);
        return *reinterpret_cast<T*>(&ret);
    }

    template <> unsigned NoiseFunctionRNG::getRand<unsigned>() {
        return m_nf.noise1D(m_pos++);
    }
    

  private:
    NoiseFunction m_nf;
    unsigned m_pos;
};

#endif // _random_h_