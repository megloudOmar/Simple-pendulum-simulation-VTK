#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSmartPointer.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkCylinderSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkAssembly.h>
#include <vtkNamedColors.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkCubeSource.h>
#include <cmath>


#include "Timer.h"
#include "Observer.h"
#include "Manager.h"

const float g = 9.80665f;								// gravitational acceleration
const double PI = 3.14159265358979323846f;				// PI value
const float	theta_0_rad = PI / 4;						// initial angular displacement
float length = 15;										// length of pendulum
float T = (2 * PI) * sqrt(length / g);					// period
const float lambda = 0.09;

int main(int, char* [])
{
	
	Manager m = Manager();

	// Color
	vtkSmartPointer<vtkNamedColors> namedColors = vtkSmartPointer<vtkNamedColors>::New();
	
	// Create a cylinder (string)
	vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
	cylinderSource->SetHeight(length);
	cylinderSource->SetRadius(0.2);
	cylinderSource->SetResolution(15);

	// Create a sphere (bob)
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(0.0, -(cylinderSource->GetHeight() / 2), 0.0);
	sphereSource->SetRadius(1.0);
	// Make the surface smooth.
	sphereSource->SetPhiResolution(100);
	sphereSource->SetThetaResolution(100);

	// Create a cube (rigid support)
	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetXLength(4.0);

	// Sphere Mapper
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

	// Cylinder Mapper
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(cylinderSource->GetOutputPort());

	// Cube Mapper
	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

	// Sphere Actor
	vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetColor(namedColors->GetColor3d("Tomato").GetData());

	// Cylinder Actor
	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->GetProperty()->SetColor(namedColors->GetColor3d("Yellow").GetData());
	cylinderActor->SetOrigin(0.0, cylinderActor->GetBounds()[3], 0.0);

	// Cube Actor
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(namedColors->GetColor3d("Black").GetData());

	// Text 1 Display
	vtkSmartPointer<vtkTextActor> txt1Actor = vtkSmartPointer<vtkTextActor>::New();
	txt1Actor->SetInput("Simple Pendulum Simulation");
	vtkTextProperty* txt1prop = txt1Actor->GetTextProperty();
	txt1prop->SetFontFamilyToArial();
	txt1prop->BoldOn();
	txt1prop->SetFontSize(30);
	txt1prop->ShadowOn();
	txt1prop->SetShadowOffset(4, 4);
	txt1prop->SetColor(namedColors->GetColor3d("Cornsilk").GetData());
	txt1Actor->SetDisplayPosition(120, 400);

	// Text 2 Display
	vtkSmartPointer<vtkTextActor> txt2Actor = vtkSmartPointer<vtkTextActor>::New();
	txt2Actor->SetInput("Then press 's' to start simulation");
	vtkTextProperty* txt2prop = txt2Actor->GetTextProperty();
	txt2prop->SetFontFamilyToArial();
	txt2prop->BoldOn();
	txt2prop->SetFontSize(14);
	txt2prop->SetColor(namedColors->GetColor3d("Cornsilk").GetData());
	txt2Actor->SetDisplayPosition(20, 20);
	// Text 3 Display
	vtkSmartPointer<vtkTextActor> txt3Actor = vtkSmartPointer<vtkTextActor>::New();
	txt3Actor->SetInput("Press 'n' for oscillation without damping");
	vtkTextProperty* txt3prop = txt3Actor->GetTextProperty();
	txt3prop->SetFontFamilyToArial();
	txt3prop->BoldOn();
	txt3prop->SetFontSize(14);
	txt3prop->SetColor(namedColors->GetColor3d("Cornsilk").GetData());
	txt3Actor->SetDisplayPosition(20, 50);
	// Text 4 Display
	vtkSmartPointer<vtkTextActor> txt4Actor = vtkSmartPointer<vtkTextActor>::New();
	txt4Actor->SetInput("Press 'd' for damped oscillation");
	vtkTextProperty* txt4prop = txt4Actor->GetTextProperty();
	txt4prop->SetFontFamilyToArial();
	txt4prop->BoldOn();
	txt4prop->SetFontSize(14);
	txt4prop->SetColor(namedColors->GetColor3d("Cornsilk").GetData());
	txt4Actor->SetDisplayPosition(20, 35);


	
	cubeActor->SetPosition(0.0, cylinderActor->GetBounds()[3], 0.0);
	
	

	

	// Setup renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(sphereActor);
	renderer->AddActor(cylinderActor);
	renderer->AddActor(cubeActor);
	renderer->AddActor(txt1Actor);
	renderer->AddActor(txt2Actor);
	renderer->AddActor(txt3Actor);
	renderer->AddActor(txt4Actor);

	
	renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());
	renderer->ResetCamera(-10, 10, -10, 10, 0, 0);
	

	vtkSmartPointer<vtkRenderWindow> rendererWindow = vtkSmartPointer<vtkRenderWindow>::New();
	rendererWindow->SetSize(640, 480);
	rendererWindow->AddRenderer(renderer);
	rendererWindow->SetWindowName("Pendulum");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(rendererWindow);

	rendererWindow->Render();
	// Initialize must be called prior to creating timer events.
	interactor->Initialize();
	// Timer
	vtkSmartPointer<Timer> timer = vtkSmartPointer<Timer>::New();
	timer->sphere = sphereActor;
	timer->cylinder = cylinderActor;
	timer->SetManager(&m);
	interactor->AddObserver(vtkCommand::TimerEvent, timer);
	// Observer
	vtkSmartPointer<Observer> observer = vtkSmartPointer<Observer>::New();
	observer->SetManager(&m);
	
    interactor->AddObserver(vtkCommand::KeyPressEvent, observer);
	// un pas de 50 ms
	int timerId = interactor->CreateRepeatingTimer(50);
	std::cout << "timerId: " << timerId << std::endl;
	// Destroy the timer when maxCount is reached.
	
	timer->maxCount = 1000;
	timer->timerId = timerId;
	
	interactor->Start();
	

	return EXIT_SUCCESS;
}
