/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:43:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/07 20:21:13 by aorji            ###   ########.fr       */
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
        algorithm.show_result();
    }
       
private:
    void get_comment()
    {
        std::getline(std::cin, _comment);
        if (_comment == "# This puzzle is unsolvable")
            exit(1);
    }
    Puzzle *_puzzle;
    std::string _comment;
};

#endif