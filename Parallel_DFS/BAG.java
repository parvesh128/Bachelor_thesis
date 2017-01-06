public class BAG
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<BAG> _RTT = new x10.rtt.RuntimeType<BAG>(
    /* base class */BAG.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "BAG";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 235
public x10.
          array.
          Array<BackBoneNode>
          backbone;
        
//#line 236
public int
          r;
        
//#line 237
public int
          size;
        
//#line 238
final public static int
          GRAINSIZE =
          128;
        
        
//#line 240
public BAG(final int r) {
            super();
            
//#line 234
this.__fieldInitializers108();
            
//#line 241
this.backbone = ((x10.
              array.
              Array)(new x10.
              array.
              Array<BackBoneNode>(BackBoneNode._RTT,
                                  ((((int)(r))) + (((int)(1)))))));
            
//#line 242
for (
//#line 242
int i =
                                0;
                              ((((int)(i))) <= (((int)(r))));
                              
//#line 242
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 243
((x10.
                  array.
                  Array<BackBoneNode>)(backbone)).set_0_$$x10$array$Array_T$G(((BackBoneNode)(new BackBoneNode())),
                                                                              (int)(i));
            }
            
//#line 245
this.r = r;
        }
        
        
//#line 248
public static BAG
                       BAG_CREATE(
                       final int r){
            
//#line 249
return new BAG(r);
        }
        
        
//#line 253
public void
                       BAG_INSERT(
                       final Pennant p1){
            
//#line 254
int k =
              0;
            
//#line 255
Pennant p =
              p1;
            
//#line 257
while ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                   ((x10.
                                                                   array.
                                                                   Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                                  p,null))) {
                
//#line 259
p = p.unionPennant(((Pennant)((((BackBoneNode)
                                                              ((x10.
                                                              array.
                                                              Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                             p)));
                
//#line 260
((BackBoneNode)
                               ((x10.
                               array.
                               Array<BackBoneNode>)(backbone)).apply$G((int)(((((int)(k = ((((int)(k))) + (((int)(1))))))) - (((int)(1))))))).p = null;
            }
            
//#line 264
((BackBoneNode)
                           ((x10.
                           array.
                           Array<BackBoneNode>)(backbone)).apply$G((int)(k))).p = p;
            
//#line 266
this.size = ((((int)(size))) + (((int)(p.
                                                                  size))));
        }
        
        
//#line 269
public void
                       BAG_INSERT(
                       final Node x){
            
//#line 270
int k =
              0;
            
//#line 271
Pennant p =
              new Pennant(x);
            
//#line 274
while ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                   ((x10.
                                                                   array.
                                                                   Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                                  p,null))) {
                
//#line 275
p = p.unionPennant(((Pennant)((((BackBoneNode)
                                                              ((x10.
                                                              array.
                                                              Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                             p)));
                
//#line 276
((BackBoneNode)
                               ((x10.
                               array.
                               Array<BackBoneNode>)(backbone)).apply$G((int)(((((int)(k = ((((int)(k))) + (((int)(1))))))) - (((int)(1))))))).p = null;
            }
            
//#line 281
((BackBoneNode)
                           ((x10.
                           array.
                           Array<BackBoneNode>)(backbone)).apply$G((int)(k))).p = p;
            
//#line 282
BAG.__$closure$apply$__114(((BAG)(this)),
                                                    (int)(1));
        }
        
        
//#line 285
private AdderResult
                       FA(
                       final Pennant x,
                       final Pennant y,
                       final Pennant z){
            
//#line 287
AdderResult ar =
              new AdderResult();
            
//#line 289
if (x10.rtt.Equality.equalsequals(x,null)) {
                
//#line 290
if (x10.rtt.Equality.equalsequals(y,null)) {
                    
//#line 291
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 292
ar.s = null;
                        
//#line 293
ar.c = null;
                    } else {
                        
//#line 297
ar.s = z;
                        
//#line 298
ar.c = null;
                    }
                } else {
                    
//#line 302
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 303
ar.s = y;
                        
//#line 304
ar.c = null;
                    } else {
                        
//#line 308
ar.s = null;
                        
//#line 309
ar.c = y.unionPennant(((Pennant)(z)));
                    }
                }
            } else {
                
//#line 315
if (x10.rtt.Equality.equalsequals(y,null)) {
                    
//#line 316
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 317
ar.s = x;
                        
//#line 318
ar.c = null;
                    } else {
                        
//#line 322
ar.s = null;
                        
//#line 323
ar.c = x.unionPennant(((Pennant)(z)));
                    }
                } else {
                    
//#line 327
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 328
ar.s = null;
                        
//#line 329
ar.c = x.unionPennant(((Pennant)(y)));
                    } else {
                        
//#line 333
ar.s = x;
                        
//#line 334
ar.c = y.unionPennant(((Pennant)(z)));
                    }
                }
            }
            
//#line 340
return ar;
        }
        
        public static AdderResult
          FA$P(
          final Pennant x,
          final Pennant y,
          final Pennant z,
          final BAG BAG){
            return BAG.FA(((Pennant)(x)),
                          ((Pennant)(y)),
                          ((Pennant)(z)));
        }
        
        
//#line 345
public void
                       BAG_UNION(
                       final BAG b){
            
//#line 346
Pennant y =
              null;
            
//#line 347
AdderResult ar =
               null;
            
//#line 348
int i1 =
               0;
            
//#line 348
int i2 =
               0;
            
//#line 348
int i3 =
               0;
            
//#line 349
i1 = BAG.findBAGSIZE((int)(this.
                                                      size));
            
//#line 350
i2 = BAG.findBAGSIZE((int)(b.
                                                      size));
            
//#line 351
if (((((int)(i1))) > (((int)(i2))))) {
                
//#line 352
i3 = ((((int)(i1))) + (((int)(1))));
            } else {
                
//#line 354
i3 = ((((int)(i2))) + (((int)(1))));
            }
            
//#line 358
for (
//#line 358
int k =
                                0;
                              ((((int)(k))) <= (((int)(i3))));
                              
//#line 358
k = ((((int)(k))) + (((int)(1))))) {
                
//#line 359
ar = this.FA(((Pennant)((((BackBoneNode)
                                                        ((x10.
                                                        array.
                                                        Array<BackBoneNode>)(this.
                                                                               backbone)).apply$G((int)(k)))).
                                                       p)),
                                          ((Pennant)((((BackBoneNode)
                                                        ((x10.
                                                        array.
                                                        Array<BackBoneNode>)(b.
                                                                               backbone)).apply$G((int)(k)))).
                                                       p)),
                                          ((Pennant)(y)));
                
//#line 360
((BackBoneNode)
                               ((x10.
                               array.
                               Array<BackBoneNode>)(this.
                                                      backbone)).apply$G((int)(k))).p = ar.
                                                                                          s;
                
//#line 361
y = ar.
                                   c;
            }
            
//#line 363
this.size = ((((int)(this.
                                                size))) + (((int)(b.
                                                                    size))));
        }
        
        
//#line 366
public BAG
                       BAG_SPLIT(
                       ){
            
//#line 367
BAG b =
              BAG.BAG_CREATE((int)(r));
            
//#line 368
Pennant y =
              (((BackBoneNode)
                 ((x10.
                 array.
                 Array<BackBoneNode>)(this.
                                        backbone)).apply$G((int)(0)))).
                p;
            
//#line 369
((BackBoneNode)
                           ((x10.
                           array.
                           Array<BackBoneNode>)(this.
                                                  backbone)).apply$G((int)(0))).p = null;
            
//#line 370
for (
//#line 370
int k =
                                1;
                              ((((int)(k))) <= (((int)(r))));
                              
//#line 370
k = ((((int)(k))) + (((int)(1))))) {
                
//#line 371
if ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                    ((x10.
                                                                    array.
                                                                    Array<BackBoneNode>)(this.
                                                                                           backbone)).apply$G((int)(k)))).
                                                                   p,null))) {
                    
//#line 372
((BackBoneNode)
                                   ((x10.
                                   array.
                                   Array<BackBoneNode>)(b.
                                                          backbone)).apply$G((int)(((((int)(k))) - (((int)(1))))))).p = (((BackBoneNode)
                                                                                                                           ((x10.
                                                                                                                           array.
                                                                                                                           Array<BackBoneNode>)(this.
                                                                                                                                                  backbone)).apply$G((int)(k)))).
                                                                                                                          p.splitPennant();
                    
//#line 373
((BackBoneNode)
                                   ((x10.
                                   array.
                                   Array<BackBoneNode>)(this.
                                                          backbone)).apply$G((int)(((((int)(k))) - (((int)(1))))))).p = (((BackBoneNode)
                                                                                                                           ((x10.
                                                                                                                           array.
                                                                                                                           Array<BackBoneNode>)(this.
                                                                                                                                                  backbone)).apply$G((int)(k)))).
                                                                                                                          p;
                    
//#line 374
((BackBoneNode)
                                   ((x10.
                                   array.
                                   Array<BackBoneNode>)(this.
                                                          backbone)).apply$G((int)(k))).p = null;
                }
            }
            
