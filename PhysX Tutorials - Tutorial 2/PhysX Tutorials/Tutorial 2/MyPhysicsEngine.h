#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	//Spawn Shit here
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box;
		Box* boxtwo;
		Sphere* sphere;
		CompoundObject* obj;

	public:
		///A custom scene class
		void SetVisualisation()
		{

			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			Add(plane);

			box = new Box(PxTransform(PxVec3(0.0f, 0.5f, 0.0f), PxQuat(0.0f, PxVec3(0.0f, 0.0f, 0.0f))));
			boxtwo = new Box(PxTransform(PxVec3(0.0f, 0.0f, 10.0f)));
			sphere = new Sphere(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
			obj = new CompoundObject(PxTransform(PxVec3(10.0f, 0.0f, 0.0f)));
			box->Color(color_palette[0]);
			boxtwo->Color(color_palette[1]);
			obj->Color(color_palette[2], 0);
			obj->Color(color_palette[3], 1);
			sphere->Color(color_palette[4]);
			Add(box);
			//Add(boxtwo);
			//Add(obj);
			//Add(sphere);
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			PxTransform boxPose = ((PxRigidBody*)box->Get())->getGlobalPose();
			boxPose.q = boxPose.q * PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f)); //Smaller the angle, slower the rotation
			((PxRigidBody*)box->Get())->setGlobalPose(boxPose);
			//((PxRigidBody*)box->Get())->addForce(PxVec3(0.0f, 0.0f, -10.0f));
		}
	};
}
