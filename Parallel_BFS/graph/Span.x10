/**
C) IBM Corporation 2007.
This code implements three algorithms that compute the spanning tree of a random
connected graph. It can be used to test X10's support for fine-grained parallelism.

To compile the code:
 1) javac X10AtomicInt.java (If it hasn't been compiled by javac)
 2) x10c -classpath . Span.x10

To run the code:
 1) x10 -classpath . Span

Author: Cong Guojing (IBM Research)

Modified by: Tong Wen (IBM Research)
  May 2007:
	Add comments
	Cosmetic changes
	Correction bugs: adding finish before foreach loop; replace "foreach" with "while" 
			in SV_twophase 	
  July 2007:
	  add SV_twophase_partition().

**/

/* vertex */
class V {
	public int parent;
	public int degree;
	public int [] neighbors;
	public int label;
	public V(){}
}

/* wripper of java array */
class IntJavaArray{ 
	public int [] D1;
	public IntJavaArray(){}
}

/* edge */
class E{
	public int v1,v2;
	public boolean intree;
	public E(int u1, int u2){ v1=u1;v2=u2;intree=false;}
}


public class Span{
	const int N=1000, M=4000; //N is the number of vertexes and M is the number of edges
	int m;
	final V [] G;
	final E [] El;
	final E [.] El1;
	final int [] color;
	int ncomps=0;
	boolean changed=true;
	final X10AtomicInt [] atmInts;
	final int NUMWORKERS;
	
	public Span (int numWorkers){
		NUMWORKERS = numWorkers;
		int i,j;
		int [] D,stack,conncomps;
		int [] parent;
		IntJavaArray [] NB; 
		
		/* Construction of the tree and make it connected */
		El = new E [M];
		for(i=0;i<M;i++){
			El[i]=new E ((int) (Math.random()*N)%N, (int) (Math.random()*N)%N);
		}
		
		D = new int [N];
		stack = new int [N];
		
		for(i=0;i<N;i++) D[i]=0;
		for(i=0;i<M;i++){
			D[El[i].v1]++;
			D[El[i].v2]++;
		}
		
		NB = new IntJavaArray [N];
	
		for(i=0;i<N;i++) {
			NB[i]=new IntJavaArray();
			NB[i].D1 =new int [D[i]+2]; /* leave room for making connected graph by +2*/
			for(j=0;j<D[i]+2;j++)
			{
				NB[i].D1[j]=0;
			}
		}
		
				  
		for(i=0;i<N;i++) D[i]=0;
		
		m=0;
		for(i=0;i<M;i++)
		{
			int r=0;    
		        for(j=0;j<D[El[i].v1];j++){ 
		        	if(El[i].v2==NB[El[i].v1].D1[j]) r=1;
		        }
		        if(r==1){
		        	El[i].v1=El[i].v2=-1; 
		        	continue;
		        }
		        m++;
		        NB[El[i].v1].D1[D[El[i].v1]]=El[i].v2;
		        NB[El[i].v2].D1[D[El[i].v2]]=El[i].v1;
		        D[El[i].v1]++;
		        D[El[i].v2]++;
		}  

		color = new int [N];
		stack = new int [N]; 
		conncomps  = new int [N]; 

		for(i=0;i<N;i++)  color[i]=0;
		int top=-1;
		ncomps=0;
		
		for(i=0;i<N;i++)
		{
			int v;
			if(color[i]==1) continue;
			else conncomps[ncomps++]=i;

			stack[++top]=i;
			color[i]=1;
			while(top!=-1) {
				v = stack[top];
				top--;

				for(j=0;j<D[v];j++)
					if(color[NB[v].D1[j]]==0){
						top++;
						stack[top]=NB[v].D1[j];
						color[NB[v].D1[j]]=1;
					}
			}
		}
		
		System.out.println("ncomps="+ncomps);
		El1 = new E [[0:m+ncomps-2]]; 
		for(i=0;i<N;i++) color[i]=0;	
		for(i=0,j=0;i<M;i++)
			if(El[i].v1!=-1) El1[j++]=El[i]; 
		if(j!=m) System.out.println("Remove duplicates failed");
		else System.out.println("Remove duplicates succeeded,j=m="+j);
		
		for(i=0;i<ncomps-1;i++)
		{
			NB[conncomps[i]].D1[D[conncomps[i]]++]=conncomps[i+1];
			NB[conncomps[i+1]].D1[D[conncomps[i+1]]++]=conncomps[i];
			El1[i+m]=new E (conncomps[i], conncomps[i+1]);
		}
		
		G = new V[N];
		for(i=0;i<N;i++)
		{			
			G[i]=new V();
			G[i].degree=D[i];
			G[i].neighbors=new int [D[i]];
			G[i].label = N;
			G[i].parent = i;
			for(j=0;j<D[i];j++)
				G[i].neighbors[j]=NB[i].D1[j];
		}

		atmInts = new X10AtomicInt [N]; //(point [i]) {return new X10AtomicInt (i);}; //X10 array doesn't work here		
	}
	
