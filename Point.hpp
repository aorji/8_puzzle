/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:07:51 by aorji             #+#    #+#             */
/*   Updated: 2019/10/05 18:08:28 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_POINT_HPP
#define I_POINT_HPP

#include <algorithm>

enum ePointState
{
    CLOSED = 0,
    OPEN = 1,
    NONE = 2
};

class Point
{
public:
    Point(int i, int j, int value):
                    _i(i), _j(j), _value(value), _point_state(NONE){}
    Point(Point const & p): _i(p._i), _j(p._j), _value(p._value), _point_state(p._point_state){}
    Point & operator=(Point const &p)
    {
        if (this != &p)
            Point(p).swap(*this);
        return *this;
    }
    void swap(Point & p)
    {
        std::swap(_i, p._i);
        std::swap(_j, p._j);
        std::swap(_value, p._value);
        std::swap(_point_state, p._point_state);
    }

    int get_value(void) const { return _value; }
    int get_i(void) const { return _i; }
    int get_j(void) const { return _j; }
    ePointState get_point_state(void) const { return _point_state; }
    void set_point_state(ePointState state) { _point_state = state; }
    
private:
    int _i;
    int _j;
    int _value;
    ePointState _point_state;
};

bool operator==(Point const& p1, Point const &p2)
{
    return (p1.get_i() == p2.get_i() && p1.get_j() == p2.get_j());
}

#endif