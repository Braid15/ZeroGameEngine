#pragma once

#include "../ZeroEngineStd.h"
#include "Point.h"

namespace ZeroEngine {

    class Rect : public IZeroObject {

    /* Construction interface */
    public:
        Rect();
        Rect( const int64 left, const int64 top, const int64 right, const int64 bottom );
        Rect( const Rect* rect );
        Rect( const Rect& rect );
        Rect( const Point<int64>& top_left, const Point<int64>& bottom_right );
        Rect( const Point<int64>* top_left, const Point<int64>* bottom_right );
        virtual ~Rect();

    /* Getters/setters interface */
    public:
        int64 get_y() const;
        int64 get_x() const;
        int64 get_top() const;
        int64 get_bottom() const;
        int64 get_right() const;
        int64 get_left() const;
        Point<int64> get_center() const;
        int64 get_width() const;
        int64 get_height() const;
        Point<int64> get_top_left() const;
        Point<int64> get_top_right() const;
        Point<int64> get_bottom_left() const;
        Point<int64> get_bottom_right() const;
        void set_x( const int64 x );
        void set_y( const int64 y );
        void set( const int64 left, const int64 top, const int64 right, const int64 bottom );
        void set_top( const int64 top );
        void set_left( const int64 left );
        void set_right( const int64 right );
        void set_bottom( const int64 bottom );

    /* Method interface */
    public:
        bool is_valid() const;
        bool is_zero() const;
        void reset();
        void shift_x( const int64 delta_x );
        void shift_y( const int64 delta_y );
        void move_delta( const int64 delta_x, const int64 delta_y );
        void move_delta( const Point<int64>& delta );
        void move_delta( const Point<int64>* delta );
        void move_to( const int64 x, const int64 y );
        void move_to( const Point<int64>* point );
        void move_to( const Point<int64>& point );
        bool is_collision( const Point<int64>& point ) const;
        bool is_collision( const Point<int64>* point ) const;
        bool is_collision( const Rect& other ) const;
        bool is_collision( const Rect* other ) const;
        bool is_within( const Point<int64>& point ) const;
        bool is_within( const Point<int64>* point ) const;
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
        int64 _left;
        int64 _right;
        int64 _top;
        int64 _bottom;

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
