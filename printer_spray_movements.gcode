;
; Preamble
;
M300 S440 P200 ; Play a tone through the beeper
M140 S105 ; Bed heating temperature
M190 S105 ; Bed heating temperature
M117 Spray start. ; Print a message on the LCD.
G28 XY ; Home all axes
G91 ; Set all axes to relative
G0 X45 Y60 F9999 ; set the starting position
; All three of the Ender 3s have an advertised and usable print area of 220 x 220 mm. However, the size of the build surface actually measures 235 x 235 mm
M302 S0 ; cold extrusion: always allow extrusion (disable checking)
;M425 F0
M204 P99999 ; increase acceleration for avoiding small pauses between steps
;M201 X9999 Y9999
;
; S shaped path, starting at south-west, ending at north-east
;
G1 X120 E30
G3 X0 Y20 I0 J10 E5
G1 X-120 E30
G2 X0 Y20 I0 J10 E5
G1 X120 E30
G3 X0 Y20 I0 J10 E5
G1 X-120 E30
G2 X0 Y20 I0 J10 E5
G1 X120 E30
G3 X0 Y20 I0 J10 E5
G1 X-120 E30
G2 X0 Y20 I0 J10 E5
G0 X120
;
; go to (210,235) towards north-east (235,235) corner and wait drying
M117 Sleep for drying.
G0 X45 Y55
G4 S30
G1 X-45 Y-55 E10
;
; N shaped path, starting at north-east, ending at south-west
;
G1 Y-120 E30
G1 X-20 E5
G1 Y120 E30
G1 X-20 E5
G1 Y-120 E30
G1 X-20 E5
G1 Y120 E30
G1 X-20 E5
G1 Y-120 E30
G1 X-20 E5
G1 Y120 E30
G1 X-20 E5
G0 Y-120
;
; go to (15,40) towards south-west (0,0) corner and wait drying
M117 Sleep for drying.
G0 X-30 Y-20
G4 S30
M117 Spray.
G1 X30 Y20 E10
; 
; \\\ shaped path, starting at south-west, ending at north-west
;
G1 Y20 E5
G1 X20 Y-20 E5
G1 X20 E5
G1 X-40 Y40 E10
G1 Y20 E5
G1 X60 Y-60 E15
G1 X20 E5
G1 X-80 Y80 E20
G1 Y20 E5
G1 X100 Y-100 E25
G1 X20 E5
G0 X-120 Y120
;
; go to (15,235) towards north-west (0,235) corner and wait drying
M117 Sleep for drying.
G0 X-30 Y55
G4 S30
M117 Spray.
G1 X30 Y-55 E10
;
; /// shaped path, starting at north-west, ending at north-east
;
G1 X20 E5
G1 X-20 Y-20 E5
G1 Y-20 E5
G1 X40 Y40 E10
G1 X20 E5
G1 X-60 Y-60 E15
G1 Y-20 E5
G1 X80 Y80 E20
G1 X20 E5
G1 X-100 Y-100 E25
G1 Y-20 E5
G0 X120 Y120
;
; go to (210,235) towards north-east (235,235) corner and wait drying
M117 Sleep for drying.
G0 X45 Y55
G4 S30
M117 Spray.
G1 X-45 Y-55 E10
;
; \\\ shaped path, starting at north-east, ending at south-east
;
G1 Y-20 E5
G1 X-20 Y20 E5
G1 X-20 E5
G1 X40 Y-40 E10
G1 Y-20 E5
G1 X-60 Y60 E15
G1 X-20 E5
G1 X80 Y-80 E20
G1 Y-20 E5
G1 X-100 Y100 E25
G1 X-20 E5
G0 X120 Y-120
;
; go to (210,40) towards south-east (235,0) corner and wait drying
M117 Sleep for drying.
G0 X45 Y-20
G4 S30
M117 Spray.
G1 X-45 Y20 E10
;
; /// shaped path, starting at south-east, ending at south-west
;
G1 X-20 E5
G1 X20 Y20 E5
G1 Y20 E5
G1 X-40 Y-40 E10
G1 X-20 E5
G1 X60 Y60 E15
G1 Y20 E5
G1 X-80 Y-80 E20
G1 X-20 E5
G1 X100 Y100 E25
G1 Y20 E5
G0 X-120 Y-120
;
; Ending
M117 Spray finished.
;
G28 XY; Home all axes
