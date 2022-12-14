/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/01/06 16:57:07 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include "utility.hpp"

namespace ft 
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > > class map {
		private:
			// ====================== Member Variables ========================= //
			std::vector<std::pair<const Key, T> >				_ctnr;
			Compare												_comp;
			Allocator											_alloc;

		public:
			// ====================== Member Types ========================= //
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef std::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer 			const_pointer;
			typedef typename Allocator::difference_type 		difference_type;
			typedef typename Allocator::size_type 				size_type;

			// ---------------------- Constructors / Destructor ----------------------- //
			explicit map(const key_compare& comp = key_compare(), const Allocator& alloc = Allocator()) : _comp(comp), _alloc(alloc) {} // empty container
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const Allocator& alloc = Allocator()) : _comp(comp), _alloc(alloc) { _ctnr.assign(first, last); }
			map(const map& x) : _ctnr(x._ctnr), _comp(x._comp), _alloc(x._alloc) {}
			~map() {}

			// ---------------------- Member Functions ----------------------------- //
			map& operator=(const map& x) { _ctnr = x._ctnr; _comp = x._comp; _alloc = x._alloc; return *this; }

			// Iterators
			iterator begin() { return _ctnr.begin(); }
			const_iterator begin() const { return _ctnr.begin(); }
			iterator end() { return _ctnr.end(); }
			const_iterator end() const { return _ctnr.end(); }
			reverse_iterator rbegin() { return _ctnr.rbegin(); }
			const_reverse_iterator rbegin() const { return _ctnr.rbegin(); }
			reverse_iterator rend() { return _ctnr.rend(); }
			const_reverse_iterator rend() const { return _ctnr.rend(); }

			// Capacity
			bool empty() const { return _ctnr.empty(); }
			size_type size() const { return _ctnr.size(); }
			size_type max_size() const { return _ctnr.max_size}
	};
}

#endif