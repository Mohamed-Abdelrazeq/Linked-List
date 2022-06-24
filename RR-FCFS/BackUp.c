#include <stdio.h>
#include <stdlib.h>

// STRUCTURE
struct process_struct
{
	int pid;
	int at; // Arrival Time
	int pt; // CPU Burst time
	int pt2;
	int bt;
	int tr; // Completion, waiting, turnaround, response time
} ps[100], rq[30], bq[100], current_proccess, old_proccess, out[100];

// FUNCTIONS
int readFileForFCFS(int matrix[][4], char *filename)
{
	FILE *fptr;
	int cols = 4, i = 0, j = 0;
	int num;
	fptr = fopen(filename, "r");
	for (i = 0; feof(fptr) == 0; i++)
	{
		for (j = 0; j < cols; j++)
		{
			fscanf(fptr, "%d", &num);
			matrix[i][j] = num;
			if (feof(fptr))
				break;
		}
	}
	fclose(fptr);
	return i; // return number of rows
}

int findmax(int a, int b)
{
	return a > b ? a : b;
}

int comparatorAT(const void *a, const void *b)
{
	int x = ((struct process_struct *)a)->at;
	int y = ((struct process_struct *)b)->at;
	if (x < y)
		return -1; // No sorting
	else
		return 1; // Sort
}

int comparatorPID(const void *a, const void *b)
{
	int x = ((struct process_struct *)a)->pid;
	int y = ((struct process_struct *)b)->pid;
	if (x < y)
		return -1; // No sorting
	else
		return 1; // Sort
}

int main(int argc, char *argv[])
{

	int n;
	int qunatom;
	int which;
	int i = 0;
	// Run Queue
	int rqe = 0;
	int rqf = 0;
	// Block Queue
	int bqe = 0;
	int bqf = 0;
	// Run Finish Time
	int rft = 0;
	int is_running = 0;
	int conflict = 0;
	// usage
	int usageCounter = 0;
	int endFlag = 1;

	char *filename;

	which = atoi(argv[1]);

	if (which == 0)
	{
		qunatom = 9999;
		filename = argv[2];
	}
	else
	{
		qunatom = atoi(argv[2]);
		filename = argv[3];
	}

	// DEFAULT VALUES
	for (int i = 0; i < 30; i++)
	{
		rq[i].pid = 999;
		rq[i].pt2 = rq[i].pt;
		rq[i].tr = 0;
		old_proccess.pid = 999;
	}

	// READ FROM FILE
	int matrix[100][4];
	n = readFileForFCFS(matrix, filename);

	for (int i = 0; i < n; i++)
	{
		ps[i].pid = matrix[i][0];
		ps[i].pt = matrix[i][1];
		ps[i].pt2 = ps[i].pt;
		ps[i].bt = matrix[i][2];
		ps[i].at = matrix[i][3];
	}



	int howManyAreIn = 0;
	// LOGIC
	while (endFlag != 0 || howManyAreIn != n)
	{
		
		int block = 0;
		endFlag = 0;

		printf("\n%d ", i);

		// CHECK BQ
		if (bqf != 0)
		{

			for (int j = bqe; j < bqf; j++)
			{

				if (bq[j].bt != 0)
				{
					bq[j].tr++;
					bq[j].bt = bq[j].bt - 1;
					printf("%d: BLOCKED ", bq[j].pid);
					endFlag = 1;
				}
				else
				{
					rq[rqf] = bq[j];
					bqe++;
					rqf++;
				}
			}
		}

		// CHECK RFT
		if (i == rft && rft != 0)
		{

			// After Blocking And Proccessing Time
			if (current_proccess.bt == 0 && current_proccess.pt == 0 && current_proccess.pt2 == 0)
			{
				// END
				old_proccess.pid = current_proccess.pid;
				out[current_proccess.pid] = current_proccess;
			}
			else if (current_proccess.pt > 0)
			{
				// Add To Ready Queue
				rq[rqf] = current_proccess;
				rqf++;
				old_proccess.pid = current_proccess.pid;
			}
			else
			{
				current_proccess.tr++;

				bq[bqf] = current_proccess;
				bq[bqf].bt = bq[bqf].bt - 1;
				bqf++;

				printf("%d: BLOCKED ", current_proccess.pid);
				endFlag = 1;
			}

			is_running = 0;
		}

		// CHECK AT
		for (int k = 0; k < n; k++)
		{
			if (ps[k].at == i)
			{
				howManyAreIn++;
			}
			if (ps[k].at == i && ps[k].pt != 0)
			{

				// printf("\n %d %d %d %d \n",ps[k].pid,ps[k].pt,ps[k].bt,ps[k].at);
				rq[rqf] = ps[k];
				rqf++;
			}
		}

		// CHECK RQ
		if (rqf != 0)
		{

			if (is_running)
			{
				current_proccess.tr++;
				printf("%d: RUNNING ", current_proccess.pid);
				usageCounter++;
				endFlag = 1;
				for (int k = 0; k < rqf - rqe; k++)
				{
					rq[k + rqe].tr++;
					printf("%d: READY ", rq[k + rqe].pid);
					endFlag = 1;
				}
			}

			if (!is_running && rqf != rqe)
			{
				struct process_struct temp[rqf - rqe];

				for (int k = 0; k < rqf - rqe; k++)
				{
					temp[k] = rq[rqe + k];
				}

				qsort((void *)temp, rqf - rqe, sizeof(struct process_struct), comparatorPID);

				// Don't Repeat the same process
				if (rqf - rqe > 1 && temp[0].pid == old_proccess.pid)
				{

					// printf("Switched ");
					struct process_struct tempProcess = temp[0];
					temp[0] = temp[1];
					temp[1] = tempProcess;
				}

				for (int k = 0; k < rqf - rqe; k++)
				{
					temp[k].tr++;
					rq[rqe + k] = temp[k];
					if (k != 0)
						printf("%d: READY ", rq[k + rqe].pid);
					endFlag = 1;
				}

				printf("%d: RUNNING ", temp[0].pid);
				usageCounter++;
				endFlag = 1;

				// Use Secondary Proccessing Time
				// printf("current proccessing time: %d , %d seconds ",temp[0].pt,temp[0].pt2);
				if (temp[0].pt == 0 && temp[0].pt2 != 0)
				{
					// printf("I'm PS2 ");
					temp[0].pt = temp[0].pt2;
					temp[0].pt2 = 0;
				}

				// Check Quantom
				if (temp[0].pt > qunatom)
				{
					temp[0].pt -= qunatom;
					rft = i + qunatom;
					// printf("I'm Bigger than Quantom ");
				}
				else
				{
					rft = i + temp[0].pt;
					// printf("I'm Smaller than Quantom ");
					temp[0].pt = 0;
				}
				// End

				is_running = 1;
				current_proccess = temp[0];
				rqe++;
			}
		}

		if (!is_running)
			old_proccess.pid = 999;

		i++;
	}

	printf("\nFinishing Time : %d\n", i - 2);
	float utlization = (float)usageCounter / (float)(i - 1);
	printf("CPU Utilization : %f\n", utlization);
	for (int p = 0; p < n; p++)
	{
		printf("Turnaround Time of Proccess : %d: %d\n", p, out[p].tr);
	}

	return 0;
}


// We Always sort the ready queue based on the PID
// And Proccess with 0 PT will not be added to any queue