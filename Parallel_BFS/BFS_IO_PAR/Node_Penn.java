public class Node_Penn
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Node_Penn> _RTT = new x10.rtt.RuntimeType<Node_Penn>(
    /* base class */Node_Penn.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Node_Penn";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 254
public Vertex
          v;
        
//#line 255
public Node_Penn
          lt;
        
//#line 256
public Node_Penn
          rt;
        
        
//#line 257
public Node_Penn(final Vertex v,
                                      final Node_Penn lt,
                                      final Node_Penn rt) {
            super();
            
//#line 253
this.__fieldInitializers160();
            
//#line 258
this.v = v;
            
//#line 259
this.lt = lt;
            
//#line 260
this.rt = rt;
        }
        
        
//#line 253
final private void
                       __fieldInitializers160(
                       ){
            
//#line 253
this.v = null;
            
//#line 253
this.lt = null;
            
//#line 253
this.rt = null;
        }
    
}
