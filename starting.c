/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <stdio.h>
#include <stdbool.h>
#include "camera_x11.h"

//using namespace std;

bool isRubyPresent(int current){
	if (current != 0){
		return true;
	}
	else{
		return false;
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
	display_picture();

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

	//if ruby is present
	if(rubyPresent){
		printf("Ruby is present\n");
		for (int row = 0; row < 50; row++) {
                for (int col = 0; col < 50; col++) {
                    set_pixel(row, col, 0, 255, 0);
                }
            }


	}else{
		//ruby is not present
		printf("Ruby is not present\n");

		for (int row = 0; row < 480; row++) {
                for (int col = 0; col < 640; col++) {
                    set_pixel(row, col, 255, 0, 0);
                }
            }
		return 0;
	}
	
	//close_screen_stream();
	//return 0;	

}
	

  }  




