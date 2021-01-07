import java.io.*;
@SuppressWarnings("unchecked")

public class Pez
{
	public static void main(String[] args) throws IOException, CloneNotSupportedException 
	{
		Stack stack1 = new Stack();
		addPez(stack1);	
		System.out.println("Original Stack:");
		toString(stack1);
		removeGreen(stack1);
		System.out.println("\nRemoved Greens:");
		toString(stack1);
	}	
	
	public static void addPez(Stack s) throws CloneNotSupportedException
	{
		s.push("yellow");
		s.push("red");
		s.push("green");
		s.push("green");
		s.push("yellow");
		s.push("yellow");
		s.push("red");
		s.push("green");	
	}

	public static Stack removeGreen(Stack s)
	{
		Stack temp = new Stack();
		while (! s.isEmpty()) {
			String toPush = (String) s.top();
			if (toPush.equals("green")) {
				s.pop();
			}
			else {
				temp.push(s.top());
				s.pop();
			}
		}
		while (! temp.isEmpty()) {
			s.push(temp.top());
			temp.pop();
		}
		return s;
	}

	public static void toString(Stack s) throws CloneNotSupportedException
 	{
		Stack temp = (Stack) (s.clone());
		while (! temp.isEmpty()) {
			String toPrint = (String) temp.top();
			System.out.println(toPrint);
			temp.pop();
		}
	}
}
