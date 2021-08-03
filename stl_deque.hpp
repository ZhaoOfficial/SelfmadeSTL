#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "stl_algorithm.hpp"
#include "stl_allocator.hpp"
#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"
#include "stl_uninitialized.hpp"

namespace SelfMadeSTL {

	inline size_t deque_buffer_size(size_t n, size_t size) {
		return n != 0 ? n :
		       (size < 512 ? size_t(512 / size) : size_t(1));
	}

	template <typename T, typename Ref, typename Ptr, size_t BufSize>
	struct deque_iterator {
		typedef deque_iterator<T, T&, T*, BufSize>       iterator;
		typedef deque_iterator<T, const T&, const T*, BufSize> const_iterator;
		static size_t buffer_size() {
			return deque_buffer_size(BufSize, sizeof(T));
		}

		typedef random_access_iterator_tag iterator_category;
		typedef T               value_type;
		typedef Ptr             pointer;
		typedef Ref             reference;
		typedef size_t          size_type;
		typedef ptrdiff_t       difference_type;
		typedef T**             map_pointer;

		// current buffer, current position
		pointer curr;
		// current buffer, current head
		pointer first;
		// current buffer, current tail
		pointer last;
		// current buffer
		map_pointer node;

		deque_iterator() :
			curr(nullptr), first(nullptr),
			last(nullptr), node(nullptr) {}
		deque_iterator(T* pos, map_pointer map) :
			curr(pos), first(*map),
			last(*map + buffer_size()), node(map) {}
		deque_iterator(const iterator& other) :
			curr(other.curr), first(other.first),
			last(other.last), node(other.node) {}
		
		reference operator*() const { return *curr; }
		pointer operator->() const { return curr; }
		// position difference
		// this - other
		difference_type operator-(const iterator& other) const {
			return difference_type(buffer_size()) * (node - other.node - 1) + 
			       (curr - first) + (other.last - other.curr);
		}

		void set_node(map_pointer new_node) {
			node = new_node;
			first = *new_node;
			last = *new_node + difference_type(buffer_size());
		}

		iterator& operator++() {
			++curr;
			if (curr == last) {
				set_node(node + 1);
				curr = first;
			}
			return *this;
		}
		iterator operator++(int) {
			iterator temp = *this;
			++*this;
			return temp;
		}
		iterator& operator--() {
			if (curr == first) {
				set_node(node - 1);
				curr = last;
			}
			--curr;
			return *this;
		}
		iterator operator--(int) {
			iterator temp = *this;
			--*this;
			return temp;
		}
		iterator& operator+=(difference_type n) {
			difference_type pos_offset = n + (curr - first);
			// if it is still in the current buffer
			// if [0, buffer_size())
			if (pos_offset >= 0 && pos_offset < difference_type(buffer_size())) {
				curr += n;
			}
			// if across other buffers
			else {
				// if [buffer_size(), +infty), divide directively
				// if (-infty, 0), move to correspond buffer's head
				difference_type node_offset = 
				pos_offset > 0 ? pos_offset / difference_type(buffer_size())
				           : -difference_type((-pos_offset - 1) / buffer_size()) - 1;
				set_node(node + node_offset);
				// then adjust the current position
				curr = first + (pos_offset - node_offset * difference_type(buffer_size()));
			}
			return *this;
		}
		iterator operator+(difference_type n) {
			iterator temp = *this;
			return temp += n;
		}
		iterator& operator-=(difference_type n) {
			return *this += (-n);
		}
		iterator operator-(difference_type n) {
			iterator temp = *this;
			return temp -= n;
		}
	
		reference operator[](difference_type n) const {
			return *((*this + n));
		}

		bool operator==(const iterator& other) const {
			return curr == other.curr;
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}
		bool operator<(const iterator& other) const {
			return (node == other.node) ? 
			       (curr < other.curr) : (node < other.node);
		}

	};

	template <typename T, typename Ref, typename Ptr, size_t BufSize>
	inline random_access_iterator_tag iterator_tag(const deque_iterator<T, Ref, Ptr, BufSize>&) {
		return random_access_iterator_tag();
	}
	template <typename T, typename Ref, typename Ptr, size_t BufSize>
	inline T* value_type(const deque_iterator<T, Ref, Ptr, BufSize>&) {
		return nullptr;
	}
	template <typename T, typename Ref, typename Ptr, size_t BufSize>
	inline ptrdiff_t* difference_type(const deque_iterator<T, Ref, Ptr, BufSize>&) {
		return nullptr;
	} 


