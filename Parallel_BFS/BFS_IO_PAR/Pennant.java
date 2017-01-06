public class Pennant
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Pennant> _RTT = new x10.rtt.RuntimeType<Pennant>(
    /* base class */Pennant.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Pennant";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 266
public Node_Penn
          root;
        
//#line 267
public int
          size;
        
        
//#line 269
public Pennant() {
            super();
            
//#line 265
this.__fieldInitializers161();
            
//#line 270
this.root = null;
            
//#line 271
this.size = 0;
        }
        
        
//#line 274
public Pennant(final Vertex v) {
            super();
            
//#line 265
this.__fieldInitializers161();
            
//#line 276
this.root = new Node_Penn(v,
                                                   null,
                                                   null);
            
//#line 277
Pennant.__$closure$apply$__217(((Pennant)(this)),
                                                        (int)(1));
        }
        
        
//#line 280
public Pennant(final Node_Penn root) {
            super();
            
//#line 265
this.__fieldInitializers161();
            
//#line 282
this.root = root;
            
//#line 283
Pennant.__$closure$apply$__218(((Pennant)(this)),
                                                        (int)(1));
        }
        
        
//#line 286
public Pennant
                       unionPennant(
                       final Pennant p){
            
//#line 287
if (((int) this.
                                      size) ==
                             ((int) p.
                                      size)) {
                
//#line 288
p.
                               root.rt = this.
                                           root.
                                           lt;
                
//#line 289
this.
                               root.lt = p.
                                           root;
                
//#line 290
this.size = ((((int)(this.
                                                    size))) + (((int)(p.
                                                                        size))));
                
//#line 292
return this;
            } else {
                
//#line 295
x10.
                  io.
                  Console.OUT.println(((java.lang.Object)("Union valid only between two pennants of same size")));
                
//#line 296
return this;
            }
        }
        
        
//#line 300
public Pennant
                       splitPennant(
                       ){
            
//#line 301
Pennant p =
              new Pennant(this.
                            root.
                            lt);
            
//#line 302
this.
                           root.lt = p.
                                       root.
                                       rt;
            
//#line 303
p.
                           root.rt = null;
            
//#line 304
this.size = p.size = ((((int)(size))) / (((int)(2))));
            
//#line 305
return p;
        }
        
        
//#line 308
private void
                       processPennantNode(
                       final Node_Penn p,
                       BAG OUT_BAG,
                       final int d){
            
//#line 310
EdgeNode en =
               null;
            
//#line 311
if ((!x10.rtt.Equality.equalsequals(p,null))) {
                
//#line 312
Vertex u =
                   null;
                
//#line 313
u = p.
                                   v;
                
//#line 314
for (
//#line 314
int i =
                                    0;
                                  ((((int)(i))) < (((int)(((x10.
                                    util.
                                    ArrayList<EdgeNode>)(u.
                                                           edgeList)).size()))));
                                  
//#line 314
i = ((((int)(i))) + (((int)(1))))) {
                    
//#line 315
en = ((x10.
                      util.
                      ArrayList<EdgeNode>)(u.
                                             edgeList)).get$G((int)(i));
                    {
                        
//#line 316
x10.
                          lang.
                          Runtime.ensureNotInAtomic();
                        {
                            
//#line 316
final EdgeNode[] $en227 =
                              new EdgeNode[1];
                            
//#line 316
$en227[0]=en;
                            
//#line 316
final BAG[] $OUT_BAG228 =
                              new BAG[1];
                            
//#line 316
$OUT_BAG228[0]=OUT_BAG;
                            
//#line 316
final Vertex[] $u229 =
                              new Vertex[1];
                            
//#line 316
$u229[0]=u;
                            
//#line 316
try {try {{
                                
//#line 316
x10.
                                  lang.
                                  Runtime.startFinish();
                                {
                                    
//#line 317
final x10.
                                      lang.
                                      Clock c1 =
                                      x10.
                                      lang.
                                      Clock.make();
                                    
//#line 318
final BAG ob =
                                      new BAG(((BAG)$OUT_BAG228[0]).
                                                r);
                                    
//#line 319
if (((((int) ((EdgeNode)$en227[0]).
                                                                destVertex.
                                                                dist) ==
                                                       ((int) Graph.MAXINF))) &&
                                                     (((!(((boolean)(((EdgeNode)$en227[0]).
                                                                       destVertex.
                                                                       visited))))))) {
                                        
//#line 320
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
                                                                                    
//#line 320
EdgeNode p1$en227 =
                                                                                      ((EdgeNode)$en227[0]);
                                                                                    
//#line 320
Vertex p1$u229 =
                                                                                      ((Vertex)$u229[0]);
                                                                                    
//#line 320
BAG p1$OUT_BAG228 =
                                                                                      ((BAG)$OUT_BAG228[0]);
                                                                                    {
                                                                                        
//#line 322
p1$en227.
                                                                                                       destVertex.dist = ((((int)(p1$u229.
                                                                                                                                    dist))) + (((int)(1))));
                                                                                        
//#line 323
p1$en227.
                                                                                                       destVertex.visited = true;
                                                                                        
//#line 324
ob.BAG_INSERT(((Vertex)(p1$en227.
                                                                                                                               destVertex)));
                                                                                        
//#line 325
x10.
                                                                                          io.
                                                                                          Console.OUT.println(((java.lang.Object)((((((("Label ") + (p1$en227.
                                                                                                                                                       destVertex.
                                                                                                                                                       label))) + (" dist "))) + (((java.lang.Integer)(p1$en227.
                                                                                                                                                                                                         destVertex.
                                                                                                                                                                                                         dist)))))));
                                                                                        
//#line 326
p1$OUT_BAG228.BAG_UNION(((BAG)(ob)));
                                                                                        
//#line 327
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
                            }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__3__) {
                                
//#line 316
x10.
                                  lang.
                                  Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__3__)));
                                throw new x10.
                                  lang.
                                  RuntimeException();
                            }finally {{
                                 
//#line 316
x10.
                                   lang.
                                   Runtime.stopFinish();
                             }}
                            
//#line 316
en = ((EdgeNode)$en227[0]);
                            
//#line 316
OUT_BAG = ((BAG)$OUT_BAG228[0]);
                            
//#line 316
u = ((Vertex)$u229[0]);
                            }
                        }
                    }
                
//#line 335
Pennant.this.processPennantNode(((Node_Penn)(p.
                                                                            lt)),
                                                             ((BAG)(OUT_BAG)),
                                                             (int)(d));
                
//#line 336
Pennant.this.processPennantNode(((Node_Penn)(p.
                                                                            rt)),
                                                             ((BAG)(OUT_BAG)),
                                                             (int)(d));
                }
            }
        
        public static void
          processPennantNode$P(
          final Node_Penn p,
          BAG OUT_BAG,
          final int d,
          final Pennant Pennant){
            Pennant.processPennantNode(((Node_Penn)(p)),
                                       ((BAG)(OUT_BAG)),
                                       (int)(d));
        }
        
        
//#line 340
public void
                       processPennant(
                       BAG OUT_BAG,
                       final int d){
            
//#line 342
Pennant.this.processPennantNode(((Node_Penn)(Pennant.this.
                                                                        root)),
                                                         ((BAG)(OUT_BAG)),
                                                         (int)(d));
        }
        
        
//#line 346
private void
                       printPennantNode(
                       final Node_Penn p){
            
//#line 347
if ((!x10.rtt.Equality.equalsequals(p,null))) {
                
//#line 348
x10.
                  io.
                  Console.OUT.print(((java.lang.String)(((p.
                                                            v.
                                                            label) + (" ")))));
                
//#line 349
this.printPennantNode(((Node_Penn)(p.
                                                                  lt)));
                
//#line 350
this.printPennantNode(((Node_Penn)(p.
                                                                  rt)));
            }
        }
        
        public static void
          printPennantNode$P(
          final Node_Penn p,
          final Pennant Pennant){
            Pennant.printPennantNode(((Node_Penn)(p)));
        }
        
        
//#line 354
public void
                       printPennant(
                       ){
            
//#line 356
this.printPennantNode(((Node_Penn)(root)));
        }
        
        
//#line 265
final private void
                       __fieldInitializers161(
                       ){
            
//#line 265
this.root = null;
            
//#line 265
this.size = 0;
        }
        
        final public static void
          __fieldInitializers161$P(
          final Pennant Pennant){
            Pennant.__fieldInitializers161();
        }
        
        final private static int
          __$closure$apply$__217(
          final Pennant x,
          final int y){
            
//#line 277
return x.size = ((((int)(x.
                                                    size))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__217$P(
          final Pennant x,
          final int y){
            return Pennant.__$closure$apply$__217(((Pennant)(x)),
                                                  (int)(y));
        }
        
        final private static int
          __$closure$apply$__218(
          final Pennant x,
          final int y){
            
//#line 283
return x.size = ((((int)(x.
                                                    size))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__218$P(
          final Pennant x,
          final int y){
            return Pennant.__$closure$apply$__218(((Pennant)(x)),
                                                  (int)(y));
        }
        
    }
    