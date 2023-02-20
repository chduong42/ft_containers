/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/02/20 15:44:15 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft 
{
	template <class T, class Container = ft::vector<T> > class stack {
		public:
			// ====================== Member Types ========================= //
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;
		
		private:
			// ====================== Member Variables ========================= //
			container_type			_ctnr;
		
		public:			
			// ---------------------- Constructors / Destructor ----------------------- //
			explicit stack(const container_type& ctnr = container_type()) : _ctnr(ctnr) {} // empty container
			~stack() {}
	
			// ---------------------- Member Functions ----------------------------- //
			bool					empty() const { return _ctnr.empty(); }
			
			size_type				size() const { return _ctnr.size(); }
			
			value_type&             top() { return _ctnr.back(); }
			const value_type&       top() const { return _ctnr.back(); }
			
			void                    push(const value_type& val) { _ctnr.push_back(val); }
			void                    pop() { _ctnr.pop_back(); }
			
			// ---------------------- Non-member Functions ----------------------------- //
			template <class _T, class _Container>
			friend bool				operator==(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);

			template <class _T, class _Container>
			friend bool				operator!=(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);

			template <class _T, class _Container>
			friend bool				operator<(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);

			template <class _T, class _Container>
			friend bool				operator<=(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);

			template <class _T, class _Container>
			friend bool				operator>(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);

			template <class _T, class _Container>
			friend bool				operator>=(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
	};
	
	template <class T, class Container>	
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr == rhs._ctnr;}
	
	template <class T, class Container>	
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr != rhs._ctnr;}
	
	template <class T, class Container>	
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr < rhs._ctnr;}
	
	template <class T, class Container>	
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr <= rhs._ctnr;}
	
	template <class T, class Container>	
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr > rhs._ctnr;}
	
	template <class T, class Container>	
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr >= rhs._ctnr;}
}

#endif
