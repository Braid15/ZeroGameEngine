#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    template <class T> 
    class Point final : public IZeroObject {
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
        void set_x(const T x);
        void set_y(const T y);
        void set(const T x, const T y);

    /* Operator interface */
    public:
        Point<T>& operator=(const Point<T>& new_point);
        Point<T>& operator=(const Point<T>* new_point);
        Point<T>& operator+=(const Point<T>& new_point);
        Point<T>& operator-=(const Point<T>& new_point);
        Point<T>& operator+=(const Point<T>* new_point);
        Point<T>& operator-=(const Point<T>* new_point);
        Point<T> operator+(const Point<T>& point);
        Point<T> operator-( const Point<T>& point);
        bool operator==(const Point<T>& point) const;
        bool operator!=(const Point<T>& point) const;

    /* Method interface */
    public:
        template <class U>
        Point<U> convert() const;
        void reset();
        bool is_zero() const;

    private:
        T _x;
        T _y;

    /* IType interface */
    public:
        virtual StringRepr to_string() const override { return "Point<>"; }
    };

    /* ostream/istream */
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << point.to_string() << ": (" << point.get_x() << ", " << point.get_y() << ")";
        return os;
    }

        
    #ifdef _DEBUG
    namespace PointUnitTest {

        extern void run();
    }
    #endif
}

