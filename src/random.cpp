#include "random.h"

int NoiseFunctionRNG::getRandInt() {
    return getRand<int>();
}

unsigned NoiseFunctionRNG::getRandUInt() {
    return getRand<unsigned>();
}

unsigned NoiseFunctionRNG::getRandUIntInRange(unsigned from, unsigned to) {
    if (to == from)
        return to;
    
    if (to < from) {
        unsigned temp = to;
        to = from;
        from = to;
    }

    unsigned ret = m_nf.noise1D(m_pos++);
    unsigned range = to - from + 1; // inclusive
    ret = ret % range;
    ret += from;

    return ret;
}