public class NodeVal
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<NodeVal> _RTT = new x10.rtt.RuntimeType<NodeVal>(
    /* base class */NodeVal.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "NodeVal";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 7
public int
          value;
        
        
//#line 8
public NodeVal(final int v) {
            super();
            
//#line 6
this.__fieldInitializers101();
            
//#line 9
this.value = v;
        }
        
        
//#line 6
final private void
                     __fieldInitializers101(
                     ){
            
//#line 6
this.value = 0;
        }
    
}
