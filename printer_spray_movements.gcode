;
; Preamble
;
M300 S440 P200 ; Play a tone through the beeper
M140 S80
M190 S80
M117 Spray start. ; Print a message on the LCD.
G28 XY; Home all axes
; All three of the Ender 3s have an advertised and usable print area of 120 x 120 mm. However, the size of the build surface actually measures 235 x 235 mm
M302 S0      ; cold extrusion: always allow extrusion (disable checking)
G91 ; Set all axes to relative
G0 X50 Y80 F9999 ; set the starting position
G1 E10 ; extrude a bit
;G1 Z80 E1 ; lift spray at 8 cm
;M425 F0
M204 P99999 ; increase acceleration for avoiding small pauses between steps
;M201 X9999 Y9999
;
; S shaped path
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
; N shaped path
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
; Ending
;
G28 XY; Home all axes