	public static void main(String[] args) {
		int numWorkers = 1;
		for (int q = 0; q < args.length; ++q)		
			if (args[q].equals("-w") || args[q].equals("-W")) {
				++q;
				numWorkers = java.lang.Integer.parseInt(args[q]);
			}
			new Span(numWorkers).run(0);		
	}
	
	void run(int root) {
		for(int i=0;i<N;i++)
			atmInts[i] = new X10AtomicInt (0);
		atmInts[root] = new X10AtomicInt (1);
	    	traverse(root);
	    	System.out.println("Verifying traverse ..."+verify_traverse(root));
		System.out.println("NumWorkers = "+ NUMWORKERS);
		SV_twophase_partition(NUMWORKERS);
		System.out.println("Verifying SV_2phase ..."+verify_SV());
		
		BFS(root);
		System.out.println("Verifying BFS ... "+verify_BFS());
	    } 
	   
	    
	    void SV_twophase (){
	    	final int [.] D1 = new int [[0:N-1]] (point [i]){ return i;};
	    	final int [.] ID = new int [[0:N-1]] (point [i]){ return -1;};
	    	/*foreach(point [i]: ID.region){
	    		ID[i]=-1;
	    	}*/
	    	
	    	System.out.println(" edge region="+El1.region);
	    	changed=true;
		//int loop=0;
	    	while(changed){
	    		//System.out.println("This is loop "+(++loop));
	    		changed = false;
	    		/* Choose the edges competitively; the output is nondeterministic. */
	    		finish foreach(point [i]: El1.region){
				final int v1=El1[i].v1, v2=El1[i].v2;
	    			if(D1[v1] < D1[v2] && D1[v2]==D1[D1[v2]]) {	
	    					ID[D1[v2]]=i;
	    			}
	    				    			
	    			if(D1[v2] < D1[v1] && D1[v1]==D1[D1[v1]]) {
	    					
	    					ID[D1[v1]]=i;
	    			}
	    		}
	    		/* Mark the edges included in the spanning tree; the second equal relationship is redundant?*/
	    		finish foreach(point [i]: El1.region){
				final int v1=El1[i].v1, v2=El1[i].v2;
	    			if(D1[v1] < D1[v2] && D1[v2]==D1[D1[v2]] && ID[D1[v2]]==i) {
    					D1[D1[v2]]=D1[v1];
    					El1[i].intree=true;
    					changed=true;
	    			}
	    			if(D1[v2] < D1[v1] && D1[v1]==D1[D1[v1]] && ID[D1[v1]]==i) {
	    				D1[D1[v1]]=D1[v2];
	    			    	El1[i].intree=true;
	    			    	changed=true;
	    			}
	    		}
			/*Make sure the labels of each group is the same.*/
	    		finish foreach(point [i]:D1.region) {
	    			while (D1[D1[i]]!=D1[i]) D1[i]=D1[D1[i]];
	    		}
	    	}
	    }

	    void SV_twophase_partition(final int numWorkers){
	    	final int [.] D1 = new int [[0:N-1]] (point [i]){ return i;};
	    	final int [.] ID = new int [[0:N-1]] (point [i]){ return -1;};
	    
	    	System.out.println(" edge region="+El1.region);
	    	
	    	final region(:rank==1 && self.rect) Workers = [0 : numWorkers - 1]; 
	    	/* partition the edges */
	    	final int edgeSize = El1.region.size();
	    	final int localEdgeSize = edgeSize/numWorkers;
	    	final region(:rank==1 && self.rect) [.] MyEdges = 
	    		new region [Workers] (point [i]){ return [i*localEdgeSize :(i+1)*localEdgeSize-1];};
	    	if (localEdgeSize*numWorkers != edgeSize) MyEdges[numWorkers-1] = [(numWorkers-1)*localEdgeSize : edgeSize-1];	
	    	/* partition the vertexes */
	    	final int localVertexSize = N/numWorkers;
	    	final region(:rank==1 && self.rect) [.] MyVertices = 
	    		new region [Workers] (point [i]){ return [i*localVertexSize : (i+1)*localVertexSize-1];};
	    	if (localVertexSize*numWorkers != N) MyVertices[numWorkers-1] = [(numWorkers-1)*localVertexSize : N-1];	
	    	
		finish async {
		    final clock ck = clock.factory.clock();
		    foreach (point [j] : Workers) clocked (ck) {
			boolean localChanged = true;
			changed = true;
			next;
			while (localChanged) {
			    changed = false;
			    localChanged = false;
			    for (point [i] : MyEdges[j]) {
				final int v1=El1[i].v1, v2=El1[i].v2;
				if(D1[v1] < D1[v2] && D1[v2]==D1[D1[v2]]) ID[D1[v2]]=i;
				if(D1[v2] < D1[v1] && D1[v1]==D1[D1[v1]]) ID[D1[v1]]=i;
			    }
			    next;
			    for (point [i] : MyEdges[j]) {
				final int v1=El1[i].v1, v2=El1[i].v2;
				if(D1[v1] < D1[v2] && D1[v2]==D1[D1[v2]] && ID[D1[v2]]==i) {
				    D1[D1[v2]]=D1[v1];
				    El1[i].intree=true;
				    localChanged=true;
				}
				if(D1[v2] < D1[v1] && D1[v1]==D1[D1[v1]] && ID[D1[v1]]==i) {
				    D1[D1[v1]]=D1[v2];
				    El1[i].intree=true;
				    localChanged=true;
				}			
			    }
			    next;
			    if (localChanged) changed = true;
			    next;
                            /*Make sure the labels of each group is the same.*/
			    for (point [i] : MyVertices[j]) 
				while (D1[D1[i]]!=D1[i]) D1[i]=D1[D1[i]]; 
			    next;
			    if (localChanged == false)
			    	if (changed) localChanged = true;
			}  // while
		    } // foreach
		} // finish asyn
	    }
	    
