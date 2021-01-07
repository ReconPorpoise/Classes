/*
 * Ronald Karamuca
 * 05.01.20
 * 
 * Program that simulates a CPU job queue 
 */

import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class TimeShare 
{
	public static void main(String[] args) throws IOException
	{
		// check for incorrect execution of the program and alert the user if so
		clearScreen();
		try {
			// if they pass, create an input queue using the command line argument 
			Queue inQ = new Queue();
			File inFile = new File(args[0]); 
			fillInput(inQ, inFile);
			// call runAll with inQ to continue operation
			runAll(inQ);
		} catch (Exception e) {
			System.out.println("Incorrect command line arguments. Follow the model of (java TimeShare jobs1.dat).");
		}
	}

	// fills inQ with all jobs from the inFile
	public static Queue fillInput(Queue inQ, File inFile) throws IOException
	{
		Scanner fileScan = new Scanner(inFile);
	
		// while the file still has lines...
		while (fileScan.hasNext())
		{
			// create an array with each of the 3 pieces from the current line in the file
			String[] job = fileScan.nextLine().split("\t");
		
			// get the name, arrivalTime, and runTime to create a Job we can insert into the inQ queue
			String name = job[0].trim();
			int arrivalTime = Integer.parseInt(job[1].trim());
			int runTime = Integer.parseInt(job[2].trim());
			Job temp = new Job(name, arrivalTime, runTime);
			inQ.enqueue(temp);
		}
		fileScan.close();
		return inQ;
	}

	// dequeue method for use in any method
	// this allows us to edit queues anywhere in the program
	public static Queue deQ(Queue in)
	{
		in.dequeue();
		return in;
	}
	
	// enqueue method for use in any method
	// this allows us to edit queues anywhere in the program
	public static Queue enQ(Queue in, Job curr)
	{
		in.enqueue(curr);
		return in;
	}

	// add processes from the input queue into the process queue
	public static double addProcess(Job curr, int clock, Queue pQ, Queue iQ)
	{
		// separate all parts of the job object to pull out arrivalTime
		String[] parts = curr.toString().split("\t");
		int arrivalTime = Integer.parseInt(parts[1]);

		// count = clock because we need to edit both clock and idle, and we cannot return two values
		// we return the one value and add it to the correct variables underneath the method call
		int count = clock;
		
		// checks to make sure a job isn't being executed too early
		// if the arrivalTime is greater, idle gets increased along with clock
		while (arrivalTime > count)
		{
			count++;
		}
		
		// when the arrivalTime comes, enqueue current job into the process queue and remove it from the input queue
		enQ(pQ, curr);
		deQ(iQ);
		
		//returns count - clock because clock should not be counted in the increase of clock itself as well as idle time
		return count - clock;	
	}

	// sets up the proper execution of a job when it's run time arrives in the process queue
	public static double runTime(Job curr, int clock, ArrayList<Integer> waits, Queue oQ, Queue pQ)	
	{
		// startTime is the current clock time always
		int startTime = clock;
		// set the current job's startTime accordingly for proper calculation later on
		curr.startTime = clock;
		// set the current job's waitTime (start - arrival times) accordingly for proper calculation later on
		curr.waitTime = startTime - curr.arrivalTime;
		// add the waitTime to waits ArrayList to calculate average waitTime later on
		waits.add(curr.waitTime);
		
		// create the parts to pull out the runTime from the job object
		String[] parts = curr.toString().split("\t");
		int runTime = Integer.parseInt(parts[3]);
		int count = clock;
	
		// check to make sure that the job hasn't finished it's execution task
		// the clock keeps increasing until the runTime has been finished
		while ((count - startTime) != runTime)
		{
			count++;
		}

		// turnTime is the turnaround of when a job finishes it's task - the arrival time of it
		curr.turnTime = count - curr.arrivalTime;
	
		// after all is done, move the job into the output queue and remove it from the process queue
		enQ(oQ, curr);
		deQ(pQ);

		// return count - clock because we don't want the clock time interferring with the usage time
		return count - clock;
	}

	// driver method that calls almost all other methods for concise and clean run of the program
	public static void runAll(Queue inQ)
	{
		// initialize clock to be 1 (default position), "CPU" usage and idle times to be 0, process and output queues, and our list of wait times
		int clock = 1;
		double usage = 0;
		double idle = 0;
		Queue processQ = new Queue();
		Queue outputQ = new Queue();
		ArrayList<Integer> waits = new ArrayList<Integer>();
	

		// check to see if the input queue is empty 
		while (! inQ.isEmpty() || ! processQ.isEmpty())
		{
			// initialize the value of clock/idle/usage increase to be 0 until we run our methods
			double increase = 0;
			
			// if the input queue still isn't empty 
			if (! inQ.isEmpty())
			{	
				// the current job will be the one in the front of the input queue
				// our priority is to get it into the process queue
				// to do this, we call addProcess and set that return value to be the value of increase,
				// then we increment our clock and "CPU" idle time by this value because any time it took
				// waiting to add the job to the process queue is time that wasn't used for execution
				Job curr = (Job) inQ.front();
				increase = addProcess(curr, clock, processQ, inQ);
				clock += increase;
				idle += increase;
				
				// once we have that value in the process queue, we get it to execute using runTime,
				// and setting the return value of that to be our new value of increase,
				// we then increment clock and "CPU" usage time by this value
				increase = runTime(curr, clock, waits, outputQ, processQ);
				clock += increase;
				usage += increase;
			}
			// if input queue is empty then we set the current job to be the one in the front of process queue
			else 
			{
				Job curr = (Job) processQ.front();
				// since the job is already in the process queue, we don't need to run addProcess
				// just run the runTime method and increase clock and usage by the return value
				increase = runTime(curr, clock, waits, outputQ, processQ);
				clock += increase;
				usage += increase;
			}
		}
		// call the print method to display our findings 
		printOut(outputQ, waits, idle, usage);
	}

	// prints out all of the information of the job queue (job name, arrivalTime, startTime, turnTime, waitTime, turnaroundTime)
	public static void printOut(Queue toPrint, ArrayList<Integer> waits, double idle, double usage)
	{
		// format all decimals to 2 decimal places
		DecimalFormat df = new DecimalFormat("###,###,###,###,###,##0.00");
		
		// if, somehow, this is reached with an empty queue, let the user know 
		if (toPrint.isEmpty())
		{
			System.out.println("Queue is empty.");
		}
		// creates a UI to make the data look better in the output display 
		else 
		{
			System.out.println("*---------------------------------------------------*");
			System.out.println("Job Control Analysis : Summary Report\n");
			System.out.println("job id\tarrival\tstart\trun\twait\tturnaround");
			System.out.println("\ttime\ttime\ttime\ttime\ttime");
			System.out.println("------\t-------\t-----\t----\t----\t----------");
			while (! toPrint.isEmpty())
			{
				Job curr = (Job) toPrint.front();
				System.out.println(curr);	
				toPrint.dequeue();
			}
			System.out.println("*---------------------------------------------------*");
			
			// finds averageWait by getting the sum of all waitTimes and dividing by the number of jobs
			double averageWait = 0;
			for (int i = 0; i < waits.size(); i++)
			{
				averageWait += waits.get(i);
			}
			averageWait = averageWait / (double) waits.size();
			
			// finds "CPU" usage percentage by dividing the usage time amount by the total "CPU" time (usage + idle times) then multiplying by 100
			double usagePercent = (usage / (usage + idle)) * 100;
			
			System.out.println("Run-time Stats:\n");
			System.out.println("  Average Wait Time => " + df.format(averageWait));
			System.out.println("         CPU Usage  => " + df.format(usage));
			System.out.println("           CPU Idle => " + df.format(idle));
			System.out.println("      CPU Usage (%) => " + df.format(usagePercent) + "%");
			System.out.println("*---------------------------------------------------*");
			System.out.println();
		}
	}

	// clears the terminal screen (used at the beginning to create a clear interface)	
	public static void clearScreen() 
	{
		System.out.println("\u001b[H\u001b[2J");
	}
}
