public class _Stack<T>
extends x10.
  util.
  Stack<T>
{
    public static final x10.rtt.RuntimeType<_Stack> _RTT = new x10.rtt.RuntimeType<_Stack>(
    /* base class */_Stack.class, 
    /* variances */ new x10.rtt.RuntimeType.Variance[] {x10.rtt.RuntimeType.Variance.INVARIANT}
    , /* parents */ new x10.rtt.Type[] {new x10.rtt.ParameterizedType(x10.
      util.
      Stack._RTT, new x10.rtt.UnresolvedType(0))}
    ) {public String typeName() {return "_Stack";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    public x10.rtt.Type<?> getParam(int i) {if (i ==0)return T;return null;}
    
        private x10.rtt.Type T;
        
        
        
//#line 464
public _Stack(final x10.rtt.Type T) {
                                                                  
//#line 464
super(T);
                                                              this.T = T;
                                                               {
                                                                  {
                                                                      
                                                                  }
                                                              }}
        
        
//#line 465
public void
                       print(
                       ){
            
//#line 466
while ((!x10.rtt.Equality.equalsequals(((T)
                                                                  this.peek$G()),null))) {
                
            }
        }
    
}
