#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofLogToFile("/home/pi/assets/logFile.txt", true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0,0,0);

	consoleListener.setup(this);
    
    TTF.loadFont("/home/pi/assets/mono.ttf", 40 );
    TTFSmall.loadFont("/home/pi/assets/mono.ttf", 20 );
    
    ofDisableAntiAliasing();

    dir.allowExt("mp4");
	dir.listDir("/home/pi/movies");
	//dir.listDir("~/desktop/");           //for Mac Testing
    

	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

	// you can now iterate through the files and load them into the ofImage vector
	currentIndex = 0;
    
    
    openIndieBG.loadImage("/home/pi/assets/openindie.png");
    
    helpActive = false;
    moviePlaying = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){

/*
if (moviePlaying){
if (ofGetElapsedTimef() > startTime + mediaTime){
	omxPlayer.close();
	moviePlaying = false;
	ofLogVerbose(__func__) << " :: movie ended closing OMX - return to OF";
}
}
*/
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(ofColor::white);
    openIndieBG.draw(0,0);
    

	if (dir.size() > 0){
		ofSetColor(ofColor::white);
        
        

		string pathInfo = dir.getName(currentIndex);
        ofStringReplace(pathInfo, ".mp4", "");
        ofStringReplace(pathInfo, ".", " ");
		TTF.drawString(pathInfo, 960-(TTF.stringWidth(pathInfo)/2), 550);

	}

    if (helpActive){
	ofSetColor(ofColor::gray);
	for(int i = 0; i < (int)dir.size(); i++){
		if(i == currentIndex) {
			ofSetColor(ofColor::red);
		}	else {
			ofSetColor(ofColor::black);
		}
		string fileInfo = dir.getName(i);
		TTFSmall.drawString(fileInfo, 150,(1080-((3+dir.size())*30) + (i * 30)));
	}
    }

}

//--------------------------------------------------------------

void ofApp :: openOMXPlayer (int index){

	string videoPath = dir.getPath(currentIndex);
	
    //Somewhat like ofFboSettings we may have a lot of options so this is the current model
    ofxOMXPlayerSettings settings;
    settings.videoPath = videoPath;
    settings.useHDMIForAudio = true;    //default true
    settings.enableTexture = false;     //default true
    settings.enableLooping = false;     //default true
    settings.enableAudio = true;        //default true, save resources by disabling
    //settings.doFlipTexture = true;        //default false

    
    omxPlayer.setup(settings);

    mediaTime = omxPlayer.getDuration();
    startTime = ofGetElapsedTimef();
    moviePlaying = true;
    ofLogVerbose(__func__) << " :: starting movie: " << dir.getPath(currentIndex);
}

//--------------------------------------------------------------

void ofApp :: openChildApp (int index)
{
	string shCommand = "/usr/bin/open";
    string shPath = dir.getPath(currentIndex);
    
    ofLogVerbose() << "command :: " << shPath << endl;
    cout << "command :: " << shPath << endl;
    
    //system(shPath.c_str());

    
	
	char *shPathChar;
	shPathChar = new char[ shPath.length() + 1 ];
	char *shCommandChar;
	shCommandChar = new char[ shCommand.length() + 1 ];
	
	strcpy( shPathChar, shPath.c_str() );
	strcpy( shCommandChar, shCommand.c_str() );
	
	//--
	
	int pid = fork();
	
	ofLogVerbose() << "pid :: " << pid << endl;
	
	switch ( pid )
	{
            case -1 :
			
			ofLogVerbose() << "Uh-Oh! fork() failed.\n" << endl;
			
            case  0 :
			
			//execl( shCommandChar, shPathChar, NULL );
			//execl( "/usr/bin/open", "open", shPathChar, NULL ); mac command
			execl( "/usr/bin/omxplayer", "omxplayer", shPathChar, NULL ); // pi command

		default :
			
			return;
	}
			moviePlaying = true;
			//ofSetFrameRate(1);
			//ofLogVerbose() << "movie started - exiting app" << endl;
			//ofExit();
}

//--------------------------------------------------------------
//  EVENT Listener for OMXPlayer

void ofApp::onCharacterReceived(SSHKeyListenerEventData& e)
{
    keyPressed((int)e.character);
}

void ofApp::onVideoEnd(ofxOMXPlayerListenerEventData& e)
{
    ofLogVerbose(__func__) << " RECEIVED";
    omxPlayer.close();
    moviePlaying = false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	ofLogVerbose(__func__) << "key: " << key;

	if (dir.size() > 0){
        if (key == 'j'){
            currentIndex--;
            if (currentIndex == -1) currentIndex = dir.size()-1;
            currentIndex %= dir.size();
            string videoPath = dir.getPath(currentIndex);
            ofLogVerbose() << videoPath;
       }

        if (key == 'k'){
            currentIndex++;
            currentIndex %= dir.size();
            string videoPath = dir.getPath(currentIndex);
            ofLogVerbose() << videoPath;

        }

        if (key == OF_KEY_UP){
            currentIndex--;
            if (currentIndex == -1) currentIndex = dir.size()-1;
            currentIndex %= dir.size();
            string videoPath = dir.getPath(currentIndex);
            ofLogVerbose() << videoPath;            
        }

        if (key == OF_KEY_DOWN){
            currentIndex++;
            currentIndex %= dir.size();
            string videoPath = dir.getPath(currentIndex);
            ofLogVerbose() << videoPath;
        }

        if (key == 'o'){
            openOMXPlayer(currentIndex);
        }

        if (key == 'x'){
            omxPlayer.close();
            moviePlaying = false;
        }

        if (key == 'e'){
            omxPlayer.close();
            moviePlaying = false;
        }

        if (key == 'h'){
            helpActive = !helpActive;
        }

        if (key == 'q'){
            ofExit();
        }

        if (key == '['){
            omxPlayer.increaseVolume();
        }
        if (key == ']'){
            omxPlayer.decreaseVolume();
        }

        
	}
	//ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::exit(){
	//omxPlayer.close();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
