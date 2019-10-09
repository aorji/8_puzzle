/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeuristicFunction.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:03:27 by aorji             #+#    #+#             */
/*   Updated: 2019/10/09 15:23:48 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://algorithmsinsight.wordpress.com/graph-theory-2/a-star-in-general/implementing-a-star-to-solve-n-puzzle/
// https://www.cs.cmu.edu/~eugene/teach/ai00/sample/index.html
#ifndef I_HEURISTIC_FUNC_HPP
#define I_HEURISTIC_FUNC_HPP

#include "Puzzle.hpp"

class HeuristicFunction
{
public:
    virtual ~HeuristicFunction(){}
    virtual long path_cost(Puzzle *) = 0;
};

class MisplacedTiles: public HeuristicFunction
{
public:
    MisplacedTiles(){}
    ~MisplacedTiles(){}
    long path_cost(Puzzle * _puzzle)
    {
        const std::vector<Point> curr = _puzzle->get_data();
        int **goal = _puzzle->get_goal_state();

        int n = _puzzle->get_puzzle_size();
        int h = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                if (curr[n * i + j].get_value() != goal[i][j] &&
                    curr[n * i + j].get_value() != '0')
                    ++h;
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
        int size = _puzzle->get_puzzle_size();
        std::vector<Point> data = _puzzle->get_data();
        int manhattan_distance = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                int value = data[size * i + j].get_value();
                if (value != 0)
                {
                    int targetX = (value - 1) / size;
                    int targetY = (value - 1) % size;
                    int dx = i - targetX;
                    int dy = j - targetY;
                    manhattan_distance += abs(dx) + abs(dy); 
                } 
            }
        }
        return manhattan_distance;
    }
};

#endif