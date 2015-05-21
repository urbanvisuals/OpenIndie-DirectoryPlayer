#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ConsoleListener.h"

class ofApp : public ofBaseApp, public SSHKeyListener{
	
	public:
		
		void setup();
		void update();
		void draw();
		void exit();
				
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
        void openChildApp(int index);
        void openOMXPlayer(int index);

        void onVideoEnd(ofxOMXPlayerListenerEventData& e);

		void onCharacterReceived(SSHKeyListenerEventData& e);
		ConsoleListener consoleListener;

    
		
		// we will have a dynamic number of images, based on the content of a directory:
		ofDirectory dir;
        ofTrueTypeFont TTF;
        ofTrueTypeFont TTFSmall;
        ofImage openIndieBG;
      	ofxOMXPlayer omxPlayer;


		int currentIndex;

		double mediaTime;
		double startTime;
    
    bool helpActive;
    bool moviePlaying;

		
};

