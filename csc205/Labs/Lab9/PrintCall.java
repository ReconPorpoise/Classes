public class PrintCall
{
        public static void main(String[] args)
        {
                printMe(1);
        }

        public static void printMe(int n)
        {

          if ( (n != 1)  && (n != 5) )
          {   
             for (int i = 1;  i <= n;  i++) 
                 System.out.print(' ');
             System.out.println("This was written by call number " + n + ".");
          }
	
          //  Add an if stmt here with a recursive stmt in its body
          //  along with a for loop similar to the one above 

	  if (n >=  1 &&  n < 5) 
	  {
	      printMe(n + 1);
	      for (int i = n; i > 0; i--)
	      {
	          System.out.print(' ');
 	      }
	      System.out.println("This was ALSO written by call number " + n + ".");
          }
	  // Runs the top if (2-4) and puts (1, 2, 3, 4) on hold in the stack.
	  // When (2-4) is done printing, using last in-first out, (4, 3, 2, 1) is printed with ALSO.
        }
}
