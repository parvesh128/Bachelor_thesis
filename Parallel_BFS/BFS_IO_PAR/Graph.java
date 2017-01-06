public class Graph
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Graph> _RTT = new x10.rtt.RuntimeType<Graph>(
    /* base class */Graph.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Graph";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 19
public x10.
          array.
          Array<Vertex>
          vertexList;
        
//#line 20
public int
          indexDone;
        
//#line 21
final public static int
          MAXINF =
          2147483647;
        
        
//#line 23
public Graph(final int num) {
            super();
            
//#line 18
this.__fieldInitializers156();
            
//#line 24
this.vertexList = ((x10.
              array.
              Array)(new x10.
              array.
              Array<Vertex>(Vertex._RTT,
                            num)));
            
//#line 25
this.indexDone = -1;
        }
        
        
//#line 29
public retType
                      isPresent(
                      final java.lang.String lblNode){
            
//#line 30
retType rt =
               null;
            
//#line 31
for (
//#line 31
int i =
                               0;
                             ((((int)(i))) <= (((int)(indexDone))));
                             
//#line 31
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 33
if (((((Vertex)
                                    ((x10.
                                    array.
                                    Array<Vertex>)(vertexList)).apply$G((int)(i)))).
                                   label).equals(lblNode)) {
                    
//#line 35
rt = new retType(true,
                                                 i);
                    
//#line 36
return rt;
                }
            }
            
//#line 39
rt = new retType(false,
                                         -1);
            
//#line 40
return rt;
        }
        
        
//#line 44
public int
                      findIndex(
                      ){
            
//#line 45
Graph.__$closure$apply$__216(((Graph)(this)),
                                                     (int)(1));
            
//#line 46
return indexDone;
        }
        
        
//#line 50
public Vertex
                      getNode(
                      final java.lang.String lblNode){
            
//#line 51
int index =
               0;
            
//#line 52
retType rt =
               null;
            
//#line 53
rt = this.isPresent(((java.lang.String)(lblNode)));
            
//#line 54
if ((!(((boolean)(rt.
                                            b))))) {
                
//#line 56
index = this.findIndex();
                
//#line 57
final Vertex newVertex =
                  ((Vertex)(new Vertex(lblNode,
                                       index)));
                
//#line 58
((x10.
                  array.
                  Array<Vertex>)(vertexList)).set_0_$$x10$array$Array_T$G(((Vertex)(newVertex)),
                                                                          (int)(index));
                
//#line 59
return ((Vertex)
                                     ((x10.
                                     array.
                                     Array<Vertex>)(vertexList)).apply$G((int)(index)));
            } else {
                
//#line 62
Vertex v =
                   null;
                
//#line 63
v = ((x10.
                  array.
                  Array<Vertex>)(vertexList)).apply$G((int)(rt.
                                                              idx));
                
//#line 64
return v;
            }
        }
        
        
//#line 68
public void
                      addEdge(
                      final Vertex src,
                      final Vertex dest,
                      final double wt){
            
//#line 69
EdgeNode en =
               null;
            
//#line 70
en = new EdgeNode(dest,
                                          wt);
            
//#line 71
src.addEdge(((EdgeNode)(en)));
        }
        
        
//#line 74
public void
                      ParallelBFSBAG(
                      final java.lang.String srclabel){
            
//#line 75
Vertex srcV =
              null;
            
//#line 76
x10.
              io.
              Console.OUT.println(((java.lang.Object)("-------------------BFS Using BAGS----------------")));
            {
                
//#line 78
x10.
                  lang.
                  Runtime.ensureNotInAtomic();
                {
                    
//#line 78
final Vertex[] $srcV223 =
                      new Vertex[1];
                    
//#line 78
$srcV223[0]=srcV;
                    
//#line 78
try {try {{
                        
//#line 78
x10.
                          lang.
                          Runtime.startFinish();
                        {
                            
//#line 78
for (
//#line 78
int i =
                                               0;
                                             ((((int)(i))) < (((int)(((x10.
                                               array.
                                               Array<Vertex>)(vertexList)).size()))));
                                             
//#line 78
i = ((((int)(i))) + (((int)(1))))) {
                                
//#line 79
final Vertex v;
                                
//#line 80
v = ((Vertex)(((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))));
                                
//#line 81
x10.
                                  lang.
                                  Runtime.runAsync(new x10.core.fun.VoidFun_0_0() {public final void apply() { try {{
                                                       
//#line 82
if ((v.
                                                                          label).equals(srclabel)) {
                                                           
//#line 83
$srcV223[0]=v;
                                                           
//#line 84
v.dist = 0;
                                                           
//#line 85
x10.
                                                             io.
                                                             Console.OUT.println(((java.lang.Object)((((((("Label ") + (v.
                                                                                                                          label))) + (" dist "))) + (((java.lang.Integer)(v.
                                                                                                                                                                            dist)))))));
                                                       } else {
                                                           
//#line 88
v.dist = Graph.MAXINF;
                                                       }
                                                   }}catch (x10.runtime.impl.java.X10WrappedThrowable ex) {x10.lang.Runtime.pushException(ex);}}
                                                   public x10.rtt.RuntimeType<?> getRTT() { return _RTT;}public x10.rtt.Type<?> getParam(int i) {return null;
                                                   }
                                                   });
                            }
                        }
                    }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__0__) {
                        
//#line 78
x10.
                          lang.
                          Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__0__)));
                        throw new x10.
                          lang.
                          RuntimeException();
                    }finally {{
                         
//#line 78
x10.
                           lang.
                           Runtime.stopFinish();
                     }}
                    
//#line 78
srcV = ((Vertex)$srcV223[0]);
                    }
                }
            
