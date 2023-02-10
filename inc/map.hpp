/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/02/09 16:03:21 by chduong          ###   ########.fr       */
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
			typedef typename tree_type::node_ptr										node_ptr;
		
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
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp), _alloc(alloc) {}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp) { insert(first, last); }
			map(const map& x) : _tree(x._tree), _comp(x._comp) {}
			~map() {}

			// ---------------------- Member Functions ----------------------------- //
			// Operator
			map&						operator=(const map& x) { _tree = x._tree; _comp = x._comp; return *this; }
						
			// Element access
			mapped_type&	at(const key_type& k)
			{
				iterator it = _tree.find(k);
				if (it == _tree.end())
					throw std::out_of_range("map::at");
				return it->second;
			}
			
			const mapped_type&	at(const key_type& k) const
			{
				const_iterator it = _tree.find(k);
				if (it == _tree.end())
					throw std::out_of_range("map::at");
				return it->second;
			}
			
			mapped_type&	operator[](const key_type &k)
			{
				node_ptr val = _tree.searchNode(k);

				if (val != _tree.getNil())
					return (val->data.second);
				else
				{
					_tree.insertNode(value_type(k, mapped_type())); // insert returns a pair an first element of pair is an it
					val = _tree.searchNode(k);
					return (val->data.second);
				}
			}

			iterator	 				begin() {return iterator(_tree.minNode(_tree.getRoot()));}
			const_iterator 				begin() const {return const_iterator(_tree.minNode(_tree.getRoot()));}
			iterator 					end() {return iterator(_tree.getNil());}
			const_iterator 				end() const {return const_iterator(_tree.getNil());}
			reverse_iterator			rbegin() {return reverse_iterator(end());}
			const_reverse_iterator		rbegin() const {return const_reverse_iterator(end());}

			reverse_iterator 			rend() {return reverse_iterator(begin());}
			const_reverse_iterator		rend() const {return const_reverse_iterator(begin());}
			bool 						empty() const {return (_tree.getSize() == 0);}
			size_type 					size() const {return (_tree.getSize());}
			size_type 					max_size() const {return (_tree.max_size());}
			
			void 						swap (map &x) {_tree.swap(x._tree);}
			void 						clear() {_tree.clear_h(_tree.getRoot());}
			key_compare 				key_comp() const {return (this->_comp);}
			value_compare 				value_comp() const {return (value_compare(this->_comp));}
			allocator_type				get_allocator() const { return _tree.get_allocator(); }

		ft::pair<iterator,bool> insert(const value_type &val)
		{
			iterator it = find(val.first);
			if (it != end())
				return (ft::pair<iterator,bool>(it, false));
			else
			{
				_tree.insertNode(val);
				it = find(val.first);
				return (ft::pair<iterator,bool>(it, true));
			}
		}

		iterator insert(iterator position, const value_type &val) {
			(void)position;
			return (insert(val).first); // insert(val) returns a pair of it ans bool so the pair.first returns an it
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last)
				insert(*first++); // first here is a bidirectional_iterator which has an * overload so *first = first._ptr->_data which is a pair in map so a value_type
		}

		// position is a bidirectional_iterator which has an * overload so *position = position._ptr->_data so position._ptr->_data.first is the key of value_type
		void erase(iterator position) {erase((*position).first);}

		size_type erase(const key_type &k)
		{
			if (_tree.deleteNode(k) == true)
				return 1;
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			while(first != last)
				erase((*(first++)).first);
		}

		iterator find(const key_type &k)
		{
			node_ptr tmp = _tree.searchNode(k);
			if (tmp == _tree.getNil())
				return (end());
			return iterator(tmp);
		}

		const_iterator find(const key_type &k) const
		{
			node_ptr tmp = _tree.searchNode(k);
			if (tmp == _tree.getNil())
				return (end());
			return const_iterator(tmp);
		}

		size_type count(const key_type& k) const
		{
			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if ((*(beg++)).first == k)
					return (1);
			}
			return (0);
		}

		iterator lower_bound(const key_type &k) 
		{
			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (_comp((*beg).first, k) == false)
					break;
				beg++;
			}
			return (beg);
		}

		const_iterator lower_bound(const key_type& k) const
		{
			iterator beg = const_iterator(this->begin());
			iterator end = this->end();

			while (beg != end)
			{
				if (_comp((*beg).first, k) == false)
					break;
				beg++;
			}
			return const_iterator(beg);
		}

		iterator upper_bound(const key_type& k) 
		{
			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (_comp(k ,(*beg).first))
					break;
				beg++;
			}
			return (beg);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (_comp(k, (*beg).first))
					break;
				beg++;
			}
			return (const_iterator(beg));
		}

		pair<iterator,iterator> 				equal_range(const key_type &k)	{return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));}
		pair<const_iterator,const_iterator> 	equal_range(const key_type &k) const {return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));}
			
		// Non-member function overloads
		friend bool operator== (const map& lhs, const map& rhs) {return (lhs._tree == rhs._tree);}
		friend bool operator!= (const map& lhs, const map& rhs) {return (lhs._tree != rhs._tree);}
		friend bool operator<  (const map& lhs, const map& rhs) {return (lhs._tree < rhs._tree);}
		friend bool operator<= (const map& lhs, const map& rhs) {return (lhs._tree <= rhs._tree);}
		friend bool operator>  (const map& lhs, const map& rhs) {return (lhs._tree > rhs._tree);}
		friend bool operator>= (const map& lhs, const map& rhs) {return (lhs._tree >= rhs._tree);}
	};
}

#endif