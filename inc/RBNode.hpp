/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBNode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:48:00 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/14 05:27:48 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
# define RBNODE_HPP
# include "utility.hpp"

namespace ft
{    
    enum Color {RED, BLACK};

	template<class Pair>
	struct RbNode {
		Pair			data;
		Color			color;
		RbNode*			parent;
		RbNode*			left;
		RbNode*			right;

		RbNode(const Pair& value) : data(value), color(BLACK), parent(0), left(0), right(0) {}
		RbNode(const Pair& v, Color c, RbNode* p, RbNode* l, RbNode* r) : data(v), color(c), parent(p), left(l), right(r) {}
		RbNode(const RbNode& x) : data(x.data), color(x.color), parent(x.parent), left(x.left), right(x.right) {}
		~RbNode() {}

		RbNode& operator=(const RbNode& x) {
			if (this != &x) {
				data = x.data;
				color = x.color;
				parent = x.parent;
				left = x.left;
				right = x.right;
			}
			return *this;
		}

		bool is_nil() const {return (color == BLACK && parent == NULL && left == this && right == this);}
		bool is_red() const {return (this->color == RED);}
		bool is_black() const {return (this->color == BLACK);}
		bool is_left() const {return (this->parent->left == this);}
		bool is_right() const {return (this->parent->right == this);}
	};
	
	template <typename NodePtr>
	NodePtr min_node(NodePtr ptr) {
		while (!ptr->left->is_nil())
			ptr = ptr->left;
		return (ptr);
	}
	
	template <typename NodePtr>
	NodePtr max_node(NodePtr ptr) {
		while (!ptr->right->is_nil())
			ptr = ptr->right;
		return (ptr);
	}

	template <typename NodePtr>
	NodePtr next_node(NodePtr node) {
		if (!node->right->is_nil())
			node = min_node(node->right);
		else {
			while (!node->parent->is_nil() && node == node->parent->right)
				node = node->parent;
		}
		return node;
	}
	
	template <typename NodePtr>
	NodePtr prev_node(NodePtr node) {
		if (!node->left->is_nil())
			node = max_node(node->left);
		else {
			while (!node->parent->is_nil() && node == node->parent->left)
				node = node->parent;
		}
		return node;
	}

	template<class P1, class P2>
	bool operator==(const RbNode<P1>& lhs, const RbNode<P2>& rhs) {return &lhs == &rhs;}

	template<class P1, class P2>
	bool operator!=(const RbNode<P1>& lhs, const RbNode<P2>& rhs) {return !(lhs == rhs);}

}

#endif