.device attiny13


rjmp reset ; 0x00
reti                 ; 0x01
rcall changeMode     ; 0x02  pc int 0
rjmp counterOverflow ; 0x03 timer overflow
reti                 ; 0x04
reti                 ; 0x05
rjmp counterMatch    ; 0x06 compare match
reti                 ; 0x07
reti                 ; 0x08
reti                 ; 0x09
reti                 ; 0x0a

changeMode:
  push r16
  in r16, $3F
  push r16
  push r17

  in r16, $16
  cbr r16, $f7          ; rising edge only
  brne endOfChangeMode

  busyBoi:
  in r16, $1c     ; make sure ready to read
  sbrc r16, 1
   rjmp busyBoi

  clr r17
  out $1E, r17 ; set address to 0

  sbr r16, $01 ; ask to read
  out $1c, r16
  
  in r17, $1d   ; get data

  cpi r17, $FF
  breq turnToMorse
  ;turn to on
    ldi r17, $FF
    out $1d, r17
    sbi $1c, 2
    sbi $1c, 1

  sbi $18, 4
  clr r16
  out $33, r16 ; stop counter

rjmp endOfChangeMode

  
  turnToMorse:
    ldi r17, $00
    out $1d, r17
    sbi $1c, 2
    sbi $1c, 1

    ldi r16, $01 ; restart counter
    out $33, r16

 endOfChangeMode:
 pop r17
 pop r16
 out $3F, r16
 pop r16
reti

counterOverflow:
  push r16
  in r16, $3f
  push r16

  in r16, $36
  cpi r16, $10
  brne setThatBit
 
  
  pop r16
  out $3F, r16
  pop r16
  
  reti
  setThatBit: 

  pop r16
  out $3F, r16
  pop r16
  
  
  sbi $18, 4
reti

counterMatch:
 cbi $18, 4
reti

reset:
  ldi r16, $00
  out $1e, r16
  sbi $1c, 0
  in r16, $1D
  cpi r16, $FF
  breq noTimer

  ldi r16, $01
  out $33, r16 ; timer clock / 1
noTimer:

  ldi r16, $06
  out $39, r16 ; enable overflow interrupt and compareA match

  sbi $17, 4  ; pin 4 to output
  sbi $18, 3  ; pin 3 high
  sbi $18, 4

  ldi r16, $20
  out $3B, r16    ; enable pcint
  out $35, r16    ; enable sleep

  ldi r16, $08    ; pc int 3 enabled
  out $15, r16
  
  sei ; enable interrupts

  ldi r30, low(morseTable)
  ldi r31, high(morseTable)
  lsl r31
  lsl r30
  brcc no31
   inc r31
  no31:

loop:

  lpm r16, z+
  cpi r16, $FF
  brne noResetZ
    ldi r30, low(morseTable)
    ldi r31, high(morseTable)
    lsl r31
    lsl r30
    brcc noInc31
      inc r31
    noInc31:
    lpm r16, z+
  noResetZ:

  clr r18   ; counter for bit loop
  bitLoop:
    cpi r18, $08
    brsh endBitLoop
    inc r18
   cbr r24, $02
;    in r17, $18
;    cbr r17, $10
    sbrc r16, 7
      sbr r24, $02
    lsl r16
  rcall smolSilly
;    out $18, r17
;    clr r19
;    sleepLoop:
;      cpi r19, 100
;      brsh endSleepLoop
;      inc r19
;      sleep
;      nop
;    rjmp sleepLoop

;    endSleepLoop:

  rjmp bitLoop
  endBitLoop:

rjmp loop

testerLoop:
;  ldi r16, $10
;  out $36, r16
;rjmp testerLoop

  sei
  in r17, $35
  sbr r17, (1 << 5) ; sleep enable
  sleep

  ldi r24, $02
  rcall smolSilly

  ldi r24, $01
  rcall smolSilly

  ldi r24, $00
  rcall smolSilly
  sleep


rjmp testerLoop

smolSilly:
  push r16
  push r17
  push r18

  ldi r16, $00
  ldi r17, $e0
  ldi r18, $f9

  ldi r23, $ED ; sent to comp a
  sbrs r24, 0
    ldi r23, $10 ; off initially

smolSillyLoop: 
  inc r18
  brne endOfBitMeme
  ldi r18, $f9

  cpi r24, $02
  brcs finalOff
 ;finalOn:
  sbrs r24, 0
  inc r23
  out $36, r23

  cpi r23, $ED      ; on on when gets to $ED
  brne skipOnStuff
  ldi r24, $03
  skipOnStuff:

rjmp endOfBitMeme

  finalOff:
    sbrc r24, 0
      dec r23
    out $36, r23

    cpi r23, $10
    brne skipOffStuff
      clr r24
    skipOffStuff:
endOfBitMeme:
  sleep
  inc r16
  brne smolSillyLoop
  inc r17
  brne smolSillyLoop

  pop r18
  pop r17
  pop r16
ret


plzWait:
clr r20
clr r21

plzWaitLoop:
inc r20
nop
nop
nop
brne plzWaitLoop
inc r21
brne plzWaitLoop

ret

;morseTable:
;.dw $0001
.include "../morseTable.asm"


.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
.dw $ffff
