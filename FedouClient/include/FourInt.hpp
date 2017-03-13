#ifndef FOURINT_HPP_
#define FOURINT_HPP_

class FourInt
{
public:
  int a;
  int b;
  int c;
  int d;

  FourInt()
  {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
  }

  FourInt(int e, int f, int g, int h)
  {
    a = e;
    b = f;
    c = g;
    d = h;
  }
  FourInt(const FourInt &o)
  {
    a = o.a;
    b = o.b;
    c = o.c;
    d = o.d;
  }

  FourInt &operator=(const FourInt &o)
  {
    a = o.a;
    b = o.b;
    c = o.c;
    d = o.d;
    return (*this);
  }

  ~FourInt(){}
};

#endif
