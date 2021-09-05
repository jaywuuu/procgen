#ifndef _noisefunc_h_
#define _noisefunc_h_

class NoiseFunction {
public:
    NoiseFunction(unsigned seed = 0) : m_seed(seed) {}

    /*
     * Apparrently simple noise function is to mangle by
     * multiplying, bit shifting, xor-not, etc.     
    */
    unsigned noise1D(unsigned pos) {
        const unsigned PRIME1 = 0xB5297A4D;
        const unsigned PRIME2 = 0x68E31DA4;
        const unsigned PRIME3 = 0x1B56C4E9;

        unsigned mang = pos;
        mang *= PRIME1;
        mang += m_seed;
        mang ^= (mang >> 8);
        mang += PRIME2;
        mang ^= (mang << 8);
        mang *= PRIME3;
        mang ^= (mang >> 8);
        return mang;
    }

    inline unsigned noise2D(unsigned x, unsigned y) {
        const unsigned PRIME = 198491317;
        return noise1D(x + (PRIME * y));
    }

private:
    unsigned m_seed;
};

#endif // _noisefunc_h_