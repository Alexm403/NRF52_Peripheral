APP_TIMER_DEF(my_IRQ);


static void my_IRQ_handler (void * p_context)
{
static int click=0,tik=0, tick, a_tik=0,ststus_BLE,battery;

if (click==0)
{
  bsp_board_led_on(BSP_BOARD_LED_1);
  app_timer_stop(my_IRQ);
  app_timer_start(my_IRQ, APP_TIMER_TICKS(1),NULL);
  click=1;
  return;
  
}

if (click==1)
{
  bsp_board_led_off(BSP_BOARD_LED_1);
  app_timer_stop(my_IRQ);
  app_timer_start(my_IRQ, APP_TIMER_TICKS(100),NULL);
  click=0;
}
}

main(){
app_timer_create(&my_IRQ, APP_TIMER_MODE_REPEATED ,my_IRQ_handler);
app_timer_start(my_IRQ, APP_TIMER_TICKS(50),NULL);

while(1){};
}
