// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"

int main(int argc, char* argv[])
{
	//Written by Steven Godshall, Ben Zug, Prottay Protivash
	//Note: The CPUs the threads end on don't matter.  Just the finishing time.
	//If there are any issues, please bring to our attention on canvas or elsewhere.

	cout << "FCFS Policy, 2 CPUs\n";
	MyScheduler myScheduler(FCFS, 2);

	myScheduler.CreateThread(1, 5, 1, 0);
	myScheduler.CreateThread(3, 13, 2, 1);
	myScheduler.CreateThread(0, 32, 2, 2);
	myScheduler.CreateThread(2, 10, 2, 3);
	myScheduler.Go();
	/*Our output

	Thread ID : 0 Finishing Time : 6 CPU No. : 1
	Thread ID : 3 Finishing Time : 16 CPU No. : 1
	Thread ID : 1 Finishing Time : 29 CPU No. : 1
	Thread ID : 2 Finishing Time : 32 CPU No. : 0
	*/
	cout << "STRFwoP Policy, 3 CPUs\n";
	MyScheduler ms2 = MyScheduler(Policy::STRFwoP, 3);
	ms2.CreateThread(0, 12, 0, 0);
	ms2.CreateThread(5, 2, 2, 1);
	ms2.CreateThread(3, 7, 1, 2);
	ms2.CreateThread(9, 1, 10, 3);
	ms2.CreateThread(1, 4, 3, 4);
	ms2.CreateThread(5, 2, 3, 5);
	ms2.CreateThread(1, 4, 3, 6);

	ms2.Go();

	/*
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 6 Finishing Time : 5 CPU No. : 2
	Thread ID : 1 Finishing Time : 7 CPU No. : 1
	Thread ID : 5 Finishing Time : 7 CPU No. : 2
	Thread ID : 3 Finishing Time : 10 CPU No. : 2
	Thread ID : 0 Finishing Time : 12 CPU No. : 0
	Thread ID : 2 Finishing Time : 14 CPU No. : 1
	All the Threads have been executed !! .. Exiting Scheduler ..
	*/
	cout << "STRFwoP Policy, 2 CPUs\n";
	MyScheduler myScheduler2(STRFwoP, 2);
	myScheduler2.CreateThread(0, 5, 1, 0);
	myScheduler2.CreateThread(5, 13, 2, 1);
	myScheduler2.CreateThread(6, 32, 2, 2);
	myScheduler2.CreateThread(2, 10, 2, 3);
	myScheduler2.Go();

	/*Our output
	Thread ID : 0 Finishing Time : 5 CPU No. : 0
	Thread ID : 3 Finishing Time : 12 CPU No. : 1
	Thread ID : 1 Finishing Time : 18 CPU No. : 0
	Thread ID : 2 Finishing Time : 44 CPU No. : 1
	*/
	cout << "STRFwP Policy, 3 CPUs\n";
	MyScheduler myScheduler3(STRFwP, 3);
	myScheduler3.CreateThread(0, 20, 1, 0);
	myScheduler3.CreateThread(0, 20, 2, 1);
	myScheduler3.CreateThread(0, 20, 2, 2);
	myScheduler3.CreateThread(1, 5, 2, 3);
	myScheduler3.CreateThread(3, 2, 2, 4);
	myScheduler3.CreateThread(3, 4, 2, 5);
	myScheduler3.CreateThread(3, 5, 2, 6);
	myScheduler3.Go();
	/*Our output
	Thread ID : 4 Finishing Time : 5 CPU No. : 0
	Thread ID : 3 Finishing Time : 6 CPU No. : 1
	Thread ID : 5 Finishing Time : 7 CPU No. : 2
	Thread ID : 6 Finishing Time : 10 CPU No. : 0
	Thread ID : 1 Finishing Time : 23 CPU No. : 1
	Thread ID : 2 Finishing Time : 24 CPU No. : 2
	Thread ID : 0 Finishing Time : 29 CPU No. : 0
	*/
	cout << "STRFwP Policy, 3 CPUs\n";
	MyScheduler ms3 = MyScheduler(Policy::STRFwP, 3);
	ms3.CreateThread(0, 12, 0, 0);
	ms3.CreateThread(5, 2, 2, 1);
	ms3.CreateThread(3, 7, 1, 2);
	ms3.CreateThread(9, 1, 10, 3);
	ms3.CreateThread(1, 4, 3, 4);
	ms3.CreateThread(5, 2, 3, 5);
	ms3.CreateThread(1, 4, 3, 6);

	ms3.Go();

	/*
	Thread ID : 6 Finishing Time : 5 CPU No. : 0
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 5 Finishing Time : 7 CPU No. : 0
	Thread ID : 1 Finishing Time : 7 CPU No. : 1
	Thread ID : 2 Finishing Time : 10 CPU No. : 0
	Thread ID : 3 Finishing Time : 10 CPU No. : 1
	Thread ID : 0 Finishing Time : 16 CPU No. : 0
	All the Threads have been executed !! .. Exiting Scheduler ..
	*/

	cout << "PBS Policy, 3 CPUs\n";
	MyScheduler myScheduler4(PBS, 3);
	myScheduler4.CreateThread(1, 202, 20, 0);
	myScheduler4.CreateThread(2, 201, 20, 1);
	myScheduler4.CreateThread(0, 200, 20, 2);
	myScheduler4.CreateThread(3, 40, 5, 3);
	myScheduler4.CreateThread(3, 40, 3, 4);
	myScheduler4.Go();
	/*our output
	Thread ID : 4 Finishing Time : 43 CPU No. : 0
	Thread ID : 3 Finishing Time : 43 CPU No. : 1
	Thread ID : 1 Finishing Time : 203 CPU No. : 2
	Thread ID : 2 Finishing Time : 240 CPU No. : 1
	Thread ID : 0 Finishing Time : 243 CPU No. : 0
	*/

	return 0;
}