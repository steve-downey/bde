// bslstl_iterator.h                                                  -*-C++-*-
#ifndef INCLUDED_BSLSTL_ITERATOR
#define INCLUDED_BSLSTL_ITERATOR

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide basic iterator traits, adaptors, and utilities.
//
//@CLASSES:
//       bsl::iterator_traits: information about iterator associated types
//      bsl::reverse_iterator: bring in 'std::reverse_iterator'
//              bsl::distance: global function to calculate iterator distance
//
//@SEE_ALSO: bslstl_forwarditerator, bslstl_bidirectionaliterator,
//           bslstl_randomaccessiterator, C++ Standard
//
//@AUTHOR: Pablo Halpern (phalpern), Herve Bronnimann (hbronnim)
//
//@DESCRIPTION: This component is for internal use only.  Please include
// '<bsl_iterator.h>' directly.  This component provides the facilities of the
// iterators library from the C++ Standard.

// Prevent 'bslstl' headers from being included directly in 'BSL_OVERRIDES_STD'
// mode.  Doing so is unsupported, and is likely to cause compilation errors.
#if defined(BSL_OVERRIDES_STD) && !defined(BSL_STDHDRS_PROLOGUE_IN_EFFECT)
#error "include <bsl_iterator.h> instead of <bslstl_iterator.h> in \
BSL_OVERRIDES_STD mode"
#endif

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLS_NATIVESTD
#include <bsls_nativestd.h>
#endif

#ifndef INCLUDED_BSLS_PLATFORM
#include <bsls_platform.h>
#endif

#ifndef INCLUDED_ITERATOR
#include <iterator>
#define INCLUDED_ITERATOR
#endif

#ifndef INCLUDED_CSTDDEF
#include <cstddef>
#define INCLUDED_CSTDDEF
#endif

namespace bsl {

// 24.3 primitives
using native_std::input_iterator_tag;
using native_std::output_iterator_tag;
using native_std::forward_iterator_tag;
using native_std::bidirectional_iterator_tag;
using native_std::random_access_iterator_tag;
using native_std::iterator;

// 24.3.4 iterator operations
using native_std::advance;

// 24.3.4 predefined iterators
using native_std::back_insert_iterator;
using native_std::back_inserter;
using native_std::front_insert_iterator;
using native_std::front_inserter;
using native_std::insert_iterator;
using native_std::inserter;

// 24.5 stream iterators
using native_std::istream_iterator;
using native_std::ostream_iterator;
using native_std::istreambuf_iterator;
using native_std::ostreambuf_iterator;

#ifdef BSLS_PLATFORM__CMP_SUN

// Sun does not provide 'std::iterator_traits' at all.  We will provide our
// own in namespace 'bsl'.

                        // =========================
                        // class bsl::IteratorTraits
                        // =========================

template <class ITER>
struct iterator_traits {
    // This 'struct' will provide access to iterator traits.

    // TYPES
    typedef typename ITER::iterator_category iterator_category;
    typedef typename ITER::value_type        value_type;
    typedef typename ITER::difference_type   difference_type;
    typedef typename ITER::pointer           pointer;
    typedef typename ITER::reference         reference;
};

// SPECIALIZATIONS
template <class TYPE>
struct iterator_traits<const TYPE *> {
    // This specialization of 'iterator_traits' will match pointer types
    // to a parameterized non-modifiable 'TYPE'.

    // TYPES
    typedef std::random_access_iterator_tag iterator_category;
    typedef TYPE                            value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const TYPE*                     pointer;
    typedef const TYPE&                     reference;
};

template <class TYPE>
struct iterator_traits<TYPE *> {
    // This specialization of 'iterator_traits' will match pointer types
    // to a parameterized modifiable 'TYPE'.

    // TYPES
    typedef std::random_access_iterator_tag iterator_category;
    typedef TYPE                            value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef TYPE*                           pointer;
    typedef TYPE&                           reference;
};

// Working around a sun compiler bug where 'std::reverse_iterator' takes 6
// (with 3 default) template arguments instead of 1, which is not standard
// compliant.  Inherit from 'std::reverse_iterator'.  For reference, the
// signature of sun's 'std::reverse_iterator' is:
//..
//  template <class Iterator,
//            class Category,
//            class T,
//            class Reference = T &,
//            class Pointer = T *,
//            class Distance = ptrdiff_t>
//  class reverse_iterator;
//..

