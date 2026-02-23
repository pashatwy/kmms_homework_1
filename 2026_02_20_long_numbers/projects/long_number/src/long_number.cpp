#include "long_number.hpp"

using biv::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
    sign = 1;
    numbers = new int[1]{0};
}

LongNumber::LongNumber(int length, int sign) {
    this->length = length;
    this->sign = sign;
    
    this->numbers = new int[length]{0};
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
	this -> length = x.length;
	this -> sign = x.sign;
	
	this -> numbers = new int[x.length];
	
	for (int i = 0; i < x.length; i++){
		this -> numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	this->length = x.length;
    this->sign = x.sign;
    
    this->numbers = x.numbers;
    
    x.numbers = nullptr;
    x.length = 0;
}

LongNumber::~LongNumber() {
	length = 0;
	delete [] numbers;
	numbers = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
	delete[] numbers;
	
	sign = (str[0] == '-') ? -1 : 1;
	length = get_length(str);
	numbers = new int[length];
	
	int str_index = 0;
	while (str[str_index] != '\0') str_index++;
	
	for (int i = 0; i < length; i++){
		numbers[i] = str[--str_index] - '0';
	}
		
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) return *this;
	delete[] numbers;
	
	length = x.length;
	sign = x.sign;
	
	numbers = new int[x.length];
	for (int i = 0; i < x.length; i++){
		numbers[i] = x.numbers[i];
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this == &x) return *this;
	delete[] numbers;
	
	numbers = x.numbers;
	sign = x.sign;
	length = x.length;
	
	x.numbers = nullptr;
	x.length = 0;
	
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (sign != x.sign || length !=x.length) return false;
	
	for (int i = 0; i < length; i++){
		if (numbers[i] != x.numbers[i]) return false;
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const { 
	return !(*this == x); 
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign != x.sign) return sign > x.sign;
	else if (length != x.length){
		if (sign == 1) return length > x.length;
		else return length < x.length;
	
	}else{
		for (int i = length - 1; i >= 0 ; i--){
			if (numbers[i] != x.numbers[i]){
				if (sign == 1) return numbers[i] > x.numbers[i];
				else return numbers[i] < x.numbers[i];
			}
		}
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return x > *this;
}

LongNumber LongNumber::operator + (const LongNumber& x) const { 
	const int* longer_numbers = nullptr;
	if (sign == x.sign){
		int max_len = std::max(length, x.length);
		biv::LongNumber result(max_len + 1, sign);
		for (int i = 0; i < std::min(length, x.length); i++){
			int char_sum = numbers[i] + x.numbers[i] + result.numbers[i];
			result.numbers[i] = char_sum % 10;
			result.numbers[i+1] = char_sum / 10;
		}
		
		if (length != x.length){
			if (length > x.length){
				longer_numbers = numbers; 
			}else{
				longer_numbers = x.numbers; 
			}
			for (int i = std::min(length, x.length); i < std::max(length, x.length); i++){
				int char_sum = result.numbers[i] + longer_numbers[i];
				result.numbers[i] = char_sum % 10;
				result.numbers[i+1] = int(char_sum / 10);
			}
		}
		while (result.length > 1 && result.numbers[result.length - 1] == 0) {
			result.length--;
		}
		return result;
	}else{
		if(sign > x.sign){
			biv::LongNumber positive_x = x;
			positive_x.sign = 1;
			return *this - positive_x;
		}
		else{
			biv::LongNumber positive_this = *this;
			positive_this.sign = 1;
			return x - positive_this;
		}
	}
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (sign == x.sign) {
        int max_len = std::max(length, x.length);
        biv::LongNumber result(max_len, sign);
        int borrow = 0;

        if (sign == 1) {
            LongNumber a_abs = *this; a_abs.sign = 1;
            LongNumber b_abs = x; b_abs.sign = 1;

            if (a_abs < b_abs) { 
                result.sign = -1;
                for (int i = 0; i < max_len; i++) {
                    int val1 = (i < x.length) ? x.numbers[i] : 0;
                    int val2 = (i < length) ? numbers[i] : 0;
                    int sub = val1 - val2 - borrow;
                    if (sub < 0) { sub += 10; borrow = 1; }
                    else borrow = 0;
                    result.numbers[i] = sub;
                }
            } else {
                for (int i = 0; i < max_len; i++) {
                    int val1 = numbers[i];
                    int val2 = (i < x.length) ? x.numbers[i] : 0;
                    int sub = val1 - val2 - borrow;
                    if (sub < 0) { sub += 10; borrow = 1; }
                    else borrow = 0;
                    result.numbers[i] = sub;
                }
            }
        } else {
            LongNumber a_abs = *this; a_abs.sign = 1;
            LongNumber b_abs = x; b_abs.sign = 1;

            if (a_abs > b_abs) {
                result.sign = -1;
                for (int i = 0; i < max_len; i++) {
                    int val1 = numbers[i];
                    int val2 = (i < x.length) ? x.numbers[i] : 0;
                    int sub = val1 - val2 - borrow;
                    if (sub < 0) { sub += 10; borrow = 1; }
                    else borrow = 0;
                    result.numbers[i] = sub;
                }
            } else {
                result.sign = 1;
                for (int i = 0; i < max_len; i++) {
                    int val1 = (i < x.length) ? x.numbers[i] : 0;
                    int val2 = (i < length) ? numbers[i] : 0;
                    int sub = val1 - val2 - borrow;
                    if (sub < 0) { sub += 10; borrow = 1; }
                    else borrow = 0;
                    result.numbers[i] = sub;
                }
            }
        }
        
        while (result.length > 1 && result.numbers[result.length - 1] == 0) {
            result.length--;
        }
        return result;
    } else {
        biv::LongNumber copy_x = x;
        copy_x.sign = sign;
        return *this + copy_x;
    }
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	LongNumber result(length + x.length, sign * x.sign);
	for (int i = 0; i < x.length; i++) {
		for (int j = 0; j < length; j++) {
			result.numbers[j + i] += x.numbers[i] * numbers[j];
			if (result.numbers[i + j] > 9){
				int q = result.numbers[i + j] / 10;
				result.numbers[i + j + 1] += q;
				result.numbers[i + j] -= q * 10;
			}
		}
	}
	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}
	return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    biv::LongNumber chastnoe(length, ((sign == x.sign) ? 1 : -1));
    
    biv::LongNumber div_copy = *this; div_copy.sign = 1;
    biv::LongNumber x_copy = x; x_copy.sign = 1;

    if (div_copy < x_copy) {
        return biv::LongNumber("0");
    }

    biv::LongNumber first("0"); 

    for (int i = length - 1; i >= 0; i--) {
        first = first * biv::LongNumber("10");
        first.numbers[0] = numbers[i]; 

        int j = 0;
        for (int k = 1; k <= 9; k++) {
            biv::LongNumber j_long(std::to_string(k).c_str());
            if (!(x_copy * j_long > first)) {
                j = k;
            } else {
                break;
            }
        }
		chastnoe.numbers[i] = j;

        biv::LongNumber j_long(std::to_string(j).c_str());
        biv::LongNumber multiplication = x_copy * j_long;
        first = first - multiplication;
    }

    while (chastnoe.length > 1 && chastnoe.numbers[chastnoe.length - 1] == 0) {
        chastnoe.length--;
    }
    if (chastnoe.length == 1 && chastnoe.numbers[0] == 0) chastnoe.sign = 1;

    return chastnoe;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	return *this - (*this / x) * x;
}

bool LongNumber::is_negative() const noexcept {
	return sign == -1;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int len = 0;
	int i = (str[0] == '-') ? 1 : 0;
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
		if (x.sign == -1){
			os << "-";
		}
		for (int i = x.length - 1; i >= 0; i--){
			os << x.numbers[i];
		}
		return os;
	}
}