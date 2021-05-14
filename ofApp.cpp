#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int span = 22;
	vector<glm::vec2> location_list = { glm::vec2(-170, -170), glm::vec2(170, -170), glm::vec2(-170, 170), glm::vec2(170, 170) };
	vector<float> rotate_list = { 180, 270, 90, 0 };
	
	for (int i = 0; i < location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(location_list[i]);
		ofRotateZ(rotate_list[i]);

		for (auto x = -132; x <= 132; x += span) {

			for (int y = -132; y <= 132; y += span) {

				ofPushMatrix();
				ofTranslate(x, y, 0);

				auto noise_value = ofNoise(location_list[i].x + x * 0.005 + ofGetFrameNum() * 0.02, location_list[i].y + y * 0.005);
				auto start_param = noise_value < 0.5 ?  0 : 25;

				auto start = this->make_point(span, start_param);
				auto end = this->make_point(span, start_param + 50);

				ofDrawLine(start, end);

				ofPopMatrix();
			}
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}