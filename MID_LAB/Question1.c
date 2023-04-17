#include <stdint.h>

struct process
{
  int process_id;
  int arrival_time;
  int burst_time;
  int priority;
};

int main()
{

  struct process p[3] = {{1, 0, 5, 2}, {2, 0, 6, 1}, {3, 0, 7, 3}};

  int i, j, k, n = 5;
  int total_time = 0;
  int total_waiting_time = 0;
  int total_turnaround_time = 0;

  int waiting_time[3];
  int turnaround_time[3];

  // Sorting the processes according to their priority
  for (i = 0; i < 3; i++)
  {
    for (j = i + 1; j < 3; j++)
    {
      if (p[i].priority > p[j].priority)
      {
        struct process temp = p[i];
        p[i] = p[j];
        p[j] = temp;
      }
    }
  }
  // Calculate waiting time
  for (i = 0; i < 3; i++)
  {
    waiting_time[i] = total_time - p[i].arrival_time;
    total_time += p[i].burst_time;
  }
  // Calculate turnaround time
  for (i = 0; i < 3; i++)
  {
    turnaround_time[i] = waiting_time[i] + p[i].burst_time;
  }
  // Calculate total waiting time
  for (i = 0; i < 3; i++)
  {
    total_waiting_time += waiting_time[i];
  }
  // Calculate total turnaround time
  for (i = 0; i < 3; i++)
  {
    total_turnaround_time += turnaround_time[i];
  }
  // Averages
  int average_waiting_time = total_waiting_time / 3;
  int average_turnaround_time = total_turnaround_time / 3;
  // Display the result
  printf("\n\nID\tWaiting Time\tTurnaround Time\n");
  for (i = 0; i < 3; i++)
  {
    printf("%d\t\t\t\t%d\t\t\t\t\t\t%d\n", p[i].process_id, waiting_time[i], turnaround_time[i]);
  }
  printf("\nAverage waiting time: %d\n", average_waiting_time);
  printf("Average turnaround time: %d\n", average_turnaround_time);

  return 0;
}