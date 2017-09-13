#include <iostream>      //For I/O Functions
#include <windows.h>   //For Beep & Sleep functions
#include <stdlib.h>  //For System Pause
using namespace std;

int main()
{
	Beep(330, 100); Sleep(100);
	Beep(330, 100); Sleep(300);

	system("pause");
	return 0;
}   //Press any key to exit