                        // ===========================
                        // class bsl::reverse_iterator
                        // ===========================

template <class ITER>
class reverse_iterator :
    public native_std::reverse_iterator<
                             ITER,
                             typename iterator_traits<ITER>::iterator_category,
                             typename iterator_traits<ITER>::value_type,
                             typename iterator_traits<ITER>::reference,
                             typename iterator_traits<ITER>::pointer> {

    // PRIVATE TYPES
    typedef native_std::reverse_iterator<
                 ITER,
                 typename iterator_traits<ITER>::iterator_category,
                 typename iterator_traits<ITER>::value_type,
                 typename iterator_traits<ITER>::reference,
                 typename iterator_traits<ITER>::pointer>                 Base;

  public:
    // For convenience:
    typedef typename reverse_iterator::difference_type difference_type;

    // CREATORS
    reverse_iterator();

    explicit reverse_iterator(ITER x);

    template <class OTHER_ITER>
    reverse_iterator(const reverse_iterator<OTHER_ITER>& other);

    // MANIPULATORS
    reverse_iterator& operator++();

    reverse_iterator  operator++(int);

    reverse_iterator& operator+=(typename difference_type n);

    reverse_iterator& operator--();

    reverse_iterator  operator--(int);

    reverse_iterator& operator-=(typename difference_type n);

    // ACCESSORS
    reverse_iterator operator+(typename difference_type n) const;

    reverse_iterator operator-(typename difference_type n) const;
};

// FREE OPERATORS
template <class ITER> inline
bool operator==(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y);

template <class ITER> inline
bool operator!=(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y);

template <class ITER> inline
bool operator<(const reverse_iterator<ITER>& x,
               const reverse_iterator<ITER>& y);

template <class ITER> inline
bool operator>(const reverse_iterator<ITER>& x,
               const reverse_iterator<ITER>& y);

template <class ITER> inline
bool operator<=(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y);

template <class ITER> inline
bool operator>=(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y);

template <class ITER> inline
typename reverse_iterator<ITER>::difference_type
operator-(const reverse_iterator<ITER>& x,
          const reverse_iterator<ITER>& y);

template <class ITER, class DIFF_TYPE> inline
reverse_iterator<ITER>
operator+(DIFF_TYPE n, const reverse_iterator<ITER>& x);

                        // ==========================
                        // struct IteratorDistanceImp
                        // ==========================

struct IteratorDistanceImp {
    // This utility class provides a namespace for functions that operate on
    // iterators.

    template <class FWD_ITER, class DIFFERENCE_TYPE>
    static void getDistance(DIFFERENCE_TYPE *ret,
                            FWD_ITER         start,
                            FWD_ITER         finish,
                            input_iterator_tag);

    template <class FWD_ITER, class DIFFERENCE_TYPE>
    static void getDistance(DIFFERENCE_TYPE *ret,
                            FWD_ITER         start,
                            FWD_ITER         finish,
                            forward_iterator_tag);

    template <class RANDOM_ITER, class DIFFERENCE_TYPE>
    static void getDistance(DIFFERENCE_TYPE *ret,
                            RANDOM_ITER      start,
                            RANDOM_ITER      finish,
                            random_access_iterator_tag);
};

template <class ITER>
static typename iterator_traits<ITER>::difference_type
distance(ITER start, ITER finish);

#else

// Just use the native version
using native_std::reverse_iterator;
using native_std::iterator_traits;
using native_std::distance;

#endif

// ===========================================================================
//                      INLINE FUNCTION DEFINITIONS
// ===========================================================================

