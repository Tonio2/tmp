#pragma once
#include <iostream>
#include "utils/utils.hpp"
#include "RBbst.hpp"

namespace ft {
	template <	class Key,												// map::key_type
				class T,												// map::mapped_type
				class Compare = std::less<Key>,							// map::key_compare
				class Alloc = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
	class map {
		public:
			typedef	Key													key_type;
			typedef T													mapped_type;
			typedef	ft::pair<const Key, T>								value_type;
			typedef	Compare												key_compare;
			typedef	Alloc												allocator_type;

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef	typename allocator_type::pointer					pointer;
			typedef	typename allocator_type::const_pointer				const_pointer;

			typedef tree_iterator<value_type>							iterator;
			typedef tree_const_iterator<value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			typedef	ptrdiff_t											difference_type;
			typedef	std::size_t											size_type;

			class value_compare : std::binary_function<value_type, value_type, bool> {
				// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				protected:
					Compare comp;
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					value_compare(Compare c) : comp(c) {}
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			explicit map (	const key_compare& _comp = key_compare(),
              				const allocator_type& _alloc = allocator_type())
				:	bst(value_compare(_comp)),
					comp(_comp),
					alloc(_alloc) {}

			template <class InputIterator>
			map (	InputIterator first, InputIterator last,
					const key_compare& _comp = key_compare(),
					const allocator_type& _alloc = allocator_type())
				:	bst(value_compare(_comp)),
					comp(_comp),
					alloc(_alloc) {
						insert(first, last);
					}
			
			map (const map& x)
				:	bst(x.bst),
					comp(x.comp),
					alloc(x.alloc) {}

			~map() {}

			map& operator=(const map& m) {
				bst = m.bst;
				return *this;
			}

			iterator begin() { return bst.begin(); }
			iterator end() { return bst.end(); }

			const_iterator begin() const { return bst.begin(); }
			const_iterator end() const { return bst.end(); }

			reverse_iterator rbegin() { return ft::reverse_iterator<iterator>(end()); }
			reverse_iterator rend() { return ft::reverse_iterator<iterator>(begin()); }

			const_reverse_iterator rbegin() const { return ft::reverse_iterator<const_iterator>(end()); }
			const_reverse_iterator rend() const { return ft::reverse_iterator<const_iterator>(begin()); }

			bool empty() const { return size() == 0; }
			size_type size() const { return bst.size(); }
			size_type max_size() const { return bst.max_size(); }

			mapped_type& operator[] (const key_type& k) {
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}

			pair<iterator,bool> insert (const value_type& val) {
				return bst.insert(val);
			}

			iterator insert (iterator position, const value_type& val) {
				(void)position;
				return bst.insert(val).first;
			}

			template <class InputIter>
			void insert(InputIter first, InputIter last) {
				for (InputIter it = first; it != last; it++)
					bst.insert(*it);
			}

			void erase (iterator position) { bst.erase(position.as_node()); }
			size_type erase (const key_type& k) {
				return bst.erase(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}
     		void erase (iterator first, iterator last) {
				iterator cur = first;
				iterator it = first;
				while (it != last)
				{
					it++;
					bst.erase(cur.as_node());
					cur = it;
				}
			}

			void swap (map& x) { bst.swap(x.bst); }

			void clear() { 
				bst.clear();
			}

			key_compare		key_comp() const { return comp; }
			value_compare	value_comp() const { return value_compare(comp); }

			iterator	find (const key_type& k) {
				return bst.find(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}
			
			const_iterator find (const key_type& k) const {
				return bst.find(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}

			size_type count (const key_type& k) const {
				return (find(k) != end());
			}

			iterator lower_bound (const key_type& k) {
				return bst.lower_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}
			const_iterator lower_bound (const key_type& k) const {
				return bst.lower_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}

			iterator upper_bound (const key_type& k) {
				return bst.upper_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}
			const_iterator upper_bound (const key_type& k) const {
				return bst.upper_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
				const_iterator it1 = bst.lower_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
				const_iterator it2 = bst.upper_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
				return ft::make_pair<const_iterator, const_iterator> (it1, it2);
			}
			pair<iterator,iterator>             equal_range (const key_type& k) {
				iterator it1 = bst.lower_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
				iterator it2 = bst.upper_bound(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
				return ft::make_pair<iterator, iterator> (it1, it2);
			}

			allocator_type get_allocator() const {
				return alloc;
			}
		private:
			RBbst<value_type, value_compare, allocator_type>	bst;
			key_compare											comp;
			allocator_type										alloc;

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		typedef typename map<Key, T, Compare, Alloc>::const_iterator const_iterator;
		if (lhs.size() != rhs.size())
			return false;
		const_iterator itab = lhs.begin();
		const_iterator itae = lhs.end();
		const_iterator itbb = rhs.begin();
		const_iterator ita_cur = itab;
		const_iterator itb_cur = itbb;
		while (ita_cur != itae)
		{
			if (*ita_cur != *itb_cur)
				return false;
			ita_cur++;
			itb_cur++;
		}
		return true;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}


	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		typedef typename map<Key, T, Compare, Alloc>::const_iterator const_iterator;
		const_iterator itab = lhs.begin();
		const_iterator itae = lhs.end();
		const_iterator itbb = rhs.begin();
		const_iterator itbe = rhs.end();
		const_iterator ita_cur = itab;
		const_iterator itb_cur = itbb;
		while (ita_cur != itae && itb_cur != itbe)
		{
			if (*ita_cur > *itb_cur)
				return false;
			if (*ita_cur < *itb_cur)
				return true;
			ita_cur++;
			itb_cur++;
		}
		if (itb_cur == itbe)
			return false;
		return true;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		typedef typename map<Key, T, Compare, Alloc>::const_iterator const_iterator;
		const_iterator itab = lhs.begin();
		const_iterator itae = lhs.end();
		const_iterator itbb = rhs.begin();
		const_iterator itbe = rhs.end();
		const_iterator ita_cur = itab;
		const_iterator itb_cur = itbb;
		while (ita_cur != itae && itb_cur != itbe)
		{
			if (*ita_cur > *itb_cur)
				return false;
			if (*ita_cur < *itb_cur)
				return true;
			ita_cur++;
			itb_cur++;
		}
		if (itb_cur == itbe && ita_cur != itae)
			return false;
		return true;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		typedef typename map<Key, T, Compare, Alloc>::const_iterator const_iterator;
		const_iterator itab = lhs.begin();
		const_iterator itae = lhs.end();
		const_iterator itbb = rhs.begin();
		const_iterator itbe = rhs.end();
		const_iterator ita_cur = itab;
		const_iterator itb_cur = itbb;
		while (ita_cur != itae && itb_cur != itbe)
		{
			if (*ita_cur < *itb_cur)
				return false;
			if (*ita_cur > *itb_cur)
				return true;
			ita_cur++;
			itb_cur++;
		}
		if (ita_cur == itae)
			return false;
		return true;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		typedef typename map<Key, T, Compare, Alloc>::const_iterator const_iterator;
		const_iterator itab = lhs.begin();
		const_iterator itae = lhs.end();
		const_iterator itbb = rhs.begin();
		const_iterator itbe = rhs.end();
		const_iterator ita_cur = itab;
		const_iterator itb_cur = itbb;
		while (ita_cur != itae && itb_cur != itbe)
		{
			if (*ita_cur < *itb_cur)
				return false;
			if (*ita_cur > *itb_cur)
				return true;
			ita_cur++;
			itb_cur++;
		}
		if (ita_cur == itae && itb_cur != itbe)
			return false;
		return true;
	}
}