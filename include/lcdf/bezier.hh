// -*- related-file-name: "../../liblcdf/bezier.cc" -*-
#ifndef LCDF_BEZIER_HH
#define LCDF_BEZIER_HH
#include <lcdf/point.hh>
#include <lcdf/vector.hh>
#include <cstring>

class Bezier { public:
  
    Bezier()				: _bb(-1) { }
    inline Bezier(Point p[4]) throw ();
    inline Bezier(const Point &, const Point &, const Point &, const Point &) throw ();
  
    const Point *points() const		{ return _p; }
    const Point &point(int i) const	{ assert(i>=0&&i<4); return _p[i]; }
    Point &mpoint(int i)		{ assert(i>=0&&i<4); _bb = -1; return _p[i]; }
    void set_point(int i, const Point &p) { mpoint(i) = p; }

    Point eval(double) const throw ();
    bool is_flat(double) const throw ();
    bool in_bb(const Point &, double) const throw ();
    bool hit(const Point &, double) const throw ();

    inline double bb_left() const throw ();
    inline double bb_right() const throw ();
    inline double bb_top() const throw ();
    inline double bb_bottom() const throw ();

    inline double bb_left_x() const throw ();
    inline double bb_right_x() const throw ();
    inline double bb_top_x() const throw ();
    inline double bb_bottom_x() const throw ();
    
    void halve(Bezier &, Bezier &) const throw ();

    inline void segmentize(Vector<Point> &) const;
    void segmentize(Vector<Point> &, bool) const;
  
    static void fit(const Vector<Point> &, double, Vector<Bezier> &);
    
  private:
  
    Point _p[4];
    mutable int _bb;

    void make_bb() const throw ();
    inline void ensure_bb() const throw ();
  
    double hit_recurse(const Point &, double, double, double, double, double) const throw ();

};


inline
Bezier::Bezier(Point p[4]) throw ()
    : _bb(-1)
{
    memcpy(_p, p, sizeof(Point) * 4);
}

inline
Bezier::Bezier(const Point &p0, const Point &p1, const Point &p2, const Point &p3) throw ()
{
    _p[0] = p0;
    _p[1] = p1;
    _p[2] = p2;
    _p[3] = p3;
    _bb = -1;
}

inline void
Bezier::ensure_bb() const throw ()
{
    if (_bb < 0)
	make_bb();
}

inline double
Bezier::bb_top_x() const throw ()
{
    return _p[(_bb >> 4) & 3].y;
}

inline double
Bezier::bb_left_x() const throw ()
{
    return _p[(_bb >> 2) & 3].x;
}

inline double
Bezier::bb_bottom_x() const throw ()
{
    return _p[(_bb >> 6) & 3].y;
}

inline double
Bezier::bb_right_x() const throw ()
{
    return _p[(_bb >> 0) & 3].x;
}

inline double
Bezier::bb_top() const throw ()
{
    ensure_bb();
    return bb_top_x();
}

inline double
Bezier::bb_left() const throw ()
{
    ensure_bb();
    return bb_left_x();
}

inline double
Bezier::bb_bottom() const throw ()
{
    ensure_bb();
    return bb_bottom_x();
}

inline double
Bezier::bb_right() const throw ()
{
    ensure_bb();
    return bb_right_x();
}

inline void
Bezier::segmentize(Vector<Point> &v) const
{
    segmentize(v, v.size() == 0 || v.back() != _p[0]);
}

#endif
