/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:59:30 by aorji             #+#    #+#             */
/*   Updated: 2019/10/14 16:37:16 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Manager.hpp"

int main(int ac, char **av)
{
    try {
        Manager manager(ac, av);
        manager.run();
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}