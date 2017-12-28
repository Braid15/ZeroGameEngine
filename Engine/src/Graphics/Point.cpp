#include "Point.h"

namespace ZeroEngine {

     /* ctors/dtors */

     template <class T>
     inline Point<T>::Point() {
         _x = 0;
         _y = 0;
     }

     template<>
     inline Point<float32>::Point() {
         _x = 0.0f;
         _y = 0.0f;
     }

     template <>
     inline Point<float64>::Point() {
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
     inline void Point<float32>::reset() {
         _x = 0.0f;
         _y = 0.0f;
     }

     template <>
     inline void Point<float64>::reset() {
         _x = 0.0;
         _y = 0.0;
     }

     template <class T>
     inline bool Point<T>::is_zero() const {
         return _x == 0 && _y == 0;
     }

     template <>
     inline bool Point<float32>::is_zero() const {
         return _x == 0.0f && _y == 0.0f;
     }

     template <>
     inline bool Point<float64>::is_zero() const {
         return _x == 0.0 && _y == 0.0;
     }

     template <>
     inline StringRepr Point<float32>::to_string() const {
         return "Point<f32>";
     }

     template <>
     inline StringRepr Point<int32>::to_string() const {
         return "Point<i32>";
     }

     template <>
     inline StringRepr Point<float64>::to_string() const {
         return "Point<f64>";
     }

     template <>
     inline StringRepr Point<int64>::to_string() const {
         return "Point<i64>";
     }

     template<>
     inline StringRepr Point<uint8>::to_string() const {
        return "Point<u8>";
     }

    template<>
    inline StringRepr Point<uint16>::to_string() const {
        return "Point<u16>";
    }

    template<>
    inline StringRepr Point<uint32>::to_string() const {
        return "Point<u32>";
    }

    template<>
    inline StringRepr Point<uint64>::to_string() const {
        return "Point<u64>";
    }

    template<>
    inline StringRepr Point<int8>::to_string() const {
        return "Point<i8>";
    }

    template<>
    inline StringRepr Point<int16>::to_string() const {
        return "Point<i16>";
    }


    template class Point<int8>;
    template class Point<int16>;
    template class Point<int32>;
    template class Point<int64>;

    template class Point<uint8>;
    template class Point<uint16>;
    template class Point<uint32>;
    template class Point<uint64>;

    template class Point<float32>;
    template class Point<float64>;


    #ifdef _DEBUG
    namespace PointUnitTest {

        extern void run() {
            Point<int64> point1;
            std::cout << point1 << std::endl;
            Point<float32> point2 = point1.convert<float32>();
            std::cout << point2 << std::endl;
        }
    }
    #endif


}