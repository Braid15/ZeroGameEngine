#include "Point.h"

namespace ZeroEngine {

     /* ctors/dtors */

     template <class T>
     inline Point<T>::Point() {
         _x = 0;
         _y = 0;
     }

     template<>
     inline Point<float>::Point() {
         _x = 0.0f;
         _y = 0.0f;
     }

     template <>
     inline Point<double>::Point() {
         _x = 0.0;
         _y = 0.0;
     }

     template<class T>
     inline Point<T>::Point( const T x, const T y ) {
         _x = x;
         _y = y;
     }

     template <class T>
     inline Point<T>::Point( const Point<T>& point ) {
         _x = point.get_x();
         _y = point.get_y();
     }

     template <class T>
     inline Point<T>::Point( const Point<T>* point ) {
         _x = point->get_x();
         _y = point->get_y();
     }

     template <class T>
     inline Point<T>::~Point() {}


     /* accessors */

     template <class T>
     inline T Point<T>::get_x() const {
         return _x;
     }

     template <class T>
     inline T Point<T>::get_y() const {
         return _y;
     }

     template <class T>
     inline void Point<T>::set_x( T x ) {
         _x = x;
     }

     template <class T>
     inline void Point<T>::set_y( T y ) {
         _y = y;
     }

     template <class T>
     inline void Point<T>::set( const T x, const T y ) {
         _x = x;
         _y = y;
     }


     /* Operator interface */

     template <class T>
     inline Point<T>& Point<T>::operator=( const Point<T>& new_point ) {
         _x = new_point.get_x();
         _y = new_point.get_y();
         return ( *this );
     }

     template <class T>
     inline Point<T>& Point<T>::operator=( const Point<T>* new_point ) {
         _x = new_point->get_x();
         _y = new_point->get_y();
         return ( *this );
     }

     template <class T>
     inline Point<T>& Point<T>::operator+=( const Point<T>& new_point ) {
         _x += new_point.get_x();
         _y += new_point.get_y();
         return ( *this );
     }

     template <class T>
     inline Point<T>& Point<T>::operator+=( const Point<T>* new_point ) {
         _x += new_point->get_x();
         _y += new_point->get_y();
         return ( *this );
     }

     template <class T>
     inline Point<T>& Point<T>::operator-=( const Point<T>& new_point ) {
         _x -= new_point.get_x();
         _y -= new_point.get_y();
         return ( *this );
     }

     template <class T>
     inline Point<T>& Point<T>::operator-=( const Point<T>* new_point ) {
         _x -= new_point->get_x();
         _y -= new_point->get_y();
         return ( *this );
     }

     template <class T>
     inline Point<T> Point<T>::operator+( const Point<T>& point ) {
         Point<T> ret_point( this );
         ret_point += point;
         return ret_point;
     }

     template <class T>
     inline Point<T> Point<T>::operator-( const Point<T>& point ) {
         Point<T> ret_point( this );
         ret_point -= point;
         return ret_point;
     }

     template <class T>
     inline bool Point<T>::operator==( const Point<T>& point ) const {
         return ( _x == point.get_x() && _y == point.get_y() );
     }

     template <class T>
     inline bool Point<T>::operator!=( const Point<T>& point ) const {
         return !( _x == point.get_x() && _y == point.get_y() );
     }


     /* Method interface */

     template <class T>
     template <class U>
     inline Point<U> Point<T>::convert() const {
         // This class can only be used with conversion types
         // so all conversions are relatively safe
         return Point<U>( (U)_x, (U)_y );
     }

     template <class T>
     inline void Point<T>::reset() {
         _x = 0;
         _y = 0;
     }

     template <>
     inline void Point<float>::reset() {
         _x = 0.0f;
         _y = 0.0f;
     }

     template <>
     inline void Point<double>::reset() {
         _x = 0.0;
         _y = 0.0;
     }

     template <class T>
     inline bool Point<T>::is_zero() const {
         return _x == 0 && _y == 0;
     }

     template <>
     inline bool Point<float>::is_zero() const {
         return _x == 0.0f && _y == 0.0f;
     }

     template <>
     inline bool Point<double>::is_zero() const {
         return _x == 0.0 && _y == 0.0;
     }

     template <>
     inline StringRepr Point<float>::to_string() const {
         return "Point<float>";
     }

     template <>
     inline StringRepr Point<int>::to_string() const {
         return "Point<int>";
     }

     template <>
     inline StringRepr Point<double>::to_string() const {
         return "Point<double>";
     }

     template <>
     inline StringRepr Point<long>::to_string() const {
         return "Point<long>";
     }

     template<>
     inline StringRepr Point<uint8_t>::to_string() const {
        return "Point<uint8_t>";
     }

    template<>
    inline StringRepr Point<uint16_t>::to_string() const {
        return "Point<uint16_t>";
    }

    template<>
    inline StringRepr Point<uint32_t>::to_string() const {
        return "Point<uint32_t>";
    }

    template<>
    inline StringRepr Point<uint64_t>::to_string() const {
        return "Point<uint64_t>";
    }

    template<>
    inline StringRepr Point<int8_t>::to_string() const {
        return "Point<int8_t>";
    }

    template<>
    inline StringRepr Point<int16_t>::to_string() const {
        return "Point<int16_t>";
    }

    // These are commented out because they are typedefed to the basic types

    //template<>
    //inline StringRepr Point<int32_t>::to_string() const {
    //    return "Point<int32_t>";
    //}

    template<>
    inline StringRepr Point<int64_t>::to_string() const {
        return "Point<int64_t>";
    }

    // template<>
    // inline StringRepr Point<float_t>::to_string() const {
    //     return "Point<float_t>";
    // }

    // template<>
    // inline StringRepr Point<double_t>::to_string() const {
    //     return "Point<double_t>";
    // }

    template class Point<int>;
    template class Point<long>;
    template class Point<double>;
    template class Point<float>;
    template class Point<uint8_t>;
    template class Point<uint16_t>;
    template class Point<uint32_t>;
    template class Point<uint64_t>;
    template class Point<int8_t>;
    template class Point<int16_t>;
    template class Point<int32_t>;
    template class Point<int64_t>;
    template class Point<float_t>;
    template class Point<double_t>;

    #ifdef _DEBUG
    namespace PointUnitTest {

        extern void run() {
            Point<long> point1;
            std::cout << point1 << std::endl;
            Point<float> point2 = point1.convert<float>();
            std::cout << point2 << std::endl;
        }
    }
    #endif


}