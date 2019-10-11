/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:29:26 by aorji             #+#    #+#             */
/*   Updated: 2019/10/11 20:45:58 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Puzzle.hpp"

Puzzle::Puzzle(): _data(NULL)
{
    _zero_tile = INT_MAX;
    _fscore = INT_MAX;
    _gscore = INT_MAX;
}
Puzzle::Puzzle(int *array, int size): _size(size), _data(new int[_size * _size])
{
    size *= size;
    for(int i = 0; i < size; ++i)
        _data[i] = array[i];
    set_zero_tile(); _fscore = INT_MAX; _gscore = INT_MAX;
}
Puzzle::Puzzle(Puzzle const &p): _size(p._size), _data(new int[_size * _size]), _zero_tile(p._zero_tile), _fscore(p._fscore), _gscore(p._gscore)
{
    int size = p._size * p._size;
    for(int i = 0; i < size; ++i)
        _data[i] = p._data[i];
}
void Puzzle::swap(Puzzle & p)
{
    std::swap(_zero_tile, p._zero_tile);
    std::swap(_data, p._data);
    std::swap(_size, p._size);
    std::swap(_fscore, p._fscore);
    std::swap(_gscore, p._gscore);
}
void Puzzle::swap_tile(int tile)
{
    std::swap(_data[_zero_tile], _data[tile]);
    _zero_tile = tile;
}
void Puzzle::set_zero_tile()
{
    int size = _size * _size;
    for(int i = 0; i < size; ++i)
        if (_data[i] == 0)
            _zero_tile = i;
}
void Puzzle::reset_fg_scores(void)
{
    _fscore = INT_MAX; _gscore = INT_MAX;
}
void Puzzle::fill_in(void)
{
    int c = 0;
    std::string line;

    do { std::getline(std::cin, line); }
    while (line[0] == '#');

    _size = line[0] - 48;
    int size = _size * _size;
    _data = new int[size];
    
    for(int i = 0; i < size; ++i)
    {
        std::cin >> _data[i];
        if (_data[i] == 0)
            _zero_tile = i;
    }
}
Puzzle & Puzzle::operator=(Puzzle const &p)
{
    if (this != &p)
        Puzzle(p).swap(*this);
    return *this;
}
// bool Puzzle::operator<(const Puzzle & p) const //for std::set
// {
//     int size = _size * _size;
//     int i = 0;
//     for(int i = 0; i < size; ++i)
//         if (_data[i] != p._data[i])
//             return _data[i] < p._data[i];
//     return false;
// }

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