	template <typename T, typename Alloc = alloc, size_t BufSize = 0>
	class deque {
	public:
		typedef T               value_type;
		typedef T*              pointer;
		typedef T&              reference;
		typedef size_t          size_type;
		typedef ptrdiff_t       difference_type;
		typedef const T*        const_pointer;
		typedef const T&        const_reference;

		typedef deque_iterator<T, T&, T*, BufSize> iterator;
		typedef deque_iterator<T, const T&, const T*, BufSize> const_iterator;

	protected:
		iterator start;
		iterator finish;
		size_type map_size;
		T** map;

		enum class MapSize { MAP_SIZE = 8 };

		typedef simple_alloc<T, Alloc> node_allocator;
		typedef simple_alloc<T*, Alloc> map_allocator;
		typedef pointer*                  map_pointer;
		
		// memory management

		map_pointer allocate_map(size_t n) {
			return map_allocator::allocate(n);
		}
		void deallocate_map(map_pointer map_ptr, size_t n) {
			map_allocator::deallocate(map_ptr, n);
		}
		void reallocate_map(size_type node_to_add, bool add_at_front) {
			size_type old_nodes_num = finish.node - start.node + 1;
			size_type new_nodes_num = old_nodes_num + node_to_add;

			map_pointer new_start_node;
			// enough space
			if (map_size > 2 * new_nodes_num) {
				// start buffer moves
				new_start_node = map + (map_size - new_nodes_num) / 2 + (add_at_front ? node_to_add : 0);
				// copy [start, finish) to [new_start_node, new_start_node + old_nodes_num)
				if (new_start_node < start.node) {
					// move forward
					copy(start.node, finish.node + 1, new_start_node)
				}
				else {
					// move backward
					copy_backward(start.node, finish.node + 1, new_start_node + old_nodes_num)
				}
			}
			else {
				size_type new_map_size = map_size + std::max(map_size, node_to_add) + 2;
				map_pointer new_map = allocate_map(new_map_size);
				// reserve place for new start node
				new_start_node = new_map + (new_map_size - new_nodes_num) / 2 + (add_at_front ? node_to_add : 0);
				copy(start.node, finish.node + 1, new_start_node);
				deallocate_map(map, map_size);
				map = new_map;
				map_size = new_map_size;
			}
		}
		void initialize_map(size_type elements_num) {
			size_type nodes_num = elements_num / deque_buffer_size(BufSize, sizeof(T)) + 1;
			this.map_size = std::max(MapSize::MAP_SIZE, nodes_num + 2);
			this.map = allocate_map(map_size);

			map_pointer start_node = map + (map_size - nodes_num) / 2;
			map_pointer finish_node = start_node + nodes_num;

			try {
				create_nodes(start_node, finish_node);
			}
			catch (const std::exception& e) {
				deallocate_map(map, map_size);
				map = nullptr;
				map_size = nullptr;
			}

			start.set_node(start_node);
			start.curr = start_node.first;
			finish.set_node(finish_node);
			finish.curr = finish_node.first + elements_num % deque_buffer_size(BufSize, sizeof(T));
		}

		iterator reserve_map_at_back(size_type node_to_add = 1) {
			// not enough space at back of the map
			if (node_to_add + 1 > map_size - (finish.node - map)) {
				reallocate_map(node_to_add, false);
			}
			// if enough, then append elements
		}
		iterator reserve_map_at_front(size_type node_to_add = 1) {
			if (node_to_add + 1 > size_type(start.node - map)) {
				reallocate_map(node_to_add, true);
			}
		}

		T* allocate_node() {
			return node_allocator::allocate(deque_buffer_size(BufSize, sizeof(T)));
		}
		void deallocate_node(T* node) {
			node_allocator::deallocate(node, deque_buffer_size(BufSize, sizeof(T)));
		}
		void create_nodes(map_pointer start_node, map_pointer finish_node) {
			map_pointer curr_node = start_node;
			try {
				for ( ; curr_node != finish_node; ++curr_node) {
					curr_node = allocate_node();
				}
			}
			catch (const std::exception& e) {
				destroy_nodes(start_node, curr_node);
			}
		}
		void destroy_nodes(map_pointer start_node, map_pointer finish_node) {
			for (map_pointer curr_node = start_node; curr_node != finish; ++curr_node) {
				deallocate_node(curr_node);
			}
		}

