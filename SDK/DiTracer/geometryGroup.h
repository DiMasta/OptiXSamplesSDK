#ifndef __GEOMETRY_GROUP_H__
#define __GEOMETRY_GROUP_H__

#include <vector>

#include "geometryInstance.h"

typedef std::vector<DiGeometryInstnace*> GeometryInstancesList;

class DiGeometryGroup {
public:
	DiGeometryGroup();
	~DiGeometryGroup();

	GeometryInstancesList getGeometryInstancesList() const;
	RTgeometrygroup* getGeometryGroup() const;

	void setGeometryInstancesList(GeometryInstancesList geometryInstancesList);
	void setGeometryGroup(RTgeometrygroup* geometryGroup);

	void addGeometryInstance(DiGeometry* geometry, DiMaterial* material);
	int getGeometryInstancesCount() const;
	DiGeometryInstnace* getGeometryInstanceByIdx(int idx) const;

private:
	GeometryInstancesList geometryInstancesList;

	RTgeometrygroup* geometryGroup;
};

#endif // __GEOMETRY_GROUP_H__
