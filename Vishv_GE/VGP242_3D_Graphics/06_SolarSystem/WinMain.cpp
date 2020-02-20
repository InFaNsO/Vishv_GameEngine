#include "Object.h"

void CameraUpdate(Vishv::Graphics::Camera &cam)
{
	const float move = 0.25f;
	const float rotate = 1.0f * Constans::DegToRad;
	if (GetAsyncKeyState(0x57))//w
	{
		cam.Walk(move * 20.0f);
	}
	else if (GetAsyncKeyState(0x53))//s
	{
		cam.Walk(-move * 20.0f);
	}
	else if (GetAsyncKeyState(0x41)) //a
	{
		cam.Strafe(-move * 20.0f);
	}
	else if (GetAsyncKeyState(0x44)) //d
	{
		cam.Strafe(move * 20.0f);
	}
	else if (GetAsyncKeyState(0x51)) //q
	{
		cam.Rise(move* 20.0f);
	}
	else if (GetAsyncKeyState(0x45)) //e
	{
		cam.Rise(-move * 20.0f);
	}
	else if (GetAsyncKeyState(0x5A)) //z
	{
		cam.Yaw(rotate);
	}
	else if (GetAsyncKeyState(0x58)) //x
	{
		cam.Yaw(-rotate);
	}
	else if (GetAsyncKeyState(0x31)) //1
	{
		cam.Pitch(-rotate);
	}
	else if (GetAsyncKeyState(0x32)) //2
	{
		cam.Pitch(rotate);
	}
}

void MeshUpdate(Vishv::Graphics::MeshBuffer &mb)
{
	if (GetAsyncKeyState(0x33)) //3
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateCubePC(5.0f, 3.0f, 8.0f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x34)) //4
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreatePlanePC(6, 10, 1.0f, 1.5f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x35)) //5
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateCylinderPC(6, 14, 2.0f, 1.0f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x36)) //6
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateConePC(6, 14, 2.0f, 1.0f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x37)) //7
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateSpherePC(14, 14, 10.0f);
		mb.Initialize(mesh);
	}
}

void MovePlanet(Matrix4 &planet, float &prevAngle, float degIncrement, float orbitRadius)
{
	prevAngle += degIncrement * Constans::DegToRad;

	planet.TranslateX(cosf(prevAngle) * orbitRadius);
	planet.TranslateZ(sinf(prevAngle) * orbitRadius);
}

void MoveMoon(const Matrix4& planet, Matrix4 &moon, float &prvAngle)
{
	const float orbitRadius = 80.0f;
	prvAngle += 0.9f * Constans::DegToRad;

	moon.TranslateX((cosf(prvAngle) * orbitRadius) + planet._41);
	moon.TranslateZ((sinf(prvAngle) * orbitRadius) + planet._43);
}

