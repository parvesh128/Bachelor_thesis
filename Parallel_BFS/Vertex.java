public class Vertex
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Vertex> _RTT = new x10.rtt.RuntimeType<Vertex>(
    /* base class */Vertex.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Vertex";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 111
public int
          dist;
        
//#line 112
public java.lang.String
          label;
        
//#line 113
public boolean
          visited;
        
//#line 114
public int
          index;
        
//#line 115
public x10.
          util.
          ArrayList<EdgeNode>
          edgeList;
        
        
//#line 117
public Vertex(final java.lang.String lbl,
                                   final int indx) {
            super();
            
//#line 110
this.__fieldInitializers102();
            
//#line 118
this.label = lbl;
            
//#line 119
this.visited = false;
            
//#line 120
this.edgeList = new x10.
              util.
              ArrayList<EdgeNode>(EdgeNode._RTT,
                                  10);
            
//#line 121
this.dist = 2147483647;
            
//#line 122
this.index = indx;
        }
        
        
//#line 125
public void
                       addEdge(
                       final EdgeNode en){
            
//#line 126
((x10.
              util.
              ArrayList<EdgeNode>)(edgeList)).add_0_$$x10$util$ArrayList_T(((EdgeNode)(en)));
        }
        
        
//#line 110
final private void
                       __fieldInitializers102(
                       ){
            
//#line 110
this.dist = 0;
            
//#line 110
this.label = null;
            
//#line 110
this.visited = false;
            
//#line 110
this.index = 0;
        }
        
        final public static void
          __fieldInitializers102$P(
          final Vertex Vertex){
            Vertex.__fieldInitializers102();
        }
    
}
