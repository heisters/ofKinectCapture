#include "KinectCapture.h"

//--------------------------------------------------------------
void KinectCapture::setup(){
	width = ofGetWidth();
	height = ofGetHeight();
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableArbTex();
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(0,0,0);

	kinect.init();
	kinect.setVerbose(true);
	kinect.open();

	visible.allocate(kinect.width, kinect.width, OF_IMAGE_COLOR);
	depth.allocate(kinect.width, kinect.width, OF_IMAGE_GRAYSCALE);

	record = false;
}

//--------------------------------------------------------------
void KinectCapture::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		visible.setFromPixels(kinect.getPixels(), kinect.width, kinect.height, OF_IMAGE_COLOR, true);
		depth.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE, true);
	}
}

//--------------------------------------------------------------
void KinectCapture::draw(){
	if(record){
		char fileName[1024];
		sprintf(fileName, "out/visible-%06d.bmp", ofGetFrameNum() - recordFrameOffset);
		visible.saveImage(ofToDataPath(fileName));
		sprintf(fileName, "out/depth-%06d.bmp", ofGetFrameNum() - recordFrameOffset);
		depth.saveImage(ofToDataPath(fileName));
	}

	int w = kinect.width / 2;
	int h = kinect.height / 2;
	visible.draw(0, 0, w, h);
	depth.draw(w + 1, 0, w, h);

	ofPushStyle();
		ofSetColor(255, 255, 255);
		char reportStr[1024];
		sprintf(reportStr, "fps: %f, rec: %s", ofGetFrameRate(), record ? "on" : "off");
		ofDrawBitmapString(reportStr, 10, height - 10);
	ofPopStyle();
}

void KinectCapture::exit(){
	kinect.setCameraTiltAngle(0);
	kinect.close();
}


//--------------------------------------------------------------
void KinectCapture::keyPressed(int key){
	if(key == 'q') {
		record = !record;
		recordFrameOffset = ofGetFrameNum();
	}
}

//--------------------------------------------------------------
void KinectCapture::keyReleased(int key){

}

//--------------------------------------------------------------
void KinectCapture::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void KinectCapture::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void KinectCapture::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void KinectCapture::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void KinectCapture::windowResized(int w, int h){

}

