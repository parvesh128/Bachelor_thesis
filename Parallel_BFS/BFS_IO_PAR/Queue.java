public class Queue
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Queue> _RTT = new x10.rtt.RuntimeType<Queue>(
    /* base class */Queue.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Queue";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 207
public x10.
          util.
          ArrayList<Vertex>
          nodeList;
        
        
//#line 209
public Queue() {
            super();
            {
                
            }
            
//#line 210
this.nodeList = new x10.
              util.
              ArrayList<Vertex>(Vertex._RTT);
        }
        
        
//#line 213
public void
                       ENQUEUE(
                       final Vertex v){
            
//#line 214
((x10.
              util.
              ArrayList<Vertex>)(nodeList)).add_0_$$x10$util$ArrayList_T(((Vertex)(v)));
        }
        
        
//#line 218
public Vertex
                       DEQUEUE(
                       ){
            
//#line 219
return ((Vertex)
                                  ((x10.
                                  util.
                                  ArrayList<Vertex>)(nodeList)).removeFirst$G());
        }
        
        
//#line 222
public boolean
                       isEmpty(
                       ){
            
//#line 223
return ((x10.
              util.
              ArrayList<Vertex>)(nodeList)).isEmpty();
        }
    
}