		void fill_initialize(const value_type& value) {
			map_pointer curr_node = start.node;
			try {
				for (; curr_node < finish.node; ++curr_node) {
					// fill the buffer
					uninitialized_fill(*curr_node, *curr_node + deque_buffer_size(BufSize, sizeof(T)), value);
				}
				// fill last buffer
				uninitialized_fill(finish.first, finish.curr, value);
			}
			catch(const std::exception& e) {
				destroy(start, iterator(*curr_node, curr_node));
			}
		}

		iterator reserve_element_at_front(size_type n) {
			size_type vacancy = start.curr - start.first;
			if (n > vacancy) {
				new_elements_at_front(n - vacancy);
			}
			return start - difference_type(n);
		}
		iterator reserve_element_at_back(size_type n) {
			size_type vacancy = (finish.last - finish.first) - 1;
			if (n > vacancy) {
				new_elements_at_back(n - vacancy);
			}
			return finish + difference_type(n);
		}
		void new_elements_at_front(size_type n) {
			size_type new_nodes = (n - 1) / deque_buffer_size(BufSize, sizeof(T)) + 1
			reserve_map_at_front(new_nodes);
			size_type i;
			try {
				for (i = 1; i <= new_nodes; ++i) {
					*(start.node - i) = allocate_node();
				}
			}
			catch (const std::exception& e) {
				for (size_type j = 1; j < i; ++j) {
					deallocate_node(*(start.node - j));
				}
			}
		}
		void new_elements_at_back(size_type n) {
			size_type new_nodes = (n - 1) / deque_buffer_size(BufSize, sizeof(T)) + 1;
			reserve_map_at_back(new_nodes);
			size_type i;
			try {
				for (i = 1; i <= new_nodes; ++i) {
					*(finish.node + i) = allocate_node();
				}
			}
			catch (const std::exception& e) {
				for (size_type j = 1; j < i; ++j) {
					deallocate_node(*(finish.node + j));
				}
			}
		}

		void push_back_aux(const value_type& value) {
			value_type value_copy = value;
			reserve_map_at_back();
			*(finish.curr + 1) = allocate_node();
			try {
				construct(finish.curr, value_copy);
				finish.set_node(finish.node + 1);
				finish.curr = finish.first;
			}
			catch (const std::exception& e) {
				deallocate_node(*(finish.node + 1));
			}
		}
		void push_back_aux() {
			reserve_map_at_back();
			*(finish.curr + 1) = allocate_node();
			try {
				construct(finish.curr);
				finish.set_node(finish.node + 1);
				finish.curr = finish.first;
			}
			catch (const std::exception& e) {
				deallocate_node(*(finish.node + 1));
			}
		}
		void push_front_aux(const value_type& value) {
			value_type value_copy = value;
			reserve_map_at_front();
			*(start - 1) = allocate_node();
			try {
				start.set_node(start.node - 1);
				start.curr = start.last - 1;
				construct(start.curr, value_copy);
			}
			catch(const std::exception& e) {
				++start;
				deallocate_node(*(start.node - 1));
			}
		}
		void push_front_aux() {
			reserve_map_at_front();
			*(start - 1) = allocate_node();
			try {
				start.set_node(start.node - 1);
				start.curr = start.last - 1;
				construct(start.curr);
			}
			catch(const std::exception& e) {
				++start;
				deallocate_node(*(start.node - 1));
			}
		}
		void pop_back_aux() {
			deallocate_node(finish.first);
			finish.set_node(finish.node - 1);
			finish.curr = finish.last - 1;
			destory(finish.curr);
		}
		void pop_front_aux() {
			destory(start.curr);
			deallocate_node(start.first);
			start.set_node(start.node + 1);
			start.curr = start.first;
		}
		
