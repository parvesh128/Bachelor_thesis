public class EdgeNode
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<EdgeNode> _RTT = new x10.rtt.RuntimeType<EdgeNode>(
    /* base class */EdgeNode.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "EdgeNode";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 151
public Vertex
          destVertex;
        
//#line 152
public double
          EdgeWt;
        
        
//#line 154
public EdgeNode(final Vertex dv,
                                     final double eW) {
            super();
            
//#line 150
this.__fieldInitializers135();
            
//#line 155
this.destVertex = dv;
            
//#line 156
this.EdgeWt = eW;
        }
        
        
//#line 150
final private void
                       __fieldInitializers135(
                       ){
            
//#line 150
this.destVertex = null;
            
//#line 150
this.EdgeWt = 0.0;
        }
    
}
