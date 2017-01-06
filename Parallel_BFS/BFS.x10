import x10.io.Console;
import x10.util.*;

class retType{
	var b : Boolean;
	var idx : Int;

	public def this(b : Boolean , i : Int){
		this.b = b;
		this.idx = i;
	}
}


class Graph{
	val vertexList:Array[Vertex](1) ;
	var indexDone :Int;
	public static val MAXINF = 2147483647;   

	public def this(num : Int){
		vertexList = new Array[Vertex](num);
		indexDone = -1;
	}
	

	public def isPresent(lblNode : String) : retType{
		var rt : retType;
		for(var i : Int = 0 ; i < indexDone ; i++)
                {
                        if(vertexList(i).label.equals(lblNode))
                        {
                                rt = new retType(true,i);
				return rt;
                        }
                }
		rt = new retType(false , -1);
		return rt;
	}

		
	public def findIndex(): Int{
 			indexDone++;
			return indexDone;
		
	}

	public def getNode(lblNode : String):Vertex{
		var index : Int;
		var rt: retType;
		rt = isPresent(lblNode);
		if(!rt.b)
		{
 			index = findIndex();
			val newVertex = new Vertex(lblNode,index);
			vertexList(index) = newVertex;
			return vertexList(index);
		}
		else{
			var v:Vertex ;
			v = vertexList(rt.idx);
			return v;
		}
	}

	public def addEdge(src : Vertex,dest : Vertex ,wt : Double){
		var en:EdgeNode;
		en = new EdgeNode(dest,wt);
		src.addEdge(en);
	}

	public def SerialBFS( src : Vertex){
		for(var i: Int = 0 ; i < vertexList.size();i++){
			if(vertexList(i).equals(src)){
				vertexList(i).dist = 0;
			}
			else{
		 		vertexList(i).dist = MAXINF;   // Initializing from Max Int - Infinity	
			}
		}
		val q = new Queue();

		q.ENQUEUE(src);

		var u : Vertex;
		var en: EdgeNode;
		while(!q.isEmpty()){
			u = q.DEQUEUE();
			for(var i :Int = 0 ; i < u.edgeList.size();i++){
				en = u.edgeList.get(i);
				finish{
					val c1 = Clock.make();
					async clocked(c1){
						if(en.destVertex.dist == MAXINF){
							en.destVertex.dist = u.dist + 1;
							q.ENQUEUE(en.destVertex);
						}
						next;
					}
				}
			}
		}
	}
				
			
}
		
	


class Vertex{
	var dist:Int ; //Distance from source node
	var label:String; //Label for Vertex
	var visited: boolean;  //Flag if Vertex has been visited or not 
	var index :Int ;    //Index of Vertex in Graph Data Structure
	val edgeList:ArrayList[EdgeNode]; //Edges from the vertex
	
	public def this(lbl : String,indx: Int){
		label = lbl;
		visited = false;
		edgeList = new ArrayList[EdgeNode](10);
		dist = 2147483647;   // Initializing from Max Int - Infinity
		index = indx;
	}

	public def addEdge(en : EdgeNode) :Void {
		edgeList.add(en);	
	}
		

}


class EdgeNode{
	var destVertex:Vertex; 
	var EdgeWt :Double;

	public def this(dv : Vertex , eW :Double){
		destVertex = dv;
		EdgeWt = eW;
	}
} 

class Queue{
	val nodeList: ArrayList[Vertex];

	public def this(){
		nodeList = new ArrayList[Vertex]();
	}

	public def ENQUEUE(v:Vertex) : Void{
		nodeList.add(v);
	}
	
	public def DEQUEUE(): Vertex{
		return nodeList.removeFirst();
	}

	public def isEmpty():Boolean{
		return nodeList.isEmpty();
	}
}
		
 
class BFS{
	public static def main(a : Array[String](1)){
		// create an array list 
		val al = new ArrayList[String](10); 
		Console.OUT.println("Initial size of al: " + al.size()); 
		// add elements to the array list 
		al.add("C"); 
		al.add("A"); 
		al.add("E"); 
		al.add("B"); 
		al.add("D"); 
		al.add("F"); 
	//	al.addBefore(1, "A2"); 
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
