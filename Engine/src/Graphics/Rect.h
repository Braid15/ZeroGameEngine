#pragma once

#include "../ZeroEngineStd.h"
#include "Point.h"

namespace ZeroEngine {

    class Rect : public IZeroObject {

    /* Construction interface */
    public:
        Rect();
        Rect( const long left, const long top, const long right, const long bottom );
        Rect( const Rect* rect );
        Rect( const Rect& rect );
        Rect( const Point<long>& top_left, const Point<long>& bottom_right );
        Rect( const Point<long>* top_left, const Point<long>* bottom_right );
        virtual ~Rect();

    /* Getters/setters interface */
    public:
        long get_y() const;
        long get_x() const;
        long get_top() const;
        long get_bottom() const;
        long get_right() const;
        long get_left() const;
        Point<long> get_center() const;
        long get_width() const;
        long get_height() const;
        Point<long> get_top_left() const;
        Point<long> get_top_right() const;
        Point<long> get_bottom_left() const;
        Point<long> get_bottom_right() const;
        void set_x( const long x );
        void set_y( const long y );
        void set( const long left, const long top, const long right, const long bottom );
        void set_top( const long top );
        void set_left( const long left );
        void set_right( const long right );
        void set_bottom( const long bottom );

    /* Method interface */
    public:
        bool is_valid() const;
        bool is_zero() const;
        void reset();
        void shift_x( const long delta_x );
        void shift_y( const long delta_y );
        void move_delta( const long delta_x, const long delta_y );
        void move_delta( const Point<long>& delta );
        void move_delta( const Point<long>* delta );
        void move_to( const long x, const long y );
        void move_to( const Point<long>* point );
        void move_to( const Point<long>& point );
        bool is_collision( const Point<long>& point ) const;
        bool is_collision( const Point<long>* point ) const;
        bool is_collision( const Rect& other ) const;
        bool is_collision( const Rect* other ) const;
        bool is_within( const Point<long>& point ) const;
        bool is_within( const Point<long>* point ) const;
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
        long _left;
        long _right;
        long _top;
        long _bottom;

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
