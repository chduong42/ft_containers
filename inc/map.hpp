/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/02/12 18:55:28 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "RBTree.hpp"

namespace ft 
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			// ====================== Member Classes ========================= //
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
			
			// ====================== Member Types ========================= //
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef RBTree<value_type, value_compare, allocator_type> 		tree_type;		
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef typename Alloc::pointer									pointer;
			typedef typename Alloc::const_pointer 							const_pointer;
			typedef typename tree_type::iterator							iterator;
			typedef typename tree_type::const_iterator						const_iterator;
			typedef typename tree_type::reverse_iterator					reverse_iterator;
			typedef typename tree_type::const_reverse_iterator				const_reverse_iterator;
			typedef typename tree_type::difference_type						difference_type;
			typedef typename tree_type::size_type							size_type;
			typedef typename tree_type::node_ptr							node_ptr;
			
		private:		
			tree_type					_tree;

		public:
			// ====================== Member Functions ========================= //
			map() :	_tree() {};
			explicit map(const Compare& comp, const Alloc& alloc = Alloc())	  : _tree(RBTree(comp, alloc)) {};
				explicit map(const map& other) :_tree(RBTree(other.key_comp(), other.get_allocator())) {_tree.insert(other.begin(), other.end());}
			~map() {}

			template<class Iter>
			map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& alloc = Alloc(), typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0)
			: _tree(RBTree(comp, alloc)) {this->insert(first, last);}

			map& operator=( const map& other ) {
				if (this != &other)
					this->_tree = other._tree;
				return *this;
			}

			allocator_type				get_allocator() const {return this->_tree.getAllocator();}

			// ====================== Element access ========================= //
			mapped_type&				at(const Key& key) {return _tree.find(key)->second;}
			const mapped_type&			at(const Key& key) const {return _tree.find(key)->second;}

			mapped_type&	operator[](const Key& key) {
				iterator ret = this->_tree.find(key);
				if (ret != this->end()) {
					mapped_type &value = this->at(key);
					return value;
				} else
					return (this->insert(value_type(key, mapped_type()))).first->second;
			}

			// ====================== Iterators ========================= //
			iterator					begin() { return this->_tree.begin(); }
			const_iterator				begin() const { return this->_tree.begin(); }
			iterator					end() { return this->_tree.end(); }
			const_iterator				end() const { return this->_tree.end(); }
			reverse_iterator			rbegin() { return this->_tree.rbegin(); }
			const_reverse_iterator		rbegin() const { return this->_tree.rbegin(); }
			reverse_iterator			rend() { return this->_tree.rend(); }
			const_reverse_iterator		rend() const { return this->_tree.rend(); }

			// ====================== Capacity ========================= //
			bool						empty() const { return this->begin() == this->end(); }
			size_type					size() const { return _tree.size(); }
			size_type					max_size() const { return this->_tree.max_size(); }

			// ====================== Modifiers ========================= //
			void						clear() { this->_tree.clear(); }
			void						erase(iterator pos) { this->_tree.erase(pos) ; }
			void						erase(iterator first, iterator last) { this->_tree.erase(first, last); }
			size_type					erase(const Key& key) { return this->_tree.erase(key); }
			void						swap(map& other) { this->_tree.swap(other._tree); }
			ft::pair<iterator, bool>	insert(const value_type& value) {return this->_tree.insertUnique(value);}
			iterator					insert( iterator hint, const value_type& value ) {return this->_tree.insertUnique(hint, value);}
			template<class Iter>
			void insert( Iter first, Iter last, typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0) {this->_tree.insertUnique(first, last);}

			// ====================== Operations ========================= //
			size_type					count( const Key& key ) const {	const_iterator ret = this->_tree.find(key);	return ret != this->end();}
			iterator					find(const Key &key) { return this->_tree.find(key); }
			const_iterator				find(const Key &key) const { return this->_tree.find(key); }
			iterator					lower_bound(const Key& key) { return this->_tree.lower_bound(key); }
			const_iterator				lower_bound(const Key& key) const { return this->_tree.lower_bound(key); }
			iterator					upper_bound(const Key& key) { return this->_tree.upper_bound(key); }
			const_iterator				upper_bound(const Key& key) const { return this->_tree.upper_bound(key); }
			
			ft::pair<iterator, iterator> 
			equal_range( const Key& key ) {return ft::pair<iterator, iterator>(lower_bound(key),upper_bound(key));	}
			
			ft::pair<const_iterator, const_iterator> 
			equal_range( const Key& key ) const {return ft::pair<const_iterator, const_iterator>(lower_bound(key),upper_bound(key));}

			// ====================== Observers ========================= //
			key_compare					key_comp() const { return this->_tree.key_comp(); }
			value_compare				value_comp() const { return value_compare(); }

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (lhs.size() != rhs.size()) ? false : ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs) {
		return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs,map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}

}

#endif