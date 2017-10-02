#include "Rect.h"

namespace ZeroEngine {

    /* Construction interface */
    Rect::Rect() {
        _left = 0;
        _right = 0;
        _top = 0;
        _bottom = 0;
    }

    Rect::Rect( const long x, const long y, const long width, const long height ) {
        _left = x;
        _top = y;
        _right = x + width;
        _bottom = y + height;
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
            long l = 1;
            long t = 1;
            long w = 2;
            long h = 2;
            Rect rect( l, t, w, h );
            assert( rect.get_y() == t );
            assert( rect.get_x() == l ); 
            assert( rect.get_top() == t );
            assert( rect.get_bottom() == t + h );
            assert( rect.get_left() == l );
            assert( rect.get_right() == l + w );
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

        extern void run() {
            std::cout << "Rect Unit Test begin" << std::endl;
            RectUnitTest::ctor();
            ctor_x_y_w_h();
            ctor_ref_rect();
            ctor_ptr_rect();
            ctor_ref_point_tl_br();
            ctor_ptr_point_tl_br();
            std::cout << "Rect Unit Test end" << std::endl; 
        }
    }
    #endif
}
