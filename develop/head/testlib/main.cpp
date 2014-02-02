#include <stdlib.h>
#include <stdio.h>
using namespace std;

extern "C" {
	void dosomething() {
		printf("Hello World, I am doing something!\n");
	}
}
