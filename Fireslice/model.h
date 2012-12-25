#ifndef MODEL_H
#define MODEL_H

#include <QGLWidget>
#include <QFile>
#include <vector>
#include "ezVector3d.h"

typedef struct {
	vector3df normal;
	vector3df point[3];
} triangle;

class model
{
public:
	model(void);
	~model(void);

	bool dirty;
	GLuint displayList;

	std::vector<triangle> triangles;
	void loadSTL(QFile &f);
	void paintModel();
	void compileObject();
};

#endif MODEL_H