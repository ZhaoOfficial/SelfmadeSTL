#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "stl_algorithm.hpp"
#include "stl_allocator.hpp"
#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"
#include "stl_uninitialized.hpp"

namespace SelfMadeSTL {
    
    template <typename T, typename Alloc = allocator<T>>
    class vector {
    public:
        // ----- typedef -----

        typedef T           value_type;
        typedef T*          pointer;
        typedef T*          iterator;
        typedef T&          reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        typedef const T*    const_pointer;
        typedef const T*    const_iterator;
        typedef const T&    const_reference;
        typedef simple_alloc<T, Alloc> vector_allocator;

    protected:
        // ----- member variable -----

        // start position of used
        iterator start;
        // end position of used
        iterator finish;
        // end position of all space
        iterator end_of_storage;

    protected:
        // allocator and deallocator, easy for use

        static pointer vector_allocate(size_type n) {
            return vector_allocator::allocate(n);
        }
        static void vector_deallocate(pointer ptr, size_type n) {
            vector_allocator::deallocate(ptr, n);
        }

    protected:
        static void insert_aux(iterator pos, const T& value) {
            // if there are some space left
            if (finish != end_of_storage) {
                // copy the value in finish - 1 to finish
                construct(finish, *(finish - 1));
                ++finish;
                // copy the value in [pos, finish - 1) to [pos + 1, finish)
                copy_backward(pos, finish - 2, finish - 1);
                // place the inserted value
                *pos = value;
            }
            // if there is no space left
            else {
                // allocate new space
                const size_type old_capacity = capacity();
                const size_type new_capacity = old_capacity != 0 ? 2 * old_capacity : 1;
                iterator new_start = vector_allocate(new_capacity);
                iterator new_finish = new_start;
                try {
                    // copy old [start, pos) to new [start, pos)
                    new_finish = uninitialized_copy(start, pos, new_start);
                    // place the inserted value
                    construct(new_finish, value);
                    ++new_finish;
                    // copy old [pos, finish) to new [pos + 1, finish)
                    new_finish = uninitialized_copy(pos, finish, new_finish);
                }
                catch (const std::exception&) {
                    // exception handling
                    destory(new_start, new_finish);
                    vector_deallocate(new_start, new_capacity);
                    throw;
                }
                // destroy and deallocation old space and assignment
                destory(begin(), end());
                vector_deallocate(start, old_capacity);
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + new_capacity;
            }
        }

        static void insert_aux(iterator pos) {
            if (finish != end_of_storage) {
                construct(finish, *(finish - 1));
                ++finish;
                copy_backward(pos, finish - 2, finish - 1);
                *pos = value_type();
            }
            else {
                const size_type old_capacity = capacity();
                const size_type new_capacity = old_capacity != 0 ? 2 * old_capacity : 1;
                iterator new_start = vector_allocate(new_capacity);
                iterator new_finish = new_start;
                try {
                    new_finish = uninitialized_copy(start, pos, new_start);
                    construct(new_finish);
                    ++new_finish;
                    new_finish = uninitialized_copy(pos, finish, new_finish);
                }
                catch (const std::exception&) {
                    destory(new_start, new_finish);
                    vector_deallocate(new_start, new_capacity);
                    throw;
                }
                destory(begin(), end());
                vector_deallocate(start, old_capacity);
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + new_capacity;
            }
        }

    public:
        // ----- basic constructor, destructor -----
        // ----- involving allocation and deallocation -----

        explicit vector()
            : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
        
        vector(size_type n, const T& value) {
            start = vector_allocate(n);
            finish = SelfMadeSTL::uninitialized_fill_n(start, n, value);
            end_of_storage = finish;
        }
        
        explicit vector(const size_type n) {
            start = vector_allocate(n);
            finish = SelfMadeSTL::uninitialized_fill_n(start, n, value_type());
            end_of_storage = finish;
        }

        vector(const vector& other) {
            start = vector_allocate(other.size());
            finish = SelfMadeSTL::uninitialized_copy(other.begin(), other.end(), begin());
            end_of_storage = finish;
        }

        vector(const vector&& other) {
            start = other.start;
            finish = other.finish;
            end_of_storage = other.end_of_storage;
            other.start = nullptr;
            other.finish = nullptr;
            other.end_of_storage = nullptr;
        }

