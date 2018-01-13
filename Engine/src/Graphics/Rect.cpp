#include "Rect.h"

namespace ZeroEngine {

    /* Construction interface */
    Rect::Rect() {
        _left = 0;
        _right = 0;
        _top = 0;
        _bottom = 0;
    }

    Rect::Rect( const Int64 left, const Int64 top, const Int64 right, const Int64 bottom ) {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }

    Rect::Rect( const Rect& rect ) {
        _left = rect.get_left();
        _top = rect.get_top();
        _right = rect.get_right();
        _bottom = rect.get_bottom();
    }

    Rect::Rect( const Rect* rect ) {
        _left = rect->get_left();
        _top = rect->get_top();
        _right = rect->get_right();
        _bottom = rect->get_bottom();
    }

    Rect::Rect( const Point<Int64>& top_left, const Point<Int64>& bottom_right ) {
        _top = top_left.get_y();
        _left = top_left.get_x();
        _right = bottom_right.get_x();
        _bottom = bottom_right.get_y();
    }

    Rect::Rect( const Point<Int64>* top_left, const Point<Int64>* bottom_right ) {
        _top = top_left->get_y();
        _left = top_left->get_x();
        _right = bottom_right->get_x();
        _bottom = bottom_right->get_y();
    }

    Rect::~Rect() {}

    /* getters/setters */

    Int64 Rect::get_y() const {
        return _top;
    }

    Int64 Rect::get_x() const {
        return _left;
    }

    Int64 Rect::get_top() const {
        return _top;
    }

    Int64 Rect::get_bottom() const {
        return _bottom;
    }

    Int64 Rect::get_right() const {
        return _right;
    }

    Int64 Rect::get_left() const {
        return _left;
    }

    Point<Int64> Rect::get_center() const {
        Point<Int64> ret_point;
        if ( is_valid() ) {
            ret_point.set_x( _left + ( get_width() / 2) );
            ret_point.set_y( _top + ( get_height() / 2 ) );
        } else {
            std::cout << "LOG THIS ERROR - Rect::get_center()" << std::endl;
        }
        return ret_point;
    }

    inline Int64 Rect::get_width() const {
        return _right - _left;
    }

    inline Int64 Rect::get_height() const {
        return _bottom - _top;
    }

    inline Point<Int64> Rect::get_top_left() const {
        return Point<Int64>( _left, _top );
    }

    inline Point<Int64> Rect::get_top_right() const {
        return Point<Int64>( _right, _top );
    }

    inline Point<Int64> Rect::get_bottom_left() const {
        return Point<Int64>( _left, _bottom );
    }

    inline Point<Int64> Rect::get_bottom_right() const {
        return Point<Int64>( _right, _bottom );
    }

    inline void Rect::set_x( const Int64 x ) {
        _left = x;
    }

    inline void Rect::set_y( const Int64 y ) {
        _top = y;
    }

    inline void Rect::set( const Int64 left, const Int64 top, const Int64 right, const Int64 bottom ) {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }

    inline void Rect::set_top( const Int64 top ) {
        _top = top;
    }

    inline void Rect::set_left( const Int64 left ) {
        _left = left;
    }

    inline void Rect::set_right( const Int64 right ) {
        _right = right;
    }

    inline void Rect::set_bottom( const Int64 bottom ) {
        _bottom = bottom;
    }


    /* Methods */

    inline bool Rect::is_valid() const {
        return _left <= _right && _top <= _bottom;
    }

    inline bool Rect::is_zero() const {
        return _left == 0 && _top == 0 && _right == 0 && _bottom == 0;
    }
    
    inline void Rect::reset() {
        _left = 0;
        _top = 0;
        _right = 0;
        _bottom = 0;
    }

    inline void Rect::shift_x( const Int64 delta_x ) {
        _left += delta_x;
        _right += delta_x;
    }

    inline void Rect::shift_y( const Int64 delta_y ) {
        _top += delta_y;
        _bottom += delta_y;
    }

    inline void Rect::move_delta( const Int64 delta_x, const Int64 delta_y ) {
        _left += delta_x;
        _top += delta_y;
        _right += delta_x;
        _bottom += delta_y;
    }

    inline void Rect::move_delta( const Point<Int64>& delta ) {
        move_delta( delta.get_x() , delta.get_y() );
    }

    inline void Rect::move_delta( const Point<Int64>* delta ) {
        move_delta( delta->get_x(), delta->get_y() );
    }

    inline void Rect::move_to( const Int64 x, const Int64 y ) {
        Int64 width = get_width();
        Int64 height = get_height();
        _left = x;
        _right = _left + width;
        _top = y;
        _bottom = _top + height;
    }

