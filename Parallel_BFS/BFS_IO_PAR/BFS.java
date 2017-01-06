











public class BFS
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<BFS> _RTT = new x10.rtt.RuntimeType<BFS>(
    /* base class */BFS.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "BFS";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
        
//#line 620
public static class Main extends x10.runtime.impl.java.Runtime {
        public static void main(java.lang.String[] args) {
        // start native runtime
        new Main().start(args);
        }
        
        // called by native runtime inside main x10 thread
        public void main(final x10.array.Array<java.lang.String> args) {
        try {
        // start xrx
        x10.lang.Runtime.start(
        // static init activity
        new x10.core.fun.VoidFun_0_0() {
        public void apply() {
        // preload classes
        if (Boolean.getBoolean("x10.PRELOAD_CLASSES")) {
        x10.runtime.impl.java.PreLoader.preLoad(this.getClass().getEnclosingClass(), Boolean.getBoolean("x10.PRELOAD_STRINGS"));
        }
        }
        public x10.rtt.RuntimeType<?> getRTT() {
        return _RTT;
        }
        public x10.rtt.Type<?> getParam(int i) {
        return null;
        }
        },
        // body of main activity
        new x10.core.fun.VoidFun_0_0() {
        public void apply() {
        // catch and rethrow checked exceptions
        // (closures cannot throw checked exceptions)
        try {
        // call the original app-main method
        BFS.main(args);
        } catch (java.lang.RuntimeException e) {
        throw e;
        } catch (java.lang.Error e) {
        throw e;
        } catch (java.lang.Throwable t) {
        throw new x10.runtime.impl.java.X10WrappedThrowable(t);
        }
        }
        public x10.rtt.RuntimeType<?> getRTT() {
        return _RTT;
        }
        public x10.rtt.Type<?> getParam(int i) {
        return null;
        }
        });
        } catch (java.lang.Throwable t) {
        t.printStackTrace();
        }
        }
        }
        
        // the original app-main method
        public static void main(final x10.
          array.
          Array<java.lang.String> a)  {
            
//#line 621
int noofNodes =
              0;
            
//#line 622
x10.core.Rail<java.lang.String> edge =
               null;
            
//#line 623
final x10.
              util.
              ArrayList<Edge> edges;
            
//#line 624
edges = ((x10.
              util.
              ArrayList)(new x10.
              util.
              ArrayList<Edge>(Edge._RTT)));
            
//#line 625
Graph G =
               null;
            
//#line 626
int opt =
              0;
            
//#line 627
java.lang.String filename =
              " ";
            
//#line 628
try {{
                
//#line 629
if (((int) a.
                                          size) ==
                                 ((int) 0)) {
                    
//#line 630
opt = 0;
                    
//#line 631
filename = "input.txt";
                } else {
                    
//#line 633
if (((int) a.
                                              size) ==
                                     ((int) 1)) {
                        
//#line 634
opt = 0;
                        
//#line 635
filename = ((x10.
                          array.
                          Array<java.lang.String>)(a)).apply$G((int)(0));
                    } else {
                        
//#line 637
if (((int) a.
                                                  size) ==
                                         ((int) 2)) {
                            
//#line 638
opt = new Object() { int eval(String s) { try { return java.lang.Integer.parseInt(s); } catch (java.lang.NumberFormatException e) { throw new x10.lang.NumberFormatException(e.getMessage()); } } }.eval(((java.lang.String)
                                                                                                                                                                                                                                                    ((x10.
                                                                                                                                                                                                                                                    array.
                                                                                                                                                                                                                                                    Array<java.lang.String>)(a)).apply$G((int)(1))));
                            
//#line 639
filename = ((x10.
                              array.
                              Array<java.lang.String>)(a)).apply$G((int)(0));
                        }
                    }
                }
                
//#line 642
final x10.
                  io.
                  File inp =
                  ((x10.
                  io.
                  File)(new x10.
                  io.
                  File(filename)));
                
//#line 644
final x10.
                  io.
                  FileReader i =
                  ((x10.
                  io.
                  FileReader)(inp.openRead()));
                
//#line 648
int j =
                  0;
                
//#line 649
int k =
                  0;
                
//#line 651
java.lang.String src =
                  " ";
                
//#line 651
java.lang.String dest =
                  " ";
                
//#line 652
double wt =
                  ((double)(int)(((int)(0))));
                
//#line 653
for (
//#line 653
final x10.
                                    lang.
                                    Iterator<java.lang.String> line182 =
                                    ((x10.
                                      lang.
                                      Iterator<java.lang.String>)(x10.
                                      lang.
                                      Iterator)
                                      ((x10.
                                      io.
                                      ReaderIterator<java.lang.String>)(i.lines())).iterator());
                                  ((x10.
                                    lang.
                                    Iterator<java.lang.String>)(line182)).hasNext();
                                  ) {
                    
//#line 653
final java.lang.String line =
                      ((java.lang.String)
                        ((x10.
                        lang.
                        Iterator<java.lang.String>)(line182)).next$G());
                    
//#line 654
if (((int) j) ==
                                     ((int) 0)) {
                        
//#line 655
noofNodes = new Object() { int eval(String s) { try { return java.lang.Integer.parseInt(s); } catch (java.lang.NumberFormatException e) { throw new x10.lang.NumberFormatException(e.getMessage()); } } }.eval((line).trim());
                    } else {
                        
//#line 660
edge = x10.core.RailFactory.<java.lang.String>makeRailFromJavaArray(x10.rtt.Types.STRING, (line).split(" "));
                        
//#line 661
k = 0;
                        
//#line 662
for (
//#line 662
final x10.
                                            lang.
                                            Iterator<java.lang.String> str180 =
                                            (edge).iterator();
                                          ((x10.
                                            lang.
                                            Iterator<java.lang.String>)(str180)).hasNext();
                                          ) {
                            
//#line 662
final java.lang.String str =
                              ((java.lang.String)
                                ((x10.
                                lang.
                                Iterator<java.lang.String>)(str180)).next$G());
                            
//#line 664
switch (k) {
                                
//#line 665
case 0:
                                    
//#line 665
src = str;
                                    
//#line 666
break;
                                
//#line 667
case 1:
                                    
//#line 667
dest = str;
                                    
//#line 668
break;
                                
//#line 669
case 2:
                                    
//#line 669
wt = java.lang.Double.parseDouble(str);
                                    
//#line 670
break;
                            }
                            
//#line 673
k = ((((int)(k))) + (((int)(1))));
                        }
                        
//#line 675
((x10.
                          util.
                          ArrayList<Edge>)(edges)).add_0_$$x10$util$ArrayList_T(((Edge)(new Edge(src,
                                                                                                 dest,
                                                                                                 wt))));
                    }
                    
//#line 677
j = ((((int)(j))) + (((int)(1))));
                }
            }}catch (final x10.
                       io.
                       IOException id$0) {
                
            }
            
//#line 684
G = new Graph(noofNodes);
            
//#line 685
Vertex v1 =
               null;
            
//#line 685
Vertex v2 =
               null;
            
//#line 686
int idx =
               0;
            
//#line 687
int j =
              0;
            
//#line 689
for (
//#line 689
final x10.
                                util.
                                ListIterator<Edge> e184 =
                                ((x10.
                                  util.
                                  ListIterator<Edge>)(x10.
                                  util.
                                  ListIterator)
                                  ((x10.
                                  util.
                                  ArrayList<Edge>)(edges)).iterator());
                              ((x10.
                                util.
                                ListIterator<Edge>)(e184)).hasNext();
                              ) {
                
//#line 689
final Edge e =
                  ((Edge)
                    ((x10.
                    util.
                    ListIterator<Edge>)(e184)).next$G());
                
//#line 691
v1 = G.getNode(((java.lang.String)(e.
                                                                  src)));
                
//#line 692
v2 = G.getNode(((java.lang.String)(e.
                                                                  dest)));
                
//#line 693
G.addEdge(((Vertex)(v1)),
                                       ((Vertex)(v2)),
                                       (double)(e.
                                                  wt));
            }
            
//#line 696
if (((int) opt) ==
                             ((int) 0)) {
                
//#line 697
G.ParallelBFSQueue(((java.lang.String)("0")));
            } else {
                
//#line 700
G.ParallelBFSBAG(((java.lang.String)("0")));
            }
        }
        
        
//#line 613
public BFS() {
            
//#line 613
super();
            {
                
            }
        }
    
}