//#line 381
if ((!x10.rtt.Equality.equalsequals(y,null))) {
                
//#line 382
this.BAG_INSERT(((Pennant)(y)));
            }
            
//#line 385
if (((int) ((((int)(size))) % (((int)(2))))) ==
                             ((int) 0)) {
                
//#line 386
this.size = ((((int)(size))) / (((int)(2))));
                
//#line 387
b.size = size;
            } else {
                
//#line 392
b.size = ((((int)(size))) / (((int)(2))));
                
//#line 393
this.size = ((((int)(b.
                                                    size))) + (((int)(1))));
            }
            
//#line 397
return b;
        }
        
        
//#line 401
public boolean
                       BAG_IS_EMPTY(
                       ){
            
//#line 402
return ((int) size) ==
            ((int) 0);
        }
        
        
//#line 405
public static int
                       findBAGSIZE(
                       int n){
            
//#line 406
int i =
              0;
            
//#line 407
while (((((int)(n))) > (((int)(0))))) {
                
//#line 408
n = ((((int)(n))) / (((int)(2))));
                
//#line 409
i = ((((int)(i))) + (((int)(1))));
            }
            
//#line 411
return i;
        }
        
        
//#line 414
public void
                       BAG_PROCESS(
                       BAG OUT_BAG,
                       final int d){
            
//#line 416
if (((((int)(size))) < (((int)(BAG.GRAINSIZE))))) {
                
//#line 417
for (
//#line 417
int i =
                                    0;
                                  ((((int)(i))) <= (((int)(r))));
                                  
//#line 417
i = ((((int)(i))) + (((int)(1))))) {
                    
//#line 418
if ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                        ((x10.
                                                                        array.
                                                                        Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                                                       p,null))) {
                        
                    }
                }
                
//#line 425
return;
            }
            
