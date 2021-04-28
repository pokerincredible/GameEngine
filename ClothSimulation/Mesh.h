#pragma once
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <vector>

// Mesh type
typedef OpenMesh::TriMesh_ArrayKernelT<> _Mesh;

#define VERTEX_DATA(mesh) (float*) &(mesh->point(*mesh->vertices_begin()))
#define NORMAL_DATA(mesh) (float*) &(mesh->normal(*mesh->vertices_begin()))
#define TEXTURE_DATA(mesh) (float*) &(mesh->texcoord2D(*mesh->vertices_begin()))

class Mesh : public _Mesh
{
private:
	std::vector<unsigned int> _ibuff;
public:
	// pointers to buffers
	float* vbuffer();
	float* nbuffer();
	float* tbuffer();
	unsigned int* ibuffer();

	// buffer sizes
	unsigned int vbufferLen();
	unsigned int nbufferLen();
	unsigned int tbufferLen();
	unsigned int ibufferLen();

	// set index buffer
	void useIBuff(std::vector<unsigned int>& _ibuffer);
};

class MeshBuilder {
private:
	Mesh* result;
public:
	void uniformGrid(float w, int n);
	Mesh* getResult();
};