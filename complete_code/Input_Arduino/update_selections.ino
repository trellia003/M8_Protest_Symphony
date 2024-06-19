void update_selections() {  //retreive the new vales, add them in the array and shift the old values
  update_decade();
  update_region();
  update_protest();
}

void update_decade() {
  int new_decade = get_decade();            //get the new value
  selected_decade[1] = selected_decade[0];  //shift old value
  selected_decade[0] = new_decade;          //add new value
}

void update_region() {
  int new_region = get_region();
  selected_region[1] = selected_region[0];
  selected_region[0] = new_region;
}

void update_protest() {
  int new_protest = get_protest();
  selected_protest[1] = selected_protest[0];
  selected_protest[0] = new_protest;
}


int get_decade() {  //read the decade and convert it to 0,1,2,3
}

int get_region() {  //read the region and convert it to 0,1,2,3
}


int get_protest() {  //read the protest and convert it to 0,1,2,3
}