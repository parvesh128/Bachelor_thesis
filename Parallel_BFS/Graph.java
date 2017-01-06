public class Graph
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Graph> _RTT = new x10.rtt.RuntimeType<Graph>(
    /* base class */Graph.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Graph";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 16
public x10.
          array.
          Array<Vertex>
          vertexList;
        
//#line 17
public int
          indexDone;
        
//#line 18
final public static int
          MAXINF =
          2147483647;
        
        
//#line 20
public Graph(final int num) {
            super();
            
//#line 15
this.__fieldInitializers101();
            
//#line 21
this.vertexList = ((x10.
              array.
              Array)(new x10.
              array.
              Array<Vertex>(Vertex._RTT,
                            num)));
            
//#line 22
this.indexDone = -1;
        }
        
        
//#line 26
public retType
                      isPresent(
                      final java.lang.String lblNode){
            
//#line 27
retType rt =
               null;
            
//#line 28
for (
//#line 28
int i =
                               0;
                             ((((int)(i))) < (((int)(indexDone))));
                             
//#line 28
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 30
if (((((Vertex)
                                    ((x10.
                                    array.
                                    Array<Vertex>)(vertexList)).apply$G((int)(i)))).
                                   label).equals(lblNode)) {
                    
//#line 32
rt = new retType(true,
                                                 i);
                    
//#line 33
return rt;
                }
            }
            
//#line 36
rt = new retType(false,
                                         -1);
            
//#line 37
return rt;
        }
        
        
//#line 41
public int
                      findIndex(
                      ){
            
//#line 42
Graph.__$closure$apply$__109(((Graph)(this)),
                                                     (int)(1));
            
//#line 43
return indexDone;
        }
        
        
//#line 47
public Vertex
                      getNode(
                      final java.lang.String lblNode){
            
//#line 48
int index =
               0;
            
//#line 49
retType rt =
               null;
            
//#line 50
rt = this.isPresent(((java.lang.String)(lblNode)));
            
//#line 51
if ((!(((boolean)(rt.
                                            b))))) {
                
//#line 53
index = this.findIndex();
                
//#line 54
final Vertex newVertex =
                  ((Vertex)(new Vertex(lblNode,
                                       index)));
                
//#line 55
((x10.
                  array.
                  Array<Vertex>)(vertexList)).set_0_$$x10$array$Array_T$G(((Vertex)(newVertex)),
                                                                          (int)(index));
                
//#line 56
return ((Vertex)
                                     ((x10.
                                     array.
                                     Array<Vertex>)(vertexList)).apply$G((int)(index)));
            } else {
                
//#line 59
Vertex v =
                   null;
                
//#line 60
v = ((x10.
                  array.
                  Array<Vertex>)(vertexList)).apply$G((int)(rt.
                                                              idx));
                
//#line 61
return v;
            }
        }
        
        
//#line 65
public void
                      addEdge(
                      final Vertex src,
                      final Vertex dest,
                      final double wt){
            
//#line 66
EdgeNode en =
               null;
            
//#line 67
en = new EdgeNode(dest,
                                          wt);
            
//#line 68
src.addEdge(((EdgeNode)(en)));
        }
        
        
//#line 71
public void
                      SerialBFS(
                      final Vertex src){
            
//#line 72
for (
//#line 72
int i =
                               0;
                             ((((int)(i))) < (((int)(((x10.
                               array.
                               Array<Vertex>)(vertexList)).size()))));
                             
//#line 72
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 73
if (((Vertex)
                                  ((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))).equals(src)) {
                    
//#line 74
((Vertex)
                                  ((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))).dist = 0;
                } else {
                    
//#line 77
((Vertex)
                                  ((x10.
                                  array.
                                  Array<Vertex>)(vertexList)).apply$G((int)(i))).dist = Graph.MAXINF;
                }
            }
            
//#line 80
final Queue q =
              ((Queue)(new Queue()));
            
//#line 82
q.ENQUEUE(((Vertex)(src)));
            
//#line 84
Vertex u =
               null;
            
//#line 85
EdgeNode en =
               null;
            
//#line 86
while ((!(((boolean)(q.isEmpty()))))) {
                
//#line 87
u = q.DEQUEUE();
                
//#line 88
for (
//#line 88
int i =
                                   0;
                                 ((((int)(i))) < (((int)(((x10.
                                   util.
                                   ArrayList<EdgeNode>)(u.
                                                          edgeList)).size()))));
                                 
//#line 88
i = ((((int)(i))) + (((int)(1))))) {
                    
//#line 89
en = ((x10.
                      util.
                      ArrayList<EdgeNode>)(u.
                                             edgeList)).get$G((int)(i));
                    {
                        
//#line 90
x10.
                          lang.
                          Runtime.ensureNotInAtomic();
                        {
                            
//#line 90
final Vertex[] $u117 =
                              new Vertex[1];
                            
//#line 90
$u117[0]=u;
                            
//#line 90
final EdgeNode[] $en118 =
                              new EdgeNode[1];
                            
//#line 90
$en118[0]=en;
                            
//#line 90
try {try {{
                                
//#line 90
x10.
                                  lang.
                                  Runtime.startFinish();
                                {
                                    
//#line 91
final x10.
                                      lang.
                                      Clock c1 =
                                      x10.
                                      lang.
                                      Clock.make();
                                    
//#line 92
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
                                                                                
//#line 92
EdgeNode p1$en118 =
                                                                                  ((EdgeNode)$en118[0]);
                                                                                
//#line 92
Vertex p1$u117 =
                                                                                  ((Vertex)$u117[0]);
                                                                                {
                                                                                    
//#line 93
if (((int) p1$en118.
                                                                                                             destVertex.
                                                                                                             dist) ==
                                                                                                    ((int) Graph.MAXINF)) {
                                                                                        
//#line 94
p1$en118.
                                                                                                      destVertex.dist = ((((int)(p1$u117.
                                                                                                                                   dist))) + (((int)(1))));
                                                                                        
//#line 95
q.ENQUEUE(((Vertex)(p1$en118.
                                                                                                                          destVertex)));
                                                                                    }
                                                                                    
//#line 97
x10.
                                                                                      lang.
                                                                                      Runtime.next();
                                                                                }
                                                                            }}catch (x10.runtime.impl.java.X10WrappedThrowable ex) {x10.lang.Runtime.pushException(ex);}}
                                                                            public x10.rtt.RuntimeType<?> getRTT() { return _RTT;}public x10.rtt.Type<?> getParam(int i) {return null;
                                                                            }
                                                                            });
                                }
                            }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__0__) {
                                
//#line 90
x10.
                                  lang.
                                  Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__0__)));
                                throw new x10.
                                  lang.
                                  RuntimeException();
                            }finally {{
                                 
//#line 90
x10.
                                   lang.
                                   Runtime.stopFinish();
                             }}
                            
//#line 90
u = ((Vertex)$u117[0]);
                            
//#line 90
en = ((EdgeNode)$en118[0]);
                            }
                        }
                    }
                }
            }
        
        
//#line 15
final private void
                      __fieldInitializers101(
                      ){
            
//#line 15
this.indexDone = 0;
        }
        
        final public static void
          __fieldInitializers101$P(
          final Graph Graph){
            Graph.__fieldInitializers101();
        }
        
        final private static int
          __$closure$apply$__109(
          final Graph x,
          final int y){
            
//#line 42
return x.indexDone = ((((int)(x.
                                                        indexDone))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__109$P(
          final Graph x,
          final int y){
            return Graph.__$closure$apply$__109(((Graph)(x)),
                                                (int)(y));
        }
        
    }
    