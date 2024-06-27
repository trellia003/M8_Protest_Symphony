void confermation_voiceover_sound() {
  int number_of_audios = 4;
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
  int number_of_audios = 1;
  stop_flag_servo();
  if (!is_flag_raised) {
    raise_flag_servo();
    Serial.println("raise servo");
  }
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(1);
      displayLED(1, accomodation_percentage);

      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    lower_flag_servo();
    Serial.println("lower servo");
    response_switch_index++;
    current_audio_index = 0;
  }
}

void ignore_response() {
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(2);

      displayLED(2, ignore_percentage);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
  }
}

void dispersal_response() {
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(3);
      displayLED(3, dispersal_percentage);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
  }
}

void arrest_response() {
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(4);
      displayLED(4, arrest_percentage);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
  }
}

void violence_response() {
  int number_of_audios = 1;
  if (current_audio_index < number_of_audios) {
    if (!is_audio_player_running) {
      play_response_sound(5);
      displayLED(5, violence_percentage);
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
  }
}