// -*- related-file-name: "../../liblcdf/permstr.cc" -*-
#ifndef LCDF_PERMSTR_HH
#define LCDF_PERMSTR_HH
#include <cassert>
#include <cstddef>
#include <cstdarg>

class PermString { struct Doodad; public:
  
    typedef Doodad *Capsule;
    // Declare a PermString::Initializer in any file in which you declare
    // static global PermStrings.
    struct Initializer { Initializer(); };
  
    PermString()			: _rep(0) { }
    explicit PermString(char c);
    PermString(const char *);
    PermString(const char *, int);
  
    operator bool() const		{ return _rep != 0; }
    int length() const			{ return doodad()->length; }
    char operator[](int) const;
  
    friend bool operator==(PermString, PermString);
    friend bool operator!=(PermString, PermString);
  
    const char *cc() const		{ return _rep; }
    const char *c_str() const		{ return _rep; }
    operator const char *() const	{ return _rep; }
  
    Capsule capsule() const		{ return doodad(); }
    static PermString decapsule(Capsule c) { return PermString(c); }
  
    friend PermString permprintf(const char *, ...);
    friend PermString vpermprintf(const char *, va_list);
    friend PermString permcat(PermString, PermString);
    friend PermString permcat(PermString, PermString, PermString);  

  private:
  
    struct Doodad {
	Doodad *next;
	int length;
	char data[2];
    };
  
    char *_rep;
  
    PermString(Doodad *d)		: _rep(d->data) { }
    Doodad *doodad() const { return (Doodad*)(_rep - offsetof(Doodad, data)); }
  
    friend class PermString::Initializer;
    static void static_initialize();

    static const int NHASH = 1024; // must be power of 2
    static Doodad zero_char_doodad, one_char_doodad[256], *buckets[NHASH];
  
};


inline bool
operator==(PermString a, PermString b)
{
    return a._rep == b._rep;
}

bool operator==(PermString, const char *);

inline bool
operator==(const char *a, PermString b)
{
    return b == a;
}

inline bool
operator!=(PermString a, PermString b)
{
    return a._rep != b._rep;
}

inline bool
operator!=(PermString a, const char *b)
{
    return !(a == b);
}

inline bool
operator!=(const char *a, PermString b)
{
    return !(b == a);
}

inline unsigned
hashcode(PermString s)
{
    return (unsigned)(s.cc());
}

#endif
