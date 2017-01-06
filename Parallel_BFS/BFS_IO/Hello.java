






public class Hello
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Hello> _RTT = new x10.rtt.RuntimeType<Hello>(
    /* base class */Hello.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Hello";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
        
//#line 212
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
        Hello.main(args);
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
          Array<java.lang.String> id$0)  {
            
//#line 213
int noofNodes =
              0;
            
//#line 214
x10.core.Rail<java.lang.String> edge =
               null;
            
//#line 215
final x10.
              util.
              ArrayList<Edge> edges;
            
//#line 216
edges = ((x10.
              util.
              ArrayList)(new x10.
              util.
              ArrayList<Edge>(Edge._RTT)));
            
//#line 217
Graph G =
               null;
            
//#line 218
try {{
                
//#line 219
final x10.
                  io.
                  File inp =
                  ((x10.
                  io.
                  File)(new x10.
                  io.
                  File("input.txt")));
                
//#line 221
final x10.
                  io.
                  FileReader i =
                  ((x10.
                  io.
                  FileReader)(inp.openRead()));
                
//#line 225
int j =
                  0;
                
//#line 226
int k =
                  0;
                
//#line 228
java.lang.String src =
                  " ";
                
//#line 228
java.lang.String dest =
                  " ";
                
//#line 229
double wt =
                  ((double)(int)(((int)(0))));
                
//#line 230
for (
//#line 230
final x10.
                                    lang.
                                    Iterator<java.lang.String> line154 =
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
                                    Iterator<java.lang.String>)(line154)).hasNext();
                                  ) {
                    
//#line 230
final java.lang.String line =
                      ((java.lang.String)
                        ((x10.
                        lang.
                        Iterator<java.lang.String>)(line154)).next$G());
                    
//#line 231
if (((int) j) ==
                                     ((int) 0)) {
                        
//#line 232
noofNodes = new Object() { int eval(String s) { try { return java.lang.Integer.parseInt(s); } catch (java.lang.NumberFormatException e) { throw new x10.lang.NumberFormatException(e.getMessage()); } } }.eval((line).trim());
                    } else {
                        
//#line 237
edge = x10.core.RailFactory.<java.lang.String>makeRailFromJavaArray(x10.rtt.Types.STRING, (line).split(" "));
                        
//#line 238
k = 0;
                        
//#line 239
for (
//#line 239
final x10.
                                            lang.
                                            Iterator<java.lang.String> str152 =
                                            (edge).iterator();
                                          ((x10.
                                            lang.
                                            Iterator<java.lang.String>)(str152)).hasNext();
                                          ) {
                            
//#line 239
final java.lang.String str =
                              ((java.lang.String)
                                ((x10.
                                lang.
                                Iterator<java.lang.String>)(str152)).next$G());
                            
//#line 241
switch (k) {
                                
//#line 242
case 0:
                                    
//#line 242
src = str;
                                    
//#line 243
break;
                                
//#line 244
case 1:
                                    
//#line 244
dest = str;
                                    
//#line 245
break;
                                
//#line 246
case 2:
                                    
//#line 246
wt = java.lang.Double.parseDouble(str);
                                    
//#line 247
break;
                            }
                            
//#line 250
k = ((((int)(k))) + (((int)(1))));
                        }
                        
//#line 252
((x10.
                          util.
                          ArrayList<Edge>)(edges)).add_0_$$x10$util$ArrayList_T(((Edge)(new Edge(src,
                                                                                                 dest,
                                                                                                 wt))));
                    }
                    
//#line 254
j = ((((int)(j))) + (((int)(1))));
                }
            }}catch (final x10.
                       io.
                       IOException id$1) {
                
            }
            
//#line 261
G = new Graph(noofNodes);
            
//#line 262
Vertex v1 =
               null;
            
//#line 262
Vertex v2 =
               null;
            
//#line 263
int idx =
               0;
            
//#line 264
int j =
              0;
            
//#line 266
for (
//#line 266
final x10.
                                util.
                                ListIterator<Edge> e156 =
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
                                ListIterator<Edge>)(e156)).hasNext();
                              ) {
                
//#line 266
final Edge e =
                  ((Edge)
                    ((x10.
                    util.
                    ListIterator<Edge>)(e156)).next$G());
                
//#line 268
v1 = G.getNode(((java.lang.String)(e.
                                                                  src)));
                
//#line 269
v2 = G.getNode(((java.lang.String)(e.
                                                                  dest)));
                
//#line 270
G.addEdge(((Vertex)(v1)),
                                       ((Vertex)(v2)),
                                       (double)(e.
                                                  wt));
            }
            
//#line 272
G.ParallelBFSQueue(((java.lang.String)("0")));
        }
        
        
//#line 205
public Hello() {
            
//#line 205
super();
            {
                
            }
        }
    
}
