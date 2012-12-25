#include "model.h"
#include <math.h>

#include <iostream>

model::model(void)
{
	displayList = -1;
	dirty = true;
}


model::~model(void)
{
}

#pragma pack(1)
struct stlTriangle {
	f32 normal[3];
	f32 triangle[3][3];
	quint16 sh;
};
#pragma pack()

void model::loadSTL(QFile &f){
	uchar *stlFile;

	unsigned int numTris;

	int o = f.open(QIODevice::ReadOnly);
	std::cout << "Open sez " << o;
	stlFile = f.map(0, f.size());

	uchar *p = stlFile;
	p+=80;
	numTris = *((unsigned int *)p);
	p+=sizeof(unsigned int);

	std::cout << sizeof(struct stlTriangle) << std::endl;

	for(int i=0;i<numTris;i++){
		struct stlTriangle *cur = (struct stlTriangle *) p;

		triangle t;

		for(int j=0;j<3;j++){
			t.point[j].X = cur->triangle[j][0];
			t.point[j].Y = cur->triangle[j][1];
			t.point[j].Z = cur->triangle[j][2];
			//std::printf("%i : x:%f y:%f z:%f\n", j, t.point[j].X, t.point[j].Y, t.point[j].Z);
		}

		// Calculate surface normals
		vector3df U, V;
		U = t.point[1] - t.point[0];
		V = t.point[2] - t.point[0];
		t.normal = U.crossProduct(V);
		t.normal.normalize();

		triangles.push_back(t);
		
		p += sizeof(struct stlTriangle);
	}

	f.unmap(stlFile);
}

void model::paintModel(){
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);

	GLfloat white[] = {1.0f, 1.0f, 1.0f};

	GLfloat lightpos[] = {0.0f, 0.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

//glScalef(0.1, 0.1, 0.1);

	if(displayList == -1){
		displayList = glGenLists(1);
	}

	if(dirty == true){
		std::cout << displayList;
		compileObject();
	}

	glCallList(displayList);
}

void model::compileObject(){
	std::vector<triangle>::iterator triIter;

	vector3df origin(0,0,1);

	glNewList(displayList, GL_COMPILE);

	for(triIter = triangles.begin(); 
			triIter != triangles.end();
			triIter++)
	{

		  glEnable(GL_CULL_FACE);

		  f32 angle = acos(origin.dotProduct(triIter->normal));

		  if(angle < 0.349066)
			glColor4f(1.0f,0.0f,0.0f,0.2f);
		  else
			glColor3f(0.3f,1.0f,0.0f);
		  
		  glBegin(GL_TRIANGLES);
		  
		  glNormal3f(triIter->normal.X, triIter->normal.Y, triIter->normal.Z);

		  for(int i=0;i<3;i++){
			glVertex3f(triIter->point[i].X, triIter->point[i].Y, triIter->point[i].Z);
		  }
          
		  glEnd();
	}

	glEndList();

	dirty = false;
}