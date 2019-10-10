/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:09:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/10 17:50:36 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_PUZZLE_HPP
#define I_PUZZLE_HPP

#include <iostream>
#include <string>
  
class Puzzle {

public:
    Puzzle(): _data(NULL){}
    Puzzle(int *array, int size): _size(size), _data(array){}
    Puzzle(Puzzle const &p): _size(p._size), _data(new int[_size * _size]), _zero_tile(p._zero_tile), _fscore(p._fscore), _gscore(p._gscore)
    {
        int size = p._size * p._size;
        for(int i = 0; i < size; ++i)
            _data[i] = p._data[i];
    }
    Puzzle & operator=(Puzzle const &p)
    {
        if (this != &p)
            Puzzle(p).swap(*this);
        return *this;
    }
    void swap(Puzzle & p)
    {
        std::swap(_zero_tile, p._zero_tile);
        std::swap(_data, p._data);
        std::swap(_size, p._size);
        std::swap(_fscore, p._fscore);
        std::swap(_gscore, p._gscore);
    }
    ~Puzzle() { delete [] _data; }

    void fill_in(void)
    {
        int c = 0;
        std::string line;

        do { std::getline(std::cin, line); }
        while (line[0] == '#');

        _size = line[0] - 48;
        int size = _size * _size;
        _data = new int[size];
        
        for(int i = 0; i < size; ++i)
            std::cin >> _data[i];
    }

    int *get_data(void) const{ return _data; }
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
};

bool operator==(Puzzle const& p1, Puzzle const &p2)
{
    int *d1 = p1.get_data();
    int *d2 = p2.get_data();
    int size = p1.get_size();
    size *= size;

    for(int i = 0; i < size; ++i)
        if (d1[i] != d2[i])
            return false;
    return true;
}

std::ostream& operator<<(std::ostream &os, Puzzle const &p)
{
    int size = p.get_size();
    int all_size = size * size;
    int *data = p.get_data();

    os << "\n";
    for(int i = 0; i < all_size; ++i)
    {
        if (i && i % size == 0)
            os << "\n";
        os << data[i] << " ";
    }
    os << "\n";
    return os;
}

struct ComparePuzzle { 
    bool operator()(Puzzle const& p1, Puzzle const& p2) 
    { 
        return p1.get_fscore() > p2.get_fscore(); 
    } 
}; 

#endif
