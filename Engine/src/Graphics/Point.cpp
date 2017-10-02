#include "Point.h"

namespace ZeroEngine {

    /* ctors/dtors */
    template <class T>
    Point<T>::Point() {
        _x = 0;
        _y = 0;
    }

    template<>
    Point<float>::Point() {
        _x = 0.0f;
        _y = 0.0f;
    }

    template <>
    Point<double>::Point() {
        _x = 0.0;
        _y = 0.0;
    }

    template<class T>
    Point<T>::Point( const T x, const T y ) {
        _x = x;
        _y = y;
    }

    template <class T>
    Point<T>::Point( const Point<T>& point ) {
        _x = point.get_x();
        _y = point.get_y();
    }

    template <class T>
    Point<T>::Point( const Point<T>* point ) {
        _x = point->get_x();
        _y = point->get_y();
    }

    template <class T>
    Point<T>::~Point() {}


    /* accessors */

    template <class T>
    T Point<T>::get_x() const {
        return _x;
    }

    template <class T>
    T Point<T>::get_y() const {
        return _y;
    }

    template <class T>
    void Point<T>::set_x( T x ) {
        _x = x;
    }

    template <class T>
    void Point<T>::set_y( T y ) {
        _y = y;
    }

    template <class T>
    void Point<T>::set( const T x, const T y ) {
        _x = x;
        _y = y;
    }


    /* Operator interface */

    template <class T>
    Point<T>& Point<T>::operator=( const Point<T>& new_point ) {
        _x = new_point.get_x();
        _y = new_point.get_y();
        return ( *this );
    }

    template <class T>
    Point<T>& Point<T>::operator=( const Point<T>* new_point ) {
        _x = new_point->get_x();
        _y = new_point->get_y();
    }

    template <class T>
    Point<T>& Point<T>::operator+=( const Point<T>& new_point ) {
        _x += new_point.get_x();
        _y += new_point.get_y();
        return ( *this );
    }

    template <class T>
    Point<T>& Point<T>::operator+=( const Point<T>* new_point ) {
        _x += new_point->get_x();
        _y += new_point->get_y();
        return ( *this );
    }

    template <class T>
    Point<T>& Point<T>::operator-=( const Point<T>& new_point ) {
        _x -= new_point.get_x();
        _y -= new_point.get_y();
        return ( *this );
    }

    template <class T>
    Point<T>& Point<T>::operator-=( const Point<T>* new_point ) {
        _x -= new_point->get_x();
        _y -= new_point->get_y();
        return ( *this );
    }

    template <class T>
    Point<T> Point<T>::operator+( const Point<T>& point ) {
        Point<T> ret_point( this );
        ret_point += point;
        return ret_point;
    }

    template <class T>
    Point<T> Point<T>::operator-( const Point<T>& point ) {
        Point<T> ret_point( this );
        ret_point -= point;
        return ret_point;
    }

    template <class T>
    bool Point<T>::operator==( const Point<T>& point ) const {
        return ( _x == point.get_x() && _y == point.get_y() );
    }

    template <class T>
    bool Point<T>::operator!=( const Point<T>& point ) const {
        return !( _x == point.get_x() && _y == point.get_y() );
    }


    /* Method interface */
    template <class T>
    Point<int> Point<T>::to_int() const {
        Point<int> ret_point;
        if ( std::is_same<T, int>::value ) {
            ret_point = this;
        } else {
            ret_point.set( (int)_x, (int)_y );
        }
        return ret_point;
    }

    template <class T>
    Point<float> Point<T>::to_float() const {
        Point<float> ret_point;
        if ( std::is_same<T, float>::value ) {
            ret_point = this;
        } else {
            ret_point.set( (float)_x, (float)_y );
        }
        return ret_point;
    }

    template <class T>
    Point<long> Point<T>::to_long() const {
        Point<long> ret_point;
        if ( std::is_same<T, long>::value ) {
            ret_point = this;
        } else {
            ret_point.set( (long)_x, (long)_y );
        }
        return ret_point;
    }

    template <class T>
    Point<double> Point<T>::to_double() const {
        Point<double> ret_point;
        if ( std::is_same<T, double>::value ) {
            ret_point = this;
        } else {
            ret_point.set( (double)_x, (double)_y );
        }
        return ret_point;
    }

    template <class T>
    void Point<T>::reset() {
        _x = 0;
        _y = 0;
    }

    template <>
    void Point<float>::reset() {
        _x = 0.0f;
        _y = 0.0f;
    }

    template <>
    void Point<double>::reset() {
        _x = 0.0;
        _y = 0.0;
    }

    template <class T>
    bool Point<T>::is_zero() const {
        return _x == 0 && _y == 0;
    }

    template <>
    bool Point<float>::is_zero() const {
        return _x == 0.0f && _y == 0.0f;
    }

    template <>
    bool Point<double>::is_zero() const {
        return _x == 0.0 && _y == 0.0;
    }


    /* ostream/istream */
    template <class T>
    std::ostream& operator<<( std::ostream& os, const Point<T>& point ) {
        os << point.get_type() << " - x: " << point.get_x() << " y: " << point.get_y();
        return os;
    }


    /* IType interface */

    template <>
    TypeName Point<float>::get_type() const {
       return "Point<float>"; 
    }

    template <>
    TypeName Point<int>::get_type() const {
        return "Point<int>";
    }

    template <>
    TypeName Point<double>::get_type() const {
        return "Point<double>";
    }

    template <>
    TypeName Point<long>::get_type() const {
        return "Point<long>";
    }



    namespace PointUnitTest {

        extern void run() {

            Point<long> a( 1, 1 );
            Point<long> b( 1, 1 );
            std::cout << a + b << std::endl;
            a -= b;
            std::cout << a << std::endl;
        }
    }
}
