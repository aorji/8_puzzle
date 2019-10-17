/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:29:26 by aorji             #+#    #+#             */
/*   Updated: 2019/10/17 15:36:13 by aorji            ###   ########.fr       */
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
    std::string line = "0";
    std::vector<std::string> params;

    do { std::getline(std::cin, line); }
    while (line[0] == '#');

    _size = line[0] - 48;
    int size = _size * _size;
    _data = new int[size];
    
    int k = 0;
    for(int i = 0; i < _size; ++i)
    {
        if (!std::getline(std::cin, line))
            throw InvalidePuzzle();
        split(line, params, ' ');
        for(int j = 0; j < _size; ++j)
        {
            int elem;
            try {
                elem = std::stoi(params[k]);
            } catch (std::exception &e) {
                throw InvalidePuzzle();
            }
            _data[k] = elem;
            if (_data[k] == 0)
                _zero_tile = k;
            k++;
        }
    }
}

void Puzzle::split(std::string str, std::vector<std::string> &container, char dlm)
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, dlm)) {
        if (token == "\0") continue;
        if (token[0] == '#') break;
        container.push_back(token);
    }
}

Puzzle & Puzzle::operator=(Puzzle const &p)
{
    if (this != &p)
        Puzzle(p).swap(*this);
    return *this;
}

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