//#line 94
int d =
              0;
            
//#line 95
int n =
              BAG.findBAGSIZE((int)(((x10.
                                array.
                                Array<Vertex>)(vertexList)).size()));
            
//#line 96
BAG IN_BAG =
              new BAG(n);
            
//#line 98
IN_BAG.BAG_INSERT(((Vertex)(srcV)));
            
//#line 100
Vertex u =
               null;
            
//#line 101
EdgeNode en =
               null;
            
//#line 104
while ((!(((boolean)(IN_BAG.BAG_IS_EMPTY()))))) {
                
//#line 105
BAG OUT_BAG =
                  BAG.BAG_CREATE((int)(n));
                
//#line 106
IN_BAG.BAG_PROCESS(((BAG)(OUT_BAG)),
                                                (int)(d));
                
//#line 107
d = ((((int)(d))) + (((int)(1))));
                
//#line 108
IN_BAG = OUT_BAG;
            }
            }
        
        
//#line 113
public void
                       ParallelBFSQueue(
                       final java.lang.String srclabel){
            
//#line 114
Vertex srcV =
              null;
            
//#line 115
x10.
              io.
              Console.OUT.println(((java.lang.Object)("----------------------BFS using Queue-----------------")));
            {
                
//#line 116
x10.
                  lang.
                  Runtime.ensureNotInAtomic();
                {
                    
//#line 116
final Vertex[] $srcV224 =
                      new Vertex[1];
                    
//#line 116
$srcV224[0]=srcV;
                    
//#line 116
try {try {{
                        
//#line 116
x10.
                          lang.
                          Runtime.startFinish();
                        {
                            
//#line 116
for (
//#line 116
int i =
                                                0;
                                              ((((int)(i))) < (((int)(((x10.
                                                array.
                                                Array<Vertex>)(vertexList)).size()))));
                                              
//#line 116
i = ((((int)(i))) + (((int)(1))))) {
                                
//#line 117
final Vertex v;
                                
//#line 118
v = ((Vertex)(((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))));
                                
//#line 119
x10.
                                  lang.
                                  Runtime.runAsync(new x10.core.fun.VoidFun_0_0() {public final void apply() { try {{
                                                       
//#line 120
if ((v.
                                                                           label).equals(srclabel)) {
                                                           
//#line 121
$srcV224[0]=v;
                                                           
//#line 122
v.dist = 0;
                                                           
//#line 123
x10.
                                                             io.
                                                             Console.OUT.println(((java.lang.Object)((((((("Label ") + (v.
                                                                                                                          label))) + (" dist "))) + (((java.lang.Integer)(v.
                                                                                                                                                                            dist)))))));
                                                       } else {
                                                           
//#line 126
v.dist = Graph.MAXINF;
                                                       }
                                                   }}catch (x10.runtime.impl.java.X10WrappedThrowable ex) {x10.lang.Runtime.pushException(ex);}}
                                                   public x10.rtt.RuntimeType<?> getRTT() { return _RTT;}public x10.rtt.Type<?> getParam(int i) {return null;
                                                   }
                                                   });
                            }
                        }
                    }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__1__) {
                        
//#line 116
x10.
                          lang.
                          Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__1__)));
                        throw new x10.
                          lang.
                          RuntimeException();
                    }finally {{
                         
//#line 116
x10.
                           lang.
                           Runtime.stopFinish();
                     }}
                    
//#line 116
srcV = ((Vertex)$srcV224[0]);
                    }
                }
            
//#line 131
final Queue q =
              ((Queue)(new Queue()));
            
//#line 133
q.ENQUEUE(((Vertex)(srcV)));
            
//#line 135
Vertex u =
               null;
            
//#line 136
EdgeNode en =
               null;
            
