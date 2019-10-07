/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:58:52 by aorji             #+#    #+#             */
/*   Updated: 2019/10/07 16:58:20 by aorji            ###   ########.fr       */
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
            add_to_slosed();
            std::cout << *(_puzzle) << std::endl;
            if (is_goal_state())
                return SUCCESS;
            for (Puzzle *state: unclosed_state())
            {
                long tmp_g = _G[_puzzle] + distance();
                if (!is_open(state) || tmp_g < _G[state])
                {
                    _G[state] = tmp_g;
                    path_cost(state);
                    if (no_state(state)){
                        add_to_open(state);}
                }
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
        int puzzle_size = _puzzle->get_puzzle_size();
        for (int i = 0; i < puzzle_size * puzzle_size; ++i)
        {
            if ((_puzzle->get_data())[i].get_value() != (_puzzle->get_goal_state())[i].get_value())
                return false;
        }
        return true;
    }
    //AVAILABLE
    bool no_state(Puzzle *p)
    {
        return (p->get_puzzle_state() == NONE);
    }
    //OPEN
    bool is_open(Puzzle *p)
    {
        return (p->get_puzzle_state() == OPEN);
    }

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
            if (**it == *p)
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
        std::vector<Puzzle *> states;
        states = get_available_states();
        // remove those who are closed
        for (auto i = 0; i < states.size(); ++i)
        {
            for (Puzzle *closed: _closed_list)
            {
                if (states[i] == closed)
                    states.erase(states.begin() + i, states.begin() + i + 1);
            }
        }
        return states;
    }

    std::vector<Puzzle *> get_available_states(void)
    {
        std::vector<Point> init_state = _puzzle->get_data();
        Point zero_point = _puzzle->get_zero_point();
        int size = _puzzle->get_puzzle_size();
        int i = zero_point.get_i();
        int j = zero_point.get_j();

        std::vector<Puzzle *> states;

        if ( j - 1 >= 0 )
        {
            Puzzle *pzl = new Puzzle(*_puzzle);
            pzl->set_puzzle_state(NONE);
            pzl->swap_points(init_state[size * i + j - 1]);
            states.push_back(pzl);
        }
        if ( j + 1 < size )
        {
            Puzzle *pzl = new Puzzle(*_puzzle);
            pzl->set_puzzle_state(NONE);
            pzl->swap_points(init_state[size * i + j + 1]);
            states.push_back(pzl);
        }
        if ( i - 1 >= 0 )
        {
            Puzzle *pzl = new Puzzle(*_puzzle);
            pzl->set_puzzle_state(NONE);
            pzl->swap_points(init_state[size * (i - 1) + j]);
            states.push_back(pzl);
        }
        if ( i + 1 < size )
        {
            Puzzle *pzl = new Puzzle(*_puzzle);
            pzl->set_puzzle_state(NONE);
            pzl->swap_points(init_state[size * (i + 1) + j]);
            states.push_back(pzl);
        }
        return states;
    }
    // //AUXILARY
    // 
    long distance(){
        return 1;
    }
    void path_cost(Puzzle *p)
    {
        _F[p] = _G[p] + _heuristic_function->path_cost(p);
        // std::cout << _F[p] << std::endl;
    }

    std::vector<Puzzle *> _closed_list;
    std::vector<Puzzle *> _open_list;
    HeuristicFunction *_heuristic_function;
    std::map<Puzzle *, long> _G;
    std::map<Puzzle *, long> _F;
    Puzzle *_puzzle;
};

#endif