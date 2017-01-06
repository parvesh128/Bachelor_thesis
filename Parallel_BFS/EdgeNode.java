public class EdgeNode
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<EdgeNode> _RTT = new x10.rtt.RuntimeType<EdgeNode>(
    /* base class */EdgeNode.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "EdgeNode";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 134
public Vertex
          destVertex;
        
//#line 135
public double
          EdgeWt;
        
        
//#line 137
public EdgeNode(final Vertex dv,
                                     final double eW) {
            super();
            
//#line 133
this.__fieldInitializers103();
            
//#line 138
this.destVertex = dv;
            
//#line 139
this.EdgeWt = eW;
        }
        
        
//#line 133
final private void
                       __fieldInitializers103(
                       ){
            
//#line 133
this.destVertex = null;
            
//#line 133
this.EdgeWt = 0.0;
        }
    
}
