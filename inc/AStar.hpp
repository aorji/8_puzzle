/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:55:42 by aorji             #+#    #+#             */
/*   Updated: 2019/10/16 16:37:37 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_ASTAR_HPP
#define I_ASTAR_HPP

#include "HeuristicFunction.hpp"

class AStar
{
public:
    explicit AStar(Puzzle *init_state, eHeuristic heuristic);
    bool run();
    void print_solution();

private:
    bool _solved;
    std::priority_queue<Puzzle *, std::vector<Puzzle *>, ComparePuzzle> _open_list;
    std::set<Puzzle *, ComparePuzzleSet> _closed_list;
    Puzzle *_curr_state;
    Puzzle *_goal_state;
    std::map<Puzzle *, Puzzle *> _from;
    std::vector<Puzzle *> _available_states;
    HeuristicFunction *_heuristic;
    size_t _complexity_in_time;
    size_t _complexity_in_size;

    AStar();
    AStar(AStar const &);
    AStar & operator=(AStar const &);

    void compute_top_state(void);
    
    void add_to_open(Puzzle *p);
    void close_top_state();
    bool in_closed(Puzzle *p);
    void remove_from_closed(Puzzle *p);
    Puzzle *is_under_review(Puzzle *p);
    std::vector<Puzzle *> available_states(void);
    
    bool is_goal_state();
    void set_goal_state();
    
    void set_score(Puzzle *p, int g);
    inline int distance()
    {
        return 1;
    }

    HeuristicFunction *choose_heuristic(eHeuristic heuristic);
};

#endif
