public class Node
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Node> _RTT = new x10.rtt.RuntimeType<Node>(
    /* base class */Node.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Node";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 14
public NodeVal
          nv;
        
//#line 15
public Node
          parentnode;
        
//#line 16
public x10.
          util.
          ArrayList<Node>
          childnodeList;
        
//#line 17
public int
          dist;
        
//#line 19
public int
          childtobevisited;
        
        
//#line 22
public Node(final Node pn,
                                final NodeVal nv) {
            super();
            
//#line 13
this.__fieldInitializers102();
            
//#line 23
this.parentnode = pn;
            
//#line 24
this.nv = nv;
            
//#line 25
this.childnodeList = new x10.
              util.
              ArrayList<Node>(Node._RTT);
            
//#line 28
this.childtobevisited = 0;
        }
        
        
//#line 32
public void
                      addChild(
                      final Node cn){
            
//#line 33
((x10.
              util.
              ArrayList<Node>)(childnodeList)).add_0_$$x10$util$ArrayList_T(((Node)(cn)));
        }
        
        
//#line 37
public void
                      visit(
                      ){
            
//#line 38
if ((!x10.rtt.Equality.equalsequals(parentnode,null))) {
                
//#line 39
this.dist = ((((int)(parentnode.
                                                   dist))) + (((int)(1))));
                
//#line 40
x10.
                  io.
                  Console.OUT.println((int)(this.
                                              nv.
                                              value));
            } else {
                
//#line 43
this.dist = 0;
            }
        }
        
        
//#line 46
public Node
                      visitChild(
                      ){
            
//#line 47
Node n =
               null;
            
//#line 48
if (((((int)(childtobevisited))) < (((int)(((x10.
                              util.
                              ArrayList<Node>)(childnodeList)).size()))))) {
                
//#line 50
n = ((x10.
                  util.
                  ArrayList<Node>)(childnodeList)).get$G((int)(childtobevisited));
                
//#line 51
n.visit();
                
//#line 52
Node.__$closure$apply$__111(((Node)(this)),
                                                        (int)(1));
                
//#line 54
return n;
            } else {
                
//#line 57
return parentnode;
            }
        }
        
        
//#line 13
final private void
                      __fieldInitializers102(
                      ){
            
//#line 13
this.nv = null;
            
//#line 13
this.parentnode = null;
            
//#line 13
this.dist = 0;
            
//#line 13
this.childtobevisited = 0;
        }
        
        final public static void
          __fieldInitializers102$P(
          final Node Node){
            Node.__fieldInitializers102();
        }
        
        final private static int
          __$closure$apply$__111(
          final Node x,
          final int y){
            
//#line 52
return x.childtobevisited = ((((int)(x.
                                                               childtobevisited))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__111$P(
          final Node x,
          final int y){
            return Node.__$closure$apply$__111(((Node)(x)),
                                               (int)(y));
        }
    
}
