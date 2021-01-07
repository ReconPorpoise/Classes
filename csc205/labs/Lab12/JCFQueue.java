
import java.util.*;

@SuppressWarnings("unchecked")
public class JCFQueue
{
	public static void main(String[] args) throws CloneNotSupportedException
	{
		LinkedList queue1 = new LinkedList();
		LinkedList queue2 = new LinkedList();
		Object key = new Character('$');

        	queue1.addLast(new Character('b'));
        	queue1.addLast(new Character('$'));
        	queue1.addLast(new Character('E'));
        	queue1.addLast(new Character('$'));
        	queue2.addLast(new Character('b'));
        	queue2.addLast(new Character('$'));
        	queue2.addLast(new Character('E'));
        	queue2.addLast(new Character('b'));
		System.out.println("dup check = " +
                    identicalCheck(queue1, queue2));
		findAndReplace(queue1, key, new Character('*'));
		System.out.println("** After findAndReplace **");
		printQueue(queue1);
	}

	private static boolean identicalCheck(LinkedList queue1,
                                              LinkedList queue2)
                throws CloneNotSupportedException
	{
		boolean check = true;
		LinkedList temp1 = (LinkedList) queue1.clone();
		LinkedList temp2 = (LinkedList) queue2.clone();
		
		if (temp1.size() != temp2.size()) {
			check = false;
			return check;
		}
		
		while (! temp1.isEmpty()) {
			if (temp1.peek().equals(temp2.peek())) {
				temp1.pop();
				temp2.pop();
			}
			else {
				check = false;
				break;
			}
		}
		
		return check;
	}

	private static void findAndReplace(LinkedList queue1, 
		Object key, Object newVal)
	{
		int index = 0;
		while (queue1.size() > index) {
			if (queue1.get(index).equals(key)) {
				queue1.set(index, newVal);
			}
			index++;
		}
	}

	private static void printQueue (LinkedList q)
		 throws CloneNotSupportedException
	{
		if (q.size() == 0) {
			System.out.println("Queue is empty.");
		}
		else {
			for (int i = 0; i < q.size(); i++) {
				System.out.println(q.get(i));
			}
		}

	}


}
