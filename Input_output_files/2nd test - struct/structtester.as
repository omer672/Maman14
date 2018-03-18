; .struct tester - checks if covers all struct edge cases

; The assembler will notice an error and line number with the error.

; 1. OK
STRCT1: .struct 100,"abcxyz123!@#"

; 2. OK
STR1:   .string "abcdefg"
;10
; 3. OK
        .struct -33,"123456"

; 4. ERROR on characters(xyz)
        .struct 4,xyz

; 5. ERROR on characters(STRCT1,"qwerty")
        .struct STRCT1,"qwerty"
				
; 6. ERROR on characters (r3,"qwerty")
        .struct r3,"qwerty"
		
; 7. ERROR on characters (r4)
        .struct 3,r4

; 8. ERROR on characters ("1234",2)
        .struct "1234",2

; 9. ERROR missing arguments
        .struct 
		
; 10. ERROR missing argument
        .struct 4

; 11. ERROR missing argument
        .struct 4,

; 12. ERROR on characters (,"12345")
        .struct -4,"8765","12345"
;40
; 13. ERROR on characters (67)
        .struct -4,"12345" 67
				
; 14. ERROR characters (3)
        cmp r1,STRCT1.3

; 15. this line is ok (struct label may be used as direct operand)
        cmp STRCT1,r1

;50 16. this line is ok (any label may be used for struct operand)
        cmp r1,STR1.1

; 17. invalid characters (.2)
        prn STRCT1.1.2

; 18. invalid characters(r2)
        prn STRCT1.r2

; 19. invalid characters (blabla)
        cmp #3,STRCT1.1 blabla
