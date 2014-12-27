int NUMBER_ELEMS = 10;

DataArray arr;

int sorting_idx = 0;
int compare_idx = 0;
int swapping_idx = 0;


// Some constants to manage elements sizes
float ewidth = 40.0;
float eheight = 40.0;
float ecenterx = ewidth / 2.0;
float ecentery = eheight / 2.0;
float margin = 10.0;
float starty = 60.0;
float anim_steps = 6.0;

//Array state to manage different animation phases
final static int IDLE    = 0;
final static int COMPARE = 1;
final static int SWAPPING_START = 2;
final static int SWAPPING_IN_PROGRESS = 3;
final static int SWAPPING_END = 4;


class Elem {
  float x, y;
  int value;

  Elem (float x, float y, int value) {
    this.x = x;
    this.y = y;
    this.value = value;
  }

  void draw() {
    stroke(#7FE5A2);
    fill(#7FE5A2);
    rect(x, y, ewidth, eheight);
    fill(0, 0, 0);
    textAlign(LEFT);
    text(value, x + ecenterx, y + ecentery);
  }
}

class DataArray {
  int nelems;
  Elem[] elems;

  int state;
  int index1 = 0;
  int index2 = 0;


  DataArray (int nsize) {
    nelems = nsize;
    elems = new Elem[nelems];
    for (int i = 0; i < nelems; i++) {
      float x = (i * (ewidth + (2 * margin))) + (2 * margin);
      elems[i] = new Elem (x, starty + margin, int(random(100)));
      //elems[i] = new Elem (x, starty + margin, nelems - i);
    }
    // initial state idle
    state = IDLE;
  }

  void drawArrayCells() {
    stroke (#D10B25);
    noFill();
    for (int i = 0; i < nelems; i++) {
      float x = (i * (ewidth + (2 * margin))) + margin;
      rect (x, starty, ewidth + (2 * margin), eheight + (2 * margin));
    }
  }

  void drawElems() {
    for (int i = 0; i < nelems; i++) {
      elems[i].draw();
    }
  }

  void draw() {
    drawArrayCells();
    drawElems();
    switch (state) {
    case IDLE:
      break;
    case COMPARE:
      drawComparision();
      break;
    case SWAPPING_START:
    case SWAPPING_IN_PROGRESS:
    case SWAPPING_END:
      drawSwapping();
      break;
    }
  }

  void drawComparision () {
    if (index1 != index2) {
      stroke(#D10B25);
      noFill();
      float x1 = (index1 * (ewidth + (2 * margin))) + (2 * margin) + ecenterx;
      float x2 = (index2 * (ewidth + (2 * margin))) + (2 * margin) + ecenterx;
      ellipseMode(CORNER);
      arc(x1, starty - (2 * margin), x2 - x1, starty, -PI, 0);
    }
  }

  void drawSwapping () {
    // if it is the same element no need to swap
    if (index1 == index2 && state == SWAPPING_START) {
      state = SWAPPING_END;
      return;
    }

    float x1 = (index1 * (ewidth + (2 * margin))) + (2 * margin);
    float x2 = (index2 * (ewidth + (2 * margin))) + (2 * margin);

    switch (state) {
    case SWAPPING_START:
      // if it is first step we have to just change y coords to
      // move elem to bottom  
      elems[index1].y = elems[index1].y + eheight + (3 * margin);
      elems[index2].y = elems[index2].y + eheight + (3 * margin);
      state = SWAPPING_IN_PROGRESS;
      break;
    case SWAPPING_IN_PROGRESS:
      elems[index1].x = elems[index1].x + (x2 - x1) / anim_steps;
      elems[index2].x = elems[index2].x + (x1 - x2) / anim_steps;
      // Due to division could give us floating point number we
      // will not have exact X coords hence need to check with
      // some delta
      if (abs(elems[index1].x - x2) < 2
          || abs(elems[index2].x - x1) < 2) {
        elems[index1].x = x2;
        elems[index2].x = x1;
        elems[index1].y = elems[index2].y = starty + margin;
        swapElems();
        state = SWAPPING_END;
      }
      break;
    case SWAPPING_END:
      state = IDLE;
      break;
    default:
      break;
    }
  }

  void swapElems() {
    // swap elements inside array itself
    if (index1 != index2) {
      Elem e = elems[index1];
      elems[index1] = elems[index2];
      elems[index2] = e;
    }
  }
}



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
  selection_sort();
  //insertion_sort();
  arr.draw();
}


void selection_sort() {
  if (sorting_idx < NUMBER_ELEMS) {
    switch (arr.state) {
    case IDLE:
      arr.index1 = sorting_idx;
      arr.index2 = compare_idx;
      swapping_idx = sorting_idx;
      arr.state = COMPARE;
      break;
    case COMPARE:
      if (arr.elems[swapping_idx].value > arr.elems[compare_idx].value) {
        swapping_idx = compare_idx;
      }

      compare_idx++;
      arr.index2 = compare_idx;

      if (compare_idx == NUMBER_ELEMS) {
        arr.index2 = swapping_idx;
        arr.state = SWAPPING_START;
      }
      break;
    case SWAPPING_END:
      sorting_idx++;
      compare_idx = sorting_idx + 1;
      if (compare_idx == NUMBER_ELEMS) compare_idx = sorting_idx;
      break;
    }
  } 
  else {
    arr.state = IDLE;
  }
}
