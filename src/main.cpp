#include "ofMain.h"
#include "ofApp.h"


class ofRedirect {
public:
    ofRedirect(const std::string &filename) {
        backup = std::cout.rdbuf();
        file.open(filename.c_str(), std::ios::out);
        std::cout.rdbuf(file.rdbuf());
    }

    ~ofRedirect() {
        file.close();
        std::cout.rdbuf(backup);
    }

private:
    std::ofstream file;
    std::streambuf *backup;
};
//========================================================================
int main( ){
		ofRedirect redirect("output.txt");
	ofSetupOpenGL(1920, 1440, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
