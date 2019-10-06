/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:43:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/06 16:39:04 by aorji            ###   ########.fr       */
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
        int size = 0;
        std::cin >> size;
        _puzzle = new Puzzle(size);
        _puzzle->fill_puzzle();
    }

    ~Manager(){}

    void run(){
        AStar algorithm(_puzzle);
        algorithm.run();
    }
       
private:
    void get_comment()
    {
        std::getline(std::cin, _comment);
    }
    Puzzle *_puzzle;
    std::string _comment;
};

#endif