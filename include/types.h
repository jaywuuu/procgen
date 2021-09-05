#ifndef _types_h_
#define _types_h_

#include "common.h"

typedef unsigned int TileType;

class Grid2D {
    // TODO: Copy/Move constructors?
  public:
    Grid2D(unsigned x, unsigned y) : m_x(x), m_y(y) {
        m_data = new TileType[x * y];
        memset(m_data, 0, sizeof(TileType) * x * y);
    };

    ~Grid2D() { delete m_data; }

    class Row {
      private:
        TileType *m_rowData;

      public:
        Row(TileType *row) : m_rowData(row) {}

        TileType &operator[](unsigned x) { return m_rowData[x]; }
    };

    Row operator[](unsigned y) { return Row(&m_data[y * m_x]); }

    unsigned getSizeX() const { return m_x; }

    unsigned getSizeY() const { return m_y; }

  private:
    unsigned m_x;
    unsigned m_y;
    TileType *m_data;
};

struct Rect {
    unsigned x1;
    unsigned y1;
    unsigned x2;
    unsigned y2;
};

#endif // _types_h_