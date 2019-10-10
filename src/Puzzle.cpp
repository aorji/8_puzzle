/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:29:26 by aorji             #+#    #+#             */
/*   Updated: 2019/10/10 16:23:31 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Puzzle.hpp"

Puzzle::Puzzle(): _data(NULL){}
void Puzzle::fill_in(void)
{
    int c = 0;
    std::string line;
    int value;

    do { std::getline(std::cin, line); }
    while (line[0] == '#');

    _size = line[0] - 48;
    _size *= _size;
    _data = new int[_size];
    
    for(int i = 0; i < _size; ++i)
        std::cin >> _data[i];
}