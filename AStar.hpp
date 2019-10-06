/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:58:52 by aorji             #+#    #+#             */
/*   Updated: 2019/10/06 19:17:46 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_ASTAR_HPP
#define I_ASTAR_HPP

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
    explicit AStar(Puzzle *puzzle): _puzzle(puzzle)
    {
        add_to_open(_puzzle);
        _G[_puzzle] = 0;
        _heuristic_function = new MisplacedNum();// = heuristic_func_generatir();
        path_cost(_puzzle);
    }
    ~AStar(){};

    eState run(void)
    {
        while (!_open_list.empty())
        {
            compute_new_state();
            if (is_goal_state())
                return SUCCESS;
        //     Point *z_point = _puzzle->get_zero_point();
            add_to_slosed();
            for (Puzzle *state: unclosed_state())
            {
        //         long tmp_g = _G[z_point] + distance(neigbour, z_point);
        //         if (!is_open(neigbour) || tmp_g < _G[neigbour]) //closed, none or 
        //         {
        //             from[neigbour] = z_point;
        //             _G[neigbour] = tmp_g;
        //             path_cost(neigbour);
        //             if (no_state(neigbour))
        //                 add_to_open(neigbour);
        //         }
            }
        }
        return FAILURE;
    }

private:
    AStar();
    AStar(AStar const &);
    AStar & operator=(AStar const &);

    void compute_new_state(void)
    {
        _puzzle = find_profitable_state();
    }
    
    Puzzle *find_profitable_state()
    {
        Puzzle *min_F = _open_list.back();
        for(Puzzle *item: _open_list)
        {
            if (_F[item] < _F[min_F])
                min_F = item;
        }
        return min_F;
    }
    
    bool is_goal_state(void)
    {
        size_t c = 0;
        int puzzle_size = _puzzle->get_puzzle_size();
        for (int i = 0; i < puzzle_size * puzzle_size; ++i)
        {
            if ((_puzzle->get_data())[i] != (_puzzle->get_goal_state())[i])
                return false;
        }
        return true;
    }
    // //AVAILABLE
    // bool no_state(Point *p)
    // {
    //     return (p->get_point_state() == NONE);
    // }
    // //OPEN
    // bool is_open(Point *p)
    // {
    //     return (p->get_point_state() == OPEN);
    // }

    void add_to_open(Puzzle *p)
    {
        if(p->get_puzzle_state() == NONE)
        {
            _open_list.push_back(p);
            p->set_puzzle_state(OPEN);
        }
    }

    void remove_from_open(Puzzle *p)
    {
        for(std::vector<Puzzle *>::iterator it = _open_list.begin(); it != _open_list.end(); ++it)
        {
            if (*it == p)
            {
                _open_list.erase(it);
                return;
            }
        }
    }
    //CLOSED
    void add_to_slosed()
    {
        remove_from_open(_puzzle);
        _puzzle->set_puzzle_state(CLOSED);
        _closed_list.push_back(_puzzle);
    }

    std::vector<Puzzle *> unclosed_state()
    {
        //create states
        //chack in closed
        //return
        std::vector<Puzzle *> unclosed;
        std::vector<Puzzle *> states;

        std::vector<Point *> init_state = _puzzle->get_data();
        int size = _puzzle->get_puzzle_size();
        Point *zero_point = _puzzle->get_zero_point();
        int i = zero_point->get_i();
        int j = zero_point->get_j();
        
        if ( j - 1 >= 0 ) states.push_back(new_state(zero_point, init_state[size * i + j - 1]));
        if ( j + 1 < size ) states.push_back(new_state(zero_point, init_state[size * i + j + 1]));
        if ( i - 1 >= 0) states.push_back(new_state(zero_point, init_state[size * (i - 1) + j]));
        if (i + 1 < size ) states.push_back(new_state(zero_point, init_state[size * (i + 1) + j]));

        for (Puzzle *available: states)
        {
            for (Puzzle *closed: _closed_list)
            {
                if (available == closed)
                    available->set_puzzle_state(CLOSED);
            }
        }

        for (Puzzle *available: states)
        {
            if (available->get_puzzle_state() != CLOSED)
                unclosed.push_back(available);
        }
        return unclosed;
    }

    Puzzle *new_state(Point *p1, Point *p2)
    {
        return new Puzzle(1);
    }
    
    // std::vector<Point *> get_neigbours_list()
    // {
    //     std::vector<Point *> initial_state = _puzzle->get_data();
    //     std::vector<Point *> unclosed;
    //     int puzzle_size = _puzzle->get_puzzle_size();
    //     Point *current = _puzzle->get_zero_point();
    //     int i = current->get_i();
    //     int j = current->get_j();

    //     if ( j - 1 >= 0 && (initial_state[puzzle_size * i + j - 1])->get_point_state() == OPEN )
    //         unclosed.push_back(initial_state[puzzle_size * i + j - 1]);
    //     if ( j + 1 < puzzle_size && (initial_state[puzzle_size * i + j + 1])->get_point_state() == OPEN )
    //         unclosed.push_back(initial_state[puzzle_size * i + j + 1]);
    //     if ( i - 1 >= 0 && (initial_state[puzzle_size * (i - 1) + j])->get_point_state() == OPEN )
    //         unclosed.push_back(initial_state[puzzle_size * (i - 1) + j]);
    //     if ( i + 1 < puzzle_size && (initial_state[puzzle_size * (i + 1) + j])->get_point_state() == OPEN )
    //         unclosed.push_back(initial_state[puzzle_size * (i + 1) + j]);

    //     return unclosed;
    // }

    // //AUXILARY
    // void print_open_closed()
    // {
    //     std::cout << "\nclosed\n";
    //     if (!_closed_list.empty())
    //     {
    //         for(Point *item: _closed_list)
    //         {
    //             std::cout << item->get_value() << " ";
    //         }
    //     }
    //     std::cout << "\nopen\n";
    //     if (!_open_list.empty())
    //     {
    //         for(Point *item: _open_list)
    //         {
    //             std::cout << item->get_value() << " ";
    //         }
    //     }
    // }
    // 
    // long distance(Point *p1, Point *p2){
    //     return 1;
    // }
    void path_cost(Puzzle *p)
    {
        _F[p] = _G[p] + _heuristic_function->path_cost(p);
    }

    std::vector<Puzzle *> _closed_list;
    std::vector<Puzzle *> _open_list;
    std::map<Puzzle *, Puzzle *> from;
    HeuristicFunction *_heuristic_function;
    std::map<Puzzle *, long> _G;
    std::map<Puzzle *, long> _F;
    // Puzzle *_current;
    Puzzle *_puzzle;
};

#endif