import java.util.*;
@SuppressWarnings("unchecked")

public class JCFStack
{
   public static void main(String[] args) throws CloneNotSupportedException
   {
        	Stack stack1 = new Stack();
		stack1.push(new Integer(27));
		stack1.push(new Integer(0));
		stack1.push(new Integer(-3));
		stack1.push(new Integer(-18));
		stack1.push(new Integer(99));
        	printStack (stack1); 
		
		Scanner in = new Scanner(System.in);
		System.out.print("\nEnter a key value to find: ");
		int temp = in.nextInt();
		Integer key = new Integer(temp);
		int pos = stack1.search(key);		
		
		if (pos == -1) {
			System.out.println("Key was not found in the stack.");
		}
		else {
			System.out.println("Key value found at position " + pos);
		}
  }

  private static void printStack (Stack s) throws CloneNotSupportedException
  {
        Stack tempStack = (Stack) (s.clone());
        if (! tempStack.isEmpty())
                System.out.println("*** Printing Out Stack:  ");

        while (! tempStack.isEmpty())
        {
               System.out.println(tempStack.peek());
               tempStack.pop();
        }
  }
}
