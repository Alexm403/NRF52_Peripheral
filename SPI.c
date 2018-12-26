void init_SPI (char port, char SCK, char MOSI,char MISO, char CS, int speed, char EN)
{
if(port ==0){
NRF_P0->PIN_CNF[SCK]= 0x000F;//out
NRF_P0->PIN_CNF[MOSI]=0x000F;//out
NRF_P0->PIN_CNF[MISO]=0x000E;//input
NRF_P0->PIN_CNF[CS]=  0x000F;//out
NRF_P0->DIRSET &= 1<<SCK;
NRF_P0->DIRSET &= 1<<MOSI;
NRF_P0->DIRCLR &= 1<<MISO;//input
NRF_P0->DIRSET &= 1<<CS;
}
else
{
 
}
NRF_SPI0->PSELSCK = SCK;
NRF_SPI0->PSELMOSI = MOSI;
NRF_SPI0->PSELMISO = MISO;
 
switch (speed){
case 125: NRF_SPI0->FREQUENCY = 0x02000000;break;//125k
case 250: NRF_SPI0->FREQUENCY = 0x04000000;break;//250k
case 500: NRF_SPI0->FREQUENCY = 0x08000000;break;//500k
case 1:   NRF_SPI0->FREQUENCY = 0x10000000;break;//1m
case 2:   NRF_SPI0->FREQUENCY = 0x20000000;break;//2m
case 4:   NRF_SPI0->FREQUENCY = 0x40000000;break;//4m
case 8:   NRF_SPI0->FREQUENCY = 0x80000000;break;//8m
default:  NRF_SPI0->FREQUENCY = 0x10000000;break;//1m
}
 
if(EN==1)NRF_SPI0->ENABLE = 1; else NRF_SPI0->ENABLE = 0;
 
}
 
 
NRF_P0->PIN_CNF[17]=0x0033;
NRF_P0->DIRSET &= 1<<17;
 
void cs (char c){
if (c==1)NRF_P0->OUTSET=1<<17;
else
NRF_P0->OUTCLR=1<<17;
}
 
 
uint8_t spi_put(uint8_t c) {
  NRF_SPI0->TXD = c;
  while (NRF_SPI0->EVENTS_READY == 0);
  NRF_SPI0->EVENTS_READY = 0;
  return NRF_SPI0->RXD;
}
 
 
 
 
 
init_SPI (0, 19, 20, 21, 17, 2, 1);
cs(1);
void wen (void){
cs(0);
spi_put(06);
cs(1);
}
 
 
wen();
while (1){
cs(0);
spi_put(0x9F);
spi_put(0xFF);
spi_put(0xFF);
 
 
cs(1);
nrf_delay_us(15);
 
 
 
};
