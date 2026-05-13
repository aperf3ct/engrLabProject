/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "camera_x11.h"

//using namespace std;

bool isRubyPresent(int current){
	if (current > 100){
		return true;
	}
	else{
		return false;
	}
}

void applyVisualFeedback(bool found){
	if (found){
		//makes square green
		for (int row = 0; row < 50; row++) {
                for (int col = 0; col < 50; col++) {
                    set_pixel(row, col, 0, 255, 0);
                }
            }
	} else{
		//gets time and prints it
		time_t currentTime;
    	time(&currentTime);
		printf("Current time: %s", ctime(&currentTime)); 

		//makes screen red
		for (int row = 0; row < 480; row++) {
                for (int col = 0; col < 640; col++) {
                    set_pixel(row, col, 255, 0, 0);
                }
            }
	}

}

int main() {

	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

  // make 1000 runs  
  for (int countrun = 0; countrun < 10000; countrun++) {
	take_picture();
	
	int currentRedPixelCount = 0;
	
    
	// for all pixels in latest image
    for (int row = 0 ; row < 480 ; row++) {	
		for (int col = 0; col < 640; col++) {
			uchar r, g ,b ;
			get_pixel(row, col, &r, &g ,&b);

			if (r > 150 && r > g + 40 && r > b + 40) { 
                currentRedPixelCount++; 

			}
		}
	}
	bool rubyPresent = isRubyPresent(currentRedPixelCount);
	
	applyVisualFeedback(rubyPresent);
	
	display_picture();

	//close_screen_stream();
	//return 0;	

	}
	
}  




