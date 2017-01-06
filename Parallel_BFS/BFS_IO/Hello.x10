import  x10.io.*;
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
		for(var i : Int = 0 ; i <= indexDone ; i++)
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

	public def ParallelBFSQueue( srclabel : String ){
		var srcV : Vertex = null;
		for(var i: Int = 0 ; i < vertexList.size();i++){
			if(vertexList(i).label.equals(srclabel)){
				srcV = vertexList(i);
				vertexList(i).dist = 0;
				Console.OUT.println("Label " + vertexList(i).label + " dist " + vertexList(i).dist); 
			}
			else{
				vertexList(i).dist = MAXINF;   // Initializing from Max Int - Infinity	
			}
		}
		val q = new Queue();

		q.ENQUEUE(srcV);

		var u : Vertex;
		var en: EdgeNode;
		

		while(!q.isEmpty()){
			u = q.DEQUEUE();
		      
			for(var i :Int = 0 ; i < u.edgeList.size();i++){
				en = u.edgeList.get(i);
				finish{
					val c1 = Clock.make();
					
						if((en.destVertex.dist == MAXINF) && (!en.destVertex.visited)){
						  async clocked(c1){
						    en.destVertex.dist = u.dist + 1;
						    en.destVertex.visited = true;
						    q.ENQUEUE(en.destVertex);
						    Console.OUT.println("Label " + en.destVertex.label + " dist " + en.destVertex.dist); 
						    resume;
						  }
						 
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
		edgeList = new ArrayList[EdgeNode]();
		dist = 2147483647;   // Initializing from Max Int - Infinity
		index = indx;
	}

	public def addEdge(en : EdgeNode)  {
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

	public def ENQUEUE(v:Vertex) {
		nodeList.add(v);
		
	}
	
	public def DEQUEUE(): Vertex{
		return nodeList.removeFirst();
	}

	public def isEmpty():Boolean{
		return nodeList.isEmpty();
	}
}


/**
 * The canonical "Hello, World" demo class expressed in X10
 */

class Edge{
	public var src : String;
	public var dest : String;
	public var wt : Double;
	
	public def this(s : String , d : String , w : Double){
		src = s;
		dest = d;
		wt = w;
	}
	
	public def toString():String{
		return src + " " + dest + " " + wt;
	}
	
	
}


public class Hello {

    /**
     * The main method for the Hello class
     */
	
	
    public static def main(Array[String]) {
    	var noofNodes : Int = 0;
    	var edge : Rail[String]();
    	val edges: ArrayList[Edge];
    	edges = new ArrayList[Edge]();
    	var G : Graph;
    	try{
    		val inp = new File("input.txt");
    		//val out = new File("C:\\Users\\parvesh\\workspace\\filetry\\src\\output.txt");
    		val i  = inp.openRead();
    		//val p = out.printer();
    		
    	   
    		var j : Int  = 0;
    		var k : Int = 0;
    		
    		var src :String = " " , dest : String = " ";
    		var wt : Double = 0;
    		for ( line in i.lines()){
    			if(j == 0){
    				noofNodes = Int.parse(line.trim());
    				
    				//p.print(line);
    			}
    			else{
    				edge = line.split(" ");
    				k = 0;
    				for(str in edge){
    					
    					switch(k){
    						case 0 : src = str;
    					          break;
    						case 1 : dest = str;
    					          break;
    						case 2 : wt = Double.parse(str);
    					          break;
    					
    					}
    					k++;
    				}
    				edges.add(new Edge(src , dest, wt));
    			}
    			j++;
    		}
    		
    	}
    
    	catch(IOException){}
    	
    	G = new Graph(noofNodes);
    	var v1 : Vertex, v2 : Vertex;
    	var idx : Int;
    	var j : Int = 0;
    	
    	for (e in edges){
    	
    		v1 = G.getNode(e.src);
    		v2 = G.getNode(e.dest);
    		G.addEdge(v1,v2,e.wt);
    	}
    	G.ParallelBFSQueue("0");
    	
    	
    	
    		
    }
}

