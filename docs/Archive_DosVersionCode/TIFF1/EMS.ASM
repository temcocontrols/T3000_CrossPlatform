;-----------------------------------------------------------
;
;  File:   EMS.ASM
;
;  Desc:   Minimal function set required to utilize
;          EMS memory from DOS real mode application
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]
arg5  equ  [bp+14]

public _EMS_installed, _EMS_pgframeaddr
public _EMS_alloc, _EMS_free, _EMS_mappage

.data

dd_name db 'EMMXXXX0'

.code

;-----------------------------------------------------------
;  Desc:  Test for presence of EMS driver. Returns 1 if
;         found or 0 if not found.
;  Use:   int EMS_installed( void );
;-----------------------------------------------------------

_EMS_installed proc far

     ; save registers
     push ds
     push es
     push di
     push si

     ; es:di -> name in device drvr hdr
     mov  al, 67h
     mov  ah, 35h
     int  21h
     mov  di, 10

     ; ds:si -> expected name
     mov  si, seg dd_name
     mov  ds, si
     mov  si, offset dd_name

     ; compare names
     mov  cx, 8
     cld
     repz cmpsb
     jnz  EMS_installed_1

     ; EMS driver found
     mov  ax, 1
     jmp  short EMS_installed_2

  EMS_installed_1:
     ; EMS driver not found
     xor  ax, ax

  EMS_installed_2:
     pop  si
     pop  di
     pop  es
     pop  ds
     ret

_EMS_installed endp

;-----------------------------------------------------------
;  Desc:  Get address of specified physical page in
;         EMS page frame buffer.
;  Use:   char * EMS_pgframeaddr( int physical_pg );
;  In:    logical page number (0 - 3)
;  Out:   far pointer to specified page
;-----------------------------------------------------------

_EMS_pgframeaddr proc far

     push bp
     mov  bp, sp
     push bx

     ; page frame seg in bx
     mov  ah, 41h
     int  67h

     ; test for error
     or   ah, ah
     jz   EMS_pgframeaddr_1

     ; error - return null pointer
     xor  dx, dx
     xor  ax, ax
     jmp short EMS_pgframeaddr_2

   EMS_pgframeaddr_1:
     ; set dx:ax to requested address
     push bx
     mov  ax, 4000h   ; page size
     mov  bx, arg1    ; page number
     mul  bx
     pop  dx

   EMS_pgframeaddr_2:
     pop  bx
     pop  bp
     ret

_EMS_pgframeaddr endp

;-----------------------------------------------------------
;  Desc:  Allocate EMS memory
;  Use:   int EMS_alloc( int npages );
;  In :   Number of 16K pages to allocate
;  Out:   EMS handle or -1 on error
;-----------------------------------------------------------

_EMS_alloc proc far

     push bp
     mov  bp, sp

     ; request allocation
     mov  bx, arg1    ; bx = page count
     mov  ah, 43h     ; func 43h = alloc pages
     int  67h

     ; test for error
     or   ah, ah
     jz   EMS_alloc_1

     ; allocation failed
     mov  ax, 0FFFFh
     jmp  short EMS_alloc_2

   EMS_alloc_1:
     ;allocation successful
     mov  ax, dx   ; ax = handle

   EMS_alloc_2:
     pop  bp
     ret

_EMS_alloc endp

;-----------------------------------------------------------
;  Desc:  Free EMS memory
;  Use:   void EMS_free( int EMShandle );
;  In :   Handle returned by EMS_alloc()
;-----------------------------------------------------------

_EMS_free proc far

     push bp
     mov  bp, sp

     mov  dx, arg1    ; DX = EMS handle
     mov  ah, 45h     ; func 45h = free pages
     int  67h

     pop  bp
     ret

_EMS_free endp

;-----------------------------------------------------------
;  Desc:  Map EMS logical page to physical page
;  Use:   int EMS_mappage( int hand, int lpage, int ppage );
;  In :   hand - EMS handle from EMS_alloc
;         lpage - logical page number
;         ppage - physical page in frame buffer
;  Out :  EMS return code (0 = success)
;-----------------------------------------------------------

_EMS_mappage proc far

     push bp
     mov  bp, sp
     push bx

     ; map page
     mov  dx, arg1
     mov  bx, arg2
     mov  al, arg3
     mov  ah, 44h
     int  67h

     ; reformat return code
     xchg ah, al
     xor  ah, ah

     pop  bx
     pop  bp
     ret

_EMS_mappage endp

end
