#include "Rect.h"

namespace ZeroEngine {

    /* Construction interface */
    Rect::Rect() {
        _left = 0;
        _right = 0;
        _top = 0;
        _bottom = 0;
    }

    Rect::Rect( const long left, const long top, const long right, const long bottom ) {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }

    // TODO: 10/1
    Rect::Rect( const Point<long>& center, const long width, const long height ) {

    }

    // TODO: 10/1
    Rect::Rect( const Point<long>* center, const long width, const long height ) {

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

    Rect::Rect( const Point<long>& top_left, const Point<long>& bottom_right ) {
        _top = top_left.get_y();
        _left = top_left.get_x();
        _right = bottom_right.get_x();
        _bottom = bottom_right.get_y();
    }

    Rect::Rect( const Point<long>* top_left, const Point<long>* bottom_right ) {
        _top = top_left->get_y();
        _left = top_left->get_x();
        _right = bottom_right->get_x();
        _bottom = bottom_right->get_y();
    }

    Rect::~Rect() {}

    /* getters/setters */

    long Rect::get_y() const {
        return _top;
    }

    long Rect::get_x() const {
        return _left;
    }

    long Rect::get_top() const {
        return _top;
    }

    long Rect::get_bottom() const {
        return _bottom;
    }

    long Rect::get_right() const {
        return _right;
    }

    long Rect::get_left() const {
        return _left;
    }

    // TODO: Unit Test - 10/2/2017
    Point<long> Rect::get_center() const {
        Point<long> ret_point;
        if ( is_valid() ) {
            ret_point.set_x( _left + ( get_width() / 2) );
            ret_point.set_y( _top + ( get_height() / 2 ) );
        } else {
            std::cout << "LOG THIS ERROR - Rect::get_center()" << std::endl;
        }
        return ret_point;
    }

    inline long Rect::get_width() const {
        return _right - _left;
    }

    inline long Rect::get_height() const {
        return _bottom - _top;
    }

    inline Point<long> Rect::get_top_left() const {
        return Point<long>( _left, _top );
    }

    inline Point<long> Rect::get_top_right() const {
        return Point<long>( _right, _top );
    }

    inline Point<long> Rect::get_bottom_left() const {
        return Point<long>( _left, _bottom );
    }

    inline Point<long> Rect::get_bottom_right() const {
        return Point<long>( _right, _bottom );
    }

    inline void Rect::set_x( const long x ) {
        _left = x;
    }

    inline void Rect::set_y( const long y ) {
        _top = y;
    }

    inline void Rect::set( const long left, const long top, const long right, const long bottom ) {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }

    inline void Rect::set_top( const long top ) {
        _top = top;
    }

    inline void Rect::set_left( const long left ) {
        _left = left;
    }

    inline void Rect::set_right( const long right ) {
        _right = right;
    }

    inline void Rect::set_bottom( const long bottom ) {
        _bottom = bottom;
    }


    /* Methods */

    inline bool Rect::is_valid() const {
        return _left <= _right && _top <= _bottom;
    }

    inline bool Rect::is_zero() const {
        return _left == 0 && _top == 0 && _right == 0 && _bottom == 0;
    }

    /* ostream/istream */

    std::ostream& operator<<( std::ostream& os, const Rect& rect ) {
        os << rect.get_type() << " - left:" << rect.get_left() << " right:" << rect.get_right()
            << " top:" << rect.get_top() << " bottom:" << rect.get_bottom();
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
            long left = 1;
            long top = 1;
            long right = 2;
            long bottom = 2;
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
            Point<long> top_left( 0, 0 );
            Point<long> bottom_right( 5, 5 );
            Rect rect( top_left, bottom_right );
            assert( rect.get_top() == top_left.get_y() );
            assert( rect.get_left() == top_left.get_x() );
            assert( rect.get_bottom() == bottom_right.get_y() );
            assert( rect.get_right() == bottom_right.get_x() );
        }

        static void ctor_ptr_point_tl_br() {
            std::cout << "ctor_ptr_point_tl_br" << std::endl;
            Point<long> top_left( 0, 0 );
            Point<long> bottom_right( 5, 5 );
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

        static void getters_tl_tr_bl_br() {
            std::cout << "get_tl_tr_bl_br" << std::endl;
            long left = 3;
            long top = 3;
            long right = 5;
            long bottom = 5;
            Rect rect1( left, top, right, bottom );
            Point<long> top_left( left, top );
            assert( rect1.get_top_left() == top_left );
            assert( rect1.get_top_right() == Point<long>( right, top ) );
            assert( rect1.get_bottom_left() == Point<long>( left, bottom ) );
            assert( rect1.get_bottom_right() == Point<long>( right, bottom ) );
            left = 30;
            top = 2;
            right = 60;
            bottom = 100;
            Rect rect2( left, top, right, bottom );
            assert( rect2.get_top_left() == Point<long>( left, top ) );
            assert( rect2.get_top_right() == Point<long>( right, top ) );
            assert( rect2.get_bottom_left() == Point<long>( left, bottom ) );
            assert( rect2.get_bottom_right() == Point<long>( right, bottom ) );
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

        static void methods_is_valid_is_zero() {
            std::cout << "methods_is_valid_is_zero" << std::endl;
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
            setters_x_y_set_t_l_r_b();
            methods_is_valid_is_zero();
            std::cout << "--------------------" << std::endl;
            std::cout << "Rect Unit Test end" << std::endl; 
        }
    }
    #endif
}
