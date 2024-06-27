void confermation_voiceover_sound() {
  // Serial.println("case 1");
  int number_of_audios = 4;
  // Serial.println("num of audios" + String(number_of_audios));
  // Serial.println("current audio index" + String(current_audio_index));
  if (current_audio_index < number_of_audios) {
    // Serial.println("player boolean:" + String(is_audio_player_running));
    if (!is_audio_player_running) {
      // Serial.println("play sound");
      play_selection_voiceover();
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    // Serial.println("case 1 last");
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
      // flag_servo_control();

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
      current_audio_index++;
    }
  } else if (!is_audio_player_running) {
    response_switch_index++;
    current_audio_index = 0;
  }
}