//#line 139
while ((!(((boolean)(q.isEmpty()))))) {
                
//#line 140
u = q.DEQUEUE();
                
//#line 142
for (
//#line 142
int i =
                                    0;
                                  ((((int)(i))) < (((int)(((x10.
                                    util.
                                    ArrayList<EdgeNode>)(u.
                                                           edgeList)).size()))));
                                  
//#line 142
i = ((((int)(i))) + (((int)(1))))) {
                    
//#line 143
en = ((x10.
                      util.
                      ArrayList<EdgeNode>)(u.
                                             edgeList)).get$G((int)(i));
                    {
                        
//#line 144
x10.
                          lang.
                          Runtime.ensureNotInAtomic();
                        {
                            
//#line 144
final EdgeNode[] $en225 =
                              new EdgeNode[1];
                            
//#line 144
$en225[0]=en;
                            
//#line 144
final Vertex[] $u226 =
                              new Vertex[1];
                            
//#line 144
$u226[0]=u;
                            
//#line 144
try {try {{
                                
//#line 144
x10.
                                  lang.
                                  Runtime.startFinish();
                                {
                                    
//#line 145
final x10.
                                      lang.
                                      Clock c1 =
                                      x10.
                                      lang.
                                      Clock.make();
                                    
//#line 147
if (((((int) ((EdgeNode)$en225[0]).
                                                                destVertex.
                                                                dist) ==
                                                       ((int) Graph.MAXINF))) &&
                                                     (((!(((boolean)(((EdgeNode)$en225[0]).
                                                                       destVertex.
                                                                       visited))))))) {
                                        
//#line 148
x10.
                                          lang.
                                          Runtime.runAsync_0_$_x10$lang$Clock_$(((x10.
                                                                                  array.
                                                                                  Array)(x10.core.RailFactory.<x10.
                                                                                  lang.
                                                                                  Clock>makeArrayFromJavaArray(x10.lang.Clock._RTT, new x10.
                                                                                  lang.
                                                                                  Clock[] {c1}))),
                                                                                new x10.core.fun.VoidFun_0_0() {public final void apply() { try {{
                                                                                    
//#line 148
EdgeNode p1$en225 =
                                                                                      ((EdgeNode)$en225[0]);
                                                                                    
//#line 148
Vertex p1$u226 =
                                                                                      ((Vertex)$u226[0]);
                                                                                    {
                                                                                        
//#line 149
p1$en225.
                                                                                                       destVertex.dist = ((((int)(p1$u226.
                                                                                                                                    dist))) + (((int)(1))));
                                                                                        
//#line 150
p1$en225.
                                                                                                       destVertex.visited = true;
                                                                                        
//#line 151
q.ENQUEUE(((Vertex)(p1$en225.
                                                                                                                           destVertex)));
                                                                                        
//#line 152
x10.
                                                                                          io.
                                                                                          Console.OUT.println(((java.lang.Object)((((((("Label ") + (p1$en225.
                                                                                                                                                       destVertex.
                                                                                                                                                       label))) + (" dist "))) + (((java.lang.Integer)(p1$en225.
                                                                                                                                                                                                         destVertex.
                                                                                                                                                                                                         dist)))))));
                                                                                        
//#line 153
x10.
                                                                                          lang.
                                                                                          Runtime.resume();
                                                                                    }
                                                                                }}catch (x10.runtime.impl.java.X10WrappedThrowable ex) {x10.lang.Runtime.pushException(ex);}}
                                                                                public x10.rtt.RuntimeType<?> getRTT() { return _RTT;}public x10.rtt.Type<?> getParam(int i) {return null;
                                                                                }
                                                                                });
                                    }
                                }
                            }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__2__) {
                                
//#line 144
x10.
                                  lang.
                                  Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__2__)));
                                throw new x10.
                                  lang.
                                  RuntimeException();
                            }finally {{
                                 
//#line 144
x10.
                                   lang.
                                   Runtime.stopFinish();
                             }}
                            
//#line 144
en = ((EdgeNode)$en225[0]);
                            
//#line 144
u = ((Vertex)$u226[0]);
                            }
                        }
                    }
                }
            }
            
            
//#line 18
final private void
                          __fieldInitializers156(
                          ){
                
//#line 18
this.indexDone = 0;
            }
            
            final public static void
              __fieldInitializers156$P(
              final Graph Graph){
                Graph.__fieldInitializers156();
            }
            
            final private static int
              __$closure$apply$__216(
              final Graph x,
              final int y){
                
//#line 45
return x.indexDone = ((((int)(x.
                                                            indexDone))) + (((int)(y))));
            }
            
            final public static int
              __$closure$apply$__216$P(
              final Graph x,
              final int y){
                return Graph.__$closure$apply$__216(((Graph)(x)),
                                                    (int)(y));
            }
        
        }
        