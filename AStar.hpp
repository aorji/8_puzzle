/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:58:52 by aorji             #+#    #+#             */
/*   Updated: 2019/10/05 18:22:16 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_ASTAR_HPP
#define I_ASTAR_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "HeuristicFunction.hpp"

enum eState
{
    FAILURE = 0,
    SUCCESS = 1
};

class AStar
{
public:
    AStar(std::vector<Point *> puzzle, int puzzle_size, Point *start):
        _initial_state(puzzle),
        _puzzle_size(puzzle_size),
        _starting_point(start)
    {
        _open_list.push_back(_starting_point);
        _G[_starting_point] = 0;
        path_cost(_starting_point);
        _heuristic_function = new ManhattanDistance();// = heuristic_func_generatir();
    }
    ~AStar(){};

    eState run(void)
    {
        while (!_open_list.empty())
        {
            Point *curr = available_min_F();
            if (is_goal_state())
                return SUCCESS;
            priint_open_closed();
            add_to_slosed(curr);
            priint_open_closed();
            std::cout << "\n----------\n";
            for (Point *neigbour: unclosed_neigbours(curr))
            {
                long tmp_g = _G[curr]; // + distance(curr, neigbour);
                if (!is_open(neigbour) || tmp_g < _G[neigbour])
                {
                    from[neigbour] = curr;
                    _G[neigbour] = tmp_g;
                    path_cost(neigbour);
                    if (is_available(neigbour))
                        add_to_open(neigbour);
                }
            }
        }
        return FAILURE;
    }

private:
    AStar();
    AStar(AStar const &);
    AStar & operator=(AStar const &);

    Point *available_min_F(void)
    {
        Point *min = _open_list.back();
        for(Point *item: _open_list)
        {
            if (_F[item] < _F[min])
                min = item;
        }
        return min;
    }
    bool is_goal_state(void)
    {
        size_t c = 0;
        for(Point *item: _initial_state)
        {
            c++;
            if (item->get_value() != c)
            {
                if (c == _puzzle_size*_puzzle_size && item->get_value() == 0)
                {
                    std::cout << "goal state\n";
                    return true;
                }
                std::cout << "not finished\n";
                return false;
            }
        }
        std::cout << "not finished\n";
        return false;
    }
    //AVAILABLE
    bool is_available(Point *p)
    {
        return (p->get_point_state() == NONE);
    }
    //OPEN
    bool is_open(Point *p)
    {
        return (p->get_point_state() == OPEN);
    }

    void add_to_open(Point *p)
    {
        if(p->get_point_state() == NONE)
        {
            _open_list.push_back(p);
            p->set_point_state(OPEN);
        }
    }
    void remove_from_open(Point *p)
    {
        for(std::vector<Point *>::iterator it = _open_list.begin(); it != _open_list.end(); ++it)
        {
            if (*it == p)
            {
                _open_list.erase(it);
                return;
            }
        }
    }
    //CLOSED
    void add_to_slosed(Point *p)
    {
        remove_from_open(p);
        p->set_point_state(CLOSED);
        _closed_list.push_back(p);
    }
    std::vector<Point *> unclosed_neigbours(Point *curr)
    {
        std::vector<Point *> unclosed;
        int i = curr->get_i();
        int j = curr->get_j();
        
        if ( j - 1 >= 0 && (_initial_state[_puzzle_size * i + j - 1])->get_point_state() != CLOSED )
            unclosed.push_back(_initial_state[_puzzle_size * i + j - 1]);
        if ( j + 1 < _puzzle_size && (_initial_state[_puzzle_size * i + j + 1])->get_point_state() != CLOSED )
            unclosed.push_back(_initial_state[_puzzle_size * i + j + 1]);
        if ( i - 1 >= 0 && (_initial_state[_puzzle_size * (i - 1) + j])->get_point_state() != CLOSED )
            unclosed.push_back(_initial_state[_puzzle_size * (i - 1) + j]);
        if ( i + 1 < _puzzle_size && (_initial_state[_puzzle_size * (i + 1) + j])->get_point_state() != CLOSED )
            unclosed.push_back(_initial_state[_puzzle_size * (i + 1) + j]);

        return unclosed;
    }
    void path_cost(Point *p)
    {
        _F[p] = _G[p] + _heuristic_function->path_cost(p);
    }
    //AUXILARY
    void priint_open_closed()
    {
        std::cout << "\nclosed\n";
        if (!_closed_list.empty())
        {
            for(Point *item: _closed_list)
            {
                std::cout << item->get_value() << " ";
            }
        }
        std::cout << "\nopen\n";
        if (!_open_list.empty())
        {
            for(Point *item: _open_list)
            {
                std::cout << item->get_value() << " ";
            }
        }
    }

    std::vector<Point *> _closed_list;
    std::vector<Point *> _open_list;
    std::map<Point *, Point *> from;
    std::vector<Point *> _initial_state;
    HeuristicFunction *_heuristic_function;
    int _puzzle_size;
    Point *_starting_point;
    std::map<Point *, long> _G;
    std::map<Point *, long> _F;
};

#endif