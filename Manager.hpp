/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:43:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/04 21:50:22 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_MANAGER_HPP
#define I_MANAGER_HPP

#include "./AStar.hpp"

class Manager {

public:
    Manager()
    {
        get_comment();
        _starting_point = NULL;
        std::cin >> _puzzle_size;
        fill_puzzle();
    }

    ~Manager(){}

    void run(){
        print_puzzle();
        AStar algorithm(_puzzle, _puzzle_size, _starting_point);
        algorithm.run();
    }
    
    void print_puzzle(void)
    {
        for(int i = 0; i < _puzzle_size * _puzzle_size; ++i)
        {
            if (i && i % _puzzle_size == 0)
                std::cout << "\n";
            std::cout << (_puzzle[i])->get_value() << " ";
        }
        std::cout << "\n";
    }
    
private:

    void fill_puzzle(void)
    {
        for(int i = 0; i < _puzzle_size; ++i)
        {
            for(int j = 0; j < _puzzle_size; ++j)
            {
                int value = 0;
                std::cin >> value;
                _puzzle.push_back(new Point(i, j, value));
                if (value == 0)
                {
                    static char times = 0;
                    ++times;
                    if (times > 1)
                    {
                        std::cout << "error: mulip 0" << std::endl;
                        exit(1); //throu exept 
                    }
                    _starting_point = _puzzle[_puzzle_size * i + j];
                }
            }
        }
        if (!_starting_point)
        {
            std::cout << "error: no 0";
            exit(1);
            //throu error
        }
    }
    void get_comment(){
        std::getline(std::cin, _comment);
    }

    std::vector<Point *> _puzzle;
    int _puzzle_size;
    Point * _starting_point;
    std::string _comment;
};

#endif