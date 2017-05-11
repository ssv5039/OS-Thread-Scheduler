/**
Name of File: myscheduler.cpp
Description: A simulation of a CPU thread scheduler using functions defined in myscheduler.h
Team Participants: Zain Hamilton, Shawn Philip, and Shawn Varughese

**/
#include "myscheduler.h"
#include <algorithm>
#include <vector>

// Data Structure
vector<ThreadDescriptorBlock> store;

// Globals
int first_time = 0;
int first_time1 = 0;
int first_time2 = 0;
int first_time3 = 0;

// Functions

/**
Name of Function: CreateThread

This function creates a thread and stores it in the student defined thread buffer.
It keeps track of the thread's arriving time, remaining time, priority, and thread ID.

**/
void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	ThreadDescriptorBlock thread;

	thread.priority = priority;
	thread.tid = tid;
	thread.arriving_time = arriving_time;
	thread.remaining_time = remaining_time;

	store.push_back(thread);
}

/**
Name of Function: Compare_ArrivalTime

This function takes two threads and compares their arriving time. The thread with the earliest arrival time
will be scheduled first. In the case of two threads arriving at the same time,
the one with the shortest remaining time will go first.

**/
bool MyScheduler::Compare_ArrivalTime(ThreadDescriptorBlock &thread1, ThreadDescriptorBlock &thread2)
{
	bool results = thread1.arriving_time < thread2.arriving_time;

	return (results);
}

/**
Name of Function: Compare_RemainingTime

This function takes two threads and compares their remaining time. The thread with the smallest remaining time
will be scheduled first. The TAs mentioned that threads for SRTF will not have the same remaining time.

**/
bool MyScheduler::Compare_RemainingTime(ThreadDescriptorBlock &thread1, ThreadDescriptorBlock &thread2)
{
	bool results = thread1.remaining_time < thread2.remaining_time;
	if (thread1.remaining_time < thread2.remaining_time) {

	}
	return (results);
}

/**
Name of Function: Compare_pri

This function takes two threads and compares their priority.
The thread with the lower priority value should be scheduled first.

**/
bool MyScheduler::Compare_pri(ThreadDescriptorBlock &thread1, ThreadDescriptorBlock &thread2)
{
	bool results = thread1.priority < thread2.priority;

	return (results);
}

