void confermation_voiceover_sound() {
  int number_of_audios = 1;  //set to 4
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_selection_voiceover();
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
  }
}

void accomodate_response() {
  stop_flag_servo();
  if (!has_run_once_every_response) {
    // displayLED(1, accomodation_percentage);
    reset_LED();
    Serial3.println("1," + String(violence_percentage) + "," + String(accomodation_percentage));

    raise_flag_servo();
    has_run_once_every_response = true;
  }

  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(1);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    lower_flag_servo();
    response_switch_index++;
    current_audio_index = 0;
    has_run_once_every_response = false;
  }
}

void ignore_response() {
  if (!has_run_once_every_response) {
    // displayLED(2, ignore_percentage);
    current_state = MOVE_OUT;
    has_run_once_every_response = true;
  }
  servoControl();
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(2);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
    has_run_once_every_response = false;
  }
}

void dispersal_response() {
  if (!has_run_once_every_response) {
    // displayLED(3, dispersal_percentage);
    digitalWrite(FOG_PIN, HIGH);
    has_run_once_every_response = true;
  }
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(3);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    digitalWrite(FOG_PIN, LOW);
    response_switch_index++;
    current_audio_index = 0;
    has_run_once_every_response = false;
  }
}

void arrest_response() {
  if (!has_run_once_every_response) {
    // displayLED(4, arrest_percentage);
    has_run_once_every_response = true;
  }
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(4);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
    has_run_once_every_response = false;
  }
}

void violence_response() {
  if (!has_run_once_every_response) {
    // displayLED(5, violence_percentage);
    has_run_once_every_response = true;
  }
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(5);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
    has_run_once_every_response = false;
  }
}