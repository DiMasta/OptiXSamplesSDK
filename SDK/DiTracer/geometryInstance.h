#ifndef __GEOMETRY_INSTANCE_H__
#define __GEOMETRY_INSTANCE_H__

#include <vector>

#include "geometry.h"
#include "material.h"

typedef std::vector<DiMaterial*> MaterialsList;

class DiGeometryInstnace {
public:
	DiGeometryInstnace();
	~DiGeometryInstnace();

	DiGeometry* getGeometry() const;
	MaterialsList getMaterials() const;
	RTgeometryinstance* getRTGeometryInstance() const;

	void setGeometry(DiGeometry* geometry);
	void setMaterials(MaterialsList materials);
	void setRTGeoemetryInstance(RTgeometryinstance* rtGeometryInstance);

	void create(RTcontext* context);
	void addMaterial(DiMaterial* material);

private:
	DiGeometry* geometry;
	MaterialsList materials;

	RTgeometryinstance* rtGeometryInstance;
};

#endif // __GEOMETRY_INSTANCE_H__

