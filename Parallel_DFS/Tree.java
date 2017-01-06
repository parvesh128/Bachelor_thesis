public class Tree
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Tree> _RTT = new x10.rtt.RuntimeType<Tree>(
    /* base class */Tree.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Tree";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 67
public Node
          root;
        
//#line 68
public int
          size;
        
        
//#line 69
public Tree(final NodeVal rootNodeVal) {
            super();
            
//#line 66
this.__fieldInitializers103();
            
//#line 70
this.root = new Node(null,
                                             rootNodeVal);
        }
        
        
//#line 73
public static void
                      serialDFS(
                      final Node root){
            
//#line 74
Node n =
               null;
            
//#line 75
if ((!x10.rtt.Equality.equalsequals(root,null))) {
                
//#line 76
n = root.visitChild();
                
//#line 77
Tree.serialDFS(((Node)(n)));
            }
        }
        
        
//#line 66
final private void
                      __fieldInitializers103(
                      ){
            
//#line 66
this.root = null;
            
//#line 66
this.size = 0;
        }
        
        final public static void
          __fieldInitializers103$P(
          final Tree Tree){
            Tree.__fieldInitializers103();
        }
    
}
