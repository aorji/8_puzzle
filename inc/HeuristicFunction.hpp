/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeuristicFunction.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:03:27 by aorji             #+#    #+#             */
/*   Updated: 2019/10/10 17:43:53 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_HEURISTIC_FUNC_HPP
#define I_HEURISTIC_FUNC_HPP

#include "Puzzle.hpp"

class HeuristicFunction
{
public:
    virtual ~HeuristicFunction(){}
    virtual float path_cost(Puzzle const &curr_state, Puzzle const &goal_state) = 0;
};

class MisplacedTiles: public HeuristicFunction
{
public:
    MisplacedTiles(){}
    ~MisplacedTiles(){}
    float path_cost(Puzzle const &curr_state, Puzzle const &goal_state)
    {
        int *curr = curr_state.get_data();
        int size = curr_state.get_size();
        size *= size;
        int *goal= goal_state.get_data();
        int h = 0;

        for (int i = 0; i < size; ++i)
                if (curr[i] != goal[i] && curr[i] != 0)
                    ++h;
        return h;
    }
};

class ManhattanDistance: public HeuristicFunction
{
public:
    ManhattanDistance(){}
    ~ManhattanDistance(){}
    
    float path_cost(Puzzle const &curr_state, Puzzle const &goal_state)
    {
        int *curr = curr_state.get_data();
        int size = curr_state.get_size();
        int *goal= goal_state.get_data();
        float manhattan_distance = 0;
        
        for(int i = 0; i < size * size; ++i)
        {
            if (curr[i] == 0 || curr[i] == goal[i])
                continue;
            auto goal_i = return_index(curr[i], goal, size);
            manhattan_distance += abs((i % size) - (goal_i % size)) + abs((i/size) - (goal_i/size));
        }
        return manhattan_distance;
    }
    private:
    int return_index(int value, int *goal, int size)
    {
        for(int i = 0; i < size * size; ++i)
            if (goal[i] == value)
                return i;
        // /throu exept
        exit(1);
        return 0;
    }
};

#endif