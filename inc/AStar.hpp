/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:55:42 by aorji             #+#    #+#             */
/*   Updated: 2019/10/10 17:48:33 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_ASTAR_HPP
#define I_ASTAR_HPP

#include <map>
#include <cmath>
#include <queue>
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
        f_score();
        g_score(0);
        _open_list.push(_curr_state);
        std::cout <<_curr_state.get_fscore() << std::endl;
        std::cout << _open_list.top() << std::endl;
        std::cout << _open_list.top().get_fscore() << std::endl;
        std::cout << _open_list.top().get_gscore() << std::endl;
        // while (!_open_list.empty())
        // {
        //     compute_new_state();
        //     if (is_goal_state())
        //         return;
        //     close_current_state();
        //     for (Puzzle state: unclosed_states())
        //     {
        //         // long tmp_g = _G[_puzzle] + distance();
        //         // if (!is_open(state) || tmp_g < _G[state])
        //         // {
        //         //     from[state] = _puzzle;
        //         //     _G[state] = tmp_g;
        //         //     path_cost(state);
        //         //     add_to_open(state);
        //         // }
        //     }
        // }
    }
    void print_solution();

private:
    std::priority_queue<Puzzle, std::vector<Puzzle>, ComparePuzzle> _open_list;
    // std::set
    Puzzle _curr_state;
    Puzzle _goal_state;
    // std::map<Puzzle *, long> _G;
    // std::map<Puzzle *, long> _F;
    // std::map<Puzzle, Puzzle> from;
    HeuristicFunction *heuristic;

    AStar();
    AStar(AStar const &);
    AStar & operator=(AStar const &);
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
    void f_score(void)
    {
        _curr_state.set_fscore(_curr_state.get_gscore() + heuristic->path_cost(_curr_state, _goal_state));
    }
    void g_score(int g)
    {
        _curr_state.set_gscore(g);
    }
};

#endif
