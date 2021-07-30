;
; Preamble
;
M300 S440 P200 ; Play a tone through the beeper
M140 S100
M190 S100
M117 Spray start. ; Print a message on the LCD.
G28 XY; Home all axes
; All three of the Ender 3s have an advertised and usable print area of 120 x 120 mm. However, the size of the build surface actually measures 235 x 235 mm
M302 S0      ; cold extrusion: always allow extrusion (disable checking)
G91 ; Set all axes to relative
G0 X50 Y80 F9999 ; set the starting position
;G1 Z80 E1 ; lift spray at 8 cm
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
G1 X120 E30
;
; maximum X position is 235, maximum Y position is 235
G0 X65 Y35
G4 S30
G0 X-65 Y-35
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
G1 Y-120 E30
;
G0 X-50 Y-80
G4 S30
G0 X50 Y80
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
G1 X-120 Y120 E30
;
;G1 X20 E5
;G1 X100 Y-100 E25
;G1 Y20 E5
;G1 X-80 Y80 E20
;G1 X20 E5
;G1 X60 Y-60 E15
;G1 Y20 E5
;G1 X-40 Y40 E10
;G1 X20 E5
;G1 X20 Y-20 E5
;G1 Y20 E5
;
G0 X-50 Y35
G4 S30
G0 X50 Y-35
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
G1 X120 Y120 E30
;
G0 X65 Y35
G4 S30
G0 X-65 Y-35
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
G1 X120 Y-120 E30
;
G0 X65 Y-80
G4 S30
G0 X-65 Y80
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
G1 X-120 Y-120 E20
;
; Ending
;
G28 XY; Home all axes
