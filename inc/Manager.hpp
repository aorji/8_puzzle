/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:43:46 by aorji             #+#    #+#             */
/*   Updated: 2019/10/11 15:58:01 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_MANAGER_HPP
#define I_MANAGER_HPP

#include "./AStar.hpp"

class Manager {

public:
    Manager(){}
    ~Manager(){ /*nothing to dealloc */ }

    void run(){
        Puzzle *init_state = new Puzzle();
        init_state->fill_in();
        AStar solver(init_state);
        solver.run();
        solver.print_solution();
    }
};

#endif
