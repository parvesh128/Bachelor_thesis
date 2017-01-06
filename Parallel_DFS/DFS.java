









public class DFS
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<DFS> _RTT = new x10.rtt.RuntimeType<DFS>(
    /* base class */DFS.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "DFS";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
        
//#line 474
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
        DFS.main(args);
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
            
//#line 484
NodeVal nv =
               null;
            
//#line 485
Node n =
               null;
            
//#line 485
Node n1 =
               null;
            
//#line 485
Node n2 =
               null;
            
//#line 485
Node n3 =
               null;
            
//#line 486
nv = new NodeVal(1);
            
//#line 487
n = new Node(null,
                                      nv);
            
//#line 488
n2 = n;
            
//#line 489
nv = new NodeVal(2);
            
//#line 490
n1 = new Node(n,
                                       nv);
            
//#line 491
n.addChild(((Node)(n1)));
            
//#line 492
nv = new NodeVal(3);
            
//#line 493
n1 = new Node(n,
                                       nv);
            
//#line 494
n.addChild(((Node)(n1)));
            
//#line 495
nv = new NodeVal(4);
            
//#line 496
n1 = new Node(n,
                                       nv);
            
//#line 497
n.addChild(((Node)(n1)));
            
//#line 499
n = ((x10.
              util.
              ArrayList<Node>)(n.
                                 childnodeList)).get$G((int)(0));
            
//#line 500
nv = new NodeVal(5);
            
//#line 501
n1 = new Node(n,
                                       nv);
            
//#line 502
n.addChild(((Node)(n1)));
            
//#line 503
nv = new NodeVal(6);
            
//#line 504
n1 = new Node(n,
                                       nv);
            
//#line 505
n.addChild(((Node)(n1)));
            
//#line 506
nv = new NodeVal(7);
            
//#line 507
n1 = new Node(n,
                                       nv);
            
//#line 508
n.addChild(((Node)(n1)));
            
//#line 510
n = ((x10.
              util.
              ArrayList<Node>)(n.
                                 childnodeList)).get$G((int)(0));
            
//#line 511
nv = new NodeVal(8);
            
//#line 512
n1 = new Node(n,
                                       nv);
            
//#line 513
n.addChild(((Node)(n1)));
            
//#line 514
nv = new NodeVal(9);
            
//#line 515
n1 = new Node(n,
                                       nv);
            
//#line 516
n.addChild(((Node)(n1)));
            
//#line 517
nv = new NodeVal(10);
            
//#line 518
n1 = new Node(n,
                                       nv);
            
//#line 519
n.addChild(((Node)(n1)));
            
//#line 521
n = ((x10.
              util.
              ArrayList<Node>)(n.
                                 childnodeList)).get$G((int)(0));
            
//#line 522
nv = new NodeVal(11);
            
//#line 523
n1 = new Node(n,
                                       nv);
            
//#line 524
n.addChild(((Node)(n1)));
            
//#line 525
nv = new NodeVal(12);
            
//#line 526
n1 = new Node(n,
                                       nv);
            
//#line 527
n.addChild(((Node)(n1)));
            
//#line 528
nv = new NodeVal(13);
            
//#line 529
n1 = new Node(n,
                                       nv);
            
//#line 530
n.addChild(((Node)(n1)));
            
//#line 534
n = n2;
            
//#line 536
x10.
              io.
              Console.OUT.println(((java.lang.Object)("Hello, World!")));
            
//#line 537
Tree.serialDFS(((Node)(n)));
        }
        
        
//#line 473
public DFS() {
            
//#line 473
super();
            {
                
            }
        }
    
}