/**
Name of Function: Dispatch

This function checks if there are any finished threads (remaining_time == 0) in the student defined 
thread buffer and removes them. If the thread buffer is empty, then the simulation should end. It
decides which threads are to be assigned to and processed by CPUs for the next clock cycle, 
depending on the different policies in each case. 

**/
bool MyScheduler::Dispatch()
{
	switch (policy)
	{
	case FCFS:		//First Come First Serve

		// Remove any threads that finished running
		for (unsigned int i = 0; i < store.size(); i++) {
			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
				break;
			}
		}

		// If the thread buffer is empty, end the simulation
		// Check to see if all the CPUs are empty
		if (store.size() == 0 && timer > 1) {
			for (unsigned int i = 0; i < num_cpu; i++) {
				CPUs[i] = NULL;
			}
			first_time = 0;
			return 0;
		}

		// First use of FCFS, sort threads based on arriving time and mark our visit
		if (first_time == 0) {
			sort(store.begin(), store.end(), Compare_ArrivalTime);
			first_time = 1;
		}

		// Go through the threads and CPUs to see which are empty or if we're revisiting CPUs
		for (unsigned int j = 0; j < store.size(); j++)
		{
			
			while (store[j].priority == 99) {
				CPUs[store[j].arriving_time] = &(store[j]);
				break;
			}

			for (unsigned int i = 0; i < num_cpu; i++) {
				while (store[j].priority != 99 && CPUs[i] == NULL &&  store[j].arriving_time <= timer) {
					CPUs[i] = &(store[j]);
					store[j].arriving_time = i;
					store[j].priority = 99;
					break;

					// If the thread is done, then remove it
					if (store[j].remaining_time == 0) {
						store.erase(store.begin() + j);
						break;
					}
				}
			}

			// If some threads have not been removed yet, then remove them now
			for (unsigned int i = 0; i < store.size(); i++) {
				if (store[i].remaining_time == 0) {
					store.erase(store.begin() + i);
					break;
				}
			}
		}

		// If the thread buffer is empty, end the simulation
		// Check to see if all the CPUs are empty
		if (store.size() == 0 && timer > 1) {
			for (unsigned int i = 0; i < num_cpu; i++) {
				CPUs[i] = NULL;
			}
			return 0;
		}

		// Check to see if some threads are still running
		for (unsigned int i = 0; i < store.size(); i++) {
			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
				break;
			}
		}
		break;

	case STRFwoP:	//Shortest Time Remaining First, without preemption

		// If some threads have been recently running, dequeue them when done
		for (unsigned int i = 0; i < store.size(); i++) {
			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
				break;
			}
		}

		// If the thread buffer is empty, end the simulation
		// Check to see if all the CPUs are empty
		if (store.size() == 0 && timer > 1) {
			for (unsigned int i = 0; i < num_cpu; i++) {
				CPUs[i] = NULL;
			}
			first_time1 = 0;
			return 0;
		}

		// First use of SRTFwoP, sort threads based on remaining time and mark our visit
		if (first_time1 == 0) {
			sort(store.begin(), store.end(), Compare_RemainingTime);
			for (unsigned int j = 0; j < store.size(); j++)
			{
				store[j].priority = 99;
			}
			first_time1 = 1;
		}

		// Go through the threads and CPUs to see which are empty or if we're revisiting CPUs
		for (unsigned int j = 0; j < store.size(); j++)
		{
			while (store[j].priority != 99) {
				CPUs[store[j].arriving_time] = &(store[j]);
				break;
			}

			for (unsigned int i = 0; i < num_cpu; i++) {
				while (store[j].priority == 99 && CPUs[i] == NULL &&  store[j].arriving_time <= timer) {
					CPUs[i] = &(store[j]);
					store[j].arriving_time = i;
					store[j].priority = 84848;
					break;

					// If the thread is done, then remove it
					if (store[j].remaining_time == 0) {
						store.erase(store.begin() + j);
						break;
					}
				}
			}

			// Check to see if some threads are still running
			for (unsigned int i = 0; i < store.size(); i++) {
				if (store[i].remaining_time == 0) {
					store.erase(store.begin() + i);
					break;
				}
			}
		}

		// If the thread buffer is empty, end the simulation
		// Check to see if all the CPUs are empty
		if (store.size() == 0 && timer > 1) {
			for (unsigned int i = 0; i < num_cpu; i++) {
				CPUs[i] = NULL;
			}
			return 0;
		}

		// If there's any threads that are still running, remove them when done
		for (unsigned int i = 0; i < store.size(); i++) {
			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
				break;
			}

		}
		break;


	case STRFwP:	//Shortest Time Remaining First, with preemption

		// If some threads have been recently running, dequeue them
		for (unsigned int i = 0; i < store.size(); i++) {
			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
				break;
			}
		}

		// If the thread buffer is empty, end the simulation
		// Check to see if all the CPUs are empty
		if (store.size() == 0 && timer > 1) {
			for (unsigned int i = 0; i < num_cpu; i++) {
				CPUs[i] = NULL;
			}
			first_time2 = 0;
			return 0;
		}

		// First use of SRTFwP, sort threads based on remaining time and mark our visit
		if (first_time2 == 0) {
			sort(store.begin(), store.end(), Compare_RemainingTime);
			for (unsigned int j = 0; j < store.size(); j++)
			{
				store[j].priority = 99;
			}
			first_time2 = 1;
		}

		// Go through all the CPUs and threads
		for (unsigned int i = 0; i < num_cpu; i++) {
			for (unsigned int j = 0; j < store.size(); j++) {
				if (store[j].priority == 99 && store[j].arriving_time <= timer) {
					CPUs[i] = &(store[j]);
					store[j].priority = 0;
					break;
				}

				// Remove threads that finish running
				if (store[j].remaining_time == 0) {
					store.erase(store.begin() + j);
				}
				CPUs[i] = 0;
			}
		}

		// Go through the store and check if any threads are still running
		for (unsigned int i = 0; i < store.size(); i++) {

			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
			}
			store[i].priority = 99;
		}

		break;

	case PBS:		//Priority Based Scheduling, with preemption

		// If some threads have been recently running, dequeue them
		for (unsigned int i = 0; i < store.size(); i++) {
			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
				break;
			}
		}

		// If the thread buffer is empty, end the simulation
		// Check to see if all the CPUs are empty
		if (store.size() == 0 && timer > 1) {

			for (unsigned int i = 0; i < num_cpu; i++) {
				CPUs[i] = NULL;
			}
			first_time3 = 0;
			return 0;
		}

		if (first_time3 == 0) {
			sort(store.begin(), store.end(), Compare_pri);
			for (unsigned int j = 0; j < store.size(); j++)
			{
				store[j].priority = 99;
			}
			first_time3 = 1;
		}

		// First use of PBS, sort threads based on high priority and mark our visit
		// Lower priority value = higher priority
		for (unsigned int i = 0; i < num_cpu; i++) {
			for (unsigned int j = 0; j < store.size(); j++) {
				if (store[j].priority == 99 && store[j].arriving_time <= timer) {
					CPUs[i] = &(store[j]);
					store[j].priority = 0;
					break;
				}

				// If the thread is done, then remove it
				if (store[j].remaining_time == 0) {
					store.erase(store.begin() + j);
				}
				CPUs[i] = 0;

			}
		}

		// Check to see if some threads are still running
		for (unsigned int i = 0; i < store.size(); i++) {

			if (store[i].remaining_time == 0) {
				store.erase(store.begin() + i);
			}
			store[i].priority = 99;
		}

		break;

	default:
		cout << "Invalid policy!";
		throw 0;
	}

	return true;
}