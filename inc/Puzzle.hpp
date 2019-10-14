/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:09:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 16:09:01 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_PUZZLE_HPP
#define I_PUZZLE_HPP

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
  
class Puzzle {

public:
    Puzzle();
    Puzzle(int *array, int size);
    Puzzle(Puzzle const &p);
    ~Puzzle() { delete [] _data; }
    
    Puzzle & operator=(Puzzle const &p);
    
    void set_zero_tile();
    void reset_fg_scores(void);
    void swap_tile(int tile);
    void swap(Puzzle & p);
    void fill_in(void);
    int *get_data(void) const{ return _data; }
    int get_zero_tile(void) const{ return _zero_tile; }
    int get_size(void) const{ return _size; }
    float get_fscore(void) const{ return _fscore; }
    void set_fscore(float f) { _fscore = f; }
    float get_gscore(void) const{ return _gscore; }
    void set_gscore(float g) { _gscore = g; }

private:
    int _size;
    int *_data;
    int _zero_tile;
    float _fscore;
    float _gscore;

    void split(std::string, std::vector<std::string> &);
};

bool operator==(Puzzle const& p1, Puzzle const &p2);
std::ostream& operator<<(std::ostream &os, Puzzle const &p);

struct ComparePuzzle {  //for std::priority_queue
    bool operator()(Puzzle *p1, Puzzle *p2) 
    {
        //with min f score is at the top
        return p1->get_fscore() > p2->get_fscore(); 
    } 
};

#endif
