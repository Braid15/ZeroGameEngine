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


     /* ostream/istream */
     // TODO - 10/2/2017 - Handle float point precision
     template <class T>
     inline std::ostream& operator<<( std::ostream& os, const Point<T>& point ) {
         os << point.get_type() << " - x: " << point.get_x() << " y: " << point.get_y();
         return os;
     }


     /* IType interface */

     template <>
     inline TypeName Point<float>::get_type() const {
         return "Point<float>";
     }

     template <>
     inline TypeName Point<int>::get_type() const {
         return "Point<int>";
     }

     template <>
     inline TypeName Point<double>::get_type() const {
         return "Point<double>";
     }

     template <>
     inline TypeName Point<long>::get_type() const {
         return "Point<long>";
     }

    template class Point<int>;
    template class Point<long>;
    template class Point<double>;
    template class Point<float>;

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