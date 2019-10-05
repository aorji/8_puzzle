/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeuristicFunction.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:03:27 by aorji             #+#    #+#             */
/*   Updated: 2019/10/05 18:16:45 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef I_HEURISTIC_FUNC_HPP
#define I_HEURISTIC_FUNC_HPP

#include "Point.hpp"

class HeuristicFunction
{
public:
    virtual ~HeuristicFunction(){}
    virtual long path_cost(Point * start) = 0;
};

class ManhattanDistance: public HeuristicFunction
{
public:
    ManhattanDistance(){}
    ~ManhattanDistance(){}
    long path_cost(Point * start)
    {
        return 1;
    }
};

#endif