/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:55:42 by aorji             #+#    #+#             */
/*   Updated: 2019/10/10 21:52:31 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_ASTAR_HPP
#define I_ASTAR_HPP

#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include "HeuristicFunction.hpp"

class AStar
{
public:
    explicit AStar(Puzzle const & init_state): _curr_state(init_state) {
        set_goal_state();
        heuristic = new ManhattanDistance();
    }
    void run()
    {
        g_score(_curr_state, 0);
        f_score(_curr_state);
        _open_list.push(_curr_state);
        _under_review.insert(_curr_state);
        while (!_open_list.empty() && _curr_state.get_gscore() < 250000)
        {
            compute_top_state();
            if (is_goal_state())
            {
                std::cout<< "GOAL STATE\n";
                return;
            }
            close_top_state();
            for (Puzzle state: unclosed_states())
            {
                float tmp_g = _curr_state.get_gscore() + distance();
                if (!is_under_review(state) || tmp_g < state.get_gscore())
                {
                    // from[state] = _curr_state;
                    g_score(state, tmp_g);
                    f_score(state);
                    _open_list.push(state);
                    _under_review.insert(state);
                }
            }
        }
    }
    void print_solution()
    {
        // std::vector<Puzzle> res;
        // Puzzle p = _curr_state;
        // std::cout << from[_curr_state] << std::endl;
        // while(p)
        // {
        //     res.push_back(p);
        //     p = from[p];
        // }
        // for(int i = res.size() - 1; i >= 0; --i)
        //     std::cout << *(res[i]);
        // std::cout << "\n" << res.size() - 1 << " steps" << std::endl;
    }

private:
    bool _success;
    std::priority_queue<Puzzle, std::vector<Puzzle>, ComparePuzzle> _open_list;
    std::set<Puzzle> _closed_list;
    std::set<Puzzle> _under_review;
    Puzzle _curr_state;
    Puzzle _goal_state;
    // std::map<Puzzle, Puzzle> from;
    std::vector<Puzzle> _available_states;
    HeuristicFunction *heuristic;

    AStar();
    AStar(AStar const &);
    AStar & operator=(AStar const &);
    
    bool is_under_review(Puzzle & p)
    {
        return (_under_review.count(p));
    }
    int distance()
    {
        return 1;
    }
    std::vector<Puzzle> unclosed_states(void)
    {
        //i % size - row; i / size - col
        int zero = _curr_state.get_zero_tile();
        int size = _curr_state.get_size();
        Puzzle new_state;
        //UP
        if (zero - size >= 0)
        {
            new_state = _curr_state;
            new_state.swap_tile(zero - size);
            if (_closed_list.count(new_state) == 0)
                _available_states.push_back(new_state);
        }
        //DOWN
        if (zero + size < size * size)
        {
            new_state = _curr_state;
            new_state.swap_tile(zero + size);
            if (_closed_list.count(new_state) == 0)
                _available_states.push_back(new_state);
        }
        // //LEFT
        if (zero - 1 >= 0 && (zero - 1) % size == (zero % size) - 1)
        {
            new_state = _curr_state;
            new_state.swap_tile(zero - 1);
            if (_closed_list.count(new_state) == 0)
                _available_states.push_back(new_state);
        }
        // //RIGHT
        if (zero + 1 < size && (zero + 1) % size == (zero % size) + 1)
        {
            new_state = _curr_state;
            new_state.swap_tile(zero + 1);
            if (_closed_list.count(new_state) == 0)
                _available_states.push_back(new_state);
        }
        return _available_states;
    }
    void close_top_state()
    {
        _open_list.pop();
        _closed_list.insert(_curr_state);

    }
    void compute_top_state(void)
    {
        _curr_state = _open_list.top();
    }
    bool is_goal_state()
    {
        return _curr_state == _goal_state;
    }
    void set_goal_state()
    {
        int size = _curr_state.get_size();
        int *goal_state = new int [size * size];
        int stop = size * size;
        int val = 1; 
        int k = 0;
        int l = 0;
        int n = size;
        int m = size;

        while (k < m && l < n)
        {
            for (int j = l; j < n; ++j) //left
            {
                if (val == stop) val = 0;
                goal_state[size * k + j] = val++;
            }
            k++;
            for (int i = k; i < m; ++i) //down
            {
                if (val == stop) val = 0;
                goal_state[size * i + n-1] = val++;
            }
            n--;
            if (k < m)  //left
            {
                for (int j = n-1; j >= l; --j)
                {
                    if (val == stop) val = 0;
                    goal_state[size * (m-1) + j] = val++;
                }
                m--;
            }
            if (l < n)  //up
            {
                for (int i = m-1; i >= k; --i)
                {
                    if (val == stop) val = 0;
                    goal_state[size * i + l] = val++;
                }
                l++;
            }
        }
        _goal_state = Puzzle(goal_state, size);
    }
    void f_score(Puzzle & p)
    {
        p.set_fscore(p.get_gscore() + heuristic->path_cost(p, _goal_state));
    }
    void g_score(Puzzle & p, int g)
    {
        p.set_gscore(g);
    }
};

#endif
