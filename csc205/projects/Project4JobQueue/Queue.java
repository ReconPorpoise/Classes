
@SuppressWarnings("unchecked")
public class Queue implements QueueInterface {
  private Node lastNode;
  
  public Queue() {
    lastNode = null;   
  }  // end default constructor
  
  // queue operations:
  public boolean isEmpty() {
        return (lastNode == null);
  }  // end isEmpty

  public void dequeueAll() {
    lastNode = null;
  }  // end dequeueAll

  public void enqueue(Object newItem) {
    // insert the new node
    if (isEmpty()) {
      // insertion into empty queue
      lastNode = new Node(newItem, null);  
      lastNode.setNext(lastNode);  
    }
    else {
      // insertion into nonempty queue
      Node newNode = new Node(newItem, lastNode.getNext());
      lastNode.setNext(newNode);
      lastNode = newNode;
    }  // end if
  }  // end enqueue

  public Object dequeue() throws QueueException {
    // lastNode != null helps push the conditions all to return if there is a null pointer exception
    // it is on both if and else if to make sure that they don't run if it will cause a null pointer which
    // only will occur if there is one item in the list and only after it has been accounted for
     
    // toReturn is the front of the queue, will always return whatever is in the front
    Object toReturn = front();
    if (isEmpty()) {
	throw new QueueException("QueueException on dequeue:"
			       + "queue empty");
    }  
    else {
	// if front and lastNode have the same value (they are the same exact node aka one node in the list)
	// and lastNode isn't null, set lastNode to null so it can read as "empty" and jump to the return
	if (front() == lastNode.getItem() && lastNode != null) {
		lastNode = null;
	}
	// else if the front value and the last value ARENT the same (aka has more than one node) and
	// lastNode isn't null, toReturn = front() and the new front becomes 2 ahead of last
	// (or the next after front()) 
	else if (lastNode.getNext().getItem() != lastNode.getItem() && lastNode != null) {
		lastNode.setNext(lastNode.getNext().getNext());
	}
    }
    return toReturn;
  } 
  
  public Object peek() {
    return lastNode.getNext().getItem();
  }

  public Object front() throws QueueException {
    if (!isEmpty()) {
      Node firstNode = lastNode.getNext();
      return firstNode.getItem();
    }
    else {
      throw new QueueException("QueueException on front:"
                             + "queue empty");
    }
  }

  public Object clone() throws CloneNotSupportedException
  {
	boolean copied = false;
        Queue copy = new Queue();
        Node curr = lastNode, prev = null;
        while ( (! copied) && (lastNode != null) )
        {
                Node temp = new Node(curr.getItem());
                if (prev == null)
                        copy.lastNode = temp;
                else
                        prev.setNext(temp);
                prev = temp;
                curr = curr.getNext();
		copied = (lastNode == curr);
        }
	prev.setNext(copy.lastNode);
        return copy;
  }
} // end Queue
