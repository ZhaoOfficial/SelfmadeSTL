#ifndef _HEAP_H_
#define _HEAP_H_

#include "stl_iterator.hpp"

namespace selfmadeSTL {

    // top index is 0 not 1

    // push
    template <typename RandomAccessIterator, typename Distance, typename T>
    void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
        Distance parent = (holeIndex - 1) / 2;
        while(holeIndex > topIndex && *(first + parent) < value) {
            // put the smaller value at the child hole
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        // put the larger value at the correct hole
        *(first + holeIndex) = value;
    }

    template <typename RandomAccessIterator, typename Distance, typename T>
    inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance, T*) {
        __push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
    }

    // push the `last` element to the proper position
    template <typename RandomAccessIterator>
    inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
        __push_heap_aux(first, last, difference_type(first), value_type(first));
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value, Compare comp) {
        Distance parent = (holeIndex - 1) / 2;
        while(holeIndex > topIndex && comp(*(first + parent), value)) {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*, Compare comp) {
        __push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)), comp);
    }

    template <typename RandomAccessIterator, typename Compare>
    inline void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        __push_heap_aux(first, last, difference_type(first), value_type(first), comp);
    }

    // pop
    template <typename RandomAccessIterator, typename Distance, typename T>
    void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
        // the popped element
        Distance topIndex = holeIndex;
        Distance secondChild = 2 * holeIndex + 2;
        while (secondChild < len) {
            if (*(first + secondChild) < *(first + (secondChild - 1))) {
                // become first child
                secondChild--;
            }
            // swap
            *(first + holeIndex) = *(first + secondChild);
            holeIndex = secondChild;
            secondChild = 2 * secondChild + 2;
        }
        // if reach the end
        if (secondChild == len) {
            *(first + holeIndex) = *(first + (secondChild - 1));
            holeIndex = secondChild - 1;
        }
        __push_heap(first, holeIndex, topIndex, value);
    }

    template <typename RandomAccessIterator, typename Distance, typename T>
    inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, Distance*, T value) {
        *result = *first;
        __adjust_heap(first, Distance(0), Distance(last - first), value);
    }

    template <typename RandomAccessIterator, typename T>
    inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
        __pop_heap(first, last - 1, last - 1, difference_type(first), T(*(last - 1)));
    }

    template <typename RandomAccessIterator>
    inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
        __pop_heap_aux(first, last, value_type(first));
    }

template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value, Compare comp) {
        Distance topIndex = holeIndex;
        Distance secondChild = 2 * holeIndex + 2;
        while (secondChild < len) {
            if (comp(*(first + secondChild), *(first + (secondChild - 1)))) {
                secondChild--;
            }
            *(first + holeIndex) = *(first + secondChild);
            holeIndex = secondChild;
            secondChild = 2 * secondChild + 2;
        }
        if (secondChild == len) {
            *(first + holeIndex) = *(first + (secondChild - 1));
            holeIndex = secondChild - 1;
        }
        __push_heap(first, holeIndex, topIndex, value, comp);
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, Distance*, T value, Compare comp) {
        *result = *first;
        __adjust_heap(first, Distance(0), Distance(last - first), value, comp);
    }

    template <typename RandomAccessIterator, typename T, typename Compare>
    inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*, Compare comp) {
        __pop_heap(first, last - 1, last - 1, difference_type(first), T(*(last - 1)), comp);
    }

    template <typename RandomAccessIterator, typename Compare>
    inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        __pop_heap_aux(first, last, value_type(first), comp);
    }

    template <typename RandomAccessIterator, typename Distance, typename T>
    void __make_heap(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*) {
        if ((last - first) < 2) {
            return;
        }
        Distance len = last - first;
        Distance parent = (len - 2) / 2;

        // Floyd Algorithm
        while (true) {
            __adjust_heap(first, parent, len, *(first + parent));
            if (parent == 0) {
                return;
            }
            --parent;
        }
    }

    template <typename RandomAccessIterator>
    inline void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
        __make_heap(first, last, value_type(first), difference_type(first));
    }
    
    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void __make_heap(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*, Compare comp) {
        if ((last - first) < 2) {
            return;
        }
        Distance len = last - first;
        Distance parent = (len - 2) / 2;

        while (true) {
            __adjust_heap(first, parent, len, *(first + parent), comp);
            if (parent == 0) {
                return;
            }
            --parent;
        }
    }

    template <typename RandomAccessIterator, typename Compare>
    inline void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        __make_heap(first, last, difference_type(first), value_type(first), comp);
    }
    
    template <typename RandomAccessIterator>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
        while(last - first > 1) {
            pop_heap(first, last - 1);
        }
    }

    template <typename RandomAccessIterator, typename Compare>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        while(last - first > 1) {
            pop_heap(first, last - 1, comp);
        }
    }

}

#endif //! _HEAP_H_