public class BAG
extends x10.core.Ref
{
    public static final x10.rtt.RuntimeType<BAG> _RTT = new x10.rtt.RuntimeType<BAG>(
    /* base class */BAG.class
    , /* parents */ new x10.rtt.Type[] {x10.rtt.Types.OBJECT}
    ) {public String typeName() {return "BAG";}};
    public x10.rtt.RuntimeType<?> getRTT() {return _RTT;}
    
    
    
        
//#line 378
public x10.
          array.
          Array<BackBoneNode>
          backbone;
        
//#line 379
public int
          r;
        
//#line 380
public int
          size;
        
//#line 381
final public static int
          GRAINSIZE =
          128;
        
        
//#line 383
public BAG(final int r) {
            super();
            
//#line 377
this.__fieldInitializers164();
            
//#line 384
this.backbone = ((x10.
              array.
              Array)(new x10.
              array.
              Array<BackBoneNode>(BackBoneNode._RTT,
                                  ((((int)(r))) + (((int)(1)))))));
            
//#line 385
for (
//#line 385
int i =
                                0;
                              ((((int)(i))) <= (((int)(r))));
                              
//#line 385
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 386
((x10.
                  array.
                  Array<BackBoneNode>)(backbone)).set_0_$$x10$array$Array_T$G(((BackBoneNode)(new BackBoneNode())),
                                                                              (int)(i));
            }
            
//#line 388
this.r = r;
        }
        
        
//#line 391
public static BAG
                       BAG_CREATE(
                       final int r){
            
//#line 392
return new BAG(r);
        }
        
        
//#line 396
public void
                       BAG_INSERT(
                       final Pennant p1){
            
//#line 397
int k =
              0;
            
//#line 398
Pennant p =
              p1;
            
//#line 400
while ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                   ((x10.
                                                                   array.
                                                                   Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                                  p,null))) {
                
//#line 402
p = p.unionPennant(((Pennant)((((BackBoneNode)
                                                              ((x10.
                                                              array.
                                                              Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                             p)));
                
//#line 403
((BackBoneNode)
                               ((x10.
                               array.
                               Array<BackBoneNode>)(backbone)).apply$G((int)(((((int)(k = ((((int)(k))) + (((int)(1))))))) - (((int)(1))))))).p = null;
            }
            
//#line 407
((BackBoneNode)
                           ((x10.
                           array.
                           Array<BackBoneNode>)(backbone)).apply$G((int)(k))).p = p;
            
//#line 409
this.size = ((((int)(size))) + (((int)(p.
                                                                  size))));
        }
        
        
//#line 412
public void
                       BAG_INSERT(
                       final Vertex x){
            
//#line 413
int k =
              0;
            
//#line 414
Pennant p =
              new Pennant(x);
            
//#line 417
while ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                   ((x10.
                                                                   array.
                                                                   Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                                  p,null))) {
                
//#line 418
p = p.unionPennant(((Pennant)((((BackBoneNode)
                                                              ((x10.
                                                              array.
                                                              Array<BackBoneNode>)(backbone)).apply$G((int)(k)))).
                                                             p)));
                
//#line 419
((BackBoneNode)
                               ((x10.
                               array.
                               Array<BackBoneNode>)(backbone)).apply$G((int)(((((int)(k = ((((int)(k))) + (((int)(1))))))) - (((int)(1))))))).p = null;
            }
            
//#line 424
((BackBoneNode)
                           ((x10.
                           array.
                           Array<BackBoneNode>)(backbone)).apply$G((int)(k))).p = p;
            
//#line 425
BAG.__$closure$apply$__219(((BAG)(this)),
                                                    (int)(1));
        }
        
        
//#line 428
private AdderResult
                       FA(
                       final Pennant x,
                       final Pennant y,
                       final Pennant z){
            
//#line 430
AdderResult ar =
              new AdderResult();
            
//#line 432
if (x10.rtt.Equality.equalsequals(x,null)) {
                
//#line 433
if (x10.rtt.Equality.equalsequals(y,null)) {
                    
//#line 434
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 435
ar.s = null;
                        
//#line 436
ar.c = null;
                    } else {
                        
//#line 440
ar.s = z;
                        
//#line 441
ar.c = null;
                    }
                } else {
                    
//#line 445
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 446
ar.s = y;
                        
//#line 447
ar.c = null;
                    } else {
                        
//#line 451
ar.s = null;
                        
//#line 452
ar.c = y.unionPennant(((Pennant)(z)));
                    }
                }
            } else {
                
//#line 458
if (x10.rtt.Equality.equalsequals(y,null)) {
                    
//#line 459
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 460
ar.s = x;
                        
//#line 461
ar.c = null;
                    } else {
                        
//#line 465
ar.s = null;
                        
//#line 466
ar.c = x.unionPennant(((Pennant)(z)));
                    }
                } else {
                    
//#line 470
if (x10.rtt.Equality.equalsequals(z,null)) {
                        
//#line 471
ar.s = null;
                        
//#line 472
ar.c = x.unionPennant(((Pennant)(y)));
                    } else {
                        
//#line 476
ar.s = x;
                        
//#line 477
ar.c = y.unionPennant(((Pennant)(z)));
                    }
                }
            }
            
//#line 483
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
        
        
//#line 488
public void
                       BAG_UNION(
                       final BAG b){
            
//#line 489
Pennant y =
              null;
            
//#line 490
AdderResult ar =
               null;
            
//#line 491
int i1 =
               0;
            
//#line 491
int i2 =
               0;
            
//#line 491
int i3 =
               0;
            
//#line 492
i1 = BAG.findBAGSIZE((int)(this.
                                                      size));
            
//#line 493
i2 = BAG.findBAGSIZE((int)(b.
                                                      size));
            
//#line 494
if (((((int)(i1))) > (((int)(i2))))) {
                
//#line 495
i3 = ((((int)(i1))) + (((int)(1))));
            } else {
                
//#line 497
i3 = ((((int)(i2))) + (((int)(1))));
            }
            
//#line 499
for (
//#line 499
int k =
                                0;
                              ((((int)(k))) <= (((int)(i3))));
                              
//#line 499
k = ((((int)(k))) + (((int)(1))))) {
                
//#line 500
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
                
//#line 501
((BackBoneNode)
                               ((x10.
                               array.
                               Array<BackBoneNode>)(this.
                                                      backbone)).apply$G((int)(k))).p = ar.
                                                                                          s;
                
//#line 502
y = ar.
                                   c;
            }
            
//#line 504
this.size = ((((int)(this.
                                                size))) + (((int)(b.
                                                                    size))));
        }
        
        
//#line 507
public BAG
                       BAG_SPLIT(
                       ){
            
//#line 508
BAG b =
              BAG.BAG_CREATE((int)(r));
            
//#line 509
Pennant y =
              (((BackBoneNode)
                 ((x10.
                 array.
                 Array<BackBoneNode>)(this.
                                        backbone)).apply$G((int)(0)))).
                p;
            
//#line 510
((BackBoneNode)
                           ((x10.
                           array.
                           Array<BackBoneNode>)(this.
                                                  backbone)).apply$G((int)(0))).p = null;
            
//#line 511
for (
//#line 511
int k =
                                1;
                              ((((int)(k))) <= (((int)(r))));
                              
//#line 511
k = ((((int)(k))) + (((int)(1))))) {
                
//#line 512
if ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                    ((x10.
                                                                    array.
                                                                    Array<BackBoneNode>)(this.
                                                                                           backbone)).apply$G((int)(k)))).
                                                                   p,null))) {
                    
//#line 513
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
                    
//#line 514
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
                    
//#line 515
((BackBoneNode)
                                   ((x10.
                                   array.
                                   Array<BackBoneNode>)(this.
                                                          backbone)).apply$G((int)(k))).p = null;
                }
            }
            
