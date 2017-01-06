public class Queue
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Queue> _RTT = new x10.rtt.RuntimeType<Queue>(
    /* base class */Queue.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Queue";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 144
public x10.
          util.
          ArrayList<Vertex>
          nodeList;
        
        
//#line 146
public Queue() {
            super();
            {
                
            }
            
//#line 147
this.nodeList = new x10.
              util.
              ArrayList<Vertex>(Vertex._RTT);
        }
        
        
//#line 150
public void
                       ENQUEUE(
                       final Vertex v){
            
//#line 151
((x10.
              util.
              ArrayList<Vertex>)(nodeList)).add_0_$$x10$util$ArrayList_T(((Vertex)(v)));
        }
        
        
//#line 154
public Vertex
                       DEQUEUE(
                       ){
            
//#line 155
return ((Vertex)
                                  ((x10.
                                  util.
                                  ArrayList<Vertex>)(nodeList)).removeFirst$G());
        }
        
        
//#line 158
public boolean
                       isEmpty(
                       ){
            
//#line 159
return ((x10.
              util.
              ArrayList<Vertex>)(nodeList)).isEmpty();
        }
    
}
