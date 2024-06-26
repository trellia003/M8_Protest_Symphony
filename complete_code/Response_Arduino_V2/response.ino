void accomodate_response(int percentage) {
  //LED shown
  inner_response_LED(response_switch_index, percentage);
  //Play sound
  // playResponseSound(response_switch_index);
  //Raise Flag
  int flag_raise = 1;
  while (flag_raise == 1) {
    flag_servo_control();
    flag_raise = 0;
  }
}
// 