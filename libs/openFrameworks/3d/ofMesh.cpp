#include "ofMesh.h"
#include "ofGraphics.h"

//--------------------------------------------------------------
ofMesh::ofMesh(){
	vbo = ofVbo();
	vertexData = NULL;
	renderMethod = OF_MESH_USING_DEFAULT_RENDERER;
	drawType = GL_STATIC_DRAW;
	bEnableIndices = false;
	bEnableColors = false;
	bEnableTexCoords = false;
	bEnableNormals = false;
}

//--------------------------------------------------------------
ofMesh::~ofMesh(){
}

//--------------------------------------------------------------
void ofMesh::setDrawType(int drawType_){
	drawType = drawType_;
}

//--------------------------------------------------------------
void ofMesh::setRenderMethod(meshRenderMethod m){
	renderMethod = m;
}

/*
//--------------------------------------------------------------
ofMesh::ofMesh(const ofMesh& v){
	clone(v);
}

//--------------------------------------------------------------
ofMesh& ofMesh::operator=(const ofMesh& v){
	clone(v);
	return *this;
}

//--------------------------------------------------------------
void ofMesh::clone(const ofMesh& v){
	vertexData = v.getvertexData();
	vbo = v.vbo;
}
 */

//--------------------------------------------------------------
void ofMesh::setVertexData(ofVertexData* m){
	vertexData = m;
}

//--------------------------------------------------------------
ofVertexData* ofMesh::getVertexData(){
	return vertexData;
}

//--------------------------------------------------------------
const ofVertexData* ofMesh::getVertexData() const{
	return vertexData;
}

//--------------------------------------------------------------
bool ofMesh::setupVerticesForVbo(int usage){
	int size = vertexData->getNumVertices();
	if(size){
		vbo.setVertexData(vertexData->getVerticesPointer(),3,size, usage);
		return true;
	}else{
		ofLog(OF_LOG_WARNING,"ofMesh:setupVertices - no vertices in vertexData.");
		return false;
	}
}

//--------------------------------------------------------------
bool ofMesh::setupColorsForVbo(int usage){
	int size = vertexData->getNumColors();
	if(size){
		vbo.setColorData(vertexData->getColorsPointer(), size, usage);
		return true;
	}else{
		ofLog(OF_LOG_WARNING,"ofMesh:setupColors - no colors in vertexData.");
		return false;
	}
}

//--------------------------------------------------------------
bool ofMesh::setupNormalsForVbo(int usage){
	int size = vertexData->getNumNormals();
	if(size){
		vbo.setNormalData(vertexData->getNormalsPointer(), size, usage);
		return true;
	}else{
		ofLog(OF_LOG_WARNING,"ofMesh:setupNormals - no normals in vertexData.");
		return false;
	}
}

//--------------------------------------------------------------
bool ofMesh::setupTexCoordsForVbo(int usage){
	int size = vertexData->getNumTexCoords();
	if(size){
		vbo.setTexCoordData(vertexData->getTexCoordsPointer(), size, usage);
		return true;
	}else{
		ofLog(OF_LOG_WARNING,"ofMesh:setupTexCoords - no texCoords in vertexData.");
		return false;
	}
}

//--------------------------------------------------------------
bool ofMesh::setupIndicesForVbo(int usage){
	int size = vertexData->getNumIndices();
	if(size){
		vbo.setIndexData(vertexData->getIndexPointer(), size, usage);
		return true;
	}else{
		ofLog(OF_LOG_WARNING,"ofMesh:setupIndices - no indices in vertexData.");
		return false;
	}
}

//--------------------------------------------------------------
bool ofMesh::enableColors(){
	if(vertexData->getNumColors()){
		bEnableColors = true;
		return true;
	}else{
		bEnableColors = false;
		return false;
	}
}

//--------------------------------------------------------------
void ofMesh::disableColors(){
	bEnableColors = false;
}

//--------------------------------------------------------------
bool ofMesh::enableNormals(){
	if(vertexData->getNumNormals()){
		bEnableNormals = true;
		return true;
	}else{
		bEnableNormals = false;
		return false;
	}
}

//--------------------------------------------------------------
void ofMesh::disableNormals(){
	bEnableNormals = false;
}

