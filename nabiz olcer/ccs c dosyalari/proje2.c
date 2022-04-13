#include <proje2.h>

int16 atis=0;//Kalp atisi
int16 nabiz;//nabiz degeri
int16 nabiz_l;//dusuk nabiz
int16 nabiz_h;//yuksek nabiz
int16 sayac;//timer her tasmada artacak deger
int16 esik_deger = 50;//gelen analog sinyal degerinin ne kadar ustunun atis olmasi icin gereken deger bu deger kisiye gore degistirilebilir
int16 sinyal=0;//gelen analog deger
int a=0,b=0;//ad kesmede kulladigimiz degiskenler



#INT_AD//her analog dijital donusum bitisinde olusacak kesme 
void  AD_isr(void) 
{
if (sinyal>esik_deger){//gelen sinyal degeri nabiz olarak algilanirsa
a=1;//if altinda sürekli deger artirimi olamamasi icin kullandigimiz degisken a degeri 1
}
if (sinyal<esik_deger) //sinyal durumu esik degerden kucukse a degerini 0 yap
a=0;
if(a!=b)// b degeri baslangicta sifir a 1 olana kadar bu kod calismaz
{
b=a;//a yi b ye ata
if(a==1)//a hala 1 ise 
{atis++;}//nabiz atisi 1 artir

}
}

#INT_TIMER1
void  TIMER1_isr(void) // zamanlama kesmesi 
{
sayac++;// her tasmada sayaci bir artir
if(sayac==20)//10 saniye tut
{
nabiz=atis*6;// bulunan atis degerini nabiza 6 ile carpýp nabize yaz
sayac=0;//timer1 degerini sifirla 
atis=0;//atis degerini sýfýrla
}


}
#define LCD_ENABLE_PIN PIN_C0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_B3
#define LCD_DATA5 PIN_B4
#define LCD_DATA6 PIN_B5
#define LCD_DATA7 PIN_B6

#include <lcd.c>// lcd ekran baglanti pinleri

void main()

{ 

   /* kesme fonksiyonlari*/
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);  //524 ms overflow timer 2 icin
   

  
   enable_interrupts(INT_AD);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);

   lcd_init();// lcd ekran kullanima ac

   while(TRUE)
   {  
    set_adc_channel(0);//hangi analog portttan okuma yapilacaksa
    delay_us(20);// ananlog okuma gerceklesmesi icin beklemesi gereken sure
    sinyal=read_adc();//okunan analog degeri sinyal degerine ata 
    lcd_gotoxy(1,1);// lcd konumu
    printf(lcd_putc"NABIZ %ld",nabiz);// nabiz degerini ekrana yazdir
    delay_ms(100);
    lcd_gotoxy(1,2);
    printf(lcd_putc"Y_NBZ %ld",nabiz_h);// en yuksek nabizi ekrana yaz
    delay_ms(100);
    lcd_gotoxy(9,2);
    printf(lcd_putc"D_NBZ %ld",nabiz_l);// en dusuk nabizi ekrana yaz
    delay_ms(100);
  

 
   }

}




   


