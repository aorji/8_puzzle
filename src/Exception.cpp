/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:26:48 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 16:59:39 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Exception.hpp"
#include <iostream>

InvalidePuzzle::InvalidePuzzle ( ) { error_line = "error: Invalide Puzzle"; }
InvalidePuzzle::InvalidePuzzle ( InvalidePuzzle const & src ) { *this = src; }
InvalidePuzzle::~InvalidePuzzle ( ) throw() {}
InvalidePuzzle &
InvalidePuzzle::operator=( InvalidePuzzle const & rhs) {
	(void)rhs;
	return *this;
}
const char *
InvalidePuzzle::what() const throw() {
    return error_line.c_str();
}

InvalideHeuristic::InvalideHeuristic ( ) { error_line = "error: Invalide Heuristic"; }
InvalideHeuristic::InvalideHeuristic ( InvalideHeuristic const & src ) { *this = src; }
InvalideHeuristic::~InvalideHeuristic ( ) throw() {}
InvalideHeuristic &
InvalideHeuristic::operator=( InvalideHeuristic const & rhs) {
	(void)rhs;
	return *this;
}
const char *
InvalideHeuristic::what() const throw() {
    return error_line.c_str();
}

CodeError::CodeError ( ) { error_line = "error: Code Error"; }
CodeError::CodeError ( CodeError const & src ) { *this = src; }
CodeError::~CodeError ( ) throw() {}
CodeError &
CodeError::operator=( CodeError const & rhs) {
	(void)rhs;
	return *this;
}
const char *
CodeError::what() const throw() {
    return error_line.c_str();
}
