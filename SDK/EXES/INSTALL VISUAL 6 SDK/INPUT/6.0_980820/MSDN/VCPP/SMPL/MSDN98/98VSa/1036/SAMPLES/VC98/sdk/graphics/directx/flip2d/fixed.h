/**************************************************************************

    Fixed.h - 16.16 Fixed point class

 **************************************************************************/

inline long fixed_mul(long a, long b) {return MulDiv(a, b, 65536);}
inline long fixed_div(long a, long b) {return MulDiv(a, 65536, b);}

class Fixed {
    private:
        long fx;
    public:
        Fixed()             {}
        ~Fixed()            {}

        Fixed(long l)       {fx = l<<16;}
        Fixed(int i)        {fx = (long)i<<16;}
        Fixed(double d)     {fx = (long)(d * 65536.0);}

        int Int()           {return (int)(fx >> 16);}
        int Frac()          {return (int)(fx & 0xFFFF);}

        operator int()      {return (int)(fx >> 16);}
        operator double()   {return (double)fx / 65536.0;}

        Fixed operator +(Fixed a) {Fixed c; c.fx = fx + a.fx; return c;}
        Fixed operator -(Fixed a) {Fixed c; c.fx = fx - a.fx; return c;}
        Fixed operator *(Fixed a) {Fixed c; c.fx = fixed_mul(fx,a.fx); return c;}
        Fixed operator /(Fixed a) {Fixed c; c.fx = fixed_div(fx,a.fx); return c;}

        int operator <(Fixed a)  {return fx < a.fx;}
        int operator >(Fixed a)  {return fx > a.fx;}
        int operator ==(Fixed a) {return fx == a.fx;}
        int operator !=(Fixed a) {return fx != a.fx;}

//      Fixed& operator  =(Fixed a) {fx  = a.fx; return *this;}
        Fixed& operator +=(Fixed a) {fx += a.fx; return *this;}
        Fixed& operator -=(Fixed a) {fx -= a.fx; return *this;}
        Fixed& operator *=(Fixed a) {fx  = fixed_mul(fx,a.fx); return *this;}
        Fixed& operator /=(Fixed a) {fx  = fixed_div(fx,a.fx); return *this;}
};
