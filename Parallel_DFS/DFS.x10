import  x10.io.*;
import x10.io.Console;
import x10.util.*;
import x10.lang.Math;

class NodeVal{
	var value : Int;
	public def this(v : Int){
		value = v;
	}
}

class Node{
	var nv : NodeVal;
	var parentnode : Node;
	val childnodeList :ArrayList[Node];
	var dist : Int;
	
	var childtobevisited : Int;
	
	
	public def this(pn : Node , nv : NodeVal){
		parentnode = pn;
		this.nv = nv;
		childnodeList = new ArrayList[Node]();
		
		
		childtobevisited = 0;
		
	}
	
	public def addChild(cn : Node){
		childnodeList.add(cn);
	}
	
	
	public def visit(){
		if (parentnode != null){
			this.dist = parentnode.dist + 1;
			Console.OUT.println(this.nv.value);
		}
		else{
			this.dist = 0;
		}
	}
	public def visitChild() : Node{
		var n : Node;
		if(childtobevisited < childnodeList.size()){
			//Console.OUT.println("CHild nodeList size" + childnodeList.size());
			 n = childnodeList.get(childtobevisited);
			 n.visit();
			childtobevisited++;
			
			return n;
		}
		else{
			return parentnode;
		}
		
		
	}
	
}


class Tree{
	var root : Node;
	var size : Int;
	public def this(rootNodeVal : NodeVal){
		root = new Node(null,rootNodeVal);
	}
	
	public static def serialDFS(root : Node){
		var n : Node;
		if(root != null){
			n = root.visitChild();
			serialDFS(n);
		}
			
			
		
		
	}
	
	/*public def ParallelDFSBAG(  ){
		
		var d : Int = 0;
		var n : Int = BAG.findBAGSIZE(size);
		var IN_BAG:BAG = new BAG(n);

		IN_BAG.BAG_INSERT(root);

		
		

		while(!IN_BAG.BAG_IS_EMPTY()){
			var OUT_BAG :BAG=  BAG.BAG_CREATE(n);
			IN_BAG.BAG_PROCESS(OUT_BAG);
			
			IN_BAG = OUT_BAG;
		}
	}
	*/

	
	
}


class Node_Penn{
	var v : Node;
	var lt : Node_Penn ;
	var rt : Node_Penn ;
	public def this(v : Node , lt : Node_Penn , rt : Node_Penn){
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
	
	public def this(v : Node){
		
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
	
	/*private def processPennantNode(p : Node_Penn,var OUT_BAG: BAG,d : Int){
		
		var en: EdgeNode;
		if (p != null){
			var u : Node;
			u = p.v;
			for(var i :Int = 0 ; i < u.edgeList.size();i++){
				en = u.edgeList.get(i);
				finish{
					val c1 = Clock.make();
					val ob : BAG = new BAG(OUT_BAG.r);
					if((en.destNode.dist == Graph.MAXINF) && (!en.destNode.visited)){
						async clocked(c1){
							
							en.destNode.dist = u.dist + 1;
							en.destNode.visited = true;
							ob.BAG_INSERT(en.destNode);
							Console.OUT.println("Label " + en.destNode.label + " dist " + en.destNode.dist); 
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
	
	*/
	private def printPennantNode(p : Node_Penn){
		if (p != null){
			Console.OUT.print(p.v.nv.value.toString() +" ");
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
	
	public def BAG_INSERT(x : Node){
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
					
					//backbone(i).p.processPennant(OUT_BAG,d);
					
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





 class _Stack[T] extends Stack[T]{
	 public def this() { super(); }
	 public def print(){
		 while(peek() != null ){
			 //Console.OUT.println( ((BAG)pop()).BAG_PRINT());
		 }
		 
	 }
 }

public class DFS {
	public static def main(Array[String]) {
		
		/*var s :_Stack[Int] = new _Stack[Int]();
		for(var i :Int= 0 ; i < 10 ; i++){
			s.push(i);
		}
		
		s.print();
		*/
		
		var nv : NodeVal;
		var n : Node , n1 : Node , n2 : Node , n3 : Node;
		nv = new NodeVal(1);
		n = new Node(null,nv);
		n2 = n;
		nv = new NodeVal(2); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(3); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(4); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		
		n = n.childnodeList.get(0);
		nv = new NodeVal(5); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(6); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(7); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		
		n = n.childnodeList.get(0);
		nv = new NodeVal(8); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(9); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(10); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		
		n = n.childnodeList.get(0);
		nv = new NodeVal(11); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(12); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		nv = new NodeVal(13); 
		n1 = new Node(n,nv);
		n.addChild(n1);
		
		
		
		n = n2;

		Console.OUT.println("Hello, World!");
		Tree.serialDFS(n);
		
		
		
	}
}
