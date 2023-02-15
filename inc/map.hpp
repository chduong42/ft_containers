/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/02/15 20:48:08 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
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
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef typename Alloc::pointer												pointer;
			typedef typename Alloc::const_pointer 										const_pointer;
			typedef typename Alloc::difference_type										difference_type;
			typedef typename Alloc::size_type											size_type;
			typedef RBNode<value_type>													node_type;
			typedef node_type*															node_ptr;
			
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
			
			typedef RBTree<key_type, value_type, value_compare, allocator_type>			tree_type;
			typedef tree_iterator<value_type, node_type>								iterator;
			typedef tree_iterator<const value_type, node_type>							const_iterator;
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			
		private:		
			tree_type																	_tree;

		public:
			// ====================== Member Functions ========================= //
			map() : _tree(tree_type()) {};
			explicit map(const Compare& comp, const Alloc& alloc = Alloc())	  : _tree(tree_type(comp, alloc)) {};

			template<class Iter>
			map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& alloc = Alloc(), typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0)
			: _tree(tree_type(comp, alloc)) {this->insert(first, last);}

			explicit map(const map& x) :_tree(tree_type(x.key_comp(), x.get_allocator())) { insert(x.begin(), x.end()); }

			~map() {}
			
			map& operator=( const map& x ) {
				if (this != &x)
					this->_tree = x._tree;
				return *this;
			}

			allocator_type				get_allocator() const {return allocator_type();}

			// ====================== Element access ========================= //
			mapped_type&				at(const Key& key) {return find(key)->second;}
			const mapped_type&			at(const Key& key) const {return find(key)->second;}

			mapped_type &operator[](const key_type &k)
			{
				node_ptr val = _tree.searchTree(k);

				if (val != _tree.getNil())
					return (val->data.second);
				else
				{
					_tree.insertNode(value_type(k, mapped_type())); // insert returns a pair an first element of pair is an it
					val = _tree.searchTree(k);
					return (val->data.second);
				}
			}


			// ====================== Iterators ========================= //
			iterator					begin() { return iterator(_tree.minimum(), _tree.getNil()); }
			const_iterator				begin() const { return const_iterator(_tree.minimum(), _tree.getNil()); }
			iterator					end() { return iterator(_tree.getNil(), _tree.getNil()); }
			const_iterator				end() const { return const_iterator(_tree.getNil(), _tree.getNil()); }
			reverse_iterator			rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator		rbegin() const { return const_reverse_iterator(end());}
			reverse_iterator			rend() { return reverse_iterator(begin()); }
			const_reverse_iterator		rend() const { return const_reverse_iterator(begin()); }

			// ====================== Capacity ========================= //
			bool						empty() const { return _tree.getSize() == 0; }
			size_type					size() const { return _tree.getSize(); }
			size_type					max_size() const { return this->_tree.max_size(); }

			// ====================== Modifiers ========================= //
			void						clear() { _tree.clear_h(_tree.getRoot()); }
			void						swap(map& x) { this->_tree.swap(x._tree); }
			
			ft::pair<iterator,bool> insert(const value_type &val) {
				iterator it = find(val.first);
				if (it != end())
					return (ft::pair<iterator,bool>(it, false));
				else {
					_tree.insertNode(val);
					it = find(val.first);
					return (ft::pair<iterator,bool>(it, true));
				}
			}

			// insert(val) returns a pair of it ans bool so the pair.first returns an it
			iterator insert(iterator position, const value_type &val) { (void)position; return (insert(val).first); }

 			// first here is a bidirectional_iterator which has an * overload so *first = first._ptr->_data which is a pair in map so a value_type
			template <class InputIterator>	void insert(InputIterator first, InputIterator last) { 
				while (first != last) 
					insert(*first++);
			}

			 // position is a bidirectional_iterator which has an * overload so *position = position._ptr->_data so position._ptr->_data.first is the key of value_type
			void erase(iterator position) {	erase((*position).first); }

			size_type erase(const key_type &k) {
				if (_tree.deleteNode(k) == true)
					return 1;
				return 0;
			}

			void erase(iterator first, iterator last) { while(first != last) erase((*(first++)).first); }

			// ====================== Operations ========================= //
			iterator find(const key_type &k) {
				node_ptr tmp = _tree.searchTree(k);
				if (tmp == _tree.getNil())
					return (end());
				return iterator(tmp, _tree.getNil());
			}

			const_iterator find(const key_type &k) const {
				node_ptr tmp = _tree.searchTree(k);
				if (tmp == _tree.getNil())
					return (end());
				return const_iterator(tmp, _tree.getNil());
			}

			size_type count(const key_type& k) const {
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if ((*(beg++)).first == k)
						return (1);
				}
				return (0);
			}

			iterator lower_bound(const key_type &k)	{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (key_comp()((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator lower_bound(const key_type& k) const	{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if (key_comp()((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			iterator upper_bound(const key_type& k)	{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (key_comp()(k ,(*beg).first))
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator upper_bound(const key_type& k) const	{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if (key_comp()(k, (*beg).first))
						break;
					beg++;
				}
				return (beg);
			}
			
			ft::pair<iterator, iterator> 
			equal_range( const Key& key ) {return ft::pair<iterator, iterator>(lower_bound(key),upper_bound(key));	}
			
			ft::pair<const_iterator, const_iterator> 
			equal_range( const Key& key ) const {return ft::pair<const_iterator, const_iterator>(lower_bound(key),upper_bound(key));}

			// ====================== Observers ========================= //
			key_compare					key_comp() const { return key_compare(); }
			value_compare				value_comp() const { return this->_tree.getComp(); }

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
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs) {
		return rhs < lhs;
	}
	
	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,const ft::map<Key, T, Compare, Alloc> &rhs) {
		return !(rhs < lhs);
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