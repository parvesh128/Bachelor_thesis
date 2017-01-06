public class Edge
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Edge> _RTT = new x10.rtt.RuntimeType<Edge>(
    /* base class */Edge.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Edge";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 233
public java.lang.String
          src;
        
//#line 234
public java.lang.String
          dest;
        
//#line 235
public double
          wt;
        
        
//#line 237
public Edge(final java.lang.String s,
                                 final java.lang.String d,
                                 final double w) {
            super();
            
//#line 232
this.__fieldInitializers159();
            
//#line 238
this.src = s;
            
//#line 239
this.dest = d;
            
//#line 240
this.wt = w;
        }
        
        
//#line 243
public java.lang.String
                       toString(
                       ){
            
//#line 244
return ((((((((src) + (" "))) + (dest))) + (" "))) + (((java.lang.Double)(wt))));
        }
        
        
//#line 232
final private void
                       __fieldInitializers159(
                       ){
            
//#line 232
this.src = null;
            
//#line 232
this.dest = null;
            
//#line 232
this.wt = 0.0;
        }
        
        final public static void
          __fieldInitializers159$P(
          final Edge Edge){
            Edge.__fieldInitializers159();
        }
    
}
