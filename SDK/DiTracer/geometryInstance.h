#ifndef __GEOMETRY_INSTANCE_H__
#define __GEOMETRY_INSTANCE_H__

#include <vector>

#include "geometry.h"
#include "material.h"

typedef std::vector<Material*> MaterialsList;

class GeoemetryInstnace {
public:
	GeoemetryInstnace();
	~GeoemetryInstnace();

	Geometry* getGeoemetry() const;
	MaterialsList getMaterials() const;
	RTgeometryinstance* getRTGeometryInstance() const;

	void setGeometry(Geometry* geometry);
	void setMaterials(MaterialsList materials);
	void setRTGeoemetryInstance(RTgeometryinstance* rtGeometryInstance);

	void create(RTcontext* context);

private:
	Geometry* geometry;
	MaterialsList materials;

	RTgeometryinstance* rtGeometryInstance;
};

#endif // __GEOMETRY_INSTANCE_H__

