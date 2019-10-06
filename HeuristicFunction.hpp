/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeuristicFunction.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:03:27 by aorji             #+#    #+#             */
/*   Updated: 2019/10/06 17:52:37 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef I_HEURISTIC_FUNC_HPP
#define I_HEURISTIC_FUNC_HPP

#include "Puzzle.hpp"

class HeuristicFunction
{
public:
    virtual ~HeuristicFunction(){}
    virtual long path_cost(Puzzle *) = 0;
};

class MisplacedNum: public HeuristicFunction
{
public:
    MisplacedNum(){}
    ~MisplacedNum(){}
    long path_cost(Puzzle * _puzzle)
    {
        const std::vector<Point *> curr = _puzzle->get_data();
        const std::vector<Point *> goal = _puzzle->get_goal_state();

        int n = _puzzle->get_puzzle_size();
        int h = 0;
        for (int i = 0; i < n * n; ++n)
        {
            if (curr[i]->get_value() != goal[i]->get_value() &&
                curr[i]->get_value() != '0')
                h++;
        }
        return h;
    }
};

class ManhattanDistance: public HeuristicFunction
{
public:
    ManhattanDistance(){}
    ~ManhattanDistance(){}
    long path_cost(Puzzle * _puzzle)
    {
        return 1;
    }
};

#endif