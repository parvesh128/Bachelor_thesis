





public class BFS
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<BFS> _RTT = new x10.rtt.RuntimeType<BFS>(
    /* base class */BFS.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "BFS";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
        
//#line 165
public static class Main extends x10.runtime.impl.java.Runtime {
        public static void main(java.lang.String[] args) {
        // start native runtime
        new Main().start(args);
        }
        
        // called by native runtime inside main x10 thread
        public void main(final x10.array.Array<java.lang.String> args) {
        try {
        // start xrx
        x10.lang.Runtime.start(
        // static init activity
        new x10.core.fun.VoidFun_0_0() {
        public void apply() {
        // preload classes
        if (Boolean.getBoolean("x10.PRELOAD_CLASSES")) {
        x10.runtime.impl.java.PreLoader.preLoad(this.getClass().getEnclosingClass(), Boolean.getBoolean("x10.PRELOAD_STRINGS"));
        }
        }
        public x10.rtt.RuntimeType<?> getRTT() {
        return _RTT;
        }
        public x10.rtt.Type<?> getParam(int i) {
        return null;
        }
        },
        // body of main activity
        new x10.core.fun.VoidFun_0_0() {
        public void apply() {
        // catch and rethrow checked exceptions
        // (closures cannot throw checked exceptions)
        try {
        // call the original app-main method
        BFS.main(args);
        } catch (java.lang.RuntimeException e) {
        throw e;
        } catch (java.lang.Error e) {
        throw e;
        } catch (java.lang.Throwable t) {
        throw new x10.runtime.impl.java.X10WrappedThrowable(t);
        }
        }
        public x10.rtt.RuntimeType<?> getRTT() {
        return _RTT;
        }
        public x10.rtt.Type<?> getParam(int i) {
        return null;
        }
        });
        } catch (java.lang.Throwable t) {
        t.printStackTrace();
        }
        }
        }
        
        // the original app-main method
        public static void main(final x10.
          array.
          Array<java.lang.String> a)  {
            
//#line 167
final x10.
              util.
              ArrayList<java.lang.String> al =
              ((x10.
              util.
              ArrayList)(new x10.
              util.
              ArrayList<java.lang.String>(x10.rtt.Types.STRING,
                                          10)));
            
//#line 168
x10.
              io.
              Console.OUT.println(((java.lang.Object)((("Initial size of al: ") + (((java.lang.Integer)(((x10.
                                    util.
                                    ArrayList<java.lang.String>)(al)).size())))))));
            
//#line 170
((x10.
              util.
              ArrayList<java.lang.String>)(al)).add_0_$$x10$util$ArrayList_T(((java.lang.String)("C")));
            
//#line 171
((x10.
              util.
              ArrayList<java.lang.String>)(al)).add_0_$$x10$util$ArrayList_T(((java.lang.String)("A")));
            
//#line 172
((x10.
              util.
              ArrayList<java.lang.String>)(al)).add_0_$$x10$util$ArrayList_T(((java.lang.String)("E")));
            
//#line 173
((x10.
              util.
              ArrayList<java.lang.String>)(al)).add_0_$$x10$util$ArrayList_T(((java.lang.String)("B")));
            
//#line 174
((x10.
              util.
              ArrayList<java.lang.String>)(al)).add_0_$$x10$util$ArrayList_T(((java.lang.String)("D")));
            
//#line 175
((x10.
              util.
              ArrayList<java.lang.String>)(al)).add_0_$$x10$util$ArrayList_T(((java.lang.String)("F")));
            
//#line 177
x10.
              io.
              Console.OUT.println(((java.lang.Object)((("Size of al after additions: ") + (((java.lang.Integer)(((x10.
                                    util.
                                    ArrayList<java.lang.String>)(al)).size())))))));
            
//#line 179
x10.
              io.
              Console.OUT.println(((java.lang.Object)((("Contents of al: ") + (al)))));
            
//#line 180
for (
//#line 180
int i =
                                0;
                              ((((int)(i))) < (((int)(((x10.
                                util.
                                ArrayList<java.lang.String>)(al)).size()))));
                              
//#line 180
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 181
x10.
                  io.
                  Console.OUT.println(((java.lang.Object)(((java.lang.String)
                                                            ((x10.
                                                            util.
                                                            ArrayList<java.lang.String>)(al)).get$G((int)(i))))));
            }
            
//#line 183
((x10.
              util.
              ArrayList<java.lang.String>)(al)).remove_0_$$x10$util$ArrayList_T(((java.lang.String)("F")));
            
//#line 184
((x10.
              util.
              ArrayList<java.lang.String>)(al)).remove_0_$$x10$util$ArrayList_T(((java.lang.String)("A2")));
            
//#line 185
x10.
              io.
              Console.OUT.println(((java.lang.Object)((("Size of al after deletions: ") + (((java.lang.Integer)(((x10.
                                    util.
                                    ArrayList<java.lang.String>)(al)).size())))))));
            
//#line 186
x10.
              io.
              Console.OUT.println(((java.lang.Object)((("Contents of al: ") + (al)))));
        }
        
        
//#line 164
public BFS() {
            
//#line 164
super();
            {
                
            }
        }
    
}
