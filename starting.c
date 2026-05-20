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

#define SEG_THICKNESS 10
#define DIGIT_WIDTH 50
#define DIGIT_HEIGHT 90

//draw a filled rectangle for 7 seg display
void drawRect(int top, int left, int height, int width,
              uchar r, uchar g, uchar b) {

    for (int row = top; row < top + height; row++) {
        for (int col = left; col < left + width; col++) {

            if (row >= 0 && row < 480 &&
                col >= 0 && col < 640) {

                set_pixel(row, col, r, g, b);
            }
        }
    }
}

//draw one segment
void drawSegment(int x, int y, char segment) {

    switch(segment) {

        //top
        case 'A':
            drawRect(y, x, SEG_THICKNESS, DIGIT_WIDTH, 255, 0, 0);
            break;

        //upper right
        case 'B':
            drawRect(y, x + DIGIT_WIDTH - SEG_THICKNESS,
                     DIGIT_HEIGHT/2, SEG_THICKNESS,
                     255, 0, 0);
            break;

        //lower right
        case 'C':
            drawRect(y + DIGIT_HEIGHT/2,
                     x + DIGIT_WIDTH - SEG_THICKNESS,
                     DIGIT_HEIGHT/2,
                     SEG_THICKNESS,
                     255, 0, 0);
            break;

        //bottom
        case 'D':
            drawRect(y + DIGIT_HEIGHT - SEG_THICKNESS,
                     x,
                     SEG_THICKNESS,
                     DIGIT_WIDTH,
                     255, 0, 0);
            break;

        //lower left
        case 'E':
            drawRect(y + DIGIT_HEIGHT/2,
                     x,
                     DIGIT_HEIGHT/2,
                     SEG_THICKNESS,
                     255, 0, 0);
            break;

        //upper left
        case 'F':
            drawRect(y,
                     x,
                     DIGIT_HEIGHT/2,
                     SEG_THICKNESS,
                     255, 0, 0);
            break;

        //middle
        case 'G':
            drawRect(y + DIGIT_HEIGHT/2 - SEG_THICKNESS/2,
                     x,
                     SEG_THICKNESS,
                     DIGIT_WIDTH,
                     255, 0, 0);
            break;
    }
}

//draw one digit
void drawDigit(int x, int y, int digit) {

    switch(digit) {

        case 0:
            drawSegment(x,y,'A');
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            drawSegment(x,y,'D');
            drawSegment(x,y,'E');
            drawSegment(x,y,'F');
            break;

        case 1:
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            break;

        case 2:
            drawSegment(x,y,'A');
            drawSegment(x,y,'B');
            drawSegment(x,y,'G');
            drawSegment(x,y,'E');
            drawSegment(x,y,'D');
            break;

        case 3:
            drawSegment(x,y,'A');
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            drawSegment(x,y,'D');
            drawSegment(x,y,'G');
            break;

        case 4:
            drawSegment(x,y,'F');
            drawSegment(x,y,'G');
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            break;

        case 5:
            drawSegment(x,y,'A');
            drawSegment(x,y,'F');
            drawSegment(x,y,'G');
            drawSegment(x,y,'C');
            drawSegment(x,y,'D');
            break;

        case 6:
            drawSegment(x,y,'A');
            drawSegment(x,y,'F');
            drawSegment(x,y,'E');
            drawSegment(x,y,'D');
            drawSegment(x,y,'C');
            drawSegment(x,y,'G');
            break;

        case 7:
            drawSegment(x,y,'A');
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            break;

        case 8:
            drawSegment(x,y,'A');
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            drawSegment(x,y,'D');
            drawSegment(x,y,'E');
            drawSegment(x,y,'F');
            drawSegment(x,y,'G');
            break;

        case 9:
            drawSegment(x,y,'A');
            drawSegment(x,y,'B');
            drawSegment(x,y,'C');
            drawSegment(x,y,'D');
            drawSegment(x,y,'F');
            drawSegment(x,y,'G');
            break;
    }
}

//draw :
void drawColon(int x, int y) {

    drawRect(y + 25, x, 10, 10, 255, 0, 0);
    drawRect(y + 60, x, 10, 10, 255, 0, 0);
}

void freezeScreen(){
	bool running = true;
	while(running){
	for (int countrun = 0; countrun < 200; countrun++){
		display_picture();
		}
	}
}

//checks if ruby is present
bool isRubyPresent(int current){
    return current > 50;
}

bool isRubyPresentAtStart = false;

//replies to visual feedback
void applyVisualFeedback(bool found){

    if (found){
		isRubyPresentAtStart = true;

        //green square
        for (int row = 0; row < 50; row++) {
            for (int col = 0; col < 50; col++) {
                set_pixel(row, col, 0, 255, 0);
            }
        }

    } else {
		
		//makes screen red at start if ruby isn't present
		if(isRubyPresentAtStart == false){
			//makes screen red
			for (int row = 0; row < 480; row++) {
                for (int col = 0; col < 640; col++) {
                    set_pixel(row, col, 255, 0, 0);
                }
            }
			freezeScreen();
		}

        //current time
        time_t currentTime;
        time(&currentTime);

        struct tm *timeInfo = localtime(&currentTime);

        int hour = timeInfo->tm_hour;
        int min  = timeInfo->tm_min;
        int sec  = timeInfo->tm_sec;

        //starting position
        int x = 40;
        int y = 180;

        //hour
        drawDigit(x, y, hour / 10);
        drawDigit(x + 60, y, hour % 10);

        drawColon(x + 125, y);

        //minute
        drawDigit(x + 150, y, min / 10);
        drawDigit(x + 210, y, min % 10);

        drawColon(x + 275, y);

        //second
        drawDigit(x + 300, y, sec / 10);
        drawDigit(x + 360, y, sec % 10);
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

	if (rubyPresent == false){
		freezeScreen();
		break;
	}

	//close_screen_stream();
	//return 0;	

	}
	
}
