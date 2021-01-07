
public class Links
{
	public static int count = 0;

	public static void main(String[] args)
	{
          	Node pos1 = null;
    		Node pos2 = null;
    		pos1 = new Node(new Integer(13));
   		pos1.setNext(new Node(new Integer(15), null));
    		pos2 = new Node(new Integer(11), null);
		pos2.setNext(pos1);
		printList(pos2);

		System.out.println(count(pos2));
		System.out.println(findMax(pos2));
	}

	private static void printList(Node head)
	{
		if (head != null)
		{
			System.out.println(head.getItem());
			printList(head.getNext());
		}
	}

	public static int count(Node head) 
	{
		if (head == null) {
			return 0;
		}
		else {
			return 1 + count(head.getNext());
		}
	}

	@SuppressWarnings("unchecked")
	public static Object findMax(Node head)  
 	{
		// set max to the first value and the nextNode to the second value
		Node max = head;
		Node nextNode = max.getNext();
		
		// until you reach the end of the list, compare the two 
		while (nextNode != null) {
			// if nextNode is higher, make that the max
			if (((Comparable) max.getItem()).compareTo((Comparable) nextNode.getItem()) < 0) {
				max = nextNode;
			}
			// make the next comparable node set to the nextNode + 1 position 
			nextNode = nextNode.getNext();
		}
		// type Object to not worry about data types. 
		// return the object value (15 in this case) 	
		Object toReturn = max.getItem();
		return toReturn;
	}
}
