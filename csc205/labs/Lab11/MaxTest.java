
import java.io.*;
@SuppressWarnings("unchecked")

public class MaxTest 
{
   public static void main(String[] args) throws IOException, CloneNotSupportedException
   {
        	Stack stack1 = new Stack();
		stack1.push("Andy");
		stack1.push("Allison");
		stack1.push("Aaron");
		stack1.push("Austin");
		stack1.push("Abbey");
		stack1.push("Alex");
        	System.out.println("findMax(stack1)="+findMax(stack1)); 
        	System.out.println("stack1.findMax()="+stack1.findMax()); 
  }

  public static String findMax(Stack s) throws CloneNotSupportedException 
  {
		
  		Stack tempStack = (Stack) (s.clone());
		String max = (String) tempStack.top();
		tempStack.pop();

		while (! tempStack.isEmpty()) {
			String next = (String) tempStack.top();
			if (next.compareTo(max) > 0) {
				max = next;
				tempStack.pop();
			}
			else {
				tempStack.pop();
			}
		}
	
		return max;		
  }
}
