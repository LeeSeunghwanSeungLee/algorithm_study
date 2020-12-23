#include <iostream>
#include <vector>

using namespace std;


int main(void) {
	int num;
	cin >> num;
	int i = 2;
	while(num > 1) {
		if (num % i == 0) {
			num /= i;
			cout << i << '\n';
		}
		else i++;
	}

	return 0;
}