		iterator insert_aux(iterator pos, const value_type& value) {
			const difference_type element_before = pos - start;
			value_type value_copy = value;
			if (element_before < (size() / 2)) {
				push_front(front());
				// map may be extended and changed memory position
				// here we need to insert after `pos`
				pos = start + element_before;
				// copy [start + 2, pos + 1) to [start + 1, pos)
				copy(start + 2, pos + 1, start + 1);
			}
			else {
				push_back(back());
				pos = start + element_before;
				// copy [pos, finish - 2) to [pos + 1, finish - 1)
				copy_backward(pos, finish - 2, finish - 1);
			}
			*pos = value_copy;
			return pos;
		}
		void insert_aux(iterator pos, size_type n, const value_type& value) {
			const difference_type element_before = pos - start;
			const difference_type element_after = finish - pos;
			value_type value_copy = value;
			// less at before
			if (element_before < size() / 2) {
				iterator new_start = reserve_element_at_front(n);
				iterator old_start = start;
				pos = start + element_before;
				try {
					// no overlapping when copy
					if (element_before < difference_type(n)) {
						// copy [old_start, pos) to [new_start, new_start + element_before)
						iterator pos_n = pos - difference_type(n);
						uninitialized_copy(old_start, pos, new_start);
						// fill [new_start + element_before, old_start) with value
						uninitialized_fill(pos_n, old_start, value_copy);
						// fill[old_start, pos) with value
						fill(old_start, pos, value_copy);
					}
					// exists overlapping
					else {
						iterator start_n = old_start + difference_type(n);
						uninitialized_copy(old_start, start_n, new_start);
						copy(start_n, pos, old_start);
						fill(pos - difference_type(n), pos, value_copy);
					}
					start = new_start;
				}
				catch (const std::exception& e) {
					destroy_nodes(new_start.node, old_start.node);
				}
			}
			// less at back
			else {
				iterator new_finish = reserve_element_at_back(n);
				iterator old_finish = finish;
				pos = old_finish - element_after;
				try {
					if (element_after <= difference_type(n)) {
						iterator pos_n = pos + difference_type(n);
						uninitialized_copy(pos, finish, pos_n);
						uninitialized_fill(finish, pos_n, value_copy);
						fill(pos, finish, value_copy);
					}
					else {
						iterator finish_n = old_finish - difference_type(n);
						uninitialized_copy(finish_n, old_finish, old_finish);
						copy_backward(pos, finish_n, old_finish);
						fill(pos, pos + difference_type(n), value_copy);
					}
					finish = new_finish;
				}
				catch (const std::exception& e) {
					destroy_nodes(old_finish.node + 1, new_finish.node + 1);
				}
			}
		}
		void insert_aux(iterator pos, const value_type* first, const value_type* last, size_type n) {
			const difference_type element_before = pos - start;
			const difference_type element_after = finish - pos;
			if (element_before < (size() / 2)) {
				iterator new_start = reserve_element_at_front(n);
				iterator old_start = start;
				pos = start + element_before;
				try {
					if (element_before < difference_type(n)) {
						iterator pos_n = pos - difference_type(n);
						const value_type* mid = first + (difference_type(n) - element_before);
						uninitialized_copy(old_start, pos, new_start);
						uninitialized_copy(first, mid, pos_n);
						copy(mid, last, old_start);
					}
					else {
						iterator start_n = old_start + difference_type(n);;
						uninitialized_copy(old_start, start_n, new_start);
						copy(start_n, pos, old_start);
						copy(first, last, pos - difference_type(n));
					}
					start = new_start;
				}
				catch (const std::exception& e) {
					destroy_nodes(new_start.node, old_start.node);
				}
			}
			else {
				iterator new_finish = reserve_element_at_back(n);
				iterator old_finish = finish;
				try {
					if (element_after <= difference_type(n)) {
						iterator pos_n = pos + difference_type(n);
						const value_type* mid = first + element_after;
						uninitialized_copy(pos, old_finish, pos_n);
						uninitialized_copy(mid, last, old_finish);
						copy(first, mid, pos);
					}
					else {
						iterator finish_n = old_finish - difference_type(n);
						uninitialized_copy(finish_n, old_finish, old_finish);
						copy_backward(pos, finish_n, old_finish);
						copy(first, last, pos);
					}
					finish = new_finish;
				}
				catch (const std::exception& e) {
					destroy_nodes(old_finish.node + 1, new_finish.node + 1);
				}
			}
		}
		void insert_aux(iterator pos, const_iterator first, const_iterator last, size_type n) {
			const difference_type element_before = pos - start;
			const difference_type element_after = finish - pos;
			if (element_before < (size() / 2)) {
				iterator new_start = reserve_element_at_front(n);
				iterator old_start = start;
				pos = start + element_before;
				try {
					if (element_before < difference_type(n)) {
						iterator pos_n = pos - difference_type(n);
						const value_type* mid = first + (difference_type(n) - element_before);
						uninitialized_copy(old_start, pos, new_start);
						uninitialized_copy(first, mid, pos_n);
						copy(mid, last, old_start);
					}
					else {
						iterator start_n = old_start + difference_type(n);;
						uninitialized_copy(old_start, start_n, new_start);
						copy(start_n, pos, old_start);
						copy(first, last, pos - difference_type(n));
					}
					start = new_start;
				}
				catch (const std::exception& e) {
					destroy_nodes(new_start.node, old_start.node);
				}
			}
			else {
				iterator new_finish = reserve_element_at_back(n);
				iterator old_finish = finish;
				pos = old_finish - element_after;
				try {
					if (element_after <= difference_type(n)) {
						iterator pos_n = pos + difference_type(n);
						const value_type* mid = first + element_after;
						uninitialized_copy(pos, old_finish, pos_n);
						uninitialized_copy(mid, last, old_finish);
						copy(first, mid, pos);
					}
					else {
						iterator finish_n = old_finish - difference_type(n);
						uninitialized_copy(finish_n, old_finish, old_finish);
						copy_backward(pos, finish_n, old_finish);
						copy(first, last, pos);
					}
					finish = new_finish;
				}
				catch (const std::exception& e) {
					destroy_nodes(old_finish.node + 1, new_finish.node + 1);
				}
			}
		}

