//
//  ofxLaserManager.hpp
//  ofxLaserRewrite
//
//  Created by Seb Lee-Delisle on 06/11/2017.
//
//

#pragma once

#ifndef OFXLASERMANAGER_H
#define OFXLASERMANAGER_H

#include "ofMain.h"
#include "ofxLaserZone.h"
#include "ofxLaserShape.h"
#include "ofxLaserLine.h"
#include "ofxLaserPolyline.h"
#include "ofxLaserCircle.h"
#include "ofxLaserProjector.h"
#include "ofxLaserDacBase.h"
#include "ofxLaserMaskManager.h"
#include "ofxGui.h"

#define OFXLASER_PROFILE_FAST "FAST"
#define OFXLASER_PROFILE_DEFAULT "DEFAULT"
#define OFXLASER_PROFILE_DETAIL "DETAIL"

enum ofxLaserZoneMode {
	OFXLASER_ZONE_MANUAL, // all zones are separate, you manually specify which zone you want
	OFXLASER_ZONE_AUTOMATIC, // non-overlapping zones assumed - shapes go in all zones that
							// contain it
	OFXLASER_ZONE_OPTIMISE // automatically puts it in the best zone
};

namespace ofxLaser {
    
	class Manager {
        
		public:
        
		// it's a Singleton so shouldn't ever have more than one.
		static Manager * instance();
		static Manager * laserManager;
        
		Manager();
		~Manager();
        
		void addProjector(DacBase& dac);
		
		void addZone(float x = 0 , float y = 0, float w = -1, float h= -1);
		void addZone(const ofRectangle& zoneRect);
		
		void addZoneToProjector(int zonenum, int projnum);
		
		void nextProjector();
		void previousProjector();
        
		void setup(int width, int height);
		void update();
		void drawUI(bool fullscreen = false);
        void renderPreview();
        
        void updateScreenSize(ofResizeEventArgs &e);
		void updateScreenSize();
		void updateGuiPositions();
		void showAdvancedPressed(bool& state);
        
        void send();
        void sendRawPoints(const std::vector<ofxLaser::Point>& points, int projectornum = 0, int zonenum = 0);
        
        int getProjectorPointRate(int projectornum = 0);
        float getProjectorFrameRate(int projectornum);
        
		void armAllProjectorsListener();
		void disarmAllProjectorsListener();
		void armAllProjectors();
		void disarmAllProjectors();
		void testPatternAllProjectors(int& pattern);
		
		void drawPoly(const ofPolyline &poly, const ofColor& col,  string profileName = OFXLASER_PROFILE_DEFAULT);
		void drawPoly(const ofPolyline & poly, vector<ofColor>& colours, string profileName = OFXLASER_PROFILE_DEFAULT);
		void drawLine(const ofPoint& start, const ofPoint& end, const ofColor& col, string profileName = OFXLASER_PROFILE_DEFAULT);
		void drawDot(const ofPoint& p, const ofColor& col, float intensity =1, string profileName = OFXLASER_PROFILE_DEFAULT);
		void drawCircle(const ofPoint & centre, const float& radius,const ofColor& col, string profileName= OFXLASER_PROFILE_DEFAULT);
		
		Projector& getProjector(int index = 0);
		void initGui(bool showAdvanced = false);
		void addCustomParameter(ofAbstractParameter& param);
		ofxPanel& getGui();
		bool togglePreview();
		bool toggleGui();
		void setGuiVisible(bool visible);
		bool isGuiVisible();
        
		void saveSettings();
		
		Zone& getZone(int zonenum);
		int getNumZones(); 
		bool setTargetZone(int zone);
		bool setZoneMode(ofxLaserZoneMode newmode);
		
		// should be called before initGui
		bool setGuideImage(string filename);
		bool isProjectorArmed(int i);
        
		int width, height;
		ofParameter<int> guiProjectorPanelWidth;
		ofParameter<int> dacStatusBoxSmallWidth;
		int dacStatusBoxHeight; 
		ofParameter<int> guiSpacing;
        ofParameter<int> smallPreviewHeight;
        
		// converts openGL coords to screen coords
		ofPoint gLProject(ofPoint p);
		ofPoint gLProject( float ax, float ay, float az ) ;
		
		int currentProjector;
		
		ofParameter<int> testPattern;
		
		ofParameter<bool> showProjectorSettings;
		
        ofParameter<bool> showZones;
        ofParameter<bool> showPreview;
		ofParameter<bool> showPathPreviews;
        ofParameter<bool> useBitmapMask;
        ofParameter<bool> showBitmapMask;
		ofParameter<bool> laserMasks; 
		
		ofParameter<float>masterIntensity;
        
		ofImage guideImage;
		
        MaskManager laserMask;
		
		ofPoint previewOffset;
		float previewScale;
		
		bool zonesChanged; 
		std::vector<Zone*> zones;
		
        ofxPanel gui;
        ofParameterGroup params;
        ofParameterGroup customParams;
        
        ofParameterGroup paramsLaser;
        
        ofParameter<bool> armAll;
        ofParameter<bool> disarmAll;
        void armAllChanged(bool & armAll);
        void disarmAllChanged(bool & disarmAll);
        
        
		protected:
        
		bool guiIsVisible;
		ofxButton armAllButton;
		ofxButton disarmAllButton;
		bool doArmAll = false;
		bool doDisarmAll = false;
		
        
		private:
        
		int createDefaultZone();
		
		ofxLaserZoneMode zoneMode = OFXLASER_ZONE_AUTOMATIC;
		int targetZone = 0; // for OFXLASER_ZONE_MANUAL mode
		
		std::vector<Projector*> projectors;
		
		std::deque <ofxLaser::Shape*> shapes;
        
		ofPolyline tmpPoly; // to avoid generating polyline objects
		int screenHeight;
	};
}

#endif
