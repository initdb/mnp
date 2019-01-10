void* mymemcpy(void* ziel, const void* quelle, size_t anzahl)
{
    asm
    {     
        naked                   //oder alternativ:   asm void* ... 

                       // zum Spass eine lokale Variable (2 Bytes),
                                    // wird hier aber nicht gebraucht
        adda    #-12, sp
        movem.l d2/a2-a3,(sp)      //Register sichern

                  //Anzahl hole              
                  //Quelleadresse holen
                   //Zieladresse holen
    loop:                
        move.b  (a2)+,(a3)+        //byteweise kopieren
                
        subi.l   #1,d2
        bne     loop               //anzahl mal wiederholen

                   //Rueckgabewert nach a0
                
        movem.l (sp),d2/a2-a3      //Register holen
        adda    #12, sp            //Stack i.O. bringen                  
                        //Stackframe abbauen
        
    }
}