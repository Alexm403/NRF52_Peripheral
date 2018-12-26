void start_TX_I2C (uint8_t adr){NRF_TWI0->ADDRESS = adr>>1;NRF_TWI0->TASKS_STARTTX=1;}
 
void start_RX_I2C (uint8_t adr){NRF_TWI0->ADDRESS = adr>>1;NRF_TWI0->TASKS_STARTRX=1;NRF_TWI0->EVENTS_BB=0;}
 
 
void write_I2C (uint8_t data)
  {
  NRF_TWI0->EVENTS_TXDSENT = 1;
  NRF_TWI0->TXD=data;
  while(NRF_TWI0->EVENTS_TXDSENT==0);
  NRF_TWI0->EVENTS_TXDSENT = 0;
  NRF_TWI0->EVENTS_BB=0;
  NRF_TWI0->EVENTS_STOPPED=0;
  NRF_TWI0->TASKS_RESUME=1;
  }
 
void stop_I2C (void){NRF_TWI0->TASKS_STOP=1;}
 
 
void tx_2b_I2C (uint8_t adr,uint8_t data1, uint8_t data2)
{
start_TX_I2C(adr);
write_I2C(data1); 
write_I2C(data2);
stop_I2C();
}
 
void tx_1b_I2C (uint8_t adr,uint8_t data1)
{
start_TX_I2C(adr);
write_I2C(data1); 
stop_I2C();
}
 
 
uint8_t rx_1b_I2C (uint8_t adr,uint8_t data1)
{
tx_1b_I2C(adr,data1);//AX
start_RX_I2C(adr);pik();pik();
stop_I2C();pik();
while(NRF_TWI0->EVENTS_RXDREADY==0);
NRF_TWI0->EVENTS_RXDREADY=0;
return NRF_TWI0->RXD;
}
 
uint16_t rx_2b_I2C (uint8_t adr,uint8_t data1)
{
tx_1b_I2C(adr,data1);
start_RX_I2C(adr);
while(NRF_TWI0->EVENTS_RXDREADY==0);
NRF_TWI0->EVENTS_RXDREADY=0;
adr = NRF_TWI0->RXD;
stop_I2C();
while(NRF_TWI0->EVENTS_RXDREADY==0);
NRF_TWI0->EVENTS_RXDREADY=0;
data1 = NRF_TWI0->RXD;
return ((uint16_t)((adr<<8) | data1));
}
 
 
 
void init_6050 (void)
{
tx_2b_I2C(0xD0,0x19,0x00);
tx_2b_I2C(0xD0,0x1A,0x00);
tx_2b_I2C(0xD0,0x1B,0xE0);
tx_2b_I2C(0xD0,0x1C,0xE0);
tx_2b_I2C(0xD0,0x23,0x00);
tx_2b_I2C(0xD0,0x6B,0x00);
}
 
 
 
 
char rxd;char rxd2;
 
init_I2C(0,30,31,0xDD,400,1);//Port,SCL,SDA,ADR,SPEED,ENABLE
nrf_delay_ms(20);
 
 
while(1){
pik();
init_6050();
uart_put (rx_1b_I2C(0xD0,0x3B));
uart_put_int(rx_2b_I2C(0xD0,0x3B));
 
}
