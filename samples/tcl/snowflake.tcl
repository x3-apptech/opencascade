# Creation of 2d drawing

#Category: Modeling
#Title: Snowflake - creation of 2d drawing

pload MODELING VISUALIZATION

puts "Generating sample drawing of snowflake..."

# make circular elements
circle c11 5 5 0 5
circle c12 5 5 0 3
circle c21 18 7 0 7
circle c22 18 7 0 5
circle c31 28.5 5 0 5
circle c32 28.5 5 0 3
trim c21 c21 pi/4 -pi/4
trim c22 c22 pi/4 -pi/4
trim c31 c31 pi/4 -pi/4
trim c32 c32 pi/4 -pi/4
line l21 18 7 0 1 1 0
line l22 18 7 0 1 -1 0
line l31 28.5 5 0 1 1 0
line l32 28.5 5 0 1 -1 0
trim l21 l21 5 7
trim l22 l22 5 7
trim l31 l31 3 5
trim l32 l32 3 5
line l1 -6 0 0 0.86602540378443864 0.5 0
line l2 -6 1 0 1 0 0
trim l1 l1 0 30
trim l2 l2 0 45
mkedge c11 c11
mkedge c12 c12
mkedge c21 c21
mkedge c22 c22
mkedge c31 c31
mkedge c32 c32
mkedge l21 l21
mkedge l22 l22
mkedge l31 l31
mkedge l32 l32
mkedge l1 l1
mkedge l2 l2
wire b11 c11
wire b12 c12
orientation b12 R

# build one ray
plane p -6 0 0 0 0 1
mkface f1 p b11
add b12 f1
wire b2 c21 l21 c22 l22
mkface f2 p b2
wire b3 c31 l31 c32 l32
mkface f3 p b3
prism f5 l1 -5 8.6602540378443864 0
prism f4 l2 0 -1 0
compound f1 f2 f3 bc
bfuse r bc f4
bcut r r f5
tcopy r r1
tmirror r1 -6 0 0 0 1 0
bfuse w r r1
unifysamedom w w
donly w

# construct complete snowflake
tcopy w w1
tcopy w w2
tcopy w w3
tcopy w w4
tcopy w w5
trotate w1 -6 0 0 0 0 1 60
trotate w2 -6 0 0 0 0 1 120
trotate w3 -6 0 0 0 0 1 180
trotate w4 -6 0 0 0 0 1 240
trotate w5 -6 0 0 0 0 1 300
bfuse w w w1
bfuse w w w2
bfuse w w w3
bfuse w w w4
bfuse w w w5
shape wsh Sh
foreach f [explode w f] {add $f wsh}
renamevar wsh w
unifysamedom r w

# keep only wires in compound
eval compound [explode r w] snowflake
tscale snowflake -6 0 0 1.5

# draw frame loosely following GOST 2.104-68
polyline frame -100 -100 0 172 -100 0 172 100 0 -100 100 0 -100 -100 0
polyline t1 52 -100 0 52 -45 0 172 -45 0
polyline t2 52 -60 0 172 -60 0
polyline t3 52 -85  0 172 -85 0
polyline t4 122 -100 0 122 -60 0
polyline t5 122 -80 0 172 -80 0
polyline t6 122 -65 0 172 -65 0
polyline t7 142 -80 0 142 -85 0
polyline t8 137 -80 0 137 -60 0
polyline t9 154 -80 0 154 -60 0
compound frame t1 t2 t3 t4 t5 t6 t7 t8 t9 lines

# add text
text2brep sample "SAMPLE" -font Arial -height 10 -pos 90 -55 0 -aspect bolditalic
text2brep occ "Open CASCADE" -font Times -height 6 -pos 125 -95 0
text2brep name "Snowflake" -font Courier -height 7 -pos 65 -75 0 -aspect italic
text2brep material "Ice" -font Courier -height 7 -pos 75 -95 0 -aspect italic
text2brep sheets "Sheets 1" -font Courier -height 3.5 -pos 145 -83 0 -aspect italic
text2brep scale "Scale\n\n1:100" -font Courier -height 3.5 -pos 157 -63 0 -aspect italic -valign topfirstline
text2brep mass "Mass\n\n1 mg" -font Courier -height 3.5 -pos 140 -63 0 -aspect italic -valign topfirstline
eval compound [explode sample w] sample
eval compound [explode occ w] occ
eval compound [explode name w] name
eval compound [explode material w] material
eval compound [explode sheets w] sheets
eval compound [explode scale w] scale
eval compound [explode mass w] mass
compound sample occ name material sheets scale mass text

compound snowflake lines text drawing
bounding snowflake -save x1 y1 z1 x2 y2 z2

# display in 3d view
vinit Driver1/Viewer1/View1 w=1024 h=768
vdisplay snowflake lines text
vrenderparams -msaa 8
vsetcolor snowflake BLACK
vsetcolor lines BLACK
vsetcolor text  BLACK
vbackground -color WHITE
vtop
vfit

# add dimension:
# detect vertices extremal in X direction
plane f1 x1 0 0 1 0 0
plane f2 x2 0 0 1 0 0
mkface f1 f1
mkface f2 f2
bsection s1 snowflake f1
bsection s2 snowflake f2
# select only upper vertices (nearer to the upper bound)
explode s1 v
explode s2 v
plane fup 0 y2 0 0 1 0
mkface fup fup
for {set i 1} {$i <= 2} {incr i} {
  set dmin 1e10
  for {set j 1} {$j <= 2} {incr j} {
    distmini d s${i}_$j fup
    set dist [dval d_val]
    if {$dmin > $dist} {
      set dmin $dist
      eval set v$i s${i}_$j
    }
  }
}
vdimension length -length -shapes $v1 $v2 -plane xoy -value 0.001 -dispunits mm -showunits -flyout 70 -label above -color black -text 5 3d sh