    inline void Rect::move_to( const Point<Int64>& point ) {
        move_to( point.get_x(), point.get_y() );
    }

    inline void Rect::move_to( const Point<Int64>* point ) {
        move_to( point->get_x(), point->get_y() );
    }

    inline bool Rect::is_collision( const Point<Int64>& point ) const {
        return ( point.get_x() >= _left && point.get_x() <= _right ) && 
               ( point.get_y() >= _top && point.get_y() <= _bottom );
    }

    inline bool Rect::is_collision( const Point<Int64>* point ) const {
        return is_collision( *point );
    }

    inline bool Rect::is_collision( const Rect& other ) const {
        return !( other.get_bottom() < _top || other.get_right() < _left ||
                  other.get_left() > _right || other.get_top() > _bottom );
    }

    inline bool Rect::is_collision( const Rect* other ) const {
        return is_collision( *other );
    }

    inline bool Rect::is_within( const Point<Int64>& point ) const {
        return ( point.get_x() > _left && point.get_x() < _right ) &&
               ( point.get_y() > _top && point.get_y() < _bottom );
    }

    inline bool Rect::is_within( const Point<Int64>* point ) const {
        return is_within( *point );
    }

    inline bool Rect::is_within( const Rect& other ) const {
        return ( other.get_left() >= _left && other.get_right() <= _right ) &&
               ( other.get_top() >= _top && other.get_bottom() <= _bottom );
    }

    inline bool Rect::is_within( const Rect* other ) const {
        return is_within( *other );
    }

    /* operator overloads */

    inline Rect& Rect::operator=( const Rect& new_rect ) {
        _left = new_rect.get_left();
        _top = new_rect.get_top();
        _right = new_rect.get_right();
        _bottom = new_rect.get_bottom();
        return ( *this );
    }

    inline Rect& Rect::operator=( const Rect* new_rect ) {
        _left = new_rect->get_left();
        _top = new_rect->get_top();
        _right = new_rect->get_right();
        _bottom = new_rect->get_bottom();
        return ( *this );
    }

    inline Rect& Rect::operator+=( const Rect& new_rect ) {
        _left += new_rect.get_left();
        _top += new_rect.get_top();
        _right += new_rect.get_right();
        _bottom += new_rect.get_bottom();
        return ( *this );
    }

    inline Rect& Rect::operator-=( const Rect& new_rect ) {
        _left -= new_rect.get_left();
        _top -= new_rect.get_top();
        _right -= new_rect.get_right();
        _bottom -= new_rect.get_bottom();
        return ( *this );
    }

    inline Rect& Rect::operator+=( const Rect* new_rect ) {
        _left += new_rect->get_left();
        _top += new_rect->get_top();
        _right += new_rect->get_right();
        _bottom += new_rect->get_bottom();
        return ( *this );
    }

    inline Rect& Rect::operator-=( const Rect* new_rect ) {
        _left -= new_rect->get_left();
        _top -= new_rect->get_top();
        _right -= new_rect->get_right();
        _bottom -= new_rect->get_bottom();
        return ( *this );
    }

    inline Rect Rect::operator+( const Rect& rect ) const {
        Rect ret_rect( this );
        ret_rect += rect;
        return ret_rect;
    }

    inline Rect Rect::operator-( const Rect& rect ) const {
        Rect ret_rect( this );
        ret_rect -= rect;
        return ret_rect;
    }

    inline bool Rect::operator==( const Rect& other ) const {
        return _left == other.get_left() && _top == other.get_top()
            && _right == other.get_right() && _bottom == other.get_bottom();
    }

    inline bool Rect::operator!=( const Rect& other ) const {
        return _left != other.get_left() || _top != other.get_top()
            || _right != other.get_right() || _bottom != other.get_bottom();
    }

    /* ostream/istream */

    std::ostream& operator<<( std::ostream& os, const Rect& rect ) {
        os << rect.to_string() << " - left:" << rect.get_left() << " top:" << rect.get_top()
            << " right:" << rect.get_right() << " bottom:" << rect.get_bottom();
        return os;
    }


    #ifdef _DEBUG
    namespace RectUnitTest {

        using namespace ZeroEngine;

        static void ctor() {
            std::cout << "ctor" << std::endl;
            Rect r;
            assert( r.get_y() == 0 );
            assert( r.get_x() == 0 );
            assert( r.get_top() == 0 );
            assert( r.get_bottom() == 0 );
            assert( r.get_left() == 0 );
            assert( r.get_right() == 0 );
        }

