#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "sceneElment.h"

class DiMaterial : public SceneElement {
public:
	DiMaterial();
	~DiMaterial();

	RTmaterial* getRTMaterial() const;

	void setRTMaterial(RTmaterial* material);

	virtual void createMaterial(RTcontext* context) = 0;
	virtual void prepareClosestHitProgram(RTcontext* context) = 0;

private:
	RTmaterial* material;
};

#endif // __MATERIAL_H__

