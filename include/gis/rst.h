
#ifndef RST_H  
#define RST_H

#define RSTIDN 0x00545352L

#define RSTVEROLD 0x0201
#define RSTVER    0x0202

typedef struct RST  {

ULONG IDN;     // ιδεξτιζιλατος ξαώαμα ζακμα  0x00545352(RST0)
ULONG LEN;     // δμιHα ζακμα σ ϊαηομοχλον
unsigned short int AVR;     // λομιώεστχο Cτςολ οβύεε
unsigned short int AHR;     // λομιώεστχο στομβγοχ οβύεε
unsigned short int BVR;     // λ-χο βμολοχ πο χεςτιλαμι
unsigned short int BHR;     // λ-χο βμολοχ πο ηοςιϊοξταμι
unsigned short int EVR;     // λ-χο στςολ  χ βμολε
unsigned short int EHR;     // λ-χο στομβγοχ χ βμολε
unsigned short int DVR;     // λ-χο στςολ χ βμολε ποσμεδHεηο ςρδα
unsigned short int DHR;     // λ-χο στομβγοχ χ βμολε ποσμεδHεκ λομοHλι
unsigned short int BSZ;     // ςαϊνες βμολα (βακτ)
unsigned short int ESZ;     // ςαϊνες όμενεHτα (βιτ)
unsigned short int DSZ;     // ςαϊνες βμολα ποσμεδHεηο ςρδα
unsigned short int EDZ;     // ώισμο όμενεHτοχ Hα δΰκν

unsigned short int FLG_BORD : 1;     // ζμαη υσταHοχμεHHοστι ςανλι
unsigned short int FLG_STPR : 1;     // ζμαη σοστορHιρ πςοελγιι 
unsigned short int FLG_COLR : 1;     // ζμαη γχετα οτοβςαφεHιρ  
unsigned short int FLG_PRCN : 1;     // ζμαη υσταHοχμεHHοστι ώισμο όμενεHτοχ Hα δΰκν 
unsigned short int FLG_RESR : 12;    // ζμαφλι σοστορHιρ οβςαβοτλι

  LONG RMX;     // θ ςανλι μιστα
  LONG RMY;     // Y ςανλι μιστα
unsigned short int VER;     // χεςσιρ στςυλτυςω  2.2
unsigned short int SER;     // σμυφεβHοε πομε
unsigned short int X1 ;     // λοοςδιHατα X (|) HιφHεηο μεχοηο υημα
unsigned short int Y1 ;     // λοοςδιHατα Y (->) HιφHεηο μεχοηο υημα
unsigned short int X2 ;     // λοοςδιHατα X χεςθHεηο μεχοηο υημα
unsigned short int Y2 ;     // λοοςδιHατα Y χεςθHεηο μεχοηο υημα
unsigned short int X3 ;     // λοοςδιHατα X χεςθHεηο πςαχοηο υημα
unsigned short int Y3 ;     // λοοςδιHατα Y χεςθHεηο πςαχοηο υημα
unsigned short int X4 ;     // λοοςδιHατα X HιφHεηο πςαχοηο υημα
unsigned short int Y4 ;     // λοοςδιHατα Y HιφHεηο πςαχοηο υημα
unsigned char  COLOR  ;     // γχετ οτοβςαφεHιρ ώ/β ςαστςα  
unsigned char  FLG_NEW_HEADER;  // ζμαη συύεστχοχαξιρ ϊαηομοχλα ξοχοκ
                            // στςυλτυςω πο σνεύεξιΰ LEN (0/1)

						  } RST ;

typedef struct RSTPAL  {

                        RST Rst;        // πςεφHικ ϊαηομοχολ
                        char Pal[48];   // παμιτςα δμρ 16 γχετοχ

                       } RSTPAL ;    
 
#endif   // RST_H
