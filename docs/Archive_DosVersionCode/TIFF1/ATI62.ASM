;-----------------------------------------------------------
;
;  File:   ATI62.ASM
;
;  Desc:   Functions to read and write scan lines in
;          ATI mode 62h (640 x 480 x 256-colors)
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]
arg5  equ  [bp+14]

; local variables

tmp1  equ  [bp-2]
ntmp  equ  2

public _put_pixels_62, _get_pixels_62

.code

;-----------------------------------------------------------
;  Desc:  Map extended video memory page
;  In:    CH = page number (0-4 for mode 62h)
;  Out:   nothing (all registers preserved)
;-----------------------------------------------------------

map_page proc near
		 ret
map_page endp

;-----------------------------------------------------------
;  Desc:  Compute page and offset of X,Y pixel coordinate
;  In:    BX = Y
;         CX = X
;  Out:   AX = Offset
;         CH = Page
;-----------------------------------------------------------

pxl_addr proc near
		 ret
pxl_addr endp

;-----------------------------------------------------------
;  Desc:  Write scan line in ATI mode 62h
;  Use:   void put_pixels_62( unsigned char *pixels
;                             int npixels, int x, int y );
;-----------------------------------------------------------

_put_pixels_62 proc
		 ; stack frame, save regs
		 ret
_put_pixels_62 endp

;-----------------------------------------------------------
;  Desc:  Read scan line in ATI mode 62h
;  Use:   void get_pixels_62( unsigned char *pixels
;                             int npixels, int x, int y );
;-----------------------------------------------------------

_get_pixels_62 proc
		 ; stack frame, save regs
		 ret
_get_pixels_62 endp

end
