/*
 * \file schedulers.c
 * \author Jordan Zech/Nathan Eloe
 * \brief runs the simulations of different CPU scheduler policies
 * Modified by: Jordan Zech
 */


#include "schedulers.h"

int fcfs(proc_t * procs, const int numprocs, const int ts)
{
	int smallestIndex = -1;
	for (int i=0; i<numprocs; i++){
		if (running(&procs[i], ts) && (smallestIndex == -1 || 
procs[i].m_arrive < procs[smallestIndex].m_arrive))
			smallestIndex = i;
	}
	return smallestIndex;
}

int sjf(proc_t * procs, const int numprocs, const int ts)
{
	int smallestIndex = -1;
	for (int i=0; i<numprocs; i++){
                if (running(&procs[i], ts) && procs[i].m_timeburst != 0) {
                         return i;
                }
        }

	for (int i=0; i<numprocs; i++){
		if (running(&procs[i], ts) && (smallestIndex == -1 || 
		procs[i].m_burst < procs[smallestIndex].m_burst)){
			smallestIndex = i;
		}
	}
	return smallestIndex;

}
int srt(proc_t * procs, const int numprocs, const int ts)
{
    	int smallestIndex = -1;
	for (int i =0; i<numprocs; i++){
		if(running(&procs[i], ts) && (smallestIndex == -1 || 
		time_remaining(&procs[i]) < time_remaining(&procs[smallestIndex]))){
		//(procs[i].m_timeburst - procs[i].m_burst) < 
		//(procs[smallestIndex].m_timeburst - procs[smallestIndex].m_burst))){
			smallestIndex = i;
		}
	}
	return smallestIndex;
}

int rr(proc_t * procs, const int numprocs, const int ts)
{
	static int my_queue[256] = {};
	static int h=0;
	static int t=0;
	static int last_run = -1;
	for (int i = 0; i < numprocs; i++){
		if (procs[i].m_arrive == ts){
			my_queue[t] = i;
			t++;
			t %= 256;
		}
	}
	    if (last_run != -1 && !isdone(&procs[last_run])){
                        my_queue[t] = last_run;
                        t += 1;
                        t %= 256;
                }
		last_run = my_queue[h];
		h += 1;
		h %=256;
		return last_run;
}

int rand_sched(proc_t * procs, const int numprocs, const int ts)
{
    int * running_procs = malloc(sizeof(int) * numprocs);
    int numrunning = 0;
    int i;
    int rand_idx;
    int to_run;
    for (i=0; i<numprocs; i++)
    {
        if (running(&procs[i], ts))
        {
            running_procs[numrunning] = i;
            numrunning ++;
        }
    }
    rand_idx = rand() % numrunning;
    to_run = running_procs[rand_idx];
    free(running_procs);
    return to_run;
}
