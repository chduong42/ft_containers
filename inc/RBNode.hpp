/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBNode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:48:00 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/16 17:43:58 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNode_HPP
# define RBNode_HPP
# include "utility.hpp"
# include <iostream>

namespace ft
{    
    enum Color {RED, BLACK};

	template<class Pair>
	struct RBNode {
		Pair			data;
		Color			color;
		RBNode*			parent;
		RBNode*			left;
		RBNode*			right;

		RBNode(const Pair& value) : data(value), color(BLACK), parent(0), left(0), right(0) {}
		RBNode(const Pair& v, Color c, RBNode* p, RBNode* l, RBNode* r) : data(v), color(c), parent(p), left(l), right(r) {}
		RBNode(const RBNode& x) : data(x.data), color(x.color), parent(x.parent), left(x.left), right(x.right) {}
		~RBNode() {}

		RBNode& operator=(const RBNode& x) {
			if (this != &x) {
				data = x.data;
				color = x.color;
				parent = x.parent;
				left = x.left;
				right = x.right;
			}
			return *this;
		}

		bool is_nil() const {return (this->parent == NULL);}
		bool is_left() const {return (this->parent->left == this);}
		bool is_right() const {return (this->parent->right == this);}
	};
	
	template <typename NodePtr>
	NodePtr min_node(NodePtr node, NodePtr nil) {
		while (node->left != nil)
			node = node->left;
		return (node);
	}
	
	template <typename NodePtr>
	NodePtr max_node(NodePtr node, NodePtr nil) {
		while (node->right != nil)
			node = node->right;
		return (node);
	}

	template <typename NodePtr>
	NodePtr next_node(NodePtr node, NodePtr nil) {
		if (node->right != nil)
			return min_node(node->right, nil);
		NodePtr parent = node->parent;
		while (parent != NULL && node->is_right()) {
			node = parent;
			parent = node->parent;
		}
		if (parent == NULL)
			return nil;
		return parent;
	}
	
	template <typename NodePtr>
	NodePtr prev_node(NodePtr node, NodePtr nil) {
		if (node->left != nil)
			return max_node(node->left, nil);
		NodePtr parent = node->parent;
		while (parent != NULL && node->is_left()) {
			node = parent;
			parent = node->parent;
		}
		return parent;
	}

}

#endif