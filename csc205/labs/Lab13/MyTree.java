public class MyTree 
{
	public static void main(String[] args)
	{	
		BinarySearchTree t = new BinarySearchTree();
		t.insert(new KeyedItem("M"));
		t.insert(new KeyedItem("J"));
		t.insert(new KeyedItem("D"));
		t.insert(new KeyedItem("F"));
		t.insert(new KeyedItem("L"));
		t.insert(new KeyedItem("W"));
		t.insert(new KeyedItem("S"));
		t.insert(new KeyedItem("T"));
		t.insert(new KeyedItem("Z"));

		System.out.println("Inorder Traversal Print:");
		System.out.println("------------------------");
		t.inorder();
		System.out.println("\nPreorder Traversal Print:");
		System.out.println("-------------------------");
		t.preorder();
		System.out.println("\nPostorder Traversal Print:");
		System.out.println("--------------------------");
		t.postorder();

		BinarySearchTree copy = new BinarySearchTree();
		copy.insert(new KeyedItem("M"));
		copy.insert(new KeyedItem("J"));
		copy.insert(new KeyedItem("D"));
		copy.insert(new KeyedItem("F"));
		copy.insert(new KeyedItem("L"));
		copy.insert(new KeyedItem("W"));
		copy.insert(new KeyedItem("S"));
		copy.insert(new KeyedItem("T"));
		copy.insert(new KeyedItem("Z"));		

		System.out.println("\nAre copy and t the same?");
		System.out.println("------------------------");
		if (t.duplicateCheck(copy))
			System.out.println("They're duplicates");
		else
			System.out.println("They're not duplicates");	

		System.out.println("\nDeleting the root...");
		System.out.println("--------------------");
		t.deleteNode(t.root);	
		t.preorder();
	}
}
