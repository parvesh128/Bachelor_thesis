public class Vertex
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Vertex> _RTT = new x10.rtt.RuntimeType<Vertex>(
    /* base class */Vertex.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Vertex";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 169
public int
          dist;
        
//#line 170
public java.lang.String
          label;
        
//#line 171
public boolean
          visited;
        
//#line 172
public int
          index;
        
//#line 173
public x10.
          util.
          ArrayList<EdgeNode>
          edgeList;
        
        
//#line 175
public Vertex(final java.lang.String lbl,
                                   final int indx) {
            super();
            
//#line 168
this.__fieldInitializers157();
            
//#line 176
this.label = lbl;
            
//#line 177
this.visited = false;
            
//#line 178
this.edgeList = new x10.
              util.
              ArrayList<EdgeNode>(EdgeNode._RTT);
            
//#line 179
this.dist = 2147483647;
            
//#line 180
this.index = indx;
        }
        
        
//#line 183
public void
                       addEdge(
                       final EdgeNode en){
            
//#line 184
((x10.
              util.
              ArrayList<EdgeNode>)(edgeList)).add_0_$$x10$util$ArrayList_T(((EdgeNode)(en)));
        }
        
        
//#line 188
public java.lang.String
                       toString(
                       ){
            
//#line 189
return label;
        }
        
        
//#line 168
final private void
                       __fieldInitializers157(
                       ){
            
//#line 168
this.dist = 0;
            
//#line 168
this.label = null;
            
//#line 168
this.visited = false;
            
//#line 168
this.index = 0;
        }
        
        final public static void
          __fieldInitializers157$P(
          final Vertex Vertex){
            Vertex.__fieldInitializers157();
        }
    
}
