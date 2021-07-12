#ifndef _LIST_H_
#define _LIST_H_

#include "stl_algorithm.hpp"
#include "stl_allocator.hpp"
#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"
#include "stl_uninitialized.hpp"

namespace SelfMadeSTL {

	template <typename T>
	struct list_node {
		list_node<T>* prev;
		list_node<T>* next;
		T             data;
	};

	template <typename T, typename Ref, typename Ptr>
	struct list_iterator {
		typedef list_iterator<T, T&, T*>             iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		typedef list_iterator<T, Ref, Ptr>           self;

		typedef bidirectional_iterator_tag iterator_category;
		typedef T            value_type;
		typedef Ptr          pointer;
		typedef Ref          reference;
		typedef size_t       size_type;
		typedef ptrdiff_t    difference_type;
		typedef list_node<T> node;

		// member variable
		node* inner;

		list_iterator(node* n) : inner(n) {}
		list_iterator() {}
		list_iterator(const iterator& other) : inner(other.inner) {}

		bool operator==(const self& other) const { return inner == other.inner; }
		bool operator!=(const self& other) const { return inner != other.inner; }
		reference operator*() const { return inner->data; }
		pointer operator->() const { return &(operator*()); }

		self& operator++() {
			inner = inner->next;
			return *this;
		}
		self operator++(int) {
			auto temp = inner;
			++* this;
			return temp;
		}
		self& operator--() {
			inner = inner->prev;
			return *this;
		}
		self operator--(int) {
			auto temp = inner;
			--* this;
			return temp;
		}
	};

	template <typename T, typename Alloc = alloc>
	class list {
	public:
		typedef T               value_type;
		typedef T*              pointer;
		typedef T&              reference;
		typedef size_t          size_type;
		typedef ptrdiff_t       difference_type;
		typedef const T*        const_pointer;
		typedef const T&        const_reference;
		typedef list_node<T>    node;

		typedef simple_alloc<node, Alloc> list_allocator;

		typedef list_iterator<T, T&, T*>             iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

	protected:
		node* sentinel;

	// auxilary function
	private:
		node* get_node() { return list_allocator::allocate((size_type)1); }
		void put_node(node* n) { list_allocator::deallocate(n); }
		node* new_node(const T& value) {
			node* n = get_node();
			construct(&(n->data), value);
			return n;
		}
		void delete_node(node* n) {
			destory(&(n->data));
			put_node(n);
		}

		void init() {
			sentinel = get_node();
			sentinel->next = sentinel;
			sentinel->prev = sentinel;
		}

	public:
		list() { init(); }
		list(size_type n, const T& value = value_type()) {
			init();
			insert(begin(), n, value);
		}
		list(const T* first, const T* last) {
			insert(begin(), first, last);
		}
		list(const_iterator first, const_iterator last) {
			insert(begin(), first, last);
		}
		list(const list& other) {
			insert(begin(), other.begin(), other.end());
		}
		list& operator=(const list& other) {
			if (this != &other) {
				iterator first1 = begin();
				iterator last1 = end();
				const_iterator first2 = other.begin();
				const_iterator last2 = other.end();
				while (first1 != last1 && first2 != last2) {
					*first1++ = *first2++;
				}
				if (first2 == last2) {
					erase(first1, last1);
				}
				else {
					insert(last1, first2, last2);
				}
			}
			return *this;
		}
		~list() {
			clear();
			delete_node(sentinel);
		}

		iterator begin() { return sentinel->next; }
		iterator end() { return sentinel; }
		const_iterator begin() const { return sentinel->next; }
		const_iterator end() const { return sentinel; }
		const_iterator cbegin() const { return sentinel->next; }
		const_iterator cend() const { return sentinel; }

		size_type size() const { return distance(begin(), end()); }
		bool empty() { return sentinel->next == sentinel; }

		reference front() { return *begin(); }
		reference back() { return *(--end()); }
		const_reference front() const { return *begin(); }
		const_reference back() const { return *(--end()); }
		
		bool operator==(const list& other) {
			node* s1 = this->sentinel;
			node* s2 = other.sentinel;
			node* n1 = s1->next;
			node* n2 = s2->next;
			for (; n1 != s1 && n2 != s2; n1 = n1->next, n2 = n2->next) {
				if (n1->data != n2->data)
					return false;
			}
			return n1 == s1 && n2 == s2;
		}

		bool operator!=(const list& other) {
			return !operator==(other);
		}

		bool operator<(const list& other) {
			return SelfMadeSTL::lexicographical_compare(begin(), end(), other.begin(), other.end());
		}

		iterator insert(iterator pos, const T& value = value_type()) {
			node* temp = new_node(value);
			temp->next = pos.inner;
			temp->prev = pos.inner->prev;
			pos.inner->prev->next = temp;
			pos.inner->prev = temp;
			return iterator(temp);
		}
		void insert(iterator pos, const T* first, const T* last) {
			for (; first != last; ++first) {
				insert(pos, *first);
			}
		}
		void insert(iterator pos, const_iterator first, const_iterator last) {
			for (; first != last; ++first) {
				insert(pos, *first);
			}
		}
		void insert(iterator pos, size_type n, const T& value) {
			for (; n > 0; --n) {
				insert(pos, value);
			}
		}

		void push_front(const T& value = value_type()) { insert(begin(), value); }
		void push_back(const T& value = value_type()) { insert(end(), value); }

