#ifndef _PAIR_H_
#define _PAIR_H_

namespace selfmadeSTL {

	template <typename T1, typename T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(T1()), second(T2()) {}
		pair(const T1& t1, const T2& t2) : first(t1), second(t2) {}
		~pair() {}
	};

}

#endif // !_PAIR_H_