void MoveRing(const Matrix4& planet, Matrix4 &moon)
{
	moon.TranslateX(planet._41);
	moon.TranslateZ(planet._43);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello Solar System", 1280, 720);

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);

	const float radiusSpace = 1500.0f;
	ObjectTexture space;
	space.meshTexture = Meshbuilder::CreateSkyDomeUV(14, 14, radiusSpace);
	space.Initialize(L"../../Assets/Images/HDRI/CrabNebula/hdr.png");

	const float radiusSun = 150.0f;
	ObjectTexture sun;
	sun.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusSun);
	sun.Initialize(L"../../Assets/Images/sun.jpg");

	const float radiusMerc = 12.0f;
	ObjectTexture mercury;
	mercury.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusMerc);
	mercury.Initialize(L"../../Assets/Images/mercury.jpg");

	const float radiusVenus = 19.0f;
	ObjectTexture venus;
	venus.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusMerc);
	venus.Initialize(L"../../Assets/Images/venus.jpg");

	const float radiusEarth = 20.0f;
	ObjectTexture earth;
	earth.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusEarth);
	earth.Initialize(L"../../Assets/Images/earth.jpg");

	const float radiusMoon = radiusEarth / 3.0f;
	ObjectTexture moon;
	moon.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusMoon);
	moon.Initialize(L"../../Assets/Images/moon.png");

	const float radiusMars = 20.0f;
	ObjectTexture mars;
	mars.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusMars);
	mars.Initialize(L"../../Assets/Images/mars.jpg");

	const float radiusBelt = 450.0f;	//calc
	ObjectTexture belt;
	belt.meshTexture = Meshbuilder::CreateTorusUV(14, 14, radiusBelt, radiusBelt + 50.0f);
	belt.Initialize(L"../../Assets/Images/belt.png");

	const float radiusJupiter = 80.0f;
	ObjectTexture jupiter;
	jupiter.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusJupiter);
	jupiter.Initialize(L"../../Assets/Images/jupiter.jpg");

	const float radiusSaturn = 65.0f;
	ObjectTexture saturn;
	saturn.meshTexture = Meshbuilder::CreateSphereUV(14, 14, radiusSaturn);
	saturn.Initialize(L"../../Assets/Images/saturn.jpg");

	const float satRingRadius = 75.0f;
	ObjectTexture satRing;
	satRing.meshTexture = Meshbuilder::CreateTorusUV(14, 14, satRingRadius, satRingRadius + 10.0f);
	satRing.Initialize(L"../../Assets/Images/satRing.png");


	/////////////////////////////////////////////////////////////////////////////////////

	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 5.0f, -40.0f });
	cam.SetDirection({ 0.0f, 0.0f, 1.0f });
	cam.SetFarPlane(4000.0f);

	float theta = 0.0f;

	space.tranformation.Translate({ 0.0f, -radiusSpace, 0.0f });
	space.tranformation.RotateY(90.0f * Vishv::Math::Constans::DegToRad);
	sun.tranformation.TranslateY(radiusSun);
	mercury.tranformation.TranslateY(radiusMerc);
	venus.tranformation.TranslateY(radiusVenus);
	earth.tranformation.TranslateY(radiusEarth);
	moon.tranformation.TranslateY(radiusMoon);
	mars.tranformation.TranslateY(radiusMars);
	jupiter.tranformation.TranslateY(radiusJupiter);
	saturn.tranformation.TranslateY(radiusSaturn);

	float mercuryAngle = 0.0f;
	float venusAngle = 0.0f;
	float earthAngle = 0.0f;
	float moonAngle = 0.0f;
	float marsAngle = 0.0f;
	float jupiterAngle = 0.0f;
	float saturnAngle = 0.0f;

	bool done = false;
	while (!done)	
	{
		done = myWindow.ProcessMessage();

		CameraUpdate(cam);
		//MeshUpdate(mb);

		MovePlanet(mercury.tranformation, mercuryAngle, 0.3f, 200.0f);
		MovePlanet(venus.tranformation, venusAngle, 0.2f, 280.0f);

		MovePlanet(earth.tranformation, earthAngle, 0.18f, 350.0f);
		MoveMoon(earth.tranformation, moon.tranformation, moonAngle);

		MovePlanet(mars.tranformation, marsAngle, 0.15f, 400.0f);
		MovePlanet(jupiter.tranformation, jupiterAngle, 0.099f, 550.0f);
		MovePlanet(saturn.tranformation, saturnAngle, 0.06f, 680.0f);

		MoveRing(saturn.tranformation, satRing.tranformation);

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			done = true;
		}

		theta += 0.025f;

		GraphicsSystem::Get()->BeginRender();
		Matrix4 rotX = Matrix4::RotateMatrixX(180 * Constans::DegToRad);
		Matrix4 rotY = Matrix4::RotateMatrixY(theta);
		Matrix4 rotZ = Matrix4::RotateMatrixZ(0);

		cam.ComputeMatricies(1280.f / 720.0f);

		Matrix4 matSpace[3];
		matSpace[0] = space.tranformation.Transpose();
		matSpace[1] = cam.GetViewMatrix().Transpose();
		matSpace[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matSun[3];
		matSun[0] = ((rotX * rotY * rotZ) * sun.tranformation).Transpose();
		matSun[1] = cam.GetViewMatrix().Transpose();
		matSun[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matMercury[3];
		matMercury[0] = ((rotX*rotY*rotZ) * mercury.tranformation).Transpose();
		matMercury[1] = cam.GetViewMatrix().Transpose();
		matMercury[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matVenus[3];
		matVenus[0] = ((rotX*rotY*rotZ) * venus.tranformation).Transpose();
		matVenus[1] = cam.GetViewMatrix().Transpose();
		matVenus[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matEarth[3];
		matEarth[0] = ((rotX*rotY*rotZ) * earth.tranformation).Transpose();
		matEarth[1] = cam.GetViewMatrix().Transpose();
		matEarth[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matMoon[3];
		matMoon[0] = ((rotX*rotY*rotZ) * moon.tranformation).Transpose();
		matMoon[1] = cam.GetViewMatrix().Transpose();
		matMoon[2] = cam.GetPerspectiveMatrix().Transpose();
		
		Matrix4 matMars[3];
		matMars[0] = ((rotX*rotY*rotZ) * mars.tranformation).Transpose();
		matMars[1] = cam.GetViewMatrix().Transpose();
		matMars[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matBelt[3];
		matBelt[0] = ((rotX*rotY*Matrix4::RotateMatrixZ(Constans::Pi)) * belt.tranformation).Transpose();
		matBelt[1] = cam.GetViewMatrix().Transpose();
		matBelt[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matJupiter[3];
		matJupiter[0] = ((rotX*rotY*rotZ) * jupiter.tranformation).Transpose();
		matJupiter[1] = cam.GetViewMatrix().Transpose();
		matJupiter[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matSaturn[3];
		matSaturn[0] = ((rotX*rotY*rotZ) * saturn.tranformation).Transpose();
		matSaturn[1] = cam.GetViewMatrix().Transpose();
		matSaturn[2] = cam.GetPerspectiveMatrix().Transpose();

		Matrix4 matSaturnRing[3];
		matSaturnRing[0] = ((Matrix4::RotateMatrixX(90.0f * Constans::DegToRad)*rotY*Matrix4::RotateMatrixZ(35.0f * Constans::DegToRad)) * satRing.tranformation).Transpose();
		matSaturnRing[1] = cam.GetViewMatrix().Transpose();
		matSaturnRing[2] = cam.GetPerspectiveMatrix().Transpose();


		space.Update(matSpace);
		sun.Update(matSun);

		mercury.Update(matMercury);
		venus.Update(matVenus);
		earth.Update(matEarth);
		moon.Update(matMoon);
		mars.Update(matMars);
		//belt.Update(matBelt);
		jupiter.Update(matJupiter);
		saturn.Update(matSaturn);
		satRing.Update(matSaturnRing);


		GraphicsSystem::Get()->EndRender();
	}

	GraphicsSystem::StaticTerminate();
	
	space.Terminate();
	sun.Terminate();
	mercury.Terminate();
	venus.Terminate();
	earth.Terminate();
	moon.Terminate();
	mars.Terminate();
	belt.Terminate();
	mars.Terminate();
	jupiter.Terminate();
	saturn.Terminate();
	satRing.Terminate();

	myWindow.Terminate();
	return 0;
}


