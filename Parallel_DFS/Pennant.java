public class Pennant
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<Pennant> _RTT = new x10.rtt.RuntimeType<Pennant>(
    /* base class */Pennant.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "Pennant";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 123
public Node_Penn
          root;
        
//#line 124
public int
          size;
        
        
//#line 126
public Pennant() {
            super();
            
//#line 122
this.__fieldInitializers105();
            
//#line 127
this.root = null;
            
//#line 128
this.size = 0;
        }
        
        
//#line 131
public Pennant(final Node v) {
            super();
            
//#line 122
this.__fieldInitializers105();
            
//#line 133
this.root = new Node_Penn(v,
                                                   null,
                                                   null);
            
//#line 134
Pennant.__$closure$apply$__112(((Pennant)(this)),
                                                        (int)(1));
        }
        
        
//#line 137
public Pennant(final Node_Penn root) {
            super();
            
//#line 122
this.__fieldInitializers105();
            
//#line 139
this.root = root;
            
//#line 140
Pennant.__$closure$apply$__113(((Pennant)(this)),
                                                        (int)(1));
        }
        
        
//#line 143
public Pennant
                       unionPennant(
                       final Pennant p){
            
//#line 144
if (((int) this.
                                      size) ==
                             ((int) p.
                                      size)) {
                
//#line 145
p.
                               root.rt = this.
                                           root.
                                           lt;
                
//#line 146
this.
                               root.lt = p.
                                           root;
                
//#line 147
this.size = ((((int)(this.
                                                    size))) + (((int)(p.
                                                                        size))));
                
//#line 149
return this;
            } else {
                
//#line 152
x10.
                  io.
                  Console.OUT.println(((java.lang.Object)("Union valid only between two pennants of same size")));
                
//#line 153
return this;
            }
        }
        
        
//#line 157
public Pennant
                       splitPennant(
                       ){
            
//#line 158
Pennant p =
              new Pennant(this.
                            root.
                            lt);
            
//#line 159
this.
                           root.lt = p.
                                       root.
                                       rt;
            
//#line 160
p.
                           root.rt = null;
            
//#line 161
this.size = p.size = ((((int)(size))) / (((int)(2))));
            
//#line 162
return p;
        }
        
        
//#line 203
private void
                       printPennantNode(
                       final Node_Penn p){
            
//#line 204
if ((!x10.rtt.Equality.equalsequals(p,null))) {
                
//#line 205
x10.
                  io.
                  Console.OUT.print(((java.lang.String)(((java.lang.Integer.toString(p.
                                                                                       v.
                                                                                       nv.
                                                                                       value)) + (" ")))));
                
//#line 206
this.printPennantNode(((Node_Penn)(p.
                                                                  lt)));
                
//#line 207
this.printPennantNode(((Node_Penn)(p.
                                                                  rt)));
            }
        }
        
        public static void
          printPennantNode$P(
          final Node_Penn p,
          final Pennant Pennant){
            Pennant.printPennantNode(((Node_Penn)(p)));
        }
        
        
//#line 211
public void
                       printPennant(
                       ){
            
//#line 213
this.printPennantNode(((Node_Penn)(root)));
        }
        
        
//#line 122
final private void
                       __fieldInitializers105(
                       ){
            
//#line 122
this.root = null;
            
//#line 122
this.size = 0;
        }
        
        final public static void
          __fieldInitializers105$P(
          final Pennant Pennant){
            Pennant.__fieldInitializers105();
        }
        
        final private static int
          __$closure$apply$__112(
          final Pennant x,
          final int y){
            
//#line 134
return x.size = ((((int)(x.
                                                    size))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__112$P(
          final Pennant x,
          final int y){
            return Pennant.__$closure$apply$__112(((Pennant)(x)),
                                                  (int)(y));
        }
        
        final private static int
          __$closure$apply$__113(
          final Pennant x,
          final int y){
            
//#line 140
return x.size = ((((int)(x.
                                                    size))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__113$P(
          final Pennant x,
          final int y){
            return Pennant.__$closure$apply$__113(((Pennant)(x)),
                                                  (int)(y));
        }
    
}
