/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:43:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 15:32:04 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_MANAGER_HPP
#define I_MANAGER_HPP

#include "AStar.hpp"

class Manager {

public:
    Manager(int ac, char **av): _ac(ac), _av(av) {}
    ~Manager(){ /*nothing to dealloc */ }

    void run(){
        choose_heuristic();
        Puzzle *init_state = new Puzzle();
        init_state->fill_in();
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
            for(int i = 0; i < heuristics.size(); ++i)
                if (heuristics[i] == _av[1])
                    _heuristic = static_cast<eHeuristic>(i);
        }
        else
        {
            std::cout << "usage: " << heuristics.size() << " heuristics are available: " << std::endl;
            for(int i = 0; i < heuristics.size(); ++i)
                std::cout << heuristics[i] << std::endl;

            exit(1);
            //throe + usage
        }
    }
    
    int _ac;
    char **_av;
    eHeuristic _heuristic;
};

#endif
