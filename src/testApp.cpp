#include "testApp.h"
#include "ofxMSAUtils.h"

#define kTextHeight				14		// height of text in pixels

ofTrueTypeFont	font;
bool			isVSynced		= false;
float			paddingFactor	= 0.05;
int				lineDuration	= 1000;		// in ms;
bool			doPause			= false;


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(isVSynced);
	ofSetBackgroundAuto(false);
	
	font.loadFont("Courier New Bold.ttf", 256, true, false, true);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	if(doPause) return;
	
	glClear( GL_COLOR_BUFFER_BIT);
	
	float padding = ofGetWidth() * paddingFactor;
	int timeNow = ofGetElapsedTimeMillis();

	
	// display time
	glColor4f(0.75, 0.75, 0.75, 1);
	string s = ofToString(timeNow % 1000);
	if(s.length() == 2) s = "0" + s;
	else if(s.length() == 1) s = "00" + s;
	
	ofRectangle rect = font.getStringBoundingBox(s, 0, 0);
	float cx = rect.x + rect.width / 2;
	float cy = rect.y + rect.height / 2;
	float scale = 0.5 * ofGetWidth() * 1.0f/rect.width;
		
	glPushMatrix();
	glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
	glScalef(scale, scale, 1);
	font.drawString(s, -cx, -cy);
	glPopMatrix();
	
	// display line
	int numSegments = (ofGetHeight()-kTextHeight) / kTextHeight;
	int timeMod = timeNow % lineDuration;
	float y = ofMap(timeNow % lineDuration, 0, lineDuration-1, kTextHeight/2, kTextHeight + numSegments * kTextHeight);
	glColor4f(1, 1, 1, 1);
	ofLine(0, y, ofGetWidth(), y);

	
	// draw scale
	float timeSize = lineDuration * 1.0f / numSegments;
	for(int i=0; i<=numSegments; i++) {
		string s = "----- " + ofToString(i * timeSize, 3) + " -----";
		static msaColor col;
		col.setHSV((i*45)%360, 1, 1);
		col.setGL();
		ofDrawBitmapString(s, ofGetWidth() - padding - s.length() * 9, i * kTextHeight + kTextHeight);
	}
	
	
	
	glColor4f(1, 1, 1, 1);
	ofDrawBitmapString("The Mega Super Awesome Visuals Company\n\nwww.msavisuals.com \n\ntimeSize: " + ofToString(timeSize, 3) + "ms | colorCycle: " + ofToString(timeSize * 8, 3) + "ms \n\nvsync (v): " + ofToString(isVSynced) + " | lineDuration (d/D): " + ofToString(lineDuration) + "\n\n" + ofToString(ofGetFrameRate(), 2), padding, padding+14);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
		
		case 'v':
			isVSynced ^= true;
			ofSetVerticalSync(isVSynced);
			break;
			
		case 'D':
			if(lineDuration < 10000) lineDuration += 100;
			else lineDuration = 10000;
			break;
			
		case 'd':
			if(lineDuration > 100) lineDuration -= 100;
			else lineDuration = 100;
			break;
			
//		case 'P':
//			if(paddingFactor < 0.25) paddingFactor += 0.01;
//			else paddingFactor = 0.25;
//			break;
			
		case 'p':
//			if(paddingFactor > 0) paddingFactor -= 0.01;
//			else paddingFactor = 0;
			doPause ^= true;
			break;
			
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