                        // ---------------------------
                        // class bsl::reverse_iterator
                        // ---------------------------

#ifdef BSLS_PLATFORM__CMP_SUN

// CREATORS
template <class ITER>
inline
reverse_iterator<ITER>::reverse_iterator()
: Base()
{
}

template <class ITER>
inline
reverse_iterator<ITER>::reverse_iterator(ITER x)
: Base(x)
{
}

template <class ITER>
template <class OTHER_ITER>
inline
reverse_iterator<ITER>::reverse_iterator(
                                    const reverse_iterator<OTHER_ITER>& other)
: Base(other.base())
{
}

// MANIPULATORS
template <class ITER>
inline
reverse_iterator<ITER>&
reverse_iterator<ITER>::operator++()
{
    Base::operator++();
    return *this;
}

template <class ITER>
inline
reverse_iterator<ITER>
reverse_iterator<ITER>::operator++(int)
{
    const reverse_iterator tmp(*this);
    this->operator++();
    return tmp;
}

template <class ITER>
inline
reverse_iterator<ITER>&
reverse_iterator<ITER>::operator+=(difference_type n)
{
    Base::operator+=(n);
    return *this;
}

template <class ITER>
inline
reverse_iterator<ITER>&
reverse_iterator<ITER>::operator--()
{
    Base::operator--();
    return *this;
}

template <class ITER>
inline
reverse_iterator<ITER>
reverse_iterator<ITER>::operator--(int)
{
    reverse_iterator tmp(*this);
    this->operator--();
    return tmp;
}

template <class ITER>
inline
reverse_iterator<ITER>&
reverse_iterator<ITER>::operator-=(difference_type n)
{
    Base::operator-=(n);
    return *this;
}

// ACCESSORS
template <class ITER>
inline
reverse_iterator<ITER>
reverse_iterator<ITER>::operator+(difference_type n) const
{
    reverse_iterator tmp(*this);
    tmp += n;
    return tmp;
}

template <class ITER>
inline
reverse_iterator<ITER>
reverse_iterator<ITER>::operator-(difference_type n) const
{
    reverse_iterator tmp(*this);
    tmp -= n;
    return tmp;
}

// FREE OPERATORS
template <class ITER>
inline
bool operator==(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y)
{
    typedef native_std::reverse_iterator<
                 ITER,
                 typename iterator_traits<ITER>::iterator_category,
                 typename iterator_traits<ITER>::value_type,
                 typename iterator_traits<ITER>::reference,
                 typename iterator_traits<ITER>::pointer>                 Base;

    return std::operator==(static_cast<const Base&>(x),
                           static_cast<const Base&>(y));
}

template <class ITER>
inline
bool operator!=(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y)
{
    return ! (x == y);
}

template <class ITER>
inline
bool operator<(const reverse_iterator<ITER>& x,
               const reverse_iterator<ITER>& y)
{
    typedef native_std::reverse_iterator<
                 ITER,
                 typename iterator_traits<ITER>::iterator_category,
                 typename iterator_traits<ITER>::value_type,
                 typename iterator_traits<ITER>::reference,
                 typename iterator_traits<ITER>::pointer>                 Base;

    return std::operator<(static_cast<const Base&>(x),
                          static_cast<const Base&>(y));
}

template <class ITER>
inline
bool operator>(const reverse_iterator<ITER>& x,
               const reverse_iterator<ITER>& y)
{
    return y < x;
}

template <class ITER>
inline
bool operator<=(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y)
{
    return !(y < x);
}

template <class ITER>
inline
bool operator>=(const reverse_iterator<ITER>& x,
                const reverse_iterator<ITER>& y)
{
    return !(x < y);
}

template <class ITER>
inline
typename reverse_iterator<ITER>::difference_type
operator-(const reverse_iterator<ITER>& x,
          const reverse_iterator<ITER>& y)
{
    typedef native_std::reverse_iterator<
                 ITER,
                 typename iterator_traits<ITER>::iterator_category,
                 typename iterator_traits<ITER>::value_type,
                 typename iterator_traits<ITER>::reference,
                 typename iterator_traits<ITER>::pointer>                 Base;

    return std::operator-(static_cast<const Base&>(x),
                          static_cast<const Base&>(y));
}

template <class ITER, class DIFF_TYPE>
inline
reverse_iterator<ITER>
operator+(DIFF_TYPE n, const reverse_iterator<ITER>& x)
{
    return x.operator+(n);
}

                         // --------------------------
                         // struct IteratorDistanceImp
                         // --------------------------

template <class FWD_ITER, class DIFFERENCE_TYPE>
void IteratorDistanceImp::getDistance(DIFFERENCE_TYPE *ret,
                                      FWD_ITER         start,
                                      FWD_ITER         finish,
                                      input_iterator_tag)
{
    DIFFERENCE_TYPE count = 0;
    for ( ; start != finish; ++start) {
        ++count;
    }

    *ret = count;
}

template <class FWD_ITER, class DIFFERENCE_TYPE>
void IteratorDistanceImp::getDistance(DIFFERENCE_TYPE *ret,
                                      FWD_ITER         start,
                                      FWD_ITER         finish,
                                      forward_iterator_tag)
{
    DIFFERENCE_TYPE count = 0;
    for ( ; start != finish; ++start) {
        ++count;
    }

    *ret = count;
}

template <class RANDOM_ITER, class DIFFERENCE_TYPE>
inline
void IteratorDistanceImp::getDistance(DIFFERENCE_TYPE *ret,
                                      RANDOM_ITER      start,
                                      RANDOM_ITER      finish,
                                      random_access_iterator_tag)
{
    *ret = DIFFERENCE_TYPE(finish - start);
}

template <class ITER>
inline
typename iterator_traits<ITER>::difference_type
distance(ITER start, ITER finish)
{
    typedef typename bsl::iterator_traits<ITER>::iterator_category tag;

    typename iterator_traits<ITER>::difference_type ret;
    IteratorDistanceImp::getDistance(&ret, start, finish, tag());
    return ret;
}

#endif  // BSLS_PLATFORM__CMP_SUN

}  // close namespace bsl

#endif

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2009
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------
