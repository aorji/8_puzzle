/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:58:52 by aorji             #+#    #+#             */
/*   Updated: 2019/10/07 22:03:09 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_ASTAR_HPP
#define I_ASTAR_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "HeuristicFunction.hpp"

static int d = 0;

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
        _heuristic_function = new ManhattanDistance();// = heuristic_func_generatir();
        path_cost(_puzzle);
    }
    ~AStar(){};
    eState run(void)
    {
        while (!_open_list.empty())
        {
            compute_new_state();
            if (is_goal_state(_puzzle))
                return SUCCESS;
            add_to_slosed();
            for (Puzzle *state: unclosed_state())
            {
                long tmp_g = _G[_puzzle] + distance();
                if (!is_open(state) || tmp_g < _G[state])
                {
                    from[state] = _puzzle;
                    _G[state] = tmp_g;
                    path_cost(state);
                    add_to_open(state);
                }
            }
        }
        return FAILURE;
    }
    void show_result()
    {
        std::vector<Puzzle *> res;
        Puzzle *p = _puzzle;
        while(p)
        {
            res.push_back(p);
            p = from[p];
        }
        for(int i = res.size() - 1; i >= 0; --i)
            std::cout << *(res[i]);
        std::cout << "\n" << res.size() - 1 << " steps" << std::endl;
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
    bool is_goal_state(Puzzle *p)
    {
        int puzzle_size = p->get_puzzle_size();
        std::vector<Point> data = p->get_data();
        std::vector<Point> goal = p->get_goal_state();
        
        for (int i = 0; i < puzzle_size * puzzle_size; ++i)
        {
            if (data[i] != goal[i])
                return false;
        }
        return true;
    }
    //OPEN
    bool is_open(Puzzle *p)
    {
        for(Puzzle *open: _open_list)
        {
            if (*open == *p)
                return true;
        }
        return false;
    }
    void add_to_open(Puzzle *p)
    {
        if (is_open(p))
            return;
        _open_list.push_back(p);
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
        _closed_list.push_back(_puzzle);
        remove_from_open(_puzzle);
    }

    bool is_closed(Puzzle *p)
    {
        for(Puzzle *closed: _closed_list)
        {
            if (*closed == *p)
                return true;
        }
        return false;
    }
    std::vector<Puzzle *> unclosed_state(void)
    {
        std::vector<Point> init_state = _puzzle->get_data();
        int size = _puzzle->get_puzzle_size();
        int i = _puzzle->get_zero_point().get_i();
        int j = _puzzle->get_zero_point().get_j();
        std::vector<Puzzle *> states;
        Puzzle *pzl;

        if ( j - 1 >= 0 )
        {
            pzl = new Puzzle(*_puzzle);
            pzl->swap_points(init_state[size * i + j - 1]);
            if (!is_closed(pzl))
                states.push_back(pzl);
        }
        if ( j + 1 < size )
        {
            pzl = new Puzzle(*_puzzle);
            pzl->swap_points(init_state[size * i + j + 1]);
            if (!is_closed(pzl))
                states.push_back(pzl);
        }
        if ( i - 1 >= 0 )
        {
            pzl = new Puzzle(*_puzzle);
            pzl->swap_points(init_state[size * (i - 1) + j]);
            if (!is_closed(pzl))
                states.push_back(pzl);
        }
        if ( i + 1 < size )
        {  
            pzl = new Puzzle(*_puzzle);
            pzl->swap_points(init_state[size * (i + 1) + j]);
            if (!is_closed(pzl))
                states.push_back(pzl);
        }
        return states;
    }
    long distance(){
        return 1;
    }
    void path_cost(Puzzle *p)
    {
        _F[p] = _G[p] + _heuristic_function->path_cost(p);
    }

    std::vector<Puzzle *> _closed_list;
    std::vector<Puzzle *> _open_list;
    HeuristicFunction *_heuristic_function;
    std::map<Puzzle *, Puzzle *> from;
    std::map<Puzzle *, long> _G;
    std::map<Puzzle *, long> _F;
    Puzzle *_puzzle;
};

#endif