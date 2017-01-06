public class Vertex
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Vertex> _RTT = new x10.rtt.RuntimeType<Vertex>(
    /* base class */Vertex.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Vertex";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 127
public int
          dist;
        
//#line 128
public java.lang.String
          label;
        
//#line 129
public boolean
          visited;
        
//#line 130
public int
          index;
        
//#line 131
public x10.
          util.
          ArrayList<EdgeNode>
          edgeList;
        
        
//#line 133
public Vertex(final java.lang.String lbl,
                                   final int indx) {
            super();
            
//#line 126
this.__fieldInitializers134();
            
//#line 134
this.label = lbl;
            
//#line 135
this.visited = false;
            
//#line 136
this.edgeList = new x10.
              util.
              ArrayList<EdgeNode>(EdgeNode._RTT);
            
//#line 137
this.dist = 2147483647;
            
//#line 138
this.index = indx;
        }
        
        
//#line 141
public void
                       addEdge(
                       final EdgeNode en){
            
//#line 142
((x10.
              util.
              ArrayList<EdgeNode>)(edgeList)).add_0_$$x10$util$ArrayList_T(((EdgeNode)(en)));
        }
        
        
//#line 126
final private void
                       __fieldInitializers134(
                       ){
            
//#line 126
this.dist = 0;
            
//#line 126
this.label = null;
            
//#line 126
this.visited = false;
            
//#line 126
this.index = 0;
        }
        
        final public static void
          __fieldInitializers134$P(
          final Vertex Vertex){
            Vertex.__fieldInitializers134();
        }
    
}
