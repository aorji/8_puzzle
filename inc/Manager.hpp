/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:43:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 18:14:15 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_MANAGER_HPP
#define I_MANAGER_HPP

#include "AStar.hpp"

class Manager {

public:
    Manager(int ac, char **av): _ac(ac), _av(av), _heuristic(ERROR) {}
    ~Manager(){ /*nothing to dealloc */ }

    void run(){
        choose_heuristic();
        Puzzle *init_state = new Puzzle();
        init_state->fill_in();
        if (!check_solability(init_state))
            throw NotSolvable();
        AStar solver(init_state, _heuristic);
        solver.run();
        solver.print_solution();
    }
    
private:
    Manager();
    Manager(Manager const &);
    Manager & operator=(Manager const &);

    void choose_heuristic()
    {
        std::vector<std::string> heuristics = {"-MisplacedTiles", "-ManhattanDistance", "-EuclideanDistance"};
        if (_ac == 2)
        {
            for(size_t i = 0; i < heuristics.size(); ++i)
                if (heuristics[i] == _av[1])
                    _heuristic = static_cast<eHeuristic>(i + 1);
        }
        if (_ac != 2 || _heuristic == ERROR)
        {
            std::cout << "usage: " << heuristics.size() << " heuristics are available: " << std::endl;
            for(size_t i = 0; i < heuristics.size(); ++i)
                std::cout << heuristics[i] << std::endl;
            throw InvalideHeuristic();
        }
    }

    int count_inversion(Puzzle *p)
    {
        int *data = p->get_data();
        int inv_count = 0;
        int size = p->get_size() * p->get_size();
        for (int i = 0; i < size - 1; ++i) 
            for (int j = i + 1; j < size; ++j) 
                if (data[j] && data[i] &&  data[i] > data[j]) 
                    inv_count++;
        return inv_count; 
    }

    bool check_solability(Puzzle *p)
    {
        int inversion = count_inversion(p);
        if (p->get_size() % 2 == 1)
            return inversion % 2 == 1;
        else
        {
            int row = p->get_size() - (p->get_zero_tile() / p->get_size());
            if (row % 2 == 1) return !(inversion % 2);
            else return (inversion % 2);
        }
    }
    
    int _ac;
    char **_av;
    eHeuristic _heuristic;
};

#endif