        static void ctor_x_y_w_h() {
            std::cout << "ctor_x_y_w_h" << std::endl;
            Int64 left = 1;
            Int64 top = 1;
            Int64 right = 2;
            Int64 bottom = 2;
            Rect rect( left, top, right, bottom );
            assert( rect.get_y() == top );
            assert( rect.get_x() == left ); 
            assert( rect.get_top() == top );
            assert( rect.get_bottom() == bottom );
            assert( rect.get_left() == left );
            assert( rect.get_right() == right );
        }

        static void ctor_ref_rect() {
            std::cout << "ctor_ref_rect" << std::endl;
            Rect rect( 3, 3, 3, 3 );
            Rect new_rect( rect );
            assert( new_rect.get_top() == rect.get_top() );
            assert( new_rect.get_bottom() == rect.get_bottom() );
            assert( new_rect.get_left() == rect.get_left() );
            assert( new_rect.get_right() == rect.get_right() );
        }

        static void ctor_ptr_rect() {
            std::cout << "ctor_ptr_rect" << std::endl;
            Rect rect( 3, 3, 3, 3 );
            Rect new_rect( &rect );
            assert( new_rect.get_top() == rect.get_top() );
            assert( new_rect.get_bottom() == rect.get_bottom() );
            assert( new_rect.get_left() == rect.get_left() );
            assert( new_rect.get_right() == rect.get_right() );
        }

        static void ctor_ref_point_tl_br() {
            std::cout << "ctor_ref_point_tl_br" << std::endl;
            Point<Int64> top_left( 0, 0 );
            Point<Int64> bottom_right( 5, 5 );
            Rect rect( top_left, bottom_right );
            assert( rect.get_top() == top_left.get_y() );
            assert( rect.get_left() == top_left.get_x() );
            assert( rect.get_bottom() == bottom_right.get_y() );
            assert( rect.get_right() == bottom_right.get_x() );
        }

        static void ctor_ptr_point_tl_br() {
            std::cout << "ctor_ptr_point_tl_br" << std::endl;
            Point<Int64> top_left( 0, 0 );
            Point<Int64> bottom_right( 5, 5 );
            Rect rect( &top_left, &bottom_right );
            assert( rect.get_top() == top_left.get_y() );
            assert( rect.get_left() == top_left.get_x() );
            assert( rect.get_bottom() == bottom_right.get_y() );
            assert( rect.get_right() == bottom_right.get_x() );
        }

        static void get_width_get_height() {
            std::cout << "get_width_get_height" << std::endl;
            Rect rect( 0, 0, 3, 3 );
            assert( rect.get_width() == 3 );
            assert( rect.get_height() == 3 );
            Rect rect2( 4, 4, 8, 8 );
            assert( rect2.get_width() == 4 );
            assert( rect2.get_height() == 4 );
        }

        static void getter_get_center() {
            std::cout << "getter_get_center" << std::endl;
            Rect rect( 1, 1, 5, 5 );
            Point<Int64> center = rect.get_center();
            assert( center == Point<Int64>( 3, 3 ) );
        }

        static void getters_tl_tr_bl_br() {
            std::cout << "get_tl_tr_bl_br" << std::endl;
            Int64 left = 3;
            Int64 top = 3;
            Int64 right = 5;
            Int64 bottom = 5;
            Rect rect1( left, top, right, bottom );
            Point<Int64> top_left( left, top );
            assert( rect1.get_top_left() == top_left );
            assert( rect1.get_top_right() == Point<Int64>( right, top ) );
            assert( rect1.get_bottom_left() == Point<Int64>( left, bottom ) );
            assert( rect1.get_bottom_right() == Point<Int64>( right, bottom ) );
            left = 30;
            top = 2;
            right = 60;
            bottom = 100;
            Rect rect2( left, top, right, bottom );
            assert( rect2.get_top_left() == Point<Int64>( left, top ) );
            assert( rect2.get_top_right() == Point<Int64>( right, top ) );
            assert( rect2.get_bottom_left() == Point<Int64>( left, bottom ) );
            assert( rect2.get_bottom_right() == Point<Int64>( right, bottom ) );
        }

        static void setters_x_y_set_t_l_r_b() {
            std::cout << "setters_x_y_set_t_l_r_b" << std::endl;
            Rect rect;
            rect.set_x( 1 );
            rect.set_y( 1 );
            assert( rect.get_x() == 1 && rect.get_y() == 1 );
            rect.set_top( 3 );
            rect.set_bottom( 3 );
            rect.set_left( 3 );
            rect.set_right( 3 );
            bool result = rect.get_top() == 3  
                       && rect.get_bottom() == 3
                       && rect.get_left() == 3 
                       && rect.get_right() == 3;
            assert( result );
            rect.set( 5, 5, 5, 5 );
            result = rect.get_top() == 5
                  && rect.get_bottom() == 5
                  && rect.get_left() == 5
                  && rect.get_right() == 5;
            assert( result );
        }