	public:
		explicit deque() {
			initialize_map(0);
		}
		explicit deque(size_t n, const value_type& value = value_type()) {
			initialize_map(n);
			fill_initialize(value);
		}
		deque(const deque& other) {
			initialize_map(other.map_size);
			SelfMadeSTL::uninitialized_copy(
				other.begin(), other.end(), start
			);
		}
		deque(const value_type* first, const value_type* last) {
			initialize_map(last - first);
			uninitialized_copy(first, last, start);
		}
		deque(const_iterator first, const_iterator last) {
			initialize_map(last - first);
			uninitialized_copy(first, last, start);
		}
		deque& operator=(const deque& other) {
			const size_type len = this.size();
			if (this != &other) {
				if (len >= other.size()) {
					iterator new_finish = copy(other.begin(), other.end(), start);
					erase(new_finish, finish);
				}
				else {
					const_iterator mid = other.begin() + difference_type(len);
					copy(other.begin(), mid, start);
					insert(finish, mid, other.end())
				}
			}
			return *this;
		}
		~deque() {
			destory(start, finish);
			if (map != nullptr) {
				destroy_nodes(start.node, finish.node + 1);
				deallocate_map(map, map_size);
			}
		}

		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator begin() const { return start; }
		const_iterator end() const { return finish; }
		const_iterator cbegin() const { return start; }
		const_iterator cend() const { return finish; }

		reference front() { return *start; }
		reference back() { return *(finish - 1); }
		const_reference front() const { return *start; }
		reference back() { return *(finish - 1); }
		reference operator[](size_t idx) {
			return start[difference_type(idx)];
		}
		const_reference operator[](size_t idx) const {
			return start[difference_type(idx)];
		}
	
		size_type size() const { return finish - start; }
		bool empty() const { return start == finish; }

		void push_back(const value_type& value) {
			// if not at the last position of current buffer
			if (finish.curr != finish.last - 1) {
				construct(finish.curr, value);
				++finish.curr;
			}
			else {
				push_back_aux(value);
			}
		}
		void push_back() {
			if (finish.curr != finish.last - 1) {
				construct(finish.curr);
				++finish.curr;
			}
			else {
				push_back_aux();
			}
		}
		void push_front(const value_type& value) {
			// if not at the first position of current buffer
			if (start.curr != start.first) {
				construct(start.curr - 1, value);
				--start.curr;
			}
			else {
				push_front_aux(value);
			}
		}
		void push_front() {
			if (start.curr != start.first) {
				construct(start.curr - 1);
				--start.curr;
			}
			else {
				push_front_aux();
			}
		}
		void pop_front() {
			if (start.curr != start.last - 1) {
				destory(start.curr);
				++start.curr;
			}
			else {
				pop_front_aux();
			}
		}
		void pop_back() {
			if (finish.curr != finish.first) {
				--finish.curr;
				destory(finish.curr);
			}
			else {
				pop_back_aux();
			}
		}

