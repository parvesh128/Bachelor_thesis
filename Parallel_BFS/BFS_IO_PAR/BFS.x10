import  x10.io.*;
import x10.io.Console;
import x10.util.*;
import x10.lang.Math;


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

	public def ParallelBFSBAG( srclabel : String ){
		var srcV : Vertex = null;
		Console.OUT.println("-------------------BFS Using BAGS----------------");
		
		finish for(var i: Int = 0 ; i < vertexList.size();i++){
			val v : Vertex;
			v = vertexList(i);
			async{
				if(v.label.equals(srclabel)){
					srcV = v;
					v.dist = 0;
					Console.OUT.println("Label " + v.label + " dist " + v.dist); 
				}
				else{
					v.dist = MAXINF;   // Initializing from Max Int - Infinity	
				}
			}
		}
		
		
		var d : Int = 0;
		var n : Int = BAG.findBAGSIZE(vertexList.size());
		var IN_BAG:BAG = new BAG(n);

		IN_BAG.BAG_INSERT(srcV);

		var u : Vertex;
		var en: EdgeNode;
		

		while(!IN_BAG.BAG_IS_EMPTY()){
			var OUT_BAG :BAG=  BAG.BAG_CREATE(n);
			IN_BAG.BAG_PROCESS(OUT_BAG,d);
			d = d+1;
			IN_BAG = OUT_BAG;
		}
	}
	
	
	public def ParallelBFSQueue( srclabel : String ){
		var srcV : Vertex = null;
		Console.OUT.println("----------------------BFS using Queue-----------------");
		finish for(var i: Int = 0 ; i < vertexList.size();i++){
			val v : Vertex;
			v = vertexList(i);
			 async{
			if(v.label.equals(srclabel)){
				srcV = v;
				v.dist = 0;
				Console.OUT.println("Label " + v.label + " dist " + v.dist); 
			}
			else{
				v.dist = MAXINF;   // Initializing from Max Int - Infinity	
			}
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
	
	public def toString():String{
		return label;
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




class Node_Penn{
	var v : Vertex;
	var lt : Node_Penn ;
	var rt : Node_Penn ;
	public def this(v : Vertex , lt : Node_Penn , rt : Node_Penn){
		this.v = v;
		this.lt = lt;
		this.rt = rt;
	}
}


class Pennant{
	var root : Node_Penn;
	var size : Int = 0;
	
	public def this(){
		root = null;
		size = 0;
	}
	
	public def this(v : Vertex){
		
		this.root = new Node_Penn(v,null,null);
		this.size++;
	}
	
	public def this(root : Node_Penn){
		
		this.root = root;
		this.size++;
	}
	
	public def unionPennant(p : Pennant) : Pennant{
		if(this.size == p.size){
			p.root.rt = this.root.lt;
			this.root.lt = p.root;
			this.size = this.size + p.size;
			
			return this;
		}
		else{
			Console.OUT.println("Union valid only between two pennants of same size");
			return this;
		}
		
	}
	public def splitPennant():Pennant{
		var p : Pennant = new Pennant(this.root.lt);
		this.root.lt = p.root.rt;
		p.root.rt = null;
		this.size = p.size = size/2;
		return p;
	}
	
	private def processPennantNode(p : Node_Penn,var OUT_BAG: BAG,d : Int){
		
		var en: EdgeNode;
		if (p != null){
			var u : Vertex;
			u = p.v;
			for(var i :Int = 0 ; i < u.edgeList.size();i++){
				en = u.edgeList.get(i);
				finish{
					val c1 = Clock.make();
					val ob : BAG = new BAG(OUT_BAG.r);
					if((en.destVertex.dist == Graph.MAXINF) && (!en.destVertex.visited)){
						async clocked(c1){
							
							en.destVertex.dist = u.dist + 1;
							en.destVertex.visited = true;
							ob.BAG_INSERT(en.destVertex);
							Console.OUT.println("Label " + en.destVertex.label + " dist " + en.destVertex.dist); 
							OUT_BAG.BAG_UNION(ob);
							resume;
						}
						
					}
					
				}
			}
			//Perform Computation at the node_Value
			Pennant.this.processPennantNode(p.lt, OUT_BAG, d);
			Pennant.this.processPennantNode(p.rt, OUT_BAG, d);
		}
	}
	
	public  def processPennant(var OUT_BAG: BAG,d : Int){
		
		Pennant.this.processPennantNode(Pennant.this.root, OUT_BAG, d);
	}
	
	
	private def printPennantNode(p : Node_Penn){
		if (p != null){
			Console.OUT.print(p.v.label +" ");
			printPennantNode(p.lt);
			printPennantNode(p.rt);
		}
	}
	
	public  def printPennant(){
		
		printPennantNode(root);
	}
	
}

class AdderResult{
	var s : Pennant;
	var c : Pennant ;
}


class BackBoneNode{
	var p : Pennant = null;
	
	public def this(){
		
	}
	
}


class BAG{
	var backbone : Array[BackBoneNode](1);
	var r : Int;
	var size : Int = 0;
	public static GRAINSIZE : Int = 128;
	
	public def this(r : Int){
		backbone = new Array[BackBoneNode](r+1);
		for(var i : Int = 0 ; i <= r ; i++){
			backbone(i) = new BackBoneNode();
		}
		this.r = r;
	}
	
	public static def BAG_CREATE(r : Int) : BAG{
		return new BAG(r);
	}
	
	
	public def BAG_INSERT( p1 : Pennant){
		var k : Int = 0;
		var p : Pennant = p1;
		
		while(backbone(k).p != null){
			
			p = p.unionPennant(backbone(k).p);
			backbone(k++).p = null;
		}
		
		
		backbone(k).p = p;
		
		size = size + p.size;
	}
	
	public def BAG_INSERT(x : Vertex){
		var k : Int = 0;
		var p : Pennant = new Pennant(x);
		
		
		while(backbone(k).p != null){
			p = p.unionPennant(backbone(k).p);
			backbone(k++).p = null;
			
		}
		
		
		backbone(k).p = p;
		size++;
	}
	
	private def FA(x : Pennant , y : Pennant ,z :Pennant) :AdderResult {
		
		var ar : AdderResult = new AdderResult();
		
		if(x == null ){
			if(y  == null){
				if(z == null){
					ar.s  = null;
					ar.c = null;
					
				}
				else{
					ar.s = z;
					ar.c = null;
				}
			}
			else{
				if(z == null){
					ar.s  = y;
					ar.c = null;
					
				}
				else{
					ar.s = null;
					ar.c = y.unionPennant(z);
				}
				
			}
		}
		else{
			if(y == null){
				if(z  == null){
					ar.s  = x;
					ar.c = null;
					
				}
				else{
					ar.s = null;
					ar.c = x.unionPennant(z);
				}
			}
			else{
				if(z == null){
					ar.s  = null;
					ar.c = x.unionPennant(y);
					
				}
				else{
					ar.s = x;
					ar.c = y.unionPennant(z);
				}
				
			}
			
		}
		return ar;
	}
	
	
	
	public def BAG_UNION(b : BAG){
		var y : Pennant = null;
		var ar : AdderResult ;
		var i1 : Int,i2 : Int,i3 : Int;
		i1 = findBAGSIZE(this.size);
		i2 = findBAGSIZE(b.size);
		if(i1 > i2){
			i3 = i1 +1 ;
		}else{
			i3 = i2 +1;
		}
		for(var k : Int = 0 ; k <= i3 ; k++){
			ar = FA(this.backbone(k).p ,b.backbone(k).p,y);
			this.backbone(k).p = ar.s;
			y = ar.c;
		}
		this.size = this.size + b.size;
	}
	
	public def BAG_SPLIT() : BAG{
		var b : BAG = BAG_CREATE(r);
		var y : Pennant = this.backbone(0).p;
		this.backbone(0).p = null;
		for(var k :Int = 1 ; k <= r ; k++){
			if(this.backbone(k).p != null){
				b.backbone(k-1).p = this.backbone(k).p.splitPennant();
				this.backbone(k-1).p = this.backbone(k).p;
				this.backbone(k).p = null;
			}
			
		}
		
		
		
		if(y != null){
			this.BAG_INSERT(y);
		}
		
		if(size % 2 == 0){
			size = size /2 ;
			b.size = size;
		}
		else
		{
			
			b.size = size/2;
			size = b.size + 1  ;
			
		}
		
		return b;
	}
	
	
	public def BAG_IS_EMPTY() : Boolean{
		return size == 0;
	}
	
	public static def findBAGSIZE(var n : Int):Int{
		var i : Int = 0;
		while(n > 0 ){
			n = n/2;
			i++;
		}
		return i;
	}
	
	public def BAG_PROCESS(var OUT_BAG: BAG,d : Int ){
		
		if(size < GRAINSIZE){
			for(var i :Int = 0 ; i <= r ;i++){
				if(backbone(i).p != null){
					
					backbone(i).p.processPennant(OUT_BAG,d);
					
				}
				
			}
			return ;
		}
		var NEW_BAG : BAG;
		NEW_BAG = BAG_SPLIT();
		finish {
			val ob :BAG = new BAG(OUT_BAG.r);
			async {
				
				NEW_BAG.BAG_PROCESS(ob,d);
			}
			BAG_PROCESS(OUT_BAG,d);
			OUT_BAG.BAG_UNION(ob);
		}
		
		
	}
	
	
	public def BAG_PRINT(){
		for(var i :Int = 0 ; i <= r ;i++){
			if(backbone(i).p == null){
				Console.OUT.println("-");
			}
			else{
				
				backbone(i).p.printPennant();
				Console.OUT.println();
			}
			
		}
	}
	
}














public class BFS {

    /**
     * The main method for the Hello class
     */
	
	
    public static def main(a : Array[String](1)) {
    	var noofNodes : Int = 0;
    	var edge : Rail[String]();
    	val edges: ArrayList[Edge];
    	edges = new ArrayList[Edge]();
    	var G : Graph;
	var opt : Int = 0;
        var filename : String = " ";
    	try{
		if(a.size == 0){
			opt = 0;
			filename = "input.txt";
		}
		else if(a.size == 1){
			opt = 0;
			filename = a(0);
		}
		else if(a.size == 2){
			opt = Int.parse(a(1));
			filename = a(0);
		}
		
    		val inp = new File(filename);
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

	if(opt == 0){
		G.ParallelBFSQueue("0");
	}
	else{
		G.ParallelBFSBAG("0");
	}
    	
    	
    	
    		
    }
}

