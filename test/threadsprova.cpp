#include <thread>
#include <iostream>

using namespace std;

int main() {
	thread([](){cout<<"ciao1\n";}).join();
	thread([](){cout<<"ciao2\n";}).join();
}