        static void methods_is_valid_is_zero_reset() {
            std::cout << "methods_is_valid_is_zero_reset" << std::endl;
            Rect rect;
            assert( rect.is_zero() == true );
            rect.set_top( 3 );
            assert( rect.is_zero() == false );
            assert( rect.is_valid() == false );
            rect.set_bottom( 10 );
            assert( rect.is_valid() == true );
            rect.set_left( 3 );
            assert( rect.is_valid() == false );
            rect.set_right( 10 );
            assert( rect.is_valid() == true );
            rect.reset();
            assert( rect.is_zero() == true );
        }

        static void methods_shift_x_shift_y() {
            std::cout << "methods_shift_x_shift_y" << std::endl;
            Int64 left = 3;
            Int64 top = 3;
            Int64 right = 6;
            Int64 bottom = 6;
            Rect rect( left, top, right, bottom );
            Int64 delta = 3;
            rect.shift_x( delta );
            assert( rect.get_left() == left + delta );
            assert( rect.get_right() == right + delta );
            rect.shift_y( delta );
            assert( rect.get_top() == top + delta );
            assert( rect.get_bottom() == bottom + delta );
        }

        static void methods_move_delta() {
            std::cout << "methods_move_delta" << std::endl;
            Int64 left = 2;
            Int64 top = 2;
            Int64 right = 5;
            Int64 bottom = 5;
            Rect rect( left, top, right, bottom );
            Point<Int64> point( 3, 3 );
            rect.move_delta( point.get_x(), point.get_y() );
            assert( rect.get_left() == left + point.get_x() );
            assert( rect.get_top() == top + point.get_y() );
            assert( rect.get_right() == right + point.get_x() );
            assert( rect.get_bottom() == bottom + point.get_y() );
            left = rect.get_left();
            top = rect.get_top();
            right = rect.get_right();
            bottom = rect.get_bottom();
            rect.move_delta( point );
            assert( rect.get_left() == left + point.get_x() );
            assert( rect.get_top() == top + point.get_y() );
            assert( rect.get_right() == right + point.get_x() );
            assert( rect.get_bottom() == bottom + point.get_y() );
            left = rect.get_left();
            top = rect.get_top();
            right = rect.get_right();
            bottom = rect.get_bottom();
            rect.move_delta( &point );
            assert( rect.get_left() == left + point.get_x() );
            assert( rect.get_top() == top + point.get_y() );
            assert( rect.get_right() == right + point.get_x() );
            assert( rect.get_bottom() == bottom + point.get_y() );
        }

        static void methods_move_to() {
            std::cout << "methods_move_to" << std::endl;
            Point<Int64> start_tl( 1, 1 );
            Point<Int64> start_br( 5, 5 );
            Point<Int64> delta( 3, 3 );
            Rect rect( start_tl, start_br );
            rect.move_to( delta.get_x(), delta.get_y() );
            assert( rect.get_left() == 3 
                    && rect.get_top() == 3 
                    && rect.get_right() == 7 
                    && rect.get_bottom() == 7 
            );
            rect.set_left( start_tl.get_x() );
            rect.set_top( start_tl.get_y() );
            rect.set_right( start_br.get_x() ); 
            rect.set_bottom( start_br.get_y() );
            rect.move_to( delta );
            assert( rect.get_left() == 3 
                    && rect.get_top() == 3 
                    && rect.get_right() == 7 
                    && rect.get_bottom() == 7 
            );
            rect.set_left( start_tl.get_x() );
            rect.set_top( start_tl.get_y() );
            rect.set_right( start_br.get_x() ); 
            rect.set_bottom( start_br.get_y() );
            rect.move_to( &delta );
            assert( rect.get_left() == 3 
                    && rect.get_top() == 3 
                    && rect.get_right() == 7 
                    && rect.get_bottom() == 7 
            );
        }

