void* mymemcpy(void* ziel, const void* quelle, size_t anzahl)
{
    asm
    {     
        naked                   //oder alternativ:   asm void* ... 

        LINK A6,#-2             // zum Spass eine lokale Variable (2 Bytes),
                                // wird hier aber nicht gebraucht
        
        adda    #-12, sp
        movem.l d2/a2-a3,(sp)      //Register sichern

        // parameter zugriff
        MOVE.L 16(A6),D2          //Anzahl holen              
        MOVE.L 12(A6),A2          //Quelleadresse holen
        MOVE.L 8(A6),A3           //Zieladresse holen
    loop:                
        move.b  (a2)+,(a3)+        //byteweise kopieren
                
        subi.l   #1,d2
        bne     loop               //anzahl mal wiederholen

        //Rueckgabewert
        MOVE.L 8(A6),A0           //Rueckgabewert nach a0
                
        MOVEM.L (SP),D2/A2-A3      //Register wiederherstellen
        ADDA.L #12,SP              //Stack i.O. bringen                  
        UNLK A6                    //Stackframe abbauen
        RTS
    }
}

main() {
    asm { 
                MOVE.L  #20, -(SP)  //Anzahl auf Stack
                PEA     string1
                PEA     string2
                JSR mymemcpy    //Aufruf von mymemcpy
                ADDA.L #10,SP    //Stack bereinigen (Parameterplatz freigeben)
    }
}