//#line 427
BAG NEW_BAG =
               null;
            
//#line 428
NEW_BAG = this.BAG_SPLIT();
            {
                
//#line 429
x10.
                  lang.
                  Runtime.ensureNotInAtomic();
                {
                    
//#line 429
final BAG[] $NEW_BAG122 =
                      new BAG[1];
                    
//#line 429
$NEW_BAG122[0]=NEW_BAG;
                    
//#line 429
try {try {{
                        
//#line 429
x10.
                          lang.
                          Runtime.startFinish();
                        {
                            
//#line 430
final BAG ob =
                              new BAG(OUT_BAG.
                                        r);
                            
//#line 431
x10.
                              lang.
                              Runtime.runAsync(new x10.core.fun.VoidFun_0_0() {public final void apply() { try {{
                                                   
//#line 431
BAG p1$NEW_BAG122 =
                                                     ((BAG)$NEW_BAG122[0]);
                                                   {
                                                       
//#line 433
p1$NEW_BAG122.BAG_PROCESS(((BAG)(ob)),
                                                                                              (int)(d));
                                                   }
                                               }}catch (x10.runtime.impl.java.X10WrappedThrowable ex) {x10.lang.Runtime.pushException(ex);}}
                                               public x10.rtt.RuntimeType<?> getRTT() { return _RTT;}public x10.rtt.Type<?> getParam(int i) {return null;
                                               }
                                               });
                            
//#line 435
this.BAG_PROCESS(((BAG)(OUT_BAG)),
                                                          (int)(d));
                            
//#line 436
OUT_BAG.BAG_UNION(((BAG)(ob)));
                        }
                    }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__0__) {
                        
//#line 429
x10.
                          lang.
                          Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__0__)));
                        throw new x10.
                          lang.
                          RuntimeException();
                    }finally {{
                         
//#line 429
x10.
                           lang.
                           Runtime.stopFinish();
                     }}
                    
//#line 429
NEW_BAG = ((BAG)$NEW_BAG122[0]);
                    }
                }
            }
        
        
//#line 443
public void
                       BAG_PRINT(
                       ){
            
//#line 444
for (
//#line 444
int i =
                                0;
                              ((((int)(i))) <= (((int)(r))));
                              
//#line 444
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 445
if (x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                  ((x10.
                                                                  array.
                                                                  Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                                                 p,null)) {
                    
//#line 446
x10.
                      io.
                      Console.OUT.println(((java.lang.Object)("-")));
                } else {
                    
//#line 450
(((BackBoneNode)
                                    ((x10.
                                    array.
                                    Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                   p.printPennant();
                    
//#line 451
x10.
                      io.
                      Console.OUT.println();
                }
            }
        }
        
        
//#line 234
final private void
                       __fieldInitializers108(
                       ){
            
//#line 234
this.backbone = null;
            
//#line 234
this.r = 0;
            
//#line 234
this.size = 0;
        }
        
        final public static void
          __fieldInitializers108$P(
          final BAG BAG){
            BAG.__fieldInitializers108();
        }
        
        final private static int
          __$closure$apply$__114(
          final BAG x,
          final int y){
            
//#line 282
return x.size = ((((int)(x.
                                                    size))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__114$P(
          final BAG x,
          final int y){
            return BAG.__$closure$apply$__114(((BAG)(x)),
                                              (int)(y));
        }
        
    }
    