		// insert at the front of the `pos`
		iterator insert(iterator pos, const value_type& value = value_type()) {
			if (pos.curr == start.curr) {
				push_back(value);
				return start;
			}
			else if (pos.curr == finish.curr) {
				push_back(value);
				return finish - 1;
			}
			else {
				return insert_aux(pos, value);
			}
		}
		void insert(iterator pos, size_type n, const value_type& value = value_type()) {
			if (pos.curr == start.curr) {
				iterator new_start = reserve_element_at_front(n);
				uninitialized_fill(new_start, start, value);
				start = new_start;
			}
			else if (pos.curr == finish.curr) {
				iterator new_finish = reserve_element_at_back(n);
				uninitialized_fill(finish, new_finish, value);
				finish = new_finish;
			}
			else {
				insert_aux(pos, n, value);
			}
		}
		void insert(iterator pos, const value_type* first, const value_type* last) {
			size_type n = last - first;
			if (pos.curr == start.curr) {
				iterator new_start = reserve_element_at_front(n);
				try {
					uninitialized_copy(first, last, new_start);
					start = new_start;
				}
				catch (const std::exception& e) {
					destroy_nodes(new_start.node, start.node);
				}
			}
			else if (pos.curr == finish.curr) {
				iterator new_finish = reserve_element_at_back(n);
				try {
					uninitialized_copy(first, last, finish);
					finish = new_finish;
				}
				catch (const std::exception& e) {
					destroy_nodes(finish.node + 1, new_finish.node + 1);
				}
			}
			else {
				insert_aux(pos, first, last, n);
			}
		}
		void insert(iterator pos, const_iterator first, const_iterator last) {
			size_type n = last - first;
			if (pos.curr == start.curr) {
				iterator new_start = reserve_element_at_front(n);
				try {
					uninitialized_copy(first, last, new_start);
					start = new_start;
				}
				catch (const std::exception& e) {
					destroy_nodes(new_start.node, start.node);
				}
			}
			else if (pos.curr == finish.curr) {
				iterator new_finish = reserve_element_at_back(n);
				try {
					uninitialized_copy(first, last, finish);
					finish = new_finish;
				}
				catch (const std::exception& e) {
					destroy_nodes(finish.node + 1, new_finish.node + 1);
				}
			}
			else {
				insert_aux(pos, first, last, n);
			}
		}

		iterator erase(iterator pos) {
			iterator next = pos;
			next++;
			difference_type dist = pos - start;
			if (dist < (size() / 2)) {
				copy_backward(start, finish, next);
				pop_front();
			}
			else {
				copy(next, finish, pos);
				pop_back();
			}
			return start + dist;
		}
		iterator erase(iterator first, iterator last) {
			if (first == start && last == finish) {
				clear();
				return finish;
			}

			difference_type n = last - first;
			difference_type element_before = first - start;
			if (element_before < (size() - n) / 2) {
				// move [start, first) to [start + n, last)
				copy_backward(start, first, last);
				iterator new_start = start + n;
				destory(start, new_start);
				destroy_nodes(start.node, new_start.node);
				start = new_start;
			}
			else {
				// move [last, finish) to [first, finish - n)
				copy(last, finish, first);
				iterator new_finish = finish - n;
				destory(new_finish, finish);
				destroy_nodes(new_finish.node + 1, finish.node + 1);
				finish = new_finish;
			}
			return start + element_before;
		}

		void resize(size_type new_size, const value_type& value = value_type()) {
			const value_type len = size();
			if (new_size < len) {
				erase(start + new_size, finish);
			}
			else {
				insert(finish, new_size - len, value);
			}
		}

		void clear() {
			for (map_pointer curr_node = start.node + 1; curr_node < finish.node; ++curr_node) {
				destory(*curr_node, *curr_node + deque_buffer_size(BufSize, sizeof(T)));
				deallocate_node(*curr_node);
			}

			if (start.node != finish.node) {
				destory(start.curr, start.last);
				destory(finish.first, finish.curr);
				deallocate_node(finish.first);
			}
			else {
				destory(start.curr, finish.curr);
			}
			finish = start;
		}

		void swap(deque& other) {
			std::swap(start, other.start);
			std::swap(finish, other.finish);
			std::swap(map, other.map);
			std::swap(map_size, other.map_size);
		}

		bool operator==(const deque& other) const {
			return (size() == other.size() && equal(begin(), end(), other.begin()));
		}
		bool operator!=(const deque& other) const {
			return !this->operator==(other);
		}
		bool operator<=(const deque& other) const {
			return lexicographical_compare(begin(), end(), other.begin(), other.end());
		}

	};

}

#endif // !_DEQUE_H_