        static void methods_is_collision() {
            std::cout << "methods_is_collision" << std::endl;
            Rect rect1( 1, 1, 4, 4 );
            Point<Int64> point1( 2, 2 );
            assert( rect1.is_collision( point1 ) == true );
            point1.set( 5, 5 );
            assert( rect1.is_collision( point1 ) == false );
            point1.set( 3, 3 );
            assert( rect1.is_collision( &point1 ) == true );
            point1.set( 4, 4 );
            assert( rect1.is_collision( &point1 ) == true );
            Rect rect2( 5, 3, 8, 6 );
            assert( rect1.is_collision( rect2 ) == false );
            rect2.move_to( 3, 1 );
            assert( rect1.is_collision( &rect2 ) == true );
            rect2.move_to( 4, 3 );
            assert( rect1.is_collision( rect2 ) == true );
        }

        static void methods_is_within() {
            std::cout << "methods_is_within" << std::endl;
            Rect rect( 1, 1, 4, 4 );
            Point<Int64> point( 2, 2 );
            assert( rect.is_within( point ) == true );
            point.set( 4, 4 );
            assert( rect.is_within( &point ) == false );
            Rect other( 1, 1, 3, 3 );
            assert( rect.is_within( other ) == true );
            other.set_bottom( rect.get_bottom() );
            other.set_right( rect.get_right() );
            assert( rect.is_within( other ) == true );
            other.move_to( 4, 4 );
            assert( rect.is_within( &other ) == false );
        }

        static void operator_assignment() {
            std::cout << "operator_assignment" << std::endl;
            Rect rect( 1, 1, 3, 3 );
            Rect rect2 = rect;
            assert( rect.get_left() == rect2.get_left()
                    && rect.get_top() == rect2.get_top()
                    && rect.get_right() == rect2.get_right()
                    && rect.get_bottom() == rect2.get_bottom()
            );
            Rect rect3( 4, 4, 8, 8 );
            rect2 = &rect3;
            assert( rect2.get_left() == rect3.get_left()
                    && rect2.get_top() == rect3.get_top()
                    && rect2.get_right() == rect3.get_right()
                    && rect2.get_bottom() == rect3.get_bottom() 
            );
        }

        static void operator_compounds() {
            std::cout << "operator_compounds" << std::endl;
            Rect rect( 1, 1, 2, 2 );
            Rect rect2 = rect;
            rect += rect2;
            assert( rect.get_left() == 2
                    && rect.get_top() == 2
                    && rect.get_right() == 4
                    && rect.get_bottom() == 4
            );
            rect += &rect2;
            assert( rect.get_left() == 3 
                    && rect.get_top() == 3 
                    && rect.get_right() == 6 
                    && rect.get_bottom() == 6 
            );
            rect -= rect2;
            assert( rect.get_left() == 2 
                    && rect.get_top() == 2 
                    && rect.get_right() == 4 
                    && rect.get_bottom() == 4 
            );
            rect -= &rect2;
            assert( rect.get_left() == 1 
                    && rect.get_top() == 1 
                    && rect.get_right() == 2 
                    && rect.get_bottom() == 2 
            );
        }

        static void operator_add_subtract() {
            std::cout << "operator_add_subtract" << std::endl;
            Rect rect1( 1, 1, 2, 2 );
            Rect rect2( rect1 );
            Rect rect = rect1 + rect2;
            assert( rect.get_left() == 2
                    && rect.get_top() == 2
                    && rect.get_right() == 4
                    && rect.get_bottom() == 4
            );
            rect = rect1 - rect2;
            assert( rect.is_zero() == true );
        }

        static void operator_comparison() {
            std::cout << "operator_comparison" << std::endl;
            Rect rect1( 3, 3, 5, 5 );
            Rect rect2( 3, 3, 5, 5 );
            assert( rect1 == rect2 );
            rect2.set( 2, 2, 6, 6 );
            assert( rect1 != rect2 );
            rect2 = rect1;
            assert( ( rect1 != rect2 ) == false );
            rect2.set( 2, 2, 6, 6 );
            assert( ( rect1 == rect2 ) == false );
        }

        extern void run() {
            std::cout << "Rect Unit Test begin" << std::endl;
            std::cout << "--------------------" << std::endl;
            RectUnitTest::ctor();
            ctor_x_y_w_h();
            ctor_ref_rect();
            ctor_ptr_rect();
            ctor_ref_point_tl_br();
            ctor_ptr_point_tl_br();
            get_width_get_height();
            getters_tl_tr_bl_br();
            getter_get_center();
            setters_x_y_set_t_l_r_b();
            methods_is_valid_is_zero_reset();
            methods_shift_x_shift_y();
            methods_move_delta();
            methods_move_to();
            methods_is_collision();
            methods_is_within();
            operator_assignment();
            operator_compounds();
            operator_add_subtract();
            operator_comparison();
            std::cout << "--------------------" << std::endl;
            std::cout << "Rect Unit Test end" << std::endl; 
        }
    }
    #endif
}
