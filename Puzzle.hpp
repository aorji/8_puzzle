/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 14:37:31 by aorji             #+#    #+#             */
/*   Updated: 2019/10/07 16:56:29 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_PUZZLE_HPP
#define I_PUZZLE_HPP

#include "Point.hpp"
#include <vector>

enum ePuzzleState
{
    CLOSED = 0,
    OPEN = 1,
    NONE = 2
};

class Puzzle
{
public:
    explicit Puzzle(int size): _puzzle_size(size), _puzzle_state(NONE) { set_goal_state(); _zero_point = Point(); }
    // Puzzle(std::vector<Point *> puzzle, int size): _data(puzzle), _puzzle_size(size), _puzzle_state(NONE) { set_goal_state(); }
    // Puzzle(std::vector<Point *> puzzle, std::vector<Point *> goal_state, int size):
    //                     _data(puzzle), _puzzle_size(size),
    //                     _goal_state(goal_state), _puzzle_state(NONE) {}
    Puzzle(Puzzle const &p)
    {
        set_goal_state();
        _zero_point = p._zero_point;
        _data = p._data;
        _puzzle_size = p._puzzle_size;
        _goal_state = p._goal_state;
        _puzzle_state = p._puzzle_state;
    }
    Puzzle & operator=(Puzzle const &p)
    {
        if (this != &p)
            Puzzle(p).swap(*this);
        return *this;
    }
    void swap(Puzzle & p)
    {
        std::swap(_zero_point, p._zero_point);
        std::swap(_data, p._data);
        std::swap(_puzzle_size, p._puzzle_size);
        std::swap(_goal_state, p._goal_state);
        std::swap(_puzzle_state, p._puzzle_state);
    }
    void swap_points(Point p)
    {
        Point zero = _zero_point;
        _data[_puzzle_size * _zero_point.get_i() + _zero_point.get_j()].swap_data(p);
        _data[_puzzle_size * p.get_i() + p.get_j()].swap_data(zero);
        set_zero_point(p);
    }
    ~Puzzle(){}

    int     get_puzzle_size(void) const { return _puzzle_size; }
    Point   get_zero_point(void) const { return _zero_point; }
    const   std::vector<Point> get_data(void) const { return _data; }
    const   std::vector<Point> get_goal_state(void) { return _goal_state; }
    
    void    set_zero_point(Point p) { if (p.get_value() == 0) _zero_point = p; }
    void    set_goal_state(void) { 
        for(int i = 1; i < _puzzle_size * _puzzle_size; ++i)
            _goal_state.push_back(Point(0, 0, i));
        _goal_state.push_back(Point(0, 0, 0));
    }
    
    void    fill_puzzle(void)
    {
        for(int i = 0; i < _puzzle_size; ++i)
        {
            for(int j = 0; j < _puzzle_size; ++j)
            {
                int value = 0;
                std::cin >> value;
                _data.push_back(Point(i, j, value));
                if (value == 0)
                {
                    static char times = 0;
                    ++times;
                    if (times > 1)
                    {
                        std::cout << "error: mulip 0" << std::endl;
                        exit(1); //throu exept 
                    }
                    _zero_point = _data[_puzzle_size * i + j];
                }
            }
        }
        if (_zero_point.get_value() != 0)
        {
            std::cout << "error: no 0";
            exit(1);
            //throu error
        }
    }

    ePuzzleState get_puzzle_state(void) const { return _puzzle_state; }
    void set_puzzle_state(ePuzzleState state) { _puzzle_state = state; }
    
private:
    Point _zero_point;
    std::vector<Point> _data;
    int _puzzle_size;
    std::vector<Point> _goal_state;
    ePuzzleState _puzzle_state;
};

std::ostream& operator<<(std::ostream &os, Puzzle const &p)
{
    int size = p.get_puzzle_size();
    std::vector<Point> data = p.get_data();

    os << "\n";
    for(int i = 0; i < size * size; ++i)
    {
        if (i && i % size == 0)
            os << "\n";
        os << (data[i]).get_value() << " ";
    }
    os << "\n";
    return os;
}

bool operator==(Puzzle const& p1, Puzzle const &p2)
{
    int puzzle_size = p1.get_puzzle_size();
    
    for (int i = 0; i < puzzle_size * puzzle_size; ++i)
    {
        if ((p1.get_data())[i] != (p2.get_data())[i])
            return false;
    }
    return true;
}
// bool operator!=(Puzzle const& p1, Puzzle const &p2)
// {
//     if (!(p1 == p2))
//         return true;
//     return false;
// }

#endif