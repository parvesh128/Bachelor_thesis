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
this.__fieldInitializers133();
            
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
Graph.__$closure$apply$__176(((Graph)(this)),
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
                      ParallelBFSQueue(
                      final java.lang.String srclabel){
            
//#line 75
Vertex srcV =
              null;
            
//#line 76
for (
//#line 76
int i =
                               0;
                             ((((int)(i))) < (((int)(((x10.
                               array.
                               Array<Vertex>)(vertexList)).size()))));
                             
//#line 76
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 77
if (((((Vertex)
                                    ((x10.
                                    array.
                                    Array<Vertex>)(vertexList)).apply$G((int)(i)))).
                                   label).equals(srclabel)) {
                    
//#line 78
srcV = ((x10.
                      array.
                      Array<Vertex>)(vertexList)).apply$G((int)(i));
                    
//#line 79
((Vertex)
                                  ((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))).dist = 0;
                    
//#line 80
x10.
                      io.
                      Console.OUT.println(((java.lang.Object)((((((("Label ") + ((((Vertex)
                                                                                    ((x10.
                                                                                    array.
                                                                                    Array<Vertex>)(vertexList)).apply$G((int)(i)))).
                                                                                   label))) + (" dist "))) + (((java.lang.Integer)((((Vertex)
                                                                                                                                      ((x10.
                                                                                                                                      array.
                                                                                                                                      Array<Vertex>)(vertexList)).apply$G((int)(i)))).
                                                                                                                                     dist)))))));
                } else {
                    
//#line 83
((Vertex)
                                  ((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))).dist = Graph.MAXINF;
                }
            }
            
//#line 86
final Queue q =
              ((Queue)(new Queue()));
            
//#line 88
q.ENQUEUE(((Vertex)(srcV)));
            
//#line 90
Vertex u =
               null;
            
//#line 91
EdgeNode en =
               null;
            
//#line 94
while ((!(((boolean)(q.isEmpty()))))) {
                
//#line 95
u = q.DEQUEUE();
                
//#line 97
for (
//#line 97
int i =
                                   0;
                                 ((((int)(i))) < (((int)(((x10.
                                   util.
                                   ArrayList<EdgeNode>)(u.
                                                          edgeList)).size()))));
                                 
//#line 97
i = ((((int)(i))) + (((int)(1))))) {
                    
//#line 98
en = ((x10.
                      util.
                      ArrayList<EdgeNode>)(u.
                                             edgeList)).get$G((int)(i));
                    {
                        
//#line 99
x10.
                          lang.
                          Runtime.ensureNotInAtomic();
                        {
                            
//#line 99
final Vertex[] $u180 =
                              new Vertex[1];
                            
//#line 99
$u180[0]=u;
                            
//#line 99
final EdgeNode[] $en181 =
                              new EdgeNode[1];
                            
//#line 99
$en181[0]=en;
                            
//#line 99
try {try {{
                                
//#line 99
x10.
                                  lang.
                                  Runtime.startFinish();
                                {
                                    
//#line 100
final x10.
                                      lang.
                                      Clock c1 =
                                      x10.
                                      lang.
                                      Clock.make();
                                    
//#line 102
if (((((int) ((EdgeNode)$en181[0]).
                                                                destVertex.
                                                                dist) ==
                                                       ((int) Graph.MAXINF))) &&
                                                     (((!(((boolean)(((EdgeNode)$en181[0]).
                                                                       destVertex.
                                                                       visited))))))) {
                                        
//#line 103
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
                                                                                    
//#line 103
EdgeNode p1$en181 =
                                                                                      ((EdgeNode)$en181[0]);
                                                                                    
//#line 103
Vertex p1$u180 =
                                                                                      ((Vertex)$u180[0]);
                                                                                    {
                                                                                        
//#line 104
p1$en181.
                                                                                                       destVertex.dist = ((((int)(p1$u180.
                                                                                                                                    dist))) + (((int)(1))));
                                                                                        
//#line 105
p1$en181.
                                                                                                       destVertex.visited = true;
                                                                                        
//#line 106
q.ENQUEUE(((Vertex)(p1$en181.
                                                                                                                           destVertex)));
                                                                                        
//#line 107
x10.
                                                                                          io.
                                                                                          Console.OUT.println(((java.lang.Object)((((((("Label ") + (p1$en181.
                                                                                                                                                       destVertex.
                                                                                                                                                       label))) + (" dist "))) + (((java.lang.Integer)(p1$en181.
                                                                                                                                                                                                         destVertex.
                                                                                                                                                                                                         dist)))))));
                                                                                        
//#line 108
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
                            }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__0__) {
                                
//#line 99
x10.
                                  lang.
                                  Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__0__)));
                                throw new x10.
                                  lang.
                                  RuntimeException();
                            }finally {{
                                 
//#line 99
x10.
                                   lang.
                                   Runtime.stopFinish();
                             }}
                            
//#line 99
u = ((Vertex)$u180[0]);
                            
//#line 99
en = ((EdgeNode)$en181[0]);
                            }
                        }
                    }
                }
            }
        
        
//#line 18
final private void
                      __fieldInitializers133(
                      ){
            
//#line 18
this.indexDone = 0;
        }
        
        final public static void
          __fieldInitializers133$P(
          final Graph Graph){
            Graph.__fieldInitializers133();
        }
        
        final private static int
          __$closure$apply$__176(
          final Graph x,
          final int y){
            
//#line 45
return x.indexDone = ((((int)(x.
                                                        indexDone))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__176$P(
          final Graph x,
          final int y){
            return Graph.__$closure$apply$__176(((Graph)(x)),
                                                (int)(y));
        }
        
    }
    