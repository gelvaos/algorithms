int NUMBER_ELEMS = 10;

DataArray arr;

int sorting_idx = 0;
int compare_idx = 0;
int swapping_idx = 0;


void setup() {
  // int window_width = int (nelems * (ewidth + (2 * margin)) + (2 * margin));
  // int window_height = 200;
  size (650, 300);
  smooth ();
  frameRate (3);
  arr = new DataArray(NUMBER_ELEMS);
}

void draw() {
  background(0);
  //selection_sort();
  insertion_sort();
  arr.draw();
}

void insertion_sort() {
  if (sorting_idx < NUMBER_ELEMS) {
    switch(arr.state) {
    case IDLE:
      if (compare_idx > 0) swapping_idx = compare_idx - 1;
      else swapping_idx = 0;
      arr.index1 = swapping_idx;
      arr.index2 = compare_idx;
      arr.state = COMPARE;
      break;
    case COMPARE:
      if (compare_idx > 0
          && arr.elems[compare_idx].value < arr.elems[swapping_idx].value) {

        arr.index1 = swapping_idx;
        arr.index2 = compare_idx;
        swapping_idx = compare_idx - 1;

        arr.state = SWAPPING_START;
      }
      compare_idx--;
      if (compare_idx > 0) swapping_idx = compare_idx - 1;
      else swapping_idx = 0;
      if (compare_idx < 0) {
        arr.state = SWAPPING_END;
        sorting_idx++;
        compare_idx = sorting_idx;
      }
      break;
    case SWAPPING_END:
      if (compare_idx <= 0 
          || arr.elems[compare_idx].value > arr.elems[swapping_idx].value) {
        sorting_idx++;
        compare_idx = sorting_idx;
        swapping_idx = compare_idx - 1;
      }
      break;
    }
  }
}


void debug_print_state () {
  switch (arr.state) {
  case IDLE:
    println ("State: IDLE");
    break;
  case COMPARE:
    println ("State: COMPARE");
    break;
  case SWAPPING_START:
    println ("State: SWAPPING_START");
    break;
  case SWAPPING_IN_PROGRESS:
    println ("State: SWAPPING_IN_PROGRESS");
    break;
  case SWAPPING_END:
    println ("State: SWAPPING_END");
    break;
  }
}

void debug_print_elems() {
  print("elems=");
  for (int i = 0; i < NUMBER_ELEMS; i++)
    print(arr.elems[i].value + " ");
  println("");
}
