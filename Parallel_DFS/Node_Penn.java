public class Node_Penn
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Node_Penn> _RTT = new x10.rtt.RuntimeType<Node_Penn>(
    /* base class */Node_Penn.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Node_Penn";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 111
public Node
          v;
        
//#line 112
public Node_Penn
          lt;
        
//#line 113
public Node_Penn
          rt;
        
        
//#line 114
public Node_Penn(final Node v,
                                      final Node_Penn lt,
                                      final Node_Penn rt) {
            super();
            
//#line 110
this.__fieldInitializers104();
            
//#line 115
this.v = v;
            
//#line 116
this.lt = lt;
            
//#line 117
this.rt = rt;
        }
        
        
//#line 110
final private void
                       __fieldInitializers104(
                       ){
            
//#line 110
this.v = null;
            
//#line 110
this.lt = null;
            
//#line 110
this.rt = null;
        }
    
}
