/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBNode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:48:00 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/17 15:04:18 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNode_HPP
# define RBNode_HPP

namespace ft
{
	enum Color {red, black};

	template <class T>
	struct RBNode
	{
		T 				data;
		RBNode*			parent;
		RBNode*			left;
		RBNode*			right;
		Color 			color;

		RBNode(T data, RBNode* parent, RBNode* left, RBNode* right, Color clr): data(data), parent(parent), left(left), right(right), color(clr) {}
	};
	
}

#endif