//--------------------------------------------------------------
bool ofMesh::enableTexCoords(){
	if(vertexData->getNumTexCoords()){
		bEnableTexCoords = true;
		return true;
	}else{
		bEnableTexCoords = false;
		return false;
	}
}

//--------------------------------------------------------------
void ofMesh::disableTexCoords(){
	bEnableTexCoords = false;
}

//--------------------------------------------------------------
bool ofMesh::enableIndices(){
	if(vertexData->getNumIndices()){
		bEnableIndices = true;
		return true;
	}else{
		bEnableIndices = false;
		return false;
	}
}

//--------------------------------------------------------------
void ofMesh::disableIndices(){
	bEnableIndices = false;
}

//--------------------------------------------------------------
bool ofMesh::getTexCoordsEnabled(){
	if(!vertexData->getNumTexCoords()){
		bEnableTexCoords = false;
	}
	return bEnableTexCoords;
}

//--------------------------------------------------------------
bool ofMesh::getNormalsEnabled(){
	if(!vertexData->getNumNormals()){
		bEnableNormals = false;
	}
	return bEnableNormals;
}

//--------------------------------------------------------------
bool ofMesh::getColorsEnabled(){
	if(!vertexData->getNumColors()){
		bEnableColors = false;
	}
	return bEnableColors;
}
	
//--------------------------------------------------------------
bool ofMesh::getIndicesEnabled(){
	if(!vertexData->getNumIndices()){
		bEnableIndices = false;
	}
	return bEnableIndices;
}

//--------------------------------------------------------------
void ofMesh::setupVbo(){
	if(vertexData->getNumVertices()){
		if(!vbo.getIsAllocated()){
			setupVerticesForVbo(drawType);
		}
		
		if (vertexData->haveVertsChanged()){
			vbo.updateVertexData(vertexData->getVerticesPointer(), 3, vertexData->getNumVertices());
		}
	}
	
	if(getColorsEnabled()){
		if(!vbo.getUsingColors()){
			setupColorsForVbo(drawType);
		}
	
		if(vertexData->haveColorsChanged()){
			vbo.updateColorData(vertexData->getColorsPointer(), vertexData->getNumColors());
		}
	}
	
	if(getNormalsEnabled()){
		if(!vbo.getUsingNormals()){
			setupNormalsForVbo(drawType);
		}
	
		if(vertexData->haveNormalsChanged()){
			vbo.updateNormalData(vertexData->getNormalsPointer(), vertexData->getNumNormals());
		}
	}
	
	if(getTexCoordsEnabled()){
		if(!vbo.getUsingTexCoords()){
			setupTexCoordsForVbo(drawType);
		}
	
		if(vertexData->haveTexCoordsChanged()){
			vbo.updateTexCoordData(vertexData->getTexCoordsPointer(), vertexData->getNumTexCoords());
		}
	}
	
	if(getIndicesEnabled()){
		if(!vbo.getUsingIndices()){
			setupIndicesForVbo(drawType);
		}
	
		if(vertexData->haveIndicesChanged()){
			vbo.updateIndexData(vertexData->getIndexPointer(), vertexData->getNumIndices());
		}
	}	
}

//--------------------------------------------------------------
void ofMesh::draw(polyMode renderType){
	if(renderMethod == OF_MESH_USING_VBO){
		setupVbo();
	}
	
#ifndef TARGET_OPENGLES 
	glPushAttrib(GL_POLYGON_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, ofGetGLPolyMode(renderType));
#endif
	GLuint mode = ofGetGLPrimitiveMode(vertexData->getMode());
	
if(renderMethod == OF_MESH_USING_VBO){
		GLuint mode = ofGetGLPrimitiveMode(vertexData->getMode());
		if(getIndicesEnabled()){
			vbo.drawElements(mode,vertexData->getNumIndices());
		}else{
			vbo.draw(mode,0,vertexData->getNumVertices());
		}
	}else{
		ofGetDefaultRenderer()->draw(*vertexData);
	}
		
#ifndef TARGET_OPENGLES
	glPopAttrib();
#endif
}

//--------------------------------------------------------------
void ofMesh::drawVertices(){
	draw(OF_MESH_POINTS);
}

//--------------------------------------------------------------
void ofMesh::drawWireframe(){
	draw(OF_MESH_WIREFRAME);
}

//--------------------------------------------------------------
void ofMesh::drawFaces(){
	draw(OF_MESH_FILL);
}