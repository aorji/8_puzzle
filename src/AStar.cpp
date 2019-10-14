/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:27:34 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 17:39:16 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AStar.hpp"

AStar::AStar(Puzzle *init_state, eHeuristic heuristic): _curr_state(init_state)
{
    set_goal_state();
    _heuristic = choose_heuristic(heuristic);
}
bool AStar::run()
{
    int loop_count = 0;
    int size = _goal_state->get_size();
    set_score(_curr_state, 0);
    _open_list.push(_curr_state);
    _available_states.push_back(_curr_state);
    while (!_open_list.empty() && ++loop_count)
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
                set_score(state, tmp_g);
                _open_list.push(state);
                _available_states.push_back(state);
                _from[state] = _curr_state;
            }
            else
            {
                if (tmp_g < reviewed->get_gscore())
                {
                    set_score(reviewed, tmp_g);
                    _from[reviewed] = _curr_state;
                    if (in_closed(reviewed))
                    {
                        remove_from_closed(reviewed);
                        _open_list.push(reviewed);
                    }
                }
            }
        }
        if ((size == 3 && loop_count >= 250000) ||
            (size == 4 && loop_count >= 600000) ||
            (size >= 5 && loop_count >= 1000000))
            return false;
    }
    return (_solved = false);
}
void AStar::print_solution()
{
    if (!_solved)
    {
        std::cout << "Solution not found" << std::endl;
        return ;
    }
    std::vector<Puzzle *> res;
    Puzzle *p = _curr_state;
    while(p)
    {
        res.push_back(p);
        p = _from[p];
    }
    for(int i = res.size() - 1; i >= 0; --i)
        std::cout << *(res[i]);
    std::cout << "\n" << res.size() - 1 << " steps" << std::endl;
}

void AStar::remove_from_closed(Puzzle *p)
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
Puzzle *AStar::is_under_review(Puzzle *p)
{
    for(auto item: _available_states)
        if (*item == *p)
            return item;
    return NULL;
}
Puzzle *AStar::in_closed(Puzzle *p)
{
    for(auto item: _closed_list)
        if (item == p)
            return item;
    return NULL;
}
std::vector<Puzzle *> AStar::available_states(void)
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
void AStar::close_top_state()
{
    _open_list.pop();
    _closed_list.push_back(_curr_state);

}
void AStar::compute_top_state(void)
{
    _curr_state = _open_list.top();
}
bool AStar::is_goal_state()
{
    return *_curr_state == *_goal_state;
}
void AStar::set_goal_state()
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
void AStar::set_score(Puzzle *p, int g)
{
    p->set_gscore(g);
    p->set_fscore(g + _heuristic->path_cost(p, _goal_state));
}

HeuristicFunction *AStar::choose_heuristic(eHeuristic heuristic)
{
    switch (heuristic)
    {
        case MT:
            std::cout << "MisplacedTiles heuristic was chosen" << std::endl;
            return new MisplacedTiles();
        case MD:
            std::cout << "ManhattanDistance heuristic was chosen" << std::endl;
            return new ManhattanDistance();
        case ED:
            std::cout << "EuclideanDistance heuristic was chosen" << std::endl;
            return new EuclideanDistance();
        default:
            return new EuclideanDistance(); //NOT POSSIBLE

    }
}