// -*- related-file-name: "../../liblcdf/transform.cc" -*-
#ifndef LCDF_TRANSFORM_HH
#define LCDF_TRANSFORM_HH
#include <lcdf/bezier.hh>
#include <cassert>

class Transform { public:

    Transform();
    Transform(double, double, double, double, double, double);

    double value(int i) const		{ assert(i>=0&&i<6); return _m[i]; }
  
    void add_scale(double, double);
    void add_scale(const Point &p)		{ add_scale(p.x, p.y); }
    void add_scale(double d)			{ add_scale(d, d); }
    void add_rotate(double);
    void add_translate(double, double);
    void add_translate(const Point &p)		{ add_translate(p.x, p.y); }

    inline Transform scale(double, double) const;
    Transform scale(const Point &p) const	{ return scale(p.x, p.y); }
    Transform scale(double d) const		{ return scale(d, d); }
    Transform rotate(double) const;
    Transform translate(double, double) const;
    Transform translate(const Point &p) const;
    Transform transform(const Transform &) const;

    // Transform operator+(Transform, const Point &);
    // Transform &operator+=(Transform &, const Point &);
    // Transform operator*(Transform, const Transform &);
    // Transform &operator*=(Transform &, const Transform &);
    friend Point operator*(const Point &, const Transform &);
    friend Point &operator*=(Point &, const Transform &);
    friend Bezier operator*(const Bezier &, const Transform &);
    friend Bezier &operator*=(Bezier &, const Transform &);

  private:
    
    double _m[6];

};


inline Transform
Transform::scale(double x, double y) const
{
    Transform t(*this);
    t.add_scale(x, y);
    return t;
}

inline Transform
Transform::rotate(double r) const
{
    Transform t(*this);
    t.add_rotate(r);
    return t;
}

inline Transform
Transform::translate(double x, double y) const
{
    Transform t(*this);
    t.add_translate(x, y);
    return t;
}

inline Transform
Transform::translate(const Point &p) const
{
    return translate(p.x, p.y);
}


inline Transform &
operator+=(Transform &t, const Point &p)
{
    t.add_translate(p);
    return t;
}

inline Transform
operator+(Transform t, const Point &p)
{
    return t += p;
}

inline Transform
operator*(const Transform &t, const Transform &tt)
{
    return t.transform(tt);
}

inline Transform &
operator*=(Transform &t, const Transform &tt)
{
    t = t.transform(tt);
    return t;
}


Point &operator*=(Point &, const Transform &);
Point &operator*=(Point &, const Transform &);

#endif
