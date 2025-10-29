#include <iostream>
#include <cmath>

double calculate_sin(double angle);
double calculate_tan(double angle);

int main(){
	double angle;
	std::cout << "Введите угол" << std::endl;
	std::cin >> angle;
	
	if  (cos(2 * angle) != 1){
		std::cout << "F(x1) = " << calculate_sin(angle)<<std::endl;
	}
	else {
		std::cout << "Неверный ввод" << std::endl;
	}
	
	if  (tan(angle) != 1){
		std::cout << "F(x2) = " << calculate_tan(angle)<<std::endl;
	}
	else{
		std::cout << "Неверный ввод" << std::endl;
		system ("Пауза");
	}
	return 0;
}

double calculate_sin(double angle) {
    return (1 + sin(2 * angle)) / (1 - cos(2 * angle));
}

double calculate_tan(double angle) {
    double tan_val = tan(angle);
    return (1 + tan_val * tan_val) / (1 - tan_val * tan_val);
}
