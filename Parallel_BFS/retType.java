public class retType
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<retType> _RTT = new x10.rtt.RuntimeType<retType>(
    /* base class */retType.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "retType";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 5
public boolean
          b;
        
//#line 6
public int
          idx;
        
        
//#line 8
public retType(final boolean b,
                                  final int i) {
            super();
            
//#line 4
this.__fieldInitializers100();
            
//#line 9
this.b = b;
            
//#line 10
this.idx = i;
        }
        
        
//#line 4
final private void
                     __fieldInitializers100(
                     ){
            
//#line 4
this.b = false;
            
//#line 4
this.idx = 0;
        }
    
}
