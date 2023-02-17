/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBNode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:48:00 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/17 20:38:28 by chduong          ###   ########.fr       */
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
	
		bool isNil() const {return (color == black && left == NULL && right == NULL);}
	};

	// find the node with the minimum key
	template <typename NodePtr>
	NodePtr minNode(NodePtr node, NodePtr nil)	{
		while (node->left != nil)
			node = node->left;
		return node;
	}

	// find the node with the maximum key
	template <typename NodePtr>
	NodePtr maxNode(NodePtr node, NodePtr nil)	{
		while (node->right != nil)
			node = node->right;
		return node;
	}

	// find the successor of a given node
	template <typename NodePtr>
	NodePtr nextNode(NodePtr node, NodePtr nil)	{
		// if the right subtree is not null the successor is the leftmost node in the sright subtree
		if (node->right != nil)
			return minNode(node->right, nil);
		// else it is the lowest ancestor of node whose left child is also an ancestor of node
		NodePtr parent = node->parent;
		while (parent != NULL && node == parent->right)	{
			node = parent;
			parent = parent->parent;
		}
		if (parent == NULL)
			return nil;
		return parent;
	}

	// find the predecessor of a given node
	template <typename NodePtr>
	NodePtr prevNode(NodePtr node, NodePtr nil)	{
		// if the left subtree is not null the predecessor is the rightmost node in the left subtree
		if (node->left != nil)
			return maxNode(node->left, nil);
		NodePtr parent = node->parent;
		while (parent != NULL && node == parent->left)	{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
	
}

#endif