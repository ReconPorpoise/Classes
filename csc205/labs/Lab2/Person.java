/*
 * Ronald Karamuca
 * An implementation class that allows for "people" to be added to a system and given an ID
 */

public class Person
{
  private String name;
  private int    id;
  private static int personCount = 0;

  // constructor
  public Person(String pname)
  {
    name = pname;
    personCount++;
    id = 100 + personCount;
  }

  // overload constructor
  public Person()
  {
    this("N/A");
    id = -1;
    personCount++;
  }
  
  // takes a new name and id as input and sets THIS objects name and id as the parameters
  public void reset(String name,int id ) 
  {
    this.name = name;
    this.id = id;
  }
  
  // returns the name of an object
  public String getName()
  {
    return name;
  }
 
  // returns the id of an object
  public int getId()
  {
    return id;
  }
    
  public String  toString()
  {
    return "name: " + name + "  id: " + id 
      + "  (Person count: " + personCount + ")";
  }

  // static/class method
  public static int getCount()
  {
    return personCount;
  }
  
}
