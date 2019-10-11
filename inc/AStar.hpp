/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:55:42 by aorji             #+#    #+#             */
/*   Updated: 2019/10/11 18:03:00 by aorji            ###   ########.fr       */
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
static int step = 0;
class AStar
{
public:
    explicit AStar(Puzzle *init_state): _curr_state(init_state) {
        set_goal_state();
        heuristic = new MisplacedTiles();
    }
    bool run()
    {
        // if (!is_solvabel(_curr_state))
        //     return (_solved = false);
        set_score(_curr_state, 0);
        _open_list.push(_curr_state);
        _available_states.push_back(_curr_state);
        while (!_open_list.empty())// && _curr_state->get_gscore() < 250000)
        {
            compute_top_state();
            if (is_goal_state())
                return (_solved = true);
            close_top_state();
            for (Puzzle *state: available_states())
            {
                float tmp_g = _curr_state->get_gscore() + distance();
                Puzzle *reviewed = is_under_review(state); //return NULL if state not in open, or pointer to same state, if is in open
                if (!reviewed)
                {
                    from[state] = _curr_state;
                    set_score(state, tmp_g);
                    _open_list.push(state);
                    _available_states.push_back(state);
                }
                else
                {
                    if (tmp_g < reviewed->get_gscore())
                    {
                        from[reviewed] = _curr_state;
                        set_score(reviewed, tmp_g);
                        if (in_closed(reviewed))
                        {
                            remove_from_closed(reviewed);
                            _open_list.push(reviewed);
                        }
                    }
                }
            }
        }
        return (_solved = false);
    }
    void print_solution()
    {
        if (!_solved)
            return ;
        std::vector<Puzzle *> res;
        Puzzle *p = _curr_state;
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
    bool _solved;
    std::priority_queue<Puzzle *, std::vector<Puzzle *>, ComparePuzzle> _open_list;
    std::vector<Puzzle *> _closed_list;
    Puzzle *_curr_state;
    Puzzle *_goal_state;
    std::map<Puzzle *, Puzzle *> from;
    std::vector<Puzzle *> _available_states;
    HeuristicFunction *heuristic;

    AStar();
    AStar(AStar const &);
    AStar & operator=(AStar const &);
    
    int is_solvabel(Puzzle *p) 
    {
        int *data = p->get_data();
        int inv_count = 0;
        int size = p->get_size() * p->get_size();
        for (int i = 0; i < size - 1; ++i) 
            for (int j = i + 1; j < size; ++j) 
                if (data[j] && data[i] &&  data[i] > data[j]) 
                    inv_count++;
        return (inv_count % 2 == 0); 
    } 

    void remove_from_closed(Puzzle *p)
    {
        for(std::vector<Puzzle *>::iterator it = _closed_list.begin(); it != _closed_list.end(); ++it)
        {
            if (*it == p)
            {
                _closed_list.erase(it);
                return;
            }
        }
    }
    Puzzle *is_under_review(Puzzle *p)
    {
        for(auto item: _available_states)
            if (*item == *p)
                return item;
        return NULL;
    }
    int distance()
    {
        return 1;
    }
    Puzzle *in_closed(Puzzle *p)
    {
        for(auto item: _closed_list)
            if (item == p)
                return item;
        return NULL;
    }
    std::vector<Puzzle *> available_states(void)
    {
        //i % size - row; i / size - col
        std::vector <Puzzle *> available_states;
        int *data = _curr_state->get_data();
        int zero = _curr_state->get_zero_tile();
        int size = _curr_state->get_size();
        Puzzle *new_state;
        //UP
        if (zero - size >= 0)
        {
            new_state = new Puzzle(data, size);
            new_state->swap_tile(zero - size);
            available_states.push_back(new_state);
        }
        //DOWN
        if (zero + size < size * size)
        {
            new_state = new Puzzle(data, size);
            new_state->swap_tile(zero + size);
            available_states.push_back(new_state);
        }
        // //LEFT
        if (zero - 1 >= 0 && (zero - 1) % size == (zero % size) - 1)
        {
            new_state = new Puzzle(data, size);
            new_state->swap_tile(zero - 1);
            available_states.push_back(new_state);
        }
        //RIGHT
        if (zero + 1 < size * size && ((zero + 1) % size) == ((zero % size) + 1))
        {
            new_state = new Puzzle(data, size);
            new_state->swap_tile(zero + 1);
            available_states.push_back(new_state);
        }
        return available_states;
    }
    void close_top_state()
    {
        _open_list.pop();
        _closed_list.push_back(_curr_state);

    }
    void compute_top_state(void)
    {
        _curr_state = _open_list.top();
    }
    bool is_goal_state()
    {
        return *_curr_state == *_goal_state;
    }
    void set_goal_state()
    {
        int size = _curr_state->get_size();
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
        _goal_state = new Puzzle(goal_state, size);
    }
    // void f_score(Puzzle *p)
    // {
    //     p->set_fscore(p->get_gscore() + heuristic->path_cost(p, _goal_state));
    // }
    void set_score(Puzzle *p, int g)
    {
        p->set_gscore(g);
        p->set_fscore(g + heuristic->path_cost(p, _goal_state));
    }
};

#endif
