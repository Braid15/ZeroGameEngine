#pragma once

#include "../ZeroEngineStd.h"
#include "Point.h"

namespace ZeroEngine {

    class Rect : public IZeroObject {

    /* Construction interface */
    public:
        Rect();
        Rect( const Int64 left, const Int64 top, const Int64 right, const Int64 bottom );
        Rect( const Rect* rect );
        Rect( const Rect& rect );
        Rect( const Point<Int64>& top_left, const Point<Int64>& bottom_right );
        Rect( const Point<Int64>* top_left, const Point<Int64>* bottom_right );
        virtual ~Rect();

    /* Getters/setters interface */
    public:
        Int64 get_y() const;
        Int64 get_x() const;
        Int64 get_top() const;
        Int64 get_bottom() const;
        Int64 get_right() const;
        Int64 get_left() const;
        Point<Int64> get_center() const;
        Int64 get_width() const;
        Int64 get_height() const;
        Point<Int64> get_top_left() const;
        Point<Int64> get_top_right() const;
        Point<Int64> get_bottom_left() const;
        Point<Int64> get_bottom_right() const;
        void set_x( const Int64 x );
        void set_y( const Int64 y );
        void set( const Int64 left, const Int64 top, const Int64 right, const Int64 bottom );
        void set_top( const Int64 top );
        void set_left( const Int64 left );
        void set_right( const Int64 right );
        void set_bottom( const Int64 bottom );

    /* Method interface */
    public:
        bool is_valid() const;
        bool is_zero() const;
        void reset();
        void shift_x( const Int64 delta_x );
        void shift_y( const Int64 delta_y );
        void move_delta( const Int64 delta_x, const Int64 delta_y );
        void move_delta( const Point<Int64>& delta );
        void move_delta( const Point<Int64>* delta );
        void move_to( const Int64 x, const Int64 y );
        void move_to( const Point<Int64>* point );
        void move_to( const Point<Int64>& point );
        bool is_collision( const Point<Int64>& point ) const;
        bool is_collision( const Point<Int64>* point ) const;
        bool is_collision( const Rect& other ) const;
        bool is_collision( const Rect* other ) const;
        bool is_within( const Point<Int64>& point ) const;
        bool is_within( const Point<Int64>* point ) const;
        bool is_within( const Rect& rect ) const;
        bool is_within( const Rect* rect ) const;

    /* Operator interface */
    public:
        Rect& operator=( const Rect& new_rect );
        Rect& operator=( const Rect* new_rect );
        Rect& operator+=( const Rect& new_rect );
        Rect& operator-=( const Rect& new_rect );
        Rect& operator+=( const Rect* new_rect );
        Rect& operator-=( const Rect* new_rect );
        Rect operator+( const Rect& rect ) const;
        Rect operator-( const Rect& rect ) const;
        bool operator==( const Rect& other ) const;
        bool operator!=( const Rect& other ) const;

    private:
        Int64 _left;
        Int64 _right;
        Int64 _top;
        Int64 _bottom;

    /* IType interface */
    public:
        virtual StringRepr to_string() const { return "Rect"; }
    };

    /* ostream/istream */
    std::ostream& operator<<( std::ostream& os, const Rect& rect );


    #ifdef _DEBUG
    namespace RectUnitTest {
        extern void run();
    }
    #endif
}