		iterator erase(iterator pos) {
			auto next_node = pos.inner->next;
			pos.inner->prev->next = pos.inner->next;
			pos.inner->next->prev = pos.inner->prev;
			delete_node(pos);
			return iterator(next_node);
		}
		void erase(iterator first, iterator last) {
			for (; first != last;) {
				first = erase(first);
			}
			return last;
		}

		void pop_front() { erase(begin()); }
		void pop_back() {
			auto temp = end();
			erase(--temp);
		}

		void resize(size_type new_size, const T& value = value_type()) {
			iterator it = begin();
			size_type len = 0;
			for (; it != end() && len < new_size; ++it) {
				++len;
			}
			if (len == new_size) {
				erase(it, end());
			}
			else {
				insert(end(), new_size - len, value);
			}
		}

		void clear() {
			node* curr = sentinel->next;
			while (curr!= sentinel) {
				node* temp = curr;
				curr = curr->next;
				delete_node(temp);
			}
			sentinel->next = sentinel;
			sentinel->prev = sentinel;
		}
	
		void swap(list& other) {
			std::swap(sentinel, other.sentinel);
		}

		void remove(const T& value) {
			iterator first = begin();
			iterator last = end();
			while (first != last) {
				iterator next = first;
				++next;
				if (*first == value) {
					erase(first);
				}
				first = next;
			}
		}

		void unique(const T& value) {
			iterator first = begin();
			iterator last = end();
			if (first == last) {
				return;
			}
			iterator next = first;
			while (++next != last) {
				if (*first == *next) {
					erase(next);
				}
				else {
					first = next;
				}
				next = first;
			}
		}
	
	protected:
		// move [first, last) to the position end with `pos`
		void transfer(iterator pos, iterator first, iterator last) {
			if (pos != last) {
				// next connection
				last.inner->prev->next = pos.inner;
				first.inner->prev->next = last.inner;
				pos.inner->prev->next = first.inner;

				// prev connection
				auto temp = pos.inner->prev;
				pos.inner->prev = last.inner->prev;
				last.inner->prev = first.inner->prev;
				first.inner->prev = temp;
			}
		}

	public:
		void splice(iterator pos, list& other) {
			if (!other.empty()) {
				transfer(pos, other.begin(), other.end());
			}
		}

		void splice(iterator pos, list&, iterator i) {
			iterator j = i;
			++j;
			if (pos == i || pos == j) {
				return;
			}
			transfer(pos, i, j);
		}

		void splice(iterator pos, list&, iterator first, iterator last) {
			if (first != last) {
				transfer(pos, first, last);
			}
		}

		// merge two sorted list ascendingly
		void merge(list& other) {
			iterator first1 = begin();
			iterator last1 = end();
			iterator first2 = other.begin();
			iterator last2 = other.end();

			while (first1 != last1 && first2 != last2) {
				if (*first1 < *first2) {
					++first1;
				}
				else {
					iterator next = first2;
					transfer(first1, first2, ++next);
					++first2;
				}
			}
			if (first2 != last2) {
				transfer(last1, first2, last2);
			}
		}
		
		template<typename Compare>
		void merge(list& other, Compare comp) {
			iterator first1 = begin();
			iterator last1 = end();
			iterator first2 = other.begin();
			iterator last2 = other.end();

			while (first1 != last1 && first2 != last2) {
				if (comp(*first1, *first2)) {
					++first1;
				}
				else {
					iterator next = first2;
					transfer(first1, first2, ++next);
					++first2;
				}
			}
			if (first2 != last2) {
				transfer(last1, first2, last2);
			}
		}

		void reverse() {
			// do nothing if size() is 0 or 1
			if (sentinel->next != sentinel && sentinel->next->next != sentinel) {
				iterator first = begin();
				++first;
				while (first != end()) {
					iterator old = first;
					++first;
					transfer(begin(), old, first);
				}
			}
		}

		// quick sort
		void sort() {
			// do nothing if size() is 0 or 1
			if (sentinel->next != sentinel && sentinel->next->next != sentinel) {
				list carry;
				// 2 ^ 64 size list
				list counter[64];

				int fill = 0;
				while (!empty()) {
					// put the begin() element to carry
					carry.splice(carry.begin(), *this, begin());
					int i = 0;
					while (i < fill && !counter[i].empty()) {
						// here we sort it
						counter[i].merge(carry);
						carry.swap(counter[i++]);
					}
					carry.swap(counter[i]);
					if (i == fill) {
						++fill;
					}
				}
				for (int i = 1; i < fill; ++i) {
					counter[i].merge(counter[i - 1]);
				}
				swap(counter[fill - 1]);
			}
		}

		template<typename Compare>
		void sort(Compare comp) {
			// do nothing if size() is 0 or 1
			if (sentinel->next != sentinel && sentinel->next->next != sentinel) {
				list carry;
				// 2 ^ 64 size list
				list counter[64];

				int fill = 0;
				while (!empty()) {
					// put the begin() element to carry
					carry.splice(carry.begin(), *this, begin());
					int i = 0;
					while (i < fill && !counter[i].empty()) {
						// here we sort it
						counter[i].merge(carry, comp);
						carry.swap(counter[i++]);
					}
					carry.swap(counter[i]);
					if (i == fill) {
						++fill;
					}
				}
				for (int i = 1; i < fill; ++i) {
					counter[i].merge(counter[i - 1]);
				}
				swap(counter[fill - 1]);
			}
		}

	};
}

#endif // !_LIST_H_
