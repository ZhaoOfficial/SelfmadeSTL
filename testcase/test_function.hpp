#ifndef _TEST_FUNCTION_H_
#define _TEST_FUNCTION_H_

#include <iostream>
#include <complex>
#include <cmath>
#include <random>

#include "../stl_algorithm.hpp"

class Npod {
public:
	Npod() {
		ptr = new std::complex<double>();
	}
	Npod(const Npod& other) {
		ptr = new std::complex<double>();
		ptr->real(other.ptr->real());
		ptr->imag(other.ptr->imag());
	}
	Npod(const Npod&& other) noexcept {
		ptr = other.ptr;
	}
	Npod(const double& real, const double& imag) {
		ptr = new std::complex<double>();
		ptr->real(real);
		ptr->imag(imag);
	}
	Npod& operator=(const Npod& other) {
		if (this != &other) {
			ptr->real(other.ptr->real());
			ptr->imag(other.ptr->imag());
		}
		return *this;
	}
	~Npod() {
		delete ptr;
	}
	bool operator==(const Npod& other) const {
		return this->ptr->real() == other.ptr->real() && this->ptr->imag() == other.ptr->imag();
	}
	bool operator!=(const Npod& other) const {
		return this->ptr->real() != other.ptr->real() || this->ptr->imag() != other.ptr->imag();
	}
	bool operator<(const Npod& other) const {
		return this->ptr->real() * this->ptr->real() + this->ptr->imag() * this->ptr->imag() <
		other.ptr->real() * other.ptr->real() + other.ptr->imag() * other.ptr->imag();
	}
	bool operator>(const Npod& other) const {
		return this->ptr->real() * this->ptr->real() + this->ptr->imag() * this->ptr->imag() >
		other.ptr->real() * other.ptr->real() + other.ptr->imag() * other.ptr->imag();
	}

	void print() const {
		std::cout << '[' << this->ptr->real() << " + " << this->ptr->imag() << ']';
	}

	void print_1arg(const char* str) const {
		std::cout << '[' << this->ptr->real() << str << this->ptr->imag() << ']';
	}

	std::complex<double>* ptr;
};


namespace selfmadeSTL {

	template <typename Container>
	void print_container(Container& c, const std::string& name) {
		std::cout << "Container " << name << " :";
		for (auto& var : c) {
			std::cout << var << ' ';
		}
		std::cout << std::endl;
	}

	template<class Container1, class Container2>
	bool container_equal(Container1& c1, Container2& c2) {
		auto first1 = c1.begin();
		auto last1 = c1.end();
		auto first2 = c2.begin();
		auto last2 = c2.end();
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (*first1 != *first2)
				return false;
		}
		return first1 == last1 && first2 == last2;
	}

	template <typename T>
	struct display {
		void operator()(const T& x) const {
			std::cout << x << ' ';
		}
	};
	
	template <typename T>
	void print(const T& x) {
		std::cout << '[' << x << ']';
	}

	struct even {
		bool operator()(int x) const {
			return x % 2 ? false : true;
		}
	};

	class add2 {
	public:
		int operator()() const {
			return a += 2;
		}
	private:
		static int a;
	};
	int add2::a = 0;
}

#endif // !_TEST_FUNCTION_H_