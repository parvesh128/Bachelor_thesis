public class retType
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<retType> _RTT = new x10.rtt.RuntimeType<retType>(
    /* base class */retType.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "retType";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 8
public boolean
          b;
        
//#line 9
public int
          idx;
        
        
//#line 11
public retType(final boolean b,
                                   final int i) {
            super();
            
//#line 7
this.__fieldInitializers155();
            
//#line 12
this.b = b;
            
//#line 13
this.idx = i;
        }
        
        
//#line 7
final private void
                     __fieldInitializers155(
                     ){
            
//#line 7
this.b = false;
            
//#line 7
this.idx = 0;
        }
    
}
