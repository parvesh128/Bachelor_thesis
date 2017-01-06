public class EdgeNode
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<EdgeNode> _RTT = new x10.rtt.RuntimeType<EdgeNode>(
    /* base class */EdgeNode.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "EdgeNode";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 197
public Vertex
          destVertex;
        
//#line 198
public double
          EdgeWt;
        
        
//#line 200
public EdgeNode(final Vertex dv,
                                     final double eW) {
            super();
            
//#line 196
this.__fieldInitializers158();
            
//#line 201
this.destVertex = dv;
            
//#line 202
this.EdgeWt = eW;
        }
        
        
//#line 196
final private void
                       __fieldInitializers158(
                       ){
            
//#line 196
this.destVertex = null;
            
//#line 196
this.EdgeWt = 0.0;
        }
    
}
