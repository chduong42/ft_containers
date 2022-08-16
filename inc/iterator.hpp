/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:17:18 by kennyduong        #+#    #+#             */
/*   Updated: 2022/08/16 18:58:51 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

namespace ft 
{
    template<typename T>
    class iterator_traits {
        private:
            ptrdiff_t       difference_type;
            T               value_type;
            T*              pointer;
            T&              reference;
            
    };
}

#endif