	    boolean verify_SV()
	    {
	    	int i,sum=0;
	    	for(i=0;i<m+ncomps-1;i++) if(El1[i].intree) sum++;
		System.out.println(" sum = "+sum);
	    	if(sum<N-1){
	    		System.out.println("verify_SV failed " + sum);
	    		return(false);
	    	}
	    	//System.out.println("verify_SV succeeded");
	    	return(true);
	    }
	    /* Travel down from the root of the spanning tree */
	    void traverse(int u) {
    		int k,v;
	    	finish for(k=0;k<G[u].degree;k++)
    		{
    			v=G[u].neighbors[k];
    			if(atmInts[v].compareAndSet(0,1)) {
    				G[v].parent=u;
    				final int V=v;
    				async { 
    					//x10.lang.perf.addLocalOps(1);
    					traverse(V);
    				}
    			}
    		}
	    }
	    
	    boolean verify_traverse(int root)
	    {
	    	int count =0;
	    	int [] D;
	    	int i;
	    	
	    	D = new int [N];
	    	for(i=0;i<N;i++)
	    	{
	    		D[i]=G[i].parent;
	    	}
	    	for(i=0;i<N;i++)
	    	{
	    		while(D[i]!=D[D[i]]) D[i]=D[D[i]];
	    	}
	    	for(i=0;i<N;i++)
	    		if(D[i]!=root) {
	    			System.out.println("verify_traverse failed at "+i);
	    			return(false);
	    		}
	    	//System.out.println("verify_traverse succeeded");
	    	return(true);
	    }
	    /* An implementation of Breadth First Search of a connected graph
	     * Each vertex is marked by its distance from the root.
	     */
	    void BFS(int u) {
	    	
	    	int maxBufferSize = N;
	    	final int [] bufferRed = new int [maxBufferSize];
	    	final int [] bufferBlack = new int [maxBufferSize];
	    
	    	int bufferSize = 1;
	    	final int [] bufferSizes = {maxBufferSize, bufferSize};
	    	/* initialize the first level */
	    	bufferRed[0] = u;
	    	int l = 0;
	    	G[u].label = l;
	    	while (bufferSize >0){
	    		bufferSizes[1] = 0; //size of bufferB
	    		final int lbl = ++l;
	    		/* compute the vertexes at the next level */
	    		finish foreach (point [i]:[0:bufferSize-1]){ //for each vertex at the current level
	    			int j, idx;
	    			V vertexA, vertexB;
	    			final int [] bufferA, bufferB;
	    			/* bufferA contains the vertexes at the current level;
	    			 * bufferB stores the vertexes at the next level.
	    			 */
	    			if (lbl%2 ==1) {
	    				bufferA = bufferRed; bufferB = bufferBlack;
	    			}
	    			else{
	    				bufferA = bufferBlack; bufferB = bufferRed;
	    			}
	    			vertexA = G[bufferA[i]];
	    			for (j=0; j<vertexA.degree; j++){ //for each neighbor of vertexA
	    				idx = vertexA.neighbors[j];
	    				vertexB = G[idx];
	    				if (vertexB.label == N){ //If not marked before, mark it and put it into buffer
	    					vertexB.label = lbl;
	    					atomic {
	    						bufferB[bufferSizes[1]] = idx;
	    						bufferSizes[1] ++;
	    					}
	    				}
	    				
	    				/*if (bufferSize == maxBufferSize - 1){ //in case buffer is not large enougth
	    					atomic{
	    						maxBufferSize+=10;
	    						int [] oldBuffer = buffer;
	    						buffer = new int [maxBufferSize];
	    						for (int k = 0;k < maxBufferSize; k++)
	    							buffer[k] = oldBuffer[k];
	    					}
	    					
	    				}*/
	    			}
	    		}
	    		bufferSize = bufferSizes[1];
	    		System.out.println("BFS level = ="+l+" bufferSize = "+bufferSize);
	    	}
	    }
	    
	    boolean verify_BFS(){
	    	int countBFS = 0;
	    	int countGraph = 0;
	    	for (int i=0;i<N; i++){
	    		if (G[i].label < N) countBFS++;
	    		if (G[i].degree >0) countGraph++;
	    	}	
	    	System.out.println("verify_BFS labeled vertexes = "+countBFS +" Connected vertexes = "+ countGraph);
	    	return countBFS == N;
	    	
	    }
}
