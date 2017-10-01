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



    /* static interface */

    template <class T>
    const Point<T> Point<T>::zero;



    /* IType interface */

    template<>
    TypeName Point<float>::get_type() const {
       return "Point<float>"; 
    }

    template<>
    TypeName Point<int>::get_type() const {
        return "Point<int>";
    }

    template<>
    TypeName Point<double>::get_type() const {
        return "Point<double>";
    }

    template<>
    TypeName Point<long>::get_type() const {
        return "Point<long>";
    }



    /* ostream/istream */
    template <class T>
    std::ostream& operator<<( std::ostream& os, const Point<T>& point ) {
        os << point.get_type() << " - x: " << point.get_x() << " y: " << point.get_y();
        return os;
    }





    namespace PointUnitTest {

        extern void run() {

            Point<int> a( 1, 1 );
            Point<int> b( 1, 1 );
            std::cout << a + b << std::endl;
            a -= b;
            std::cout << a << std::endl;
        }
    }
}
