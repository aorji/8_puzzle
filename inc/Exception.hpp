/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:27:12 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 16:59:13 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEPTION_HPP
#define EXEPTION_HPP

#include <exception>
#include <string>

class InvalidePuzzle: public std::exception {
public:
    explicit InvalidePuzzle();
    InvalidePuzzle( InvalidePuzzle const & src );
    ~InvalidePuzzle( ) throw();
    InvalidePuzzle & operator=( InvalidePuzzle const & rhs);
    const char* what() const throw() override;

private:
    std::string error_line;
};

class InvalideHeuristic: public std::exception {
public:
    explicit InvalideHeuristic();
    InvalideHeuristic( InvalideHeuristic const & src );
    ~InvalideHeuristic( ) throw();
    InvalideHeuristic & operator=( InvalideHeuristic const & rhs);
    const char* what() const throw() override;

private:
    std::string error_line;
};

class CodeError: public std::exception {
public:
    explicit CodeError();
    CodeError( CodeError const & src );
    ~CodeError( ) throw();
    CodeError & operator=( CodeError const & rhs);
    const char* what() const throw() override;

private:
    std::string error_line;
};


#endif