//#line 522
if ((!x10.rtt.Equality.equalsequals(y,null))) {
                
//#line 523
this.BAG_INSERT(((Pennant)(y)));
            }
            
//#line 526
if (((int) ((((int)(size))) % (((int)(2))))) ==
                             ((int) 0)) {
                
//#line 527
this.size = ((((int)(size))) / (((int)(2))));
                
//#line 528
b.size = size;
            } else {
                
//#line 533
b.size = ((((int)(size))) / (((int)(2))));
                
//#line 534
this.size = ((((int)(b.
                                                    size))) + (((int)(1))));
            }
            
//#line 538
return b;
        }
        
        
//#line 542
public boolean
                       BAG_IS_EMPTY(
                       ){
            
//#line 543
return ((int) size) ==
            ((int) 0);
        }
        
        
//#line 546
public static int
                       findBAGSIZE(
                       int n){
            
//#line 547
int i =
              0;
            
//#line 548
while (((((int)(n))) > (((int)(0))))) {
                
//#line 549
n = ((((int)(n))) / (((int)(2))));
                
//#line 550
i = ((((int)(i))) + (((int)(1))));
            }
            
//#line 552
return i;
        }
        
        
//#line 555
public void
                       BAG_PROCESS(
                       BAG OUT_BAG,
                       final int d){
            
//#line 557
if (((((int)(size))) < (((int)(BAG.GRAINSIZE))))) {
                
//#line 558
for (
//#line 558
int i =
                                    0;
                                  ((((int)(i))) <= (((int)(r))));
                                  
//#line 558
i = ((((int)(i))) + (((int)(1))))) {
                    
//#line 559
if ((!x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                        ((x10.
                                                                        array.
                                                                        Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                                                       p,null))) {
                        
//#line 561
(((BackBoneNode)
                                        ((x10.
                                        array.
                                        Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                       p.processPennant(((BAG)(OUT_BAG)),
                                                        (int)(d));
                    }
                }
                
//#line 566
return;
            }
            
//#line 568
BAG NEW_BAG =
               null;
            
//#line 569
NEW_BAG = this.BAG_SPLIT();
            {
                
//#line 570
x10.
                  lang.
                  Runtime.ensureNotInAtomic();
                {
                    
//#line 570
final BAG[] $NEW_BAG230 =
                      new BAG[1];
                    
//#line 570
$NEW_BAG230[0]=NEW_BAG;
                    
//#line 570
try {try {{
                        
//#line 570
x10.
                          lang.
                          Runtime.startFinish();
                        {
                            
//#line 571
final BAG ob =
                              new BAG(OUT_BAG.
                                        r);
                            
//#line 572
x10.
                              lang.
                              Runtime.runAsync(new x10.core.fun.VoidFun_0_0() {public final void apply() { try {{
                                                   
//#line 572
BAG p1$NEW_BAG230 =
                                                     ((BAG)$NEW_BAG230[0]);
                                                   {
                                                       
//#line 574
p1$NEW_BAG230.BAG_PROCESS(((BAG)(ob)),
                                                                                              (int)(d));
                                                   }
                                               }}catch (x10.runtime.impl.java.X10WrappedThrowable ex) {x10.lang.Runtime.pushException(ex);}}
                                               public x10.rtt.RuntimeType<?> getRTT() { return _RTT;}public x10.rtt.Type<?> getParam(int i) {return null;
                                               }
                                               });
                            
//#line 576
this.BAG_PROCESS(((BAG)(OUT_BAG)),
                                                          (int)(d));
                            
//#line 577
OUT_BAG.BAG_UNION(((BAG)(ob)));
                        }
                    }}catch (x10.runtime.impl.java.X10Throwable __t__) {throw __t__;}catch (java.lang.RuntimeException __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Exception(__e__);}catch (java.lang.Error __e__) {throw x10.runtime.impl.java.X10Throwable.getCorrespondingX10Error(__e__);}}catch (x10.runtime.impl.java.X10Throwable __desugarer__var__4__) {
                        
//#line 570
x10.
                          lang.
                          Runtime.pushException(((x10.runtime.impl.java.X10Throwable)(__desugarer__var__4__)));
                        throw new x10.
                          lang.
                          RuntimeException();
                    }finally {{
                         
//#line 570
x10.
                           lang.
                           Runtime.stopFinish();
                     }}
                    
//#line 570
NEW_BAG = ((BAG)$NEW_BAG230[0]);
                    }
                }
            }
        
        
//#line 584
public void
                       BAG_PRINT(
                       ){
            
//#line 585
for (
//#line 585
int i =
                                0;
                              ((((int)(i))) <= (((int)(r))));
                              
//#line 585
i = ((((int)(i))) + (((int)(1))))) {
                
//#line 586
if (x10.rtt.Equality.equalsequals((((BackBoneNode)
                                                                  ((x10.
                                                                  array.
                                                                  Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                                                 p,null)) {
                    
//#line 587
x10.
                      io.
                      Console.OUT.println(((java.lang.Object)("-")));
                } else {
                    
//#line 591
(((BackBoneNode)
                                    ((x10.
                                    array.
                                    Array<BackBoneNode>)(backbone)).apply$G((int)(i)))).
                                   p.printPennant();
                    
//#line 592
x10.
                      io.
                      Console.OUT.println();
                }
            }
        }
        
        
//#line 377
final private void
                       __fieldInitializers164(
                       ){
            
//#line 377
this.backbone = null;
            
//#line 377
this.r = 0;
            
//#line 377
this.size = 0;
        }
        
        final public static void
          __fieldInitializers164$P(
          final BAG BAG){
            BAG.__fieldInitializers164();
        }
        
        final private static int
          __$closure$apply$__219(
          final BAG x,
          final int y){
            
//#line 425
return x.size = ((((int)(x.
                                                    size))) + (((int)(y))));
        }
        
        final public static int
          __$closure$apply$__219$P(
          final BAG x,
          final int y){
            return BAG.__$closure$apply$__219(((BAG)(x)),
                                              (int)(y));
        }
        
    }
    