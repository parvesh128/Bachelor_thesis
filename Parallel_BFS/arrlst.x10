import x10.util.*;
import x10.io.Console;

class arrlst{
        public static def main(a : Array[String](1)){
                // create an array list
                val al = new ArrayList[String](2);
                Console.OUT.println("Initial size of al: " + al.size());
                // add elements to the array list
                al.add("C");
                al.add("A");
                al.add("E");
                al.add("B");
                al.add("D");
                al.add("F");
        //      al.addBefore(1, "A2");
                Console.OUT.println("Size of al after additions: " + al.size());
                // display the array list
                Console.OUT.println("Contents of al: " + al);
                for(var i:Int = 0 ; i < al.size();i++)
                        Console.OUT.println(al.get(i));
                // Remove elements from the array list
                al.remove("F");
                al.remove("A2");
                Console.OUT.println("Size of al after deletions: " + al.size());
                Console.OUT.println("Contents of al: " + al);

        }
}
 
