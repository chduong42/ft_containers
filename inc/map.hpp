/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/01/30 19:31:59 by chduong          ###   ########.fr       */
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
			// ====================== Member Types ========================= //
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef Compare																key_compare;
			typedef Alloc																allocator_type;
			typedef ft::RBTree<key_type, value_type, key_compare, allocator_type> 		tree_type;					
			
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef typename Alloc::pointer												pointer;
			typedef typename Alloc::const_pointer 										const_pointer;
			typedef typename tree_type::iterator										iterator;
			typedef typename tree_type::const_iterator									const_iterator;
			typedef typename tree_type::reverse_iterator								reverse_iterator;
			typedef typename tree_type::const_reverse_iterator							const_reverse_iterator;
			typedef typename tree_type::difference_type									difference_type;
			typedef typename tree_type::size_type										size_type;
		
			// ====================== Member Classes ========================= //
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
		
		private:
			// ====================== Member Variables ========================= //
			
			tree_type					_tree;
			key_compare					_comp;
			allocator_type				_alloc;
			
		public:
			// ---------------------- Constructors / Destructor ----------------------- //
			explicit map(const key_compare& comp = key_compare(), const Alloc& alloc = Alloc()) : _comp(comp), _alloc(alloc) {}
			
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const Alloc& alloc = Alloc())
			: _comp(comp), _alloc(alloc) { _tree.assign(first, last); }
			
			map(const map& x) : _tree(x._tree), _comp(x._comp), _alloc(x._alloc) {}
			~map() {}

			// ---------------------- Member Functions ----------------------------- //
			map& operator=(const map& x) {
				if (this != &x){
					this->clear();
					this->swap(x);
				}
				return *this;
			}
			
			allocator_type							get_allocator() const { return _alloc; }
			
			// Element access
			mapped_type&							at(const key_type& k) { return _tree.at(k);}
			const mapped_type&						at(const key_type& k) const { return _tree.at(k);}
			mapped_type& 							operator[](const key_type& k) { return _tree[k]; }

			// Iterators
			iterator 								begin() { return _tree.begin(); }
			const_iterator 							begin() const { return _tree.begin(); }
			iterator 								end() { return _tree.end(); }
			const_iterator 							end() const { return _tree.end(); }
			reverse_iterator 						rbegin() { return _tree.rbegin(); }
			const_reverse_iterator 					rbegin() const { return _tree.rbegin(); }
			reverse_iterator 						rend() { return _tree.rend(); }
			const_reverse_iterator 					rend() const { return _tree.rend(); }

			// Capacity
			bool 									empty() const { return _tree.empty(); }
			size_type 								size() const { return _tree.size(); }
			size_type 								max_size() const { return _tree.max_size;}
			
			// Modifiers
			pair<iterator,bool> 					insert(const value_type& val) { return _tree.insert(val); }
			iterator 								insert(iterator position, const value_type& val) { return _tree.insert(position, val); }
			template<class InputIterator> void		insert(InputIterator first, InputIterator last) { _tree.insert(first, last); }
			void 									erase(iterator position) { _tree.erase(position); }
			size_type 								erase(const key_type& k) { return _tree.erase(k); }
			void 									erase(iterator first, iterator last) { _tree.erase(first, last); }
			void 									swap(map& x) {std::swap(_tree, x._tree); std::swap(_comp, x._comp); std::swap(_alloc, x._alloc); }
			void 									clear() { _tree.clear(); }
			
			// Operations
			size_type 								count(const key_type& k) const { return _tree.count(k); }
			iterator 								find(const key_type& k) { return _tree.find(k); }
			const_iterator 							find(const key_type& k) const { return _tree.find(k); }
			pair<iterator,iterator> 				equal_range(const key_type& k) { return _tree.equal_range(k); }
			pair<const_iterator,const_iterator> 	equal_range(const key_type& k) const { return _tree.equal_range(k); }
			iterator 								lower_bound(const key_type& k) { return _tree.lower_bound(k); }
			const_iterator 							lower_bound(const key_type& k) const { return _tree.lower_bound(k); }
			iterator 								upper_bound(const key_type& k) { return _tree.upper_bound(k); }
			const_iterator 							upper_bound(const key_type& k) const { return _tree.upper_bound(k); }
			
			// Observers
			key_compare 							key_comp() const { return _comp; }
			value_compare 							value_comp() const { return _comp; }
			
			// Non-member function overloads
			friend bool operator==(const map& lhs, const map& rhs)	{return lhs._tree == rhs._tree;}
			friend bool operator!=(const map& lhs, const map& rhs)	{return lhs._tree != rhs._tree;}
			friend bool operator<(const map& lhs, const map& rhs)	{return lhs._tree <  rhs._tree;}
			friend bool operator<=(const map& lhs, const map& rhs)	{return lhs._tree <= rhs._tree;}
			friend bool operator>(const map& lhs, const map& rhs)	{return lhs._tree >  rhs._tree;}
			friend bool operator>=(const map& lhs, const map& rhs)	{return lhs._tree >= rhs._tree;}
			friend void swap(map& lhs,map& rhs) {lhs.swap(rhs);}
	};
}

#endif