        vector(const iterator first, const iterator last) {
            start = vector_allocate(last - first);
            finish = SelfMadeSTL::uninitialized_copy(first, last, begin());
            end_of_storage = finish;
        }
        
        vector& operator=(const vector& other) {
            if (this == &other) {
                return *this;
            }
            else {
                destory(start, finish);
                vector_deallocate(start, capacity());
                start = vector_allocate(other.size());
                finish = SelfMadeSTL::uninitialized_copy(other.begin(), other.end(), begin());
                end_of_storage = finish;
            }
        }

        ~vector() {
            destory(start, finish);
            vector_deallocate(start, capacity());
            start = nullptr;
            finish = nullptr;
            end_of_storage = nullptr;
        }

        // ----- iterator function -----

        iterator begin() { return start; }
        iterator end() { return finish; }
        const_iterator begin() const { return start; }
        const_iterator end() const { return finish; }
        const_iterator cbegin() const { return start; }
        const_iterator cend() const { return finish; }

        // ----- function that related to container size/capacity -----

        size_type size() const { return (size_type)(end() - begin()); }
        size_type capacity() const { return (size_type)(end_of_storage - begin()); }
        bool empty() const { return begin() == end(); }


        // ----- funtion that access elements -----

        reference front() { return *begin(); }
        reference back() { return *(end() - 1); }
        reference operator[](size_type idx) { return *(begin() + idx); }
        const_reference front() const { return *begin(); }
        const_reference back() const { return *(end() - 1); }
        const_reference operator[](size_type idx) const { return *(begin() + idx); }

        // ----- function that change element in vector -----

        void push_back(const T& value) {
            if (finish != end_of_storage) {
                construct(finish, value);
                ++finish;
            }
            else {
                insert_aux(end(), value);
            }
        }

        void push_back() {
            if (finish != end_of_storage) {
                construct(finish);
                ++finish;
            }
            else {
                insert_aux(end());
            }
        }

        void pop_back() {
            --finish;
            destory(finish);
        }

        iterator insert(iterator pos, const T& value) {
            size_type n = pos - begin();
            // insert at finish
            if (finish != end_of_storage && pos == end()) {
                construct(finish, value);
                ++finish;
            }
            // insert at middle
            else {
                insert_aux(pos, value);
            }
            return begin() + n;
        }

        iterator insert(iterator pos) {
            size_type n = pos - begin();
            // insert at finish
            if (finish != end_of_storage && pos == end()) {
                construct(finish);
                ++finish;
            }
            // insert at middle
            else {
                insert_aux(pos);
            }
            return begin() + n;
        }

        void insert(iterator pos, size_type n, const T& value) {
            if (n != 0) {
                // enough space
                if (end_of_storage - finish >= n) {
                    const size_type after_pos = finish - pos;
                    iterator old_finish = finish;
                    // more tail elements
                    if (after_pos > n) {
                        // copy [finish - n, finish) to [finish, finish + n)
                        uninitialized_copy(finish - n, finish, finish);
                        finish += n;
                        // copy [pos, finish - n) to [pos + n, finish)
                        copy_backward(pos, old_finish - n, old_finish);
                        // fill [pos, pos + n)
                        fill(pos, pos + n, value);
                    }
                    // more inserted value
                    else {
                        // fill [finish, pos + n)
                        uninitialized_fill_n(finish, n - after_pos, value);
                        finish += n - after_pos;
                        // copy [pos, finish) to [pos + n, finish + n)
                        uninitialized_copy(pos, old_finish, finish);
                        finish += after_pos;
                        // fill [pos, finish)
                        fill(pos, old_finish, value);
                    }
                }
                // not enough space
                else {
                    // allocate space
                    const size_type old_size = size();
                    const size_type old_capacity = capacity();
                    const size_type new_capacity = old_size + n;
                    iterator new_start = vector_allocate(new_capacity);
                    iterator new_finish = new_start;
                    try {
                        // copy old [start, pos) to new [start, pos)
                        new_finish = uninitialized_copy(start, pos, new_start);
                        // place n inserted value
                        new_finish = uninitialized_fill_n(new_finish, n, value);
                        // copy old [pos, finish) to new [pos + n, finish + n)
                        new_finish = uninitialized_copy(pos, finish, new_finish);
                    }
                    catch (const std::exception&) {
                        // exception handling
                        destory(new_start, new_finish);
                        vector_deallocate(new_start, new_capacity);
                        throw;
                    }
                    // destroy and deallocation old space and assignment
                    destory(begin(), end());
                    vector_deallocate(start, old_capacity);
                    start = new_start;
                    finish = new_finish;
                    end_of_storage = new_start + new_capacity;
                }
            }
        }

        template <typename InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last) {
            size_type n = distance(first, last);
            if (n != 0) {
                if (end_of_storage - finish >= n) {
                    const size_type after_pos = finish - pos;
                    iterator old_finish = finish;
                    if (after_pos > n) {
                        // copy [finish - n, finish) to [finish, finish + n)
                        uninitialized_copy(finish - n, finish, finish);
                        finish += n;
                        // copy [pos, finish - n) to [pos + n, finish)
                        copy_backward(pos, old_finish - n, old_finish);
                        // copy [first, last) to [pos, pos + n)
                        copy(first, last, pos);
                    }
                    else {
                        // copy [first + after_pos, last) to [finish, pos + n)
                        uninitialized_copy(first + after_pos, last, finish);
                        finish += n - after_pos;
                        // copy [pos, finish) to [pos + n, finish + n)
                        uninitialized_copy(pos, old_finish, finish);
                        finish += after_pos;
                        // copy [first, first + after_pos) to [pos, finish)
                        copy(first, first + after_pos, pos);
                    }
                }
                else {
                    const size_type old_size = size();
                    const size_type old_capacity = capacity();
                    const size_type new_capacity = old_size + n;
                    iterator new_start = vector_allocate(new_capacity);
                    iterator new_finish = new_start;
                    try {
                        new_finish = uninitialized_copy(start, pos, new_start);
                        new_finish = uninitialized_copy(first, last, new_finish);
                        new_finish = uninitialized_copy(pos, finish, new_finish);
                    }
                    catch (const std::exception&) {
                        destory(new_start, new_finish);
                        vector_deallocate(new_start, new_capacity);
                        throw;
                    }
                    destory(begin(), end());
                    vector_deallocate(start, old_capacity);
                    start = new_start;
                    finish = new_finish;
                    end_of_storage = new_start + new_capacity;
                }
            }
        }

        iterator erase(iterator pos) {
            if (pos + 1 != end()) {
                copy(pos + 1, finish, pos);
            }
            pop_back();
            return pos;
        }
        
        iterator erase(iterator first, iterator last) {
            iterator new_finish = copy(last, finish, first);
            destory(new_finish, finish);
            finish = new_finish;
            return first;
        }

        void clear() {
            erase(begin(), end());
        }

        void resize(size_type new_size, const T& value = value_type()) {
            if (new_size < size()) {
                erase(begin() + new_size, end());
            }
            else {
                insert(end(), new_size - size(), value);
            }
        }

        void reserve(size_type n) {
            if (capacity() < n) {
                const size_type old_capacity = capacity();
                iterator new_start = vector_allocate(n);
                iterator new_finish = uninitialized_copy(begin(), end(), new_start);
                destory(start, finish);
                vector_deallocate(start, old_capacity);
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + n;
            }
        }

        void shrink_to_fit() {
            if (size() != capacity()) {
                iterator new_start = vector_allocate(size());
                iterator new_finish = uninitialized_copy(begin(), end(), new_start);
                destory(start, finish);
                vector_deallocate(start, capacity());
                start = new_start;
                finish = new_finish;
                end_of_storage = new_finish;
            }
        }

        void swap(vector& other) {
            std::swap(start, other.start);
            std::swap(finish, other.finish);
            std::swap(end_of_storage, other.end_of_storage);
        }

        // ----- operators override -----

        bool operator==(const vector& other) {
            return size() == other.size() && equal(begin(), end(), other.begin());
        }

        bool operator!=(const vector& other) {
            return !operator==(other);
        }

        bool operator<(const list& other) {
            return lexicographical_compare(begin(), end(), other.begin(), other.end());
        }

    };
}

#endif // !_VECTOR_H_
