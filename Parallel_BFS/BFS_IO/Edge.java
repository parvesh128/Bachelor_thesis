public class Edge
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Edge> _RTT = new x10.rtt.RuntimeType<Edge>(
    /* base class */Edge.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Edge";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 187
public java.lang.String
          src;
        
//#line 188
public java.lang.String
          dest;
        
//#line 189
public double
          wt;
        
        
//#line 191
public Edge(final java.lang.String s,
                                 final java.lang.String d,
                                 final double w) {
            super();
            
//#line 186
this.__fieldInitializers136();
            
//#line 192
this.src = s;
            
//#line 193
this.dest = d;
            
//#line 194
this.wt = w;
        }
        
        
//#line 197
public java.lang.String
                       toString(
                       ){
            
//#line 198
return ((((((((src) + (" "))) + (dest))) + (" "))) + (((java.lang.Double)(wt))));
        }
        
        
//#line 186
final private void
                       __fieldInitializers136(
                       ){
            
//#line 186
this.src = null;
            
//#line 186
this.dest = null;
            
//#line 186
this.wt = 0.0;
        }
        
        final public static void
          __fieldInitializers136$P(
          final Edge Edge){
            Edge.__fieldInitializers136();
        }
    
}
