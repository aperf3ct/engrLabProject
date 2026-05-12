/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <stdio.h>
#include "camera_x11.h"

//using namespace std;

int main() {
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }
   
  // make 1000 runs  
  for (int countrun = 0; countrun < 10000; countrun++) {
	take_picture();
	display_picture();
	int totRed = 0;
	int totInt = 0;
	double redness = 0.0;
    // for all pixels in latest image
    for (int row = 0 ; row < 480 ; row++) {	
		for (int col = 0; col < 640; col++) {
			uchar r, g ,b ;
			get_pixel(row, col, &r, &g ,&b);
			totRed = totRed + r;
			totInt = totInt + (r+g+b)/3;
			redness = (double)totRed/(3.0*(double)totInt);
		}
	}

	printf(" countrun: %d\n",countrun);
	printf(" Total red:%d\n",totRed);
	printf(" Total intensity: %d\n",totInt);
	printf("  redness : %f\n", redness);
	//sleep1(1000); // slow down a bit to make display easier
	
  }  
  //close_screen_stream();
  return 0;
}
