#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    template <class T> 
    class Point : public IType {
        static_assert( std::is_arithmetic<T>::value,
                       "Point can only be initialized with arithmetic types" );

    /* Construction interface */
    public:
        Point();
        Point( const T x, const T y );
        Point( const Point<T>& point );
        Point( const Point<T>* point );
        virtual ~Point();

    /* Accessor interface */
    public:
        T get_x() const; 
        T get_y() const;
        void set_x( const T x );
        void set_y( const T y );
        void set( const T x, const T y );

    /* Operator interface */
    public:
        Point<T>& operator=( const Point<T>& new_point );
        Point<T>& operator=( const Point<T>* new_point );
        Point<T>& operator+=( const Point<T>& new_point );
        Point<T>& operator-=( const Point<T>& new_point );
        Point<T>& operator+=( const Point<T>* new_point );
        Point<T>& operator-=( const Point<T>* new_point );
        Point<T> operator+( const Point<T>& point );
        Point<T> operator-( const Point<T>& point );
        bool operator==( const Point<T>& point ) const;
        bool operator!=( const Point<T>& point ) const;

    /* Method interface */
    public:
        Point<int> to_int() const;
        Point<float> to_float() const;
        Point<long> to_long() const;
        Point<double> to_double() const;
        void reset();
        bool is_zero() const;

    private:
        T _x;
        T _y;

    /* IType interface */
    public:
        virtual TypeName get_type() const override { return "Point<>"; }
    };

    /* ostream/istream */
    template <class T>
    std::ostream& operator<<( std::ostream& os, const Point<T>& point );


        
    namespace PointUnitTest {

        extern void run();
    }
}
