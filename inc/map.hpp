/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/01/20 19:13:29 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "rbt.hpp"

namespace ft 
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			// ====================== Member Types ========================= //
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;
			typedef typename Allocator::reference								reference;
			typedef typename Allocator::const_reference							const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer 							const_pointer;
			typedef typename ft::random_access_iterator::iterator				iterator;
			typedef typename ft::random_access_iterator::const_iterator			const_iterator;
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<iterator>::size_type			size_type;
		
			// ====================== Member Classes ========================= //
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
		
		private:
			// ====================== Member Variables ========================= //
			// ft::rb_tree<key_type, value_type, ft::select1st<value_type>, key_compare, allocator_type>	_ctnr;
			key_compare																					_comp;
			allocator_type																				_alloc;
			
		public:
			// ---------------------- Constructors / Destructor ----------------------- //
			explicit map(const key_compare& comp = key_compare(), const Allocator& alloc = Allocator()) : _comp(comp), _alloc(alloc) {} // empty container
			
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const Allocator& alloc = Allocator())
			: _comp(comp), _alloc(alloc) { _ctnr.assign(first, last); }
			
			map(const map& x) : _ctnr(x._ctnr), _comp(x._comp), _alloc(x._alloc) {}
			~map() {}

			// ---------------------- Member Functions ----------------------------- //
			map& 									operator=(const map& x) { _ctnr = x._ctnr; _comp = x._comp; _alloc = x._alloc; return *this; }
			allocator_type							get_allocator() const { return _alloc; }
			
			// Element access
			mapped_type&							at(const key_type& k) { return _ctnr.at(k);}
			const mapped_type&						at(const key_type& k) const { return _ctnr.at(k);}
			mapped_type& 							operator[](const key_type& k) { return _ctnr[k]; }

			// Iterators
			iterator 								begin() { return _ctnr.begin(); }
			const_iterator 							begin() const { return _ctnr.begin(); }
			iterator 								end() { return _ctnr.end(); }
			const_iterator 							end() const { return _ctnr.end(); }
			reverse_iterator 						rbegin() { return _ctnr.rbegin(); }
			const_reverse_iterator 					rbegin() const { return _ctnr.rbegin(); }
			reverse_iterator 						rend() { return _ctnr.rend(); }
			const_reverse_iterator 					rend() const { return _ctnr.rend(); }

			// Capacity
			bool 									empty() const { return _ctnr.empty(); }
			size_type 								size() const { return _ctnr.size(); }
			size_type 								max_size() const { return _ctnr.max_size}
			
			// Modifiers
			pair<iterator,bool> 					insert(const value_type& val) { return _ctnr.insert(val); }
			iterator 								insert(iterator position, const value_type& val) { return _ctnr.insert(position, val); }
			template <class InputIterator>
			void 									insert(InputIterator first, InputIterator last) { _ctnr.insert(first, last); }
			void 									erase(iterator position) { _ctnr.erase(position); }
			size_type 								erase(const key_type& k) { return _ctnr.erase(k); }
			void 									erase(iterator first, iterator last) { _ctnr.erase(first, last); }
			void 									swap(map& x) { _ctnr.swap(x._ctnr); }
			void 									clear() { _ctnr.clear(); }
			
			// Operations
			size_type 								count(const key_type& k) const { return _ctnr.count(k); }
			iterator 								find(const key_type& k) { return _ctnr.find(k); }
			const_iterator 							find(const key_type& k) const { return _ctnr.find(k); }
			pair<const_iterator,const_iterator> 	equal_range(const key_type& k) const { return _ctnr.equal_range(k); }
			pair<iterator,iterator> 				equal_range(const key_type& k) { return _ctnr.equal_range(k); }
			iterator 								lower_bound(const key_type& k) { return _ctnr.lower_bound(k); }
			const_iterator 							lower_bound(const key_type& k) const { return _ctnr.lower_bound(k); }
			iterator 								upper_bound(const key_type& k) { return _ctnr.upper_bound(k); }
			const_iterator 							upper_bound(const key_type& k) const { return _ctnr.upper_bound(k); }
			
			// Observers
			key_compare 							key_comp() const { return _comp; }
			value_compare 							value_comp() const { return _comp; }
			
			// Non-member function overloads
			friend bool 							operator==(const map& lhs, const map& rhs)	{return lhs._ctnr == rhs._ctnr;}
			friend bool 							operator!=(const map& lhs, const map& rhs)	{return lhs._ctnr != rhs._ctnr;}
			friend bool 							operator<(const map& lhs, const map& rhs)	{return lhs._ctnr <  rhs._ctnr;}
			friend bool 							operator<=(const map& lhs, const map& rhs)	{return lhs._ctnr <= rhs._ctnr;}
			friend bool 							operator>(const map& lhs, const map& rhs)	{return lhs._ctnr >  rhs._ctnr;}
			friend bool 							operator>=(const map& lhs, const map& rhs)	{return lhs._ctnr >= rhs._ctnr;}
	};
}

#endif