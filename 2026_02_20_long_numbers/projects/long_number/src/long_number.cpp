#include "long_number.hpp"

using biv::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
    sign = 1;
    numbers = new int[1]{0};
}

LongNumber::LongNumber(int length, int sign) {
	// TODO
}

LongNumber::LongNumber(const char* const str) {
	sign = (str[0] == '-') ? -1 : 1;
	length = get_length(str);
	numbers = new int[length];
	
	int str_index = 0;
	while (str[str_index] != '\0') str_index++;
	
	for (int i = 0; i < length; i++){
		numbers[i] = str[--str_index] - '0';
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	// TODO
}

LongNumber::LongNumber(LongNumber&& x) {
	// TODO
}

LongNumber::~LongNumber() {
	delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
	// TODO
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	// TODO
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	// TODO
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (sign != x.sign || length !=x.length) return false;
	
	for (int i = 0; i < length; i++){
		if (numbers[i] != x.numbers[i]) return false;
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	// TODO
}

bool LongNumber::operator > (const LongNumber& x) const {
	// TODO
}

bool LongNumber::operator < (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	// TODO
}

bool LongNumber::is_negative() const noexcept {
	// TODO
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int len = 0;
	int i = (str[0] == '-') ? : 0;
	while (str[i]!= '\0'){
		len++;
		i++;
	}
	return len;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		